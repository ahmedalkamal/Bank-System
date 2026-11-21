#ifndef CLASS_UPDATE_CURRENCY_SCREEN_HPP
#define CLASS_UPDATE_CURRENCY_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/Currency.hpp"
#include "../../Utils/Color.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class UpdateCurrencyScreen : protected Screen {
   public:
    static void show_update_currency_screen() {
        draw_screen_header("Update Currency Screen.");

        std::string currency_code = ScreenHelper::read_object_id<Currency>(
            "Currency Code: ", true, Currency::find_by_code);
        if (currency_code.empty()) return;

        Currency currency = Currency::find_by_code(currency_code).response;
        if (currency.is_empty()) {
            std::cout << std::setw(30) << std::left << "";
            std::cout << "[!] " +
                             Color::bright_red("Currency was not found!\n\n");
            return;
        }

        print_currency_card(currency);
        float currency_rate = currency.getRate();

        std::cout << "\n" << std::setw(30) << std::left << "";
        char answer = InputValidate::read_template<char>(
            "[?] Are you sure want to update the rate of  this Currency y/n: ");

        if (std::tolower(answer) == 'y') {
            std::cout << "\n" << std::setw(30) << std::left << "";

            std::cout << "[#] Update Currency Rate: ";
            currency_rate = InputValidate::input<float>(
                std::string(30, ' ') + "[+] Please enter new rate: ",
                std::string(30, ' ') + "[!] Invalid, enter new rate: ");

            if (currency.update_rate(currency_rate)) {
                std::cout << "[+] " +
                                 Color::bright_green(
                                     "Currency Rate Updated Successfully :)\n");
                print_currency_card(currency);
            } else {
                std::cout << "[!] " + Color::bright_red(
                                          "Currency Rate was not Updated!\n\n");
            }
        }
    }

   private:
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

#endif  // CLASS_UPDATE_CURRENCY_SCREEN_HPP
