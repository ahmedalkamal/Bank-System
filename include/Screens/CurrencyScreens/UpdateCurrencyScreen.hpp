#ifndef CLASS_UPDATE_CURRENCY_SCREEN_HPP
#define CLASS_UPDATE_CURRENCY_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/Currency.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class UpdateCurrencyScreen : protected Screen {
   public:
    static void show_update_currency_screen() {
        draw_screen_header("Update Currency Screen.");

        Currency currency = get_currency();
        if (currency.is_empty()) {
            std::cout << "\nCurrency was not found!\n\n";
            return;
        }

        print_currency(currency);
        float currency_rate = currency.getRate();
        char answer = InputValidate::read_template<char>(
            "Are you sure want to update the rate of  this Currency y/n: ");
        if (std::tolower(answer) == 'y') {
            std::cout << "\n\nUpdate Currency Rate: ";
            std::cout << "\n_________________________\n\n";
            currency_rate = InputValidate::input<float>(
                "Enter New Rate: ", "Invalid, Enter New Rate: ");
            if (currency.update_rate(currency_rate)) {
                std::cout << "\nCurrency Rate Updated Successfully :)\n";
                print_currency(currency);
            } else {
                std::cout << "Currency Rate was not Updated!\n\n";
            }
        }
    }

   private:
    static Currency get_currency() {
        std::string currency_code = "";
        std::cout << "\nPlease enter currency code : ";
        std::cin >> currency_code;
        return Currency::find_by_code(currency_code);
    }

    static void print_currency(Currency currency) {
        std::cout << "\nCurrency Card: \n";
        std::cout << "____________________________________\n";
        std::cout << "\nCountry    : " << currency.getCountry();
        std::cout << "\nCode       : " << currency.getCurrencyCode();
        std::cout << "\nName       : " << currency.getCurrencyName();
        std::cout << "\nRate(1$)   : " << currency.getRate();
        std::cout << "\n____________________________________\n" << std::endl;
    }
};

#endif  // CLASS_UPDATE_CURRENCY_SCREEN_HPP
