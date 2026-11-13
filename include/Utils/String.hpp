#ifndef CLASS_STRING_HPP
#define CLASS_STRING_HPP

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "../Core/Property.hpp"

class _utli_class_string_hpp {
   public:
};

class String {
   private:
    std::string _value = "";
    bool _status = true;

    // static String* THIS;

    bool checkValue(std::string value) {
        if (value.empty()) {
            std::cout << "Value must not be empty!" << std::endl;
            return (this->_status = false);
        }
        return (this->_status = true);
    }

   public:
    String() {}
    String(std::string value) { setValue(value); }

    // setter and getter proprety..
    void setValue(std::string value) {
        if (!value.empty())
            this->_value = value;
        else {
            std::cout << "Value must not be empty!" << std::endl;
        }
    }
    std::string getValue() { return this->_value; }

    Property<std::string> value{
        [this]() { return getValue(); },
        [this](const std::string value) { setValue(value); }};

    // functions to change character case... done
    // friend std::string upper(std::string value);
    static std::string upper(std::string value) {
        for (int index = 0; index < value.size(); ++index) {
            if (islower(value[index])) {
                value.at(index) = (value.at(index) - 32);
            }
        }
        return value;
    }
    static std::string lower(std::string value) {
        for (int index = 0; index < value.length(); ++index) {
            if (isupper(value[index])) {
                value.at(index) = (value.at(index) + 32);
            }
        }
        return value;
    }
    static std::string capitalize(std::string value) {
        if (value.empty()) return value;
        if (islower(value.at(0))) {
            value.at(0) = (value.at(0) - 32);
        }
        return value;
    }
    static std::string title(std::string value) {
        bool was_space = true;
        for (int index = 0; index < value.size(); ++index) {
            if (was_space && isletter(value[index]))
                if (islower(value.at(index))) {
                    value.at(index) = (value.at(index) - 32);
                }
            was_space = (isspace(value.at(index)) ? true : false);
        }
        return value;
    }
    static char swapchar(char value) {
        if (islower(value)) return (value - 32);
        if (isupper(value)) return (value + 32);
        return value;
    }
    static std::string swapcase(std::string value) {
        for (int index = 0; index < value.size(); ++index) {
            if (isletter(value.at(index)))
                value.at(index) = swapchar(value.at(index));
        }
        return value;
    }

    std::string upper() { return this->upper(this->_value); }
    std::string lower() { return this->lower(this->_value); }
    std::string capitalize() { return this->capitalize(this->_value); }
    std::string title() { return this->title(this->_value); }
    std::string swapcase() { return this->swapcase(this->_value); }

    // functions to search inside string... done
    static int find(std::string value, std::string sub, int start = -1,
                    int end = -1) {
        // -1 : everything
        if (value.empty()) return -1;
        if (start <= -1) start = 0;
        if (end <= -1) end = value.size();

        int sub_size = sub.size();
        for (int index = start; index < end; index++) {
            if (end - index < sub_size) break;
            if (value.substr(index, sub_size) == sub) return index;
        }
        return -1;
    }
    static int find(std::string value, char sub, int start = -1, int end = -1) {
        return find(value, std::to_string(sub), start, end);
    }
    static int count(std::string value, std::string sub, int start = -1,
                     int end = -1) {
        // -1 : everything
        if (value.empty()) return 0;
        if (start <= -1) start = 0;
        if (end <= -1) end = value.size();

        int counter = 0;
        while ((start = find(value, sub, start, end)) != -1) {
            counter++;
            start++;
        }
        return counter;
    }
    static bool startswith(std::string value, std::string prefix,
                           int start = -1, int end = -1) {
        // -1 : everything
        if (value.empty()) return false;

        int size = prefix.size();
        if (start <= -1) start = 0;
        if (end <= -1) end = start + size;
        if (end > value.size()) return false;

        // if (size > (end - start)) return false;
        return prefix == value.substr(start, size);
    }
    static bool endswith(std::string value, std::string suffix, int start = -1,
                         int end = -1) {
        // -1 : everything
        if (value.empty()) return false;

        int size = suffix.size();
        if (end <= -1) end = value.size();
        if (start <= -1) start = (end - size);

        if (size > end) return false;
        if (start > end) return false;

        for (int index = 1; index <= size; index++) {
            // if (size == index) break;
            if (value.at(end - index) != suffix.at(size - index)) {
                return false;
            }
        }
        return true;
    }

    int find(std::string sub, int start = -1, int end = -1) {
        return this->find(this->_value, sub, start, end);
    }
    int count(std::string sub, int start = -1, int end = -1) {
        return this->count(this->_value, sub, start, end);
    }
    int startswith(std::string prefix, int start = -1, int end = -1) {
        return this->startswith(this->_value, prefix, start, end);
    }
    int endswith(std::string suffix, int start = -1, int end = -1) {
        return this->startswith(this->_value, suffix, start, end);
    }

    // function to delete spaces...done
    static void removechar(std::string& value, int index) {
        value.at(index) = 0;
    }
    static std::string strip(std::string value, char chars = ' ') {
        return lstrip(rstrip(value, chars), chars);
    }
    static std::string lstrip(std::string value, char chars = ' ') {
        int size = value.size();
        for (int index = 0; index < size; index++) {
            if (chars != value[index]) {
                break;
            } else {
                removechar(value, index);
            }
        }
        return value;
    }
    static std::string rstrip(std::string value, char chars = ' ') {
        int size = value.size();
        for (int index = size - 1; index >= 0; index--) {
            if (chars != value[index]) {
                break;
            } else {
                removechar(value, index);
            }
        }
        return value;
    }

    std::string strip(char chars = ' ') {
        return this->strip(this->_value, chars);
    }
    std::string lstrip(char chars = ' ') {
        return this->lstrip(this->_value, chars);
    }
    std::string rstrip(char chars = ' ') {
        return this->rstrip(this->_value, chars);
    }

    // functions to replace and split...done
    static std::string replace(std::string value, std::string old_value,
                               std::string new_value, int count = -1) {
        // -1 : everthing
        if (value.empty()) return value;
        short index = 0;
        int counter = 0;
        while ((index = find(value, old_value, index)) != -1 &&
               count != counter) {
            value.erase(index, old_value.length());
            value.insert(index, new_value);
            index += new_value.length();
            counter++;
        }
        return value;
    }
    static std::vector<std::string> split(std::string value, std::string sep,
                                          int maxsplit = -1) {
        // -1 : everthing
        if (value.empty()) return {};

        std::vector<std::string> tokens;
        std::string token = "";
        int index = 0;
        while ((index = find(value, sep)) != -1 && tokens.size() != maxsplit) {
            token = value.substr(0, index);
            // if (!token.empty()) {}
            tokens.push_back(token);

            value.erase(0, index + sep.length());
        }
        if (!value.empty()) tokens.push_back(value);

        return tokens;
    }
    static std::string join(std::vector<std::string> tokens, std::string sep) {
        std::string line = "";
        if (tokens.empty()) return line;
        for (const std::string& token : tokens) {
            line = line + token + sep;
        }
        return line.substr(0, line.length() - sep.length());
    }

    std::string replace(std::string old_value, std::string new_value,
                        int count = -1) {
        return this->replace(this->_value, old_value, new_value, count);
    }
    std::vector<std::string> split(std::string sep, int maxsplit = -1) {
        return this->split(this->_value, sep, maxsplit);
    }

    // functions to check of string contents... done
    static bool isupper(char value) { return value >= 'A' && 'Z' >= value; }
    static bool islower(char value) { return value >= 'a' && 'z' >= value; }
    static bool isletter(char value) {
        return islower(value) || isupper(value);
    }
    static bool isspace(char value) { return value == ' '; }
    static bool isalpha(std::string value) {
        if (value.empty()) {
            // std::cout << "Value must not be empty!" << std::endl;
            return false;
        }
        for (const char& c : value) {
            if (!isletter(c)) return false;
        }
        return true;
    }
    // only 0-9 ...
    static bool isdigit(std::string value) {
        if (value.empty()) {
            // std::cout << "Value must not be empty!" << std::endl;
            return false;
        }
        for (const short c : value) {
            if (!(48 <= c && c <= 57)) return false;
        }
        return true;
    }
    static bool isalnum(std::string value) {
        if (value.empty()) {
            // std::cout << "Value must not be empty!" << std::endl;
            return false;
        }
        return isalpha(value) || isdigit(value);
    }
    static bool islower(std::string value) {
        if (value.empty()) {
            // std::cout << "Value must not be empty!" << std::endl;
            return false;
        }
        for (const char& c : value) {
            if (!islower(c)) return false;
        }
        return true;
    }
    static bool isupper(std::string value) {
        if (value.empty()) {
            // std::cout << "Value must not be empty!" << std::endl;
            return false;
        }
        for (const char& c : value) {
            if (!isupper(c)) return false;
        }
        return true;
    }
    static bool istitle(std::string value) {
        if (value.empty()) {
            // std::cout << "Value must not be empty!" << std::endl;
            return false;
        }
        return value == title(value);
        bool was_space = true;
        for (int index = 0; index < value.size(); ++index) {
            if (was_space && isletter(value[index]))
                if (!isupper(value[index])) {
                    return false;
                }
            was_space = (isspace(value.at(index)) ? true : false);
        }
        return true;
    }
    static bool isspace(std::string value) {
        if (value.empty()) {
            // std::cout << "Value must not be empty!" << std::endl;
            return false;
        }
        for (const char& c : value) {
            if (!isspace(c)) return false;
        }
        return true;
    }
    static bool isascii(std::string value) {
        if (value.empty()) {
            // std::cout << "Value must not be empty!" << std::endl;
            return false;
        }
        for (const short c : value) {
            if (c < 0 || c > 255) return false;
        }
        return true;
    }

    bool isalpha() { return this->isalpha(this->_value); }
    bool isdigit() { return this->isdigit(this->_value); }
    bool isalnum() { return this->isalnum(this->_value); }
    bool islower() { return this->islower(this->_value); }
    bool isupper() { return this->isupper(this->_value); }
    bool istitle() { return this->istitle(this->_value); }
    bool isspace() { return this->isspace(this->_value); }
    bool isascii() { return this->isascii(this->_value); }

    // functions to format string... done
    static std::string center(std::string value, int width,
                              char fillchar = ' ') {
        int size = len(value);
        if (width <= 0 || size >= width) return value;

        int rwidth = std::ceil(float(width - size) / 2.f);
        value = rjust(value, rwidth + size, fillchar);
        return ljust(value, width, fillchar);
    }
    static std::string ljust(std::string value, int width,
                             char fillchar = ' ') {
        int size = len(value);
        if (width <= 0 || size >= width) {
            return value;
        }
        for (int index = 0; index < (width - size); index++) {
            value += fillchar;
        }
        return value;
    }
    static std::string rjust(std::string value, int width,
                             char fillchar = ' ') {
        int size = len(value);
        if (width <= 0 || size >= width) {
            return value;
        }
        for (int index = 0; index < (width - size); index++) {
            value = fillchar + value;
        }
        return value;
    }
    static std::string zfill(std::string value, int width) {
        int size = len(value);
        if (width <= 0 || size >= width) {
            return value;
        }
        for (int index = 0; index < (width - size); index++) {
            value = "0" + value;
        }
        // value.insert(0, static_cast<std::size_t>(width) - value.size(), '0');
        return value;
    }

    std::string center(int width, char fillchar = ' ') {
        return this->center(this->_value, width, fillchar);
    }
    std::string ljust(int width, char fillchar = ' ') {
        return this->ljust(this->_value, width, fillchar);
    }
    std::string rjust(int width, char fillchar = ' ') {
        return this->rjust(this->_value, width, fillchar);
    }
    std::string zfill(int width) { return this->zfill(this->_value, width); }

    // additional..
    static int len(std::string value) {
        if (value.empty()) {
            // std::cout << "Value must not be empty!" << std::endl;
            return 0;
        }
        return value.length();
    }
    int len() { return this->len(this->_value); }
    static int ord(char character) { return (int)character; }
    static char chr(int ascii) { return (char)ascii; }

    // abuHadhoud additioanl...
    static bool isvowel(char character) {
        if (isupper(character)) {
            character = character + 32;
        }
        // return find("aeiou", value) < 5;
        switch (std::tolower(character)) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                return true;
            default:
                return false;
        }
    }
    static int count_vowel(std::string value) {
        int count = 0;
        for (const char character : value) {
            if (isvowel(character)) count++;
        }
        return count;
    }
    static int count_words(std::string value) {
        return split(value, " ").size();
    }
    static std::string remove_punctuation(std::string value) {
        for (char& character : value) {
            // if (std::toupper (character) < 'A'
            //     || std::toupper (character) > 'Z')
            //     if (character != ' ')
            if (!isletter(character)) character = 0;
        }
        return value;
    }

    int count_vowel() { return this->count_vowel(this->_value); }
    int count_words() { return this->count_words(this->_value); }
    std::string remove_punctuation() {
        return this->remove_punctuation(this->_value);
    }
};

#endif  // CLASS_STRING_HPP