#ifndef CLASS_UTIL_HPP
#define CLASS_UTIL_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class Util {
   public:
    static void clear_buffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    // Util() { this->seed(); }
    enum CharacterType {
        Alphabet,
        CapitalLetter,
        SmallLetter,
        Decimal,
        Random,
    };
    static void seed() { std::srand(unsigned(time(NULL))); }
    static int random_number(int start, int end) {
        return rand() % (end - start + 1) + start;
    }

    // static int get_size(){}

    static int random(std::vector<int> list) {
        int index = random_number(0, list.size() - 1);
        return list[index];
    }
    static std::string random(std::vector<std::string> list) {
        int index = random_number(0, list.size() - 1);
        return list[index];
    }
    template <typename T>
    static T random(std::vector<T> list) {
        int index = random_number(0, list.size() - 1);
        return list[index];
    }

    static int random(int list[], int size) {
        // int size = sizeof(list) / sizeof(int);
        int index = random_number(0, size - 1);
        return list[index];
    }
    static std::string random(std::string list[], int size) {
        int index = random_number(0, size - 1);
        return list[index];
    }
    template <typename T>
    static T random(T list[], int size) {
        int index = random_number(0, size - 1);
        return list[index];
    }

    static void shuffle(std::vector<int>& list) {
        int end = list.size() - 1;
        for (int index = 0; index <= end; index++) {
            swap(list[index], list[random_number(0, end)]);
        }
    }
    static void shuffle(std::vector<std::string>& list) {
        int end = list.size() - 1;
        for (int index = 0; index <= end; index++) {
            swap(list[index], list[random_number(0, end)]);
        }
    }
    template <typename T>
    static void shuffle(std::vector<T>& list) {
        int end = list.size() - 1;
        for (int index = 0; index <= end; index++) {
            swap(list[index], list[random_number(0, end)]);
        }
    }

    static void shuffle(int list[], int size) {
        for (int index = 0; index <= size - 1; index++) {
            swap(list[index], list[random_number(0, size - 1)]);
        }
    }
    static void shuffle(std::string list[], int size) {
        for (int index = 0; index <= size - 1; index++) {
            swap(list[index], list[random_number(0, size - 1)]);
        }
    }
    template <typename T>
    static void shuffle(T list[], int size) {
        for (int index = 0; index <= size - 1; index++) {
            swap(list[index], list[random_number(0, size - 1)]);
        }
    }

    static void swap(int& first, int& second) {
        int temp = first;
        first = second;
        second = temp;
    }
    static void swap(std::string& first, std::string& second) {
        std::string temp = first;
        first = second;
        second = temp;
    }
    template <typename T>
    static void swap(T& first, T& second) {
        T temp = first;
        first = second;
        second = temp;
    }

    static char generate_alphabet(CharacterType ctype = CharacterType::Random) {
        if (ctype == CharacterType::CapitalLetter) {
            return (char)random_number('A', 'Z');
        }
        if (ctype == CharacterType::SmallLetter) {
            return (char)random_number('a', 'z');
        }

        return (random_number(0, 1)) ? (char)random_number('A', 'Z')
                                     : (char)random_number('a', 'z');
    }
    static std::string generate(CharacterType ctype, int length) {
        char character;
        std::string resutl = "";
        for (; length > 0; length--) {
            if (ctype == CharacterType::Decimal ||
                (random_number(0, 1) && ctype == CharacterType::Random)) {
                character = (char)random_number('0', '9');
            } else {
                character = generate_alphabet(ctype);
            }
            resutl.push_back(character);
        }
        return resutl;
    }
    static std::string generate(char character, int length) {
        std::string result = "";
        for (; length > 0; length--) {
            result.push_back(character);
        }
        return result;
    }
    static std::string generate(std::string character, int length) {
        std::string result = "";
        for (; length > 0; length--) {
            result += character;
        }
        return result;
    }

    static std::string generate_key(CharacterType ctype = CharacterType::Random,
                                    char sep = '-') {
        std::string key = "";
        for (short i = 0;; i++) {
            key += generate(ctype, 5);
            if (i >= 4) break;
            key.push_back(sep);
        }
        return key;
    }
    static std::vector<std::string> generate_keys(
        int amount, CharacterType ctype = CharacterType::Random,
        char sep = '-') {
        std::vector<std::string> keys;
        for (; amount > 0; amount--) {
            keys.push_back(generate_key(ctype, sep));
        }
        return keys;
    }

    template <typename T>
    static void print_list(std::vector<T> list) {
        for (int index = 0; index < list.size(); index++) {
            std::cout << "[" << index + 1 << "]: " << list.at(index)
                      << std::endl;
        }
    }
    template <typename T>
    static void print_list(T list[], int size) {
        for (int index = 0; index < size; index++) {
            std::cout << "[" << index + 1 << "]: " << list[index] << std::endl;
        }
    }

    static std::string encrypt(std::string text, short encryption_key) {
        for (int i = 0; i < text.length(); i++) {
            text.at(i) = char((int)text.at(i) + encryption_key);
        }
        return text;
    }
    static std::string decrypt(std::string text, short encryption_key) {
        for (int i = 0; i < text.length(); i++) {
            text.at(i) = char((int)text.at(i) - encryption_key);
        }
        return text;
    }

   private:
};

#endif  // CLASS_UTIL_HPP