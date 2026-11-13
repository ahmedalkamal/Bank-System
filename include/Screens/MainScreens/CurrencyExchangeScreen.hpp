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
        if (!has_permission(User::Permissions::CurrencyExchange)) {
            return;
        }

        system(Config::clear.c_str());
        draw_screen_header("console application", "", 39);

        std::cout << std::setw(37) << std::left << ""
                  << "========================================================="
                     "=========\n";
        std::cout << std::setw(57) << std::left << ""
                  << "Currency Exchange Menu\n";
        std::cout << std::setw(37) << std::left << ""
                  << "========================================================="
                     "=========\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[1] List Currencies.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[2] Find Currency.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[3] Update Rate.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[4] Currency Calculator.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[5] Main Menu.\n";

        std::cout << std::setw(37) << std::left << ""
                  << "========================================================="
                     "=========\n";

        perform_currency_exchange_menu_option(
            (CurrencyExchangeOptions)read_currency_exchange_menu_option());
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

    static short read_currency_exchange_menu_option() {
        bool valid = false;
        short choice;
        std::cout << std::setw(37) << std::left << ""
                  << "Choose what do you want to do [1 - 5]: ";
        while (!valid) {
            std::cin >> choice;
            valid = InputValidate::is_valid();
            if (!valid) {
                std::cout << std::setw(37) << std::left << ""
                          << "Invalid Input, Enter again [1 - 5]: ";
                continue;
            }
            if (!InputValidate::in_range<short>(choice, 1, 5)) {
                std::cout << std::setw(37) << std::left << ""
                          << "Input Out Of Range, Enter again [1 - 5]: ";
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