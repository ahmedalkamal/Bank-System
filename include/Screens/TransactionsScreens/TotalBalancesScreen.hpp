#ifndef CLASS_TOTAL_BALANCES_SCREEN_HPP
#define CLASS_TOTAL_BALANCES_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Utils/NumberToWords.hpp"
#include "../../Utils/Util.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"

class TotalBalancesScreen : protected Screen {
   public:
    static void show_total_balances() {
        std::vector<BankClient> clients =
            BankClient::get_clients_list().response;
        std::string title = "Balances List Screen.";
        std::string subtitle =
            "(" + std::to_string(clients.size()) + ") Client(s).";

        draw_screen_header(title, subtitle);

        Table table{title, subtitle};
        table.setAlignment(11);

        table.add_column(" Account Number", 15, Table::Align::Center);
        table.add_column(" Client Name", 40, Table::Align::Center);
        table.add_column(" Balance", 38, Table::Align::Center);

        double TotalBalances = BankClient::get_total_balances().response;

        if (clients.size() == 0) {
            table.panel(
                {Color::bright_red("No Clients Available In The System!")}, 95,
                Table::Align::Center, true);
        }

        else {
            for (BankClient client : clients) {
                table.add_row({
                    " " + client.getAccountNumber(),
                    " " + client.getFullName(),
                    " " + ScreenHelper::format_number(client.getBalance()),
                });
            }
            table.print_table();
        }

        table.panel({"Total Balances = " + std::to_string(TotalBalances),
                     NumberToWords::conver_number_to_words(TotalBalances)},
                    95, Table::Align::Center, true);
    }

   private:
};

#endif  // CLASS_TOTAL_BALANCES_SCREEN_HPP