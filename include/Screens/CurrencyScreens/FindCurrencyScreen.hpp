#ifndef CLASS_FIND_CURRENCY_SCREEN_HPP
#define CLASS_FIND_CURRENCY_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include "../../Core/Currency.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"

class FindCurrencyScreen : protected Screen {
   public:
    static void show_find_currency_screen() {
        draw_screen_header("Find Currency Screen.");

        short choice = ScreenHelper::read_option_enum(
            "Find by : [1]: country / [2]: code ? ", 2);
        Currency currency = handle_find_by((Currency::FindBy)choice);
        if (!currency.is_empty()) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[#] " + Color::bright_green("Currency Found.\n");

            print_currency_card(currency);
        } else {
            // std::cout << "\n" << std::setw(30) << std::left << "";
            // std::cout << "[!] " + Color::bright_red("Currency Is Not
            // Found!\n")
            //           << std::endl;
        }
    }

   private:
    static Currency handle_find_by(Currency::FindBy by) {
        std::string target = "";

        switch (by) {
            case Currency::FindBy::Country:
                target = ScreenHelper::read_object_id<Currency>(
                    "Currency Name: ", true, Currency::find_by_country);
                // std::cout << "\n" << std::setw(30) << std::left << "";
                // std::cout << "[+] Please enter country name: ";
                // // target = InputValidate::ReadString();
                // std::cin >> target;
                return Currency::find_by_country(target).response;
            case Currency::FindBy::CurrencyCode:
                target = ScreenHelper::read_object_id<Currency>(
                    "Currency Code: ", true, Currency::find_by_code);
                // std::cout << "\n" << std::setw(30) << std::left << "";
                // std::cout << "[+] Please enter currency code: ";
                // std::cin >> target;
                // // target = InputValidate::ReadString();
                return Currency::find_by_code(target).response;

            default:
                return Currency::get_empty_object();
        }
    }

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

#endif  // CLASS_FIND_CURRENCY_SCREEN_HPP