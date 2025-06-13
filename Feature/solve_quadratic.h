#ifndef SOLVE_QUADRATIC_H
#define SOLVE_QUADRATIC_H

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>

// Hàm chuẩn hóa Unicode dash (en-dash/em-dash → ASCII dash)
std::string normalizeUnicodeDashes(const std::string& input) {
    std::string output;
    for (size_t i = 0; i < input.length(); ) {
        if (i + 2 < input.length() &&
            (unsigned char)input[i] == 0xE2 &&
            (unsigned char)input[i + 1] == 0x80 &&
            ((unsigned char)input[i + 2] == 0x93 || (unsigned char)input[i + 2] == 0x94)) {
            output += '-';
            i += 3;
        } else {
            output += input[i];
            ++i;
        }
    }
    return output;
}


// Hàm chính giải phương trình bậc hai
void solveQuadratic(const std::vector<std::string> &args) {
    if (args.size() != 3) {
        std::cout << "Usage: solve_quadratic <a> <b> <c>" << std::endl;
        return;
    }

    double a, b, c;
    try {
        a = std::stod(normalizeUnicodeDashes(args[0]));
        b = std::stod(normalizeUnicodeDashes(args[1]));
        c = std::stod(normalizeUnicodeDashes(args[2]));
    } catch (...) {
        std::cerr << "Invalid input. Please enter numeric coefficients." << std::endl;
        return;
    }

    if (a == 0) {
        std::cerr << "Coefficient 'a' cannot be zero in a quadratic equation." << std::endl;
        return;
    }

    double delta = b * b - 4 * a * c;

    std::cout << "Solving: " << a << "x^2 + " << b << "x + " << c << " = 0" << std::endl;

    if (delta > 0) {
        double x1 = (-b + std::sqrt(delta)) / (2 * a);
        double x2 = (-b - std::sqrt(delta)) / (2 * a);
        std::cout << "Two distinct real roots: x1 = " << x1 << ", x2 = " << x2 << std::endl;
    } else if (delta == 0) {
        double x = -b / (2 * a);
        std::cout << "One real root (double root): x = " << x << std::endl;
    } else {
        double real = -b / (2 * a);
        double imag = std::sqrt(-delta) / (2 * a);
        std::cout << "Two complex roots: "
                  << "x1 = " << real << " + " << imag << "i, "
                  << "x2 = " << real << " - " << imag << "i" << std::endl;
    }
}


#endif // SOLVE_QUADRATIC_H
