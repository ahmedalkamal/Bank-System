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
                get_currency("[+] Please enter first currency code: ");
            std::cout << "\n";
            print_currency(first_currency);

            Currency second_currency =
                get_currency("[+] Please enter second currency code: ");
            std::cout << "\n";
            print_currency(second_currency);

            std::cout << "\n";
            float amount = InputValidate::input<float>(
                std::string(30, ' ') + "[+] Enter Amount to Exchange: : ",
                std::string(30, ' ') + "[!] " +
                    Color::bright_red("Invalid, Amount to Exchange: "));

            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[#] " << amount << " "
                      << first_currency.getCurrencyCode() << " = "
                      << first_currency.convert_to_other_currency(
                             amount, second_currency)
                      << " " << second_currency.getCurrencyCode() << std::endl;

            std::cout << "\n" << std::setw(30) << std::left << "";
            char answer = InputValidate::read_template<char>(
                "[?] Do you want to perform another calculation y/n: ");
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
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << message;
            std::cin >> currency_code;
            currency = Currency::find_by_code(currency_code).response;
        }

        return currency;
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

#endif  // CLASS_CURRENCY_CALCULATOR_SCREEN_HPP