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
#include "../ScreenHelper.hpp"

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
        draw_screen_header("Currency Exchange Screen");
        if (!has_permission(User::Permissions::CurrencyExchange)) {
            return;
        }

        std::vector<std::string> menus{
            " List Currencies.",     " Find Currency.", " Update Rate.",
            " Currency Calculator.", " Main Menu.",
        };

        Table table{"Menu"};
        table.add_column("No.", 4, Table::Align::Center);
        table.add_column(" Options", 64, Table::Align::Center);

        table.setAlignment(25);

        for (short i = 0; i < menus.size(); i++) {
            std::string num = String::zfill(std::to_string(i + 1), 2);

            table.add_row({num, menus[i]});
        }
        table.print_menu();
        perform_currency_exchange_menu_option(
            (CurrencyExchangeOptions)ScreenHelper::read_option_enum(
                "Please choose option: ", menus.size()));
    }

   private:
    static void back_to_currency_exchange_menu() {
        ScreenHelper::back_to_selected_screen(
            "Press enter to go back to Currency Exchange Menu...",
            show_currency_exchange_menu);
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