#ifndef CLASS_CURRENCY_EXCHANGE_SCREEN_HPP
#define CLASS_CURRENCY_EXCHANGE_SCREEN_HPP

#include <iomanip>
#include <iostream>

#include "../../Global/Config.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../CurrencyScreens/CurrenciesListScreen.hpp"
#include "../CurrencyScreens/CurrencyCalculatorScreen.hpp"
#include "../CurrencyScreens/FindCurrencyScreen.hpp"
#include "../CurrencyScreens/UpdateCurrencyScreen.hpp"
#include "../Screen.hpp"

class CurrencyExchangeScreen : protected Screen {
   private:
    enum class CurrencyExchangeOptions {
        ListCurrencies,
        FindCurrency,
        UpdateRate,
        CurrencyCalculator,
        MainMenu,
    };

   public:
    static void show_currency_exchange_menu() {
        system(Config::clear.c_str());
        draw_screen_header("console application");
        if (!has_permission(User::Permissions::CurrencyExchange)) {
            return;
        }

        std::vector<std::string> menus{
            "List Currencies.",     "Find Currency.", "Update Rate.",
            "Currency Calculator.", "Main Menu",
        };

        Table table{"Currency Exchange Menu"};
        table.add_column("#", 4, Table::Align::Center);
        table.add_column(" Options", 64, Table::Align::Center);

        table.setAlignment(25);
        for (short i = 0; i < menus.size(); i++) {
            table.add_row({std::to_string(i + 1), menus[i]});
        }
        table.print_menu();
        perform_currency_exchange_menu_option(
            (CurrencyExchangeOptions)read_currency_exchange_menu_option(
                menus.size()));
    }

   private:
    static void back_to_currency_exchange_menu() {
        // if (std::cin.fail() || std::cin.peek() != '\n') {
        Util::clear_buffer();
        // }
        std::cout << "Press enter to go back to Currency Exchange Menu...";
        std::cin.get();
        show_currency_exchange_menu();
    }

    static short read_currency_exchange_menu_option(short max) {
        bool valid = false;
        short choice;
        std::cout << std::setw(37) << std::left << ""
                  << "[+] Choose what do you want to do [1 - " << max << "]: ";
        while (!valid) {
            std::cin >> choice;
            valid = InputValidate::is_valid();
            if (!valid) {
                std::cout << std::setw(37) << std::left << ""
                          << Color::yellow("[!] Invalid Input") +
                                 ", Enter again [1 - "
                          << max << "]: ";
                continue;
            }
            if (!InputValidate::in_range<short>(choice, 1, max)) {
                std::cout << std::setw(37) << std::left << ""
                          << Color::yellow("[!] Input Out Of Range") +
                                 ", Enter again [1 - "
                          << max << "]: ";
                valid = false;
            }
        }
        return choice - 1;
    }

    static void show_list_currencies_screen() {
        // std::cout << "\nList Currencies Screen will be here. \n";
        CurrenciesListScreen::show_currencies_list_screen();
    }
    static void show_find_currency_screen() {
        // std::cout << "\nFind Currency Screen will be here. \n";
        FindCurrencyScreen::show_find_currency_screen();
    }
    static void show_update_rate_screen() {
        // std::cout << "\nUpdate Rate Screen will be here. \n";
        UpdateCurrencyScreen::show_update_currency_screen();
    }
    static void show_currency_calculator_screen() {
        // std::cout << "\nCurrency Calculator Screen will be here. \n";
        CurrencyCalculatorScreen::show_currency_calculator_screen();
    }

    static void perform_currency_exchange_menu_option(
        CurrencyExchangeOptions option) {
        system(Config::clear.c_str());

        switch (option) {
            case CurrencyExchangeOptions::ListCurrencies:
                show_list_currencies_screen();
                back_to_currency_exchange_menu();
                break;
            case CurrencyExchangeOptions::FindCurrency:
                show_find_currency_screen();
                back_to_currency_exchange_menu();
                break;
            case CurrencyExchangeOptions::UpdateRate:
                show_update_rate_screen();
                back_to_currency_exchange_menu();
                break;
            case CurrencyExchangeOptions::CurrencyCalculator:
                show_currency_calculator_screen();
                back_to_currency_exchange_menu();
                break;
            case CurrencyExchangeOptions::MainMenu:
                /* code */
            default:
                break;
        }
    }
};

#endif  // CLASS_CURRENCY_EXCHANGE_SCREEN_HPP