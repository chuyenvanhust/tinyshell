#include <windows.h>
#include <stdio.h>
#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <random>
#include <chrono>
#include <cstdlib>

// --- Configuration defaults ---
const int DEFAULT_BUFFER_SIZE = 10;
const int DEFAULT_NUM_PRODUCERS = 2;
const int DEFAULT_NUM_CONSUMERS = 2;
const int DEFAULT_ITEMS_PER_PRODUCER = 5;

// --- Configuration variables ---
int MAX_BUFFER_SIZE_VAR = DEFAULT_BUFFER_SIZE;
int NUM_PRODUCERS_VAR = DEFAULT_NUM_PRODUCERS;
int NUM_CONSUMERS_VAR = DEFAULT_NUM_CONSUMERS;
int ITEMS_PER_PRODUCER_VAR = DEFAULT_ITEMS_PER_PRODUCER;

// --- Shared data ---
std::deque<int> g_buffer;
CRITICAL_SECTION g_buffer_cs;
CRITICAL_SECTION g_output_cs;
HANDLE g_empty_slots_semaphore = NULL;
HANDLE g_filled_slots_semaphore = NULL;
int g_item_id_counter = 0;
volatile bool g_all_producers_done = false;

// --- Utility functions ---
void SafePrintf(const char* format, ...) {
    EnterCriticalSection(&g_output_cs);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    fflush(stdout);
    LeaveCriticalSection(&g_output_cs);
}

void ShowUsage(const char* program_name) {
    printf("Usage: %s [num_producers] [num_consumers] [items_per_producer] [buffer_size]\n", program_name);
    printf("Parameters:\n");
    printf("  num_producers     : Number of producer threads (default: %d)\n", DEFAULT_NUM_PRODUCERS);
    printf("  num_consumers     : Number of consumer threads (default: %d)\n", DEFAULT_NUM_CONSUMERS);
    printf("  items_per_producer: Items each producer will create (default: %d)\n", DEFAULT_ITEMS_PER_PRODUCER);
    printf("  buffer_size       : Maximum buffer size (default: %d)\n", DEFAULT_BUFFER_SIZE);
    printf("\nExamples:\n");
    printf("  %s 3 4 10 15          # 3 producers, 4 consumers, 10 items each, buffer size 15\n", program_name);
}

bool ParseArguments(int argc, char* argv[]) {
    if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        ShowUsage(argv[0]);
        return false;
    }

    auto parse_arg_to_int = [&](const char* arg_str, const char* arg_name, int& target_var, int default_val) {
        if (arg_str) {
            char* endptr;
            long val = strtol(arg_str, &endptr, 10);
            if (*endptr == '\0' && val > 0) {
                target_var = static_cast<int>(val);
            } else {
                SafePrintf("Warning: Invalid value for %s: '%s'. Using default %d.\n", 
                          arg_name, arg_str, default_val);
                target_var = default_val;
            }
        } else {
            target_var = default_val;
        }
    };

    parse_arg_to_int((argc > 1) ? argv[1] : nullptr, "num_producers", NUM_PRODUCERS_VAR, DEFAULT_NUM_PRODUCERS);
    parse_arg_to_int((argc > 2) ? argv[2] : nullptr, "num_consumers", NUM_CONSUMERS_VAR, DEFAULT_NUM_CONSUMERS);
    parse_arg_to_int((argc > 3) ? argv[3] : nullptr, "items_per_producer", ITEMS_PER_PRODUCER_VAR, DEFAULT_ITEMS_PER_PRODUCER);
    parse_arg_to_int((argc > 4) ? argv[4] : nullptr, "buffer_size", MAX_BUFFER_SIZE_VAR, DEFAULT_BUFFER_SIZE);

    return true;
}

