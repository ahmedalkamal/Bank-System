#ifndef CLASS_CURRENCIES_LIST_SCREEN_HPP
#define CLASS_CURRENCIES_LIST_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../../Core/Currency.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"

class CurrenciesListScreen : protected Screen {
   public:
    static void show_currencies_list_screen() {
        std::vector<Currency> currencies =
            Currency::get_currency_list().response;
        std::string title = "Currencies List Screen.";
        std::string subtitle = std::to_string(currencies.size()) + " Currency.";

        draw_screen_header(title, subtitle);

        Table table{title, subtitle};
        table.setAlignment(11);

        table.add_column("Country", 27, Table::Align::Center);
        table.add_column("Code", 8, Table::Align::Center);
        table.add_column("Name", 45, Table::Align::Center);
        table.add_column("Rate/(1$)", 12, Table::Align::Center);

        if (currencies.size() == 0) {
            table.panel(
                {Color::bright_red("No Currencies Available In The System!")},
                95, Table::Align::Center, true);
        } else {
            for (Currency currency : currencies) {
                table.add_row({
                    " " + currency.getCountry(),
                    " " + currency.getCurrencyCode(),
                    " " + currency.getCurrencyName(),
                    " " + ScreenHelper::format_number(currency.getRate()),
                });
            }
            table.print_table();
        }
    }

   private:
};

#endif  // CLASS_CURRENCIES_LIST_SCREEN_HPP