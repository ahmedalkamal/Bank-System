#ifndef CLASS_CURRENCIES_LIST_SCREEN_HPP
#define CLASS_CURRENCIES_LIST_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../../Core/Currency.hpp"
#include "../Screen.hpp"

class CurrenciesListScreen : protected Screen {
   public:
    static void show_currencies_list_screen() {
        std::vector<Currency> currencies = Currency::get_currency_list();

        std::string title = "Currencies List Screen.";
        std::string subtitle =
            "\t" + std::to_string(currencies.size()) + " Currency.";
        draw_screen_header(title, subtitle);

        std::string line = std::string(112, '_');

        std::cout << std::setw(8) << "" << line << "\n\n";
        std::cout << std::setw(10) << std::right << "| " << std::setw(35)
                  << std::left << "Country" << "| " << std::setw(8) << "Code"
                  << "| " << std::setw(50) << "Name" << "| " << std::setw(12)
                  << "Rate/(1$)" << "\n";
        std::cout << std::setw(8) << "" << line << "\n\n";
        for (Currency currency : currencies) {
            print_currency_line(currency);
            std::cout << std::endl;
        }
        std::cout << std::setw(8) << "" << line << "\n\n";
    }

   private:
    static void print_currency_line(Currency currency) {
        std::cout << std::setw(10) << std::right << "| " << std::setw(35)
                  << std::left << currency.getCountry() << "| " << std::setw(8)
                  << currency.getCurrencyCode() << "| " << std::setw(50)
                  << currency.getCurrencyName() << "| " << std::setw(12)
                  << currency.getRate();
    }
};

#endif  // CLASS_CURRENCIES_LIST_SCREEN_HPP