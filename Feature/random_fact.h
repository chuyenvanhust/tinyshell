#ifndef RANDOM_FACT_H
#define RANDOM_FACT_H

#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

void printRandomFact() {
    static std::vector<std::string> facts = {
        "Honey never spoils.",
        "Octopuses have three hearts.",
        "Bananas are berries, but strawberries aren't.",
        "A day on Venus is longer than its year.",
        "Humans share 60% of DNA with bananas.",
        "The Eiffel Tower can grow 15 cm taller in summer.",
        "Some cats are allergic to humans.",
        "You can't hum while holding your nose closed.",
        "Greatest quote of all time: Sunday the kings play"
        
    };

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int index = std::rand() % facts.size();

    std::cout << "Random Fact: " << facts[index] << std::endl;
}


#endif // RONALDO_H