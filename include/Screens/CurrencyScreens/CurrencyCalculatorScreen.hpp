#ifndef CLASS_CURRENCY_CALCULATOR_SCREEN_HPP
#define CLASS_CURRENCY_CALCULATOR_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include "../../Core/Currency.hpp"
#include "../../Global/Config.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"

class CurrencyCalculatorScreen : protected Screen {
   public:
    static void show_currency_calculator_screen() {
    redo:
        system(Config::clear.c_str());
        draw_screen_header("Currency Calculator Screen.");

        Currency first_currency =
            Currency::find_by_code(
                ScreenHelper::read_object_id<Currency>(
                    "Currency Code (from): ", true, Currency::find_by_code))
                .response;

        if (first_currency.is_empty()) {
            return;
        }
        print_currency_card(first_currency);

        Currency second_currency =
            Currency::find_by_code(
                ScreenHelper::read_object_id<Currency>(
                    "Currency Code (to): ", true, Currency::find_by_code))
                .response;
        if (second_currency.is_empty()) {
            return;
        }
        print_currency_card(second_currency);

        std::cout << "\n";
        float amount = InputValidate::input<float>(
            std::string(30, ' ') + "[+] Enter Amount to Exchange: : ",
            std::string(30, ' ') + "[!] " +
                Color::bright_red("Invalid, Amount to Exchange: "));

        std::cout << "\n" << std::setw(30) << std::left << "";
        std::cout << "[#] " << amount << " " << first_currency.getCurrencyCode()
                  << " = "
                  << first_currency.convert_to_other_currency(amount,
                                                              second_currency)
                  << " " << second_currency.getCurrencyCode() << std::endl;

        std::cout << "\n" << std::setw(30) << std::left << "";
        char answer = InputValidate::read_template<char>(
            "[?] Do you want to perform another calculation y/n: ");
        if (std::tolower(answer) == 'y') {
            goto redo;
        }
    }

   private:
    static void print_exchange(Currency first, Currency second) {
        std::cout << "\n";
        float amount = InputValidate::input<float>(
            std::string(30, ' ') + "[+] Enter Amount to Exchange: : ",
            std::string(30, ' ') + "[!] " +
                Color::bright_red("Invalid, Amount to Exchange: "));

        std::cout << "\n" << std::setw(30) << std::left << "";
        std::cout << "[#] " << amount << " " << first.getCurrencyCode() << " = "
                  << first.convert_to_other_currency(amount, second) << " "
                  << second.getCurrencyCode() << std::endl;
    }
    // static float calculate_exchange() {}

    static void print_currency_card(Currency currency) {
        std::map<std::string, std::string> rows;

        rows.insert({"Country", currency.getCountry()});
        rows.insert({"Code", currency.getCurrencyCode()});
        rows.insert({"Name", currency.getCurrencyName()});
        rows.insert(
            {"Rate(1$)", ScreenHelper::format_number(currency.getRate())});

        ScreenHelper::print_object_card("Currency Card", rows);
    }
};

#endif  // CLASS_CURRENCY_CALCULATOR_SCREEN_HPP