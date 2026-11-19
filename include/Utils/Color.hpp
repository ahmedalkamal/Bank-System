#ifndef CLASS_CUSTOM_COLOR_HPP
#define CLASS_CUSTOM_COLOR_HPP

#include <iostream>
#include <string>

#include "String.hpp"

class Color {
   public:
    static void show_color_list() {
        for (short code = 0; code <= 255; code++) {
            std::cout << custom_color("##########", code)
                      << " | code : " << code << std::endl;
        }
    }
    static std::string custom_color(const std::string& text, short code = -1) {
        return ansi_color(code) + initialize(text);
    }

    static std::string black(const std::string& text) {
        return custom_color(text, 16);
    }
    static std::string red(const std::string& text) {
        return custom_color(text, 1);
    }
    static std::string green(const std::string& text) {
        return custom_color(text, 2);
    }
    static std::string yellow(const std::string& text) {
        return custom_color(text, 3);
    }
    static std::string blue(const std::string& text) {
        return custom_color(text, 4);
    }
    static std::string magenta(const std::string& text) {
        return custom_color(text, 5);
    }
    static std::string cyan(const std::string& text) {
        return custom_color(text, 6);
    }
    static std::string white(const std::string& text) {
        return custom_color(text, 7);
    }

    static std::string bright_red(const std::string& text) {
        return custom_color(text, 9);
    }
    static std::string bright_green(const std::string& text) {
        return custom_color(text, 10);
    }
    static std::string bright_yellow(const std::string& text) {
        return custom_color(text, 11);
    }
    static std::string bright_blue(const std::string& text) {
        return custom_color(text, 12);
    }
    static std::string bright_magenta(const std::string& text) {
        return custom_color(text, 13);
    }
    static std::string bright_cyan(const std::string& text) {
        return custom_color(text, 14);
    }
    static std::string bright_white(const std::string& text) {
        return custom_color(text, 15);
    }

   private:
    static std::string get_default_color() { return "\033[0m"; }
    static std::string ansi_color(short code) {
        return String::join({"\033[38;5;", std::to_string(code), "m"}, "");
    }
    static std::string initialize(const std::string& text) {
        return text + get_default_color();
    }
};

#endif  // CLASS_CUSTOM_COLOR_HPP