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
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[#] " + Color::bright_green("Currency Found.\n");

            print_currency(currency);
        } else {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[!] " + Color::bright_red("Currency Is Not Found!\n")
                      << std::endl;
        }
    }

   private:
    static short read_choice() {
        bool valid = false;
        short choice;
        std::string message = "Find by : [1]: country / [2]: code ? ";
        std::cout << std::setw(30) << std::left << "" << "[?] " + message;
        while (!valid) {
            std::cin >> choice;
            valid = InputValidate::is_valid();
            if (!valid) {
                std::cout << "\n"
                          << std::setw(30) << std::left << ""
                          << "[!] " + Color::bright_yellow("Invalid Input") +
                                 ", " + message;
                continue;
            }
            if (!InputValidate::in_range<short>(choice, 1, 2)) {
                std::cout << "\n"
                          << std::setw(30) << std::left << ""
                          << "[!] " +
                                 Color::bright_yellow("Input Out Of Range") +
                                 ", " + message;
                valid = false;
            }
        }
        return choice - 1;
    }
    static Currency handle_find_by(Currency::FindBy by) {
        std::string target = "";

        switch (by) {
            case Currency::FindBy::Country:
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[+] Please enter country name: ";
                // target = InputValidate::ReadString();
                std::cin >> target;
                return Currency::find_by_country(target).response;
            case Currency::FindBy::CurrencyCode:
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[+] Please enter currency code: ";
                std::cin >> target;
                // target = InputValidate::ReadString();
                return Currency::find_by_code(target).response;

            default:
                return Currency::get_empty_object();
        }
    }

    static std::string format_balance(std::string balance) {
        short zero = 0;
        for (short i = short(balance.find(".")); i < balance.size(); i++) {
            if (zero == 3) {
                return balance.substr(0, i - 1);
            }
            if (balance[i] == '0') {
                zero++;
            } else {
                zero = 0;
            }
        }
        return "0.0";
    };

    static void print_currency(Currency currency) {
        Table table{"Currency Card."};
        table.add_column("", 16);
        table.add_column(" info ", 45, Table::Align::Center);

        table.add_row({" Country", " " + currency.getCountry()});
        table.add_row({" Code", " " + currency.getCurrencyCode()});
        table.add_row({" Name", " " + currency.getCurrencyName()});
        table.add_row({" Rate(1$)", " " + format_balance(std::to_string(
                                              currency.getRate()))});

        table.setAlignment(25);
        table.print_table();
    }
};

#endif  // CLASS_FIND_CURRENCY_SCREEN_HPP