// --- Producer thread function ---
DWORD WINAPI ProducerThreadFunc(LPVOID lpParam) {
    int producer_id = static_cast<int>(reinterpret_cast<intptr_t>(lpParam));

    std::random_device rd;
    std::mt19937 gen(rd() + producer_id + GetCurrentThreadId());
    std::uniform_int_distribution<> produce_interval_dist(30, 150);
    std::uniform_int_distribution<> item_creation_time_dist(80, 250);

    for (int i = 0; i < ITEMS_PER_PRODUCER_VAR; ++i) {
        Sleep(item_creation_time_dist(gen));

        // Wait for empty slot in buffer
        DWORD wait_result = WaitForSingleObject(g_empty_slots_semaphore, INFINITE);
        if (wait_result != WAIT_OBJECT_0) {
            SafePrintf("[P%d] Error waiting for empty slot: %lu\n", producer_id, GetLastError());
            return 1;
        }

        EnterCriticalSection(&g_buffer_cs);
        int item = ++g_item_id_counter;
        g_buffer.push_back(item);
        SafePrintf("[P%d] Produced: %2d (Buffer: %2zu/%2d)\n",
                   producer_id, item, g_buffer.size(), MAX_BUFFER_SIZE_VAR);
        LeaveCriticalSection(&g_buffer_cs);

        // Signal new item available
        if (!ReleaseSemaphore(g_filled_slots_semaphore, 1, NULL)) {
            SafePrintf("[P%d] Error releasing filled_slots_semaphore: %lu\n", 
                      producer_id, GetLastError());
        }

        Sleep(produce_interval_dist(gen));
    }
    
    SafePrintf("[P%d] Finished producing all %d items.\n", producer_id, ITEMS_PER_PRODUCER_VAR);
    return 0;
}

// --- Consumer thread function ---
DWORD WINAPI ConsumerThreadFunc(LPVOID lpParam) {
    int consumer_id = static_cast<int>(reinterpret_cast<intptr_t>(lpParam));

    std::random_device rd;
    std::mt19937 gen(rd() + consumer_id + 1000 + GetCurrentThreadId());
    std::uniform_int_distribution<> consume_processing_time_dist(100, 350);
    std::uniform_int_distribution<> post_consume_sleep_dist(80, 200);

    while (true) {
        // Wait for item in buffer with timeout
        DWORD wait_result = WaitForSingleObject(g_filled_slots_semaphore, 200);

        if (wait_result == WAIT_OBJECT_0) {
            bool item_consumed = false;
            EnterCriticalSection(&g_buffer_cs);

            if (!g_buffer.empty()) {
                int item = g_buffer.front();
                g_buffer.pop_front();
                SafePrintf("[C%d] Consumed: %2d (Buffer: %2zu/%2d)\n",
                           consumer_id, item, g_buffer.size(), MAX_BUFFER_SIZE_VAR);
                item_consumed = true;
            }

            bool should_exit = g_all_producers_done && g_buffer.empty();
            LeaveCriticalSection(&g_buffer_cs);

            if (item_consumed) {
                ReleaseSemaphore(g_empty_slots_semaphore, 1, NULL);
                Sleep(consume_processing_time_dist(gen));
            } else {
                // Return the semaphore count if buffer was unexpectedly empty
                ReleaseSemaphore(g_filled_slots_semaphore, 1, NULL);
            }

            if (should_exit) break;

        } else if (wait_result == WAIT_TIMEOUT) {
            EnterCriticalSection(&g_buffer_cs);
            bool should_exit = g_all_producers_done && g_buffer.empty();
            LeaveCriticalSection(&g_buffer_cs);
            
            if (should_exit) break;
        } else {
            SafePrintf("[C%d] Error waiting for filled_slot semaphore: %lu\n", 
                      consumer_id, GetLastError());
            break;
        }
        
        Sleep(post_consume_sleep_dist(gen));
    }
    
    SafePrintf("[C%d] Finished consuming.\n", consumer_id);
    return 0;
}

// --- Cleanup function ---
void CleanupResources(const std::vector<HANDLE>& p_threads, const std::vector<HANDLE>& c_threads) {
    for (HANDLE th : p_threads) {
        if (th && th != INVALID_HANDLE_VALUE) CloseHandle(th);
    }
    for (HANDLE th : c_threads) {
        if (th && th != INVALID_HANDLE_VALUE) CloseHandle(th);
    }
    if (g_empty_slots_semaphore) CloseHandle(g_empty_slots_semaphore);
    if (g_filled_slots_semaphore) CloseHandle(g_filled_slots_semaphore);
    DeleteCriticalSection(&g_buffer_cs);
    DeleteCriticalSection(&g_output_cs);
}

int main(int argc, char* argv[]) {
    InitializeCriticalSection(&g_output_cs);

    if (!ParseArguments(argc, argv)) {
        DeleteCriticalSection(&g_output_cs);
        return 1;
    }

    SafePrintf("=== Producer-Consumer Simulation ===\n");
    SafePrintf("Producers: %d, Consumers: %d, Items per Producer: %d, Buffer Size: %d\n",
               NUM_PRODUCERS_VAR, NUM_CONSUMERS_VAR, ITEMS_PER_PRODUCER_VAR, MAX_BUFFER_SIZE_VAR);
    SafePrintf("Total Items: %d\n", NUM_PRODUCERS_VAR * ITEMS_PER_PRODUCER_VAR);
    SafePrintf("=====================================\n");

    InitializeCriticalSection(&g_buffer_cs);

    // Create semaphores
    g_empty_slots_semaphore = CreateSemaphore(NULL, MAX_BUFFER_SIZE_VAR, MAX_BUFFER_SIZE_VAR, NULL);
    g_filled_slots_semaphore = CreateSemaphore(NULL, 0, MAX_BUFFER_SIZE_VAR, NULL);
    
    if (!g_empty_slots_semaphore || !g_filled_slots_semaphore) {
        SafePrintf("Fatal: Failed to create semaphores\n");
        CleanupResources({}, {});
        return 1;
    }

    std::vector<HANDLE> producer_threads(NUM_PRODUCERS_VAR);
    std::vector<HANDLE> consumer_threads(NUM_CONSUMERS_VAR);
    DWORD thread_id;

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS_VAR; ++i) {
        producer_threads[i] = CreateThread(NULL, 0, ProducerThreadFunc,
                                         reinterpret_cast<LPVOID>(static_cast<intptr_t>(i + 1)),
                                         0, &thread_id);
        if (!producer_threads[i]) {
            SafePrintf("Failed to create producer thread %d\n", i + 1);
            CleanupResources(producer_threads, consumer_threads);
            return 1;
        }
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS_VAR; ++i) {
        consumer_threads[i] = CreateThread(NULL, 0, ConsumerThreadFunc,
                                         reinterpret_cast<LPVOID>(static_cast<intptr_t>(i + 1)),
                                         0, &thread_id);
        if (!consumer_threads[i]) {
            SafePrintf("Failed to create consumer thread %d\n", i + 1);
            CleanupResources(producer_threads, consumer_threads);
            return 1;
        }
    }

    // Wait for all producers to finish
    WaitForMultipleObjects(NUM_PRODUCERS_VAR, producer_threads.data(), TRUE, INFINITE);
    SafePrintf("\n>>> All producers finished.\n");

    // Signal producers are done
    EnterCriticalSection(&g_buffer_cs);
    g_all_producers_done = true;
    LeaveCriticalSection(&g_buffer_cs);

    // Wake up consumers to check completion
    for (int i = 0; i < NUM_CONSUMERS_VAR; ++i) {
        ReleaseSemaphore(g_filled_slots_semaphore, 1, NULL);
    }

    // Wait for all consumers to finish
    WaitForMultipleObjects(NUM_CONSUMERS_VAR, consumer_threads.data(), TRUE, INFINITE);
    SafePrintf(">>> All consumers finished.\n");

    CleanupResources(producer_threads, consumer_threads);

    // Final results
    SafePrintf("\n=== Results ===\n");
    SafePrintf("Items produced: %d\n", g_item_id_counter);
    SafePrintf("Expected items: %d\n", NUM_PRODUCERS_VAR * ITEMS_PER_PRODUCER_VAR);
    SafePrintf("Buffer final size: %zu\n", g_buffer.size());
    
    if (g_buffer.empty()) {
        SafePrintf("✓ All items consumed successfully\n");
    } else {
        SafePrintf("⚠ Warning: %zu items remain in buffer\n", g_buffer.size());
    }

    return 0;
}