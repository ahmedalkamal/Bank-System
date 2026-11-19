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

        Currency currency = get_currency();
        if (currency.is_empty()) {
            std::cout << std::setw(30) << std::left << "";
            std::cout << "[!] " +
                             Color::bright_red("Currency was not found!\n\n");
            return;
        }

        print_currency(currency);
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
                print_currency(currency);
            } else {
                std::cout << "[!] " + Color::bright_red(
                                          "Currency Rate was not Updated!\n\n");
            }
        }
    }

   private:
    static Currency get_currency() {
        std::string currency_code = "";

        std::cout << std::setw(30) << std::left << "";
        std::cout << "[+] Please enter currency code : ";
        std::cin >> currency_code;
        return Currency::find_by_code(currency_code).response;
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

#endif  // CLASS_UPDATE_CURRENCY_SCREEN_HPP
