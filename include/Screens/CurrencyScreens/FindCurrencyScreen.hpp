#ifndef CLASS_FIND_CURRENCY_SCREEN_HPP
#define CLASS_FIND_CURRENCY_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/Currency.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class FindCurrencyScreen : protected Screen {
   public:
    static void show_find_currency_screen() {
        draw_screen_header("Find Currency Screen.");

        short choice = read_choice();
        Currency currency = handle_find_by((Currency::FindBy)choice);
        if (!currency.is_empty()) {
            std::cout << "Currency Found :) \n";
            print_currency(currency);
        } else {
            std::cout << "\nCurrency Is Not Found!\n" << std::endl;
        }
    }

   private:
    static short read_choice() {
        bool valid = false;
        short choice;
        std::string message = "Find by : [1]: country / [2]: code ? ";
        std::cout << std::setw(37) << std::left << "" << message;
        while (!valid) {
            std::cin >> choice;
            valid = InputValidate::is_valid();
            if (!valid) {
                std::cout << std::setw(37) << std::left << ""
                          << "Invalid Input, " + message;
                continue;
            }
            if (!InputValidate::in_range<short>(choice, 1, 2)) {
                std::cout << std::setw(37) << std::left << ""
                          << "Input Out Of Range, " + message;
                valid = false;
            }
        }
        return choice - 1;
    }
    static Currency handle_find_by(Currency::FindBy by) {
        std::string target = "";

        switch (by) {
            case Currency::FindBy::Country:
                std::cout << "\nPlease enter country name: ";
                // target = InputValidate::ReadString();
                std::cin >> target;
                return Currency::find_by_country(target);
            case Currency::FindBy::CurrencyCode:
                std::cout << "\nPlease enter currency code: ";
                std::cin >> target;
                // target = InputValidate::ReadString();
                return Currency::find_by_code(target);

            default:
                return Currency::get_empty_object();
        }
    }
    static void print_currency(Currency currency) {
        std::cout << "\nCurrency Card: \n";
        std::cout << "____________________________________\n";
        std::cout << "\nCountry    : " << currency.country;
        std::cout << "\nCode       : " << currency.currency_code;
        std::cout << "\nName       : " << currency.currency_name;
        std::cout << "\nRate(1$)   : " << currency.rate;
        std::cout << "\n____________________________________\n" << std::endl;
    }
};

#endif  // CLASS_FIND_CURRENCY_SCREEN_HPP