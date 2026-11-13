#ifndef CLASS_NUMBER_TO_WORDS_HPP
#define CLASS_NUMBER_TO_WORDS_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class NumberToWords {
   public:
    static std::string conver_number_to_words(long long number) {
        return NumberToWords().convert_number_to_words(number);
    }

    std::string convert_number_to_words(long long number) {
        if (number == 0) return "Zero";

        std::vector<short> groups = digit_grouping(number);
        std::string number_spelling = (number < 0 ? "minus " : "");

        for (int index = groups.size() - 1; index >= 0; --index) {
            // std::cout << groups[index] << std::endl;
            const short group = groups[index];
            if (group == 0) continue;

            number_spelling +=
                get_digit_name(group) + " " + this->scale_name[index];
            if (index > 0) number_spelling += ", ";
        }

        return number_spelling;
    }

   private:
    const std::string scale_name[7]{
        "",        "Thousand",    "Million",     "Billion",
        "Tillion", "Quadrillion", "Quintillion",
    };
    const std::string ones[20]{
        "",        "One",     "Two",       "Three",    "Four",
        "Five",    "Six",     "Seven",     "Eight",    "Nine",
        "Ten",     "Eleven",  "Twelve",    "Thirteen", "Fourteen",
        "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen",
    };
    const std::string tens[10]{
        "",      "",      "Twenty",  "Thirty", "Forty",
        "Fifty", "Sixty", "Seventy", "Eighty", "Ninety",
    };

    std::vector<short> digit_grouping(long long number) {
        number = std::abs(number);
        std::vector<short> groups;
        while (number != 0) {
            groups.push_back(number % 1000);
            number /= 1000;
        }
        return groups;
    }

    std::string get_digit_name(short digit) {
        bool is_hundred = digit > 99;
        std::string digit_name = "";
        if (digit % 100 < 20)
            digit_name = this->ones[digit % 100];

        else if (digit % 100 < 100 && digit % 100 > 19)
            digit_name =
                this->tens[digit % 100 / 10] + " " + this->ones[digit % 10];

        if (digit / 100 && is_hundred)
            digit_name = this->ones[digit / 100] + " Hundred " + digit_name;

        return digit_name;
    }
};

#endif  // CLASS_NUMBER_TO_WORDS_HPP