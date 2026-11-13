#ifndef CLASS_INPUT_VALIDATE_HPP
#define CLASS_INPUT_VALIDATE_HPP

#include <iostream>
#include <string>

#include "Util.hpp"

class InputValidate {
   public:
    template <typename T>
    static T input(std::string message, std::string invalid_message) {
        T variable;
        bool valid = false;

        std::cout << message;
        while (!valid) {
            std::cin >> variable;
            valid = is_valid();
            if (!valid) {
                std::cout << invalid_message;
            }
        }
        return variable;
    }

    template <typename T>
    static T input_in_range(T min, T max, std::string message,
                            std::string invalid_message) {
        T value;
        bool valid = false;

        std::cout << message;
        while (!valid) {
            std::cin >> value;
            valid = is_valid();
            if (valid) {
                valid = in_range<T>(value, min, max);
            }
            if (!valid) {
                std::cout << invalid_message;
            }
        }
        return value;
    }

    template <typename T>
    static bool is_between(T value, T min, T max) {
        return in_range<T>(value, min, max);
    }

    template <typename T>
    static T read_template(std::string message = "", bool read_line = false) {
        T value;
        if (!message.empty()) std::cout << message;
        if (read_line) {
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
            // '\n');
            std::cin >> value;
            // std::getline(std::cin >> std::ws, value);
        } else {
            std::cin >> value;
        }
        return value;
    }

    template <typename T>
    static bool in_range(T value, T min, T max) {
        if (min > max) {
            Util::swap<T>(min, max);
        }
        return value >= min && value <= max;
    }

    static bool is_valid() {
        if (std::cin.fail() || std::cin.peek() != '\n') {
            Util::clear_buffer();
            return false;
        }
        return true;
    }
};

#endif  // CLASS_INPUT_VALIDATE_HPP