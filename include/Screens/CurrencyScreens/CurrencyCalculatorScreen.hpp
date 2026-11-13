#ifndef CLASS_CURRENCY_CALCULATOR_SCREEN_HPP
#define CLASS_CURRENCY_CALCULATOR_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/Currency.hpp"
#include "../../Global/Config.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class CurrencyCalculatorScreen : protected Screen {
   public:
    static void show_currency_calculator_screen() {
        while (true) {
            system(Config::clear.c_str());
            draw_screen_header("Currency Calculator Screen.");
            Currency first_currency =
                get_currency("\nPlease enter first currency code: ");
            Currency second_currency =
                get_currency("\nPlease enter second currency code: ");

            float amount =
                InputValidate::input<float>("\nEnter Amount to Exchange: : ",
                                            "Invalid, Amount to Exchange: ");

            std::cout << "\nConvert from: ";
            print_currency(first_currency);

            if (second_currency.getCurrencyCode() != "USD") {
                std::cout << "\nTo: ";
                print_currency(second_currency);
            }
            std::cout << amount << " " << first_currency.getCurrencyCode()
                      << " = "
                      << first_currency.convert_to_other_currency(
                             amount, second_currency)
                      << " " << second_currency.getCurrencyCode() << std::endl;

            char answer = InputValidate::read_template<char>(
                "\nDo you want to perform another calculation y/n: ");
            if (std::tolower(answer) != 'y') {
                break;
            }
        }
    }

   private:
    // static float calculate_exchange() {}
    static Currency get_currency(std::string message) {
        std::string currency_code = "";
        Currency currency = Currency::get_empty_object();
        while (currency.is_empty()) {
            std::cout << message;
            std::cin >> currency_code;
            currency = Currency::find_by_code(currency_code);
        }

        return currency;
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

#endif  // CLASS_CURRENCY_CALCULATOR_SCREEN_HPP