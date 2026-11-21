#ifndef CLASS_CLIENTS_LIST_SCREEN_HPP
#define CLASS_CLIENTS_LIST_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <vector>

#include "../../Core/BankClient.hpp"
#include "../../Core/User.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"

class ClientsListScreen : protected Screen {
   public:
    static void show_clients_list() {
        std::vector<BankClient> clients =
            BankClient::get_clients_list().response;
        std::string title = "Clients List Screen.";
        std::string subtitle =
            "(" + std::to_string(clients.size()) + ") Client(s).";

        draw_screen_header(title, subtitle);
        if (!has_permission(User::Permissions::ListClients)) {
            return;
        }

        Table table{title, subtitle};
        table.setAlignment(11);

        table.add_column("Account Number", 15, Table::Align::Center);
        table.add_column("Full Name", 20, Table::Align::Center);
        table.add_column("Phone", 12, Table::Align::Center);
        table.add_column("Email", 20, Table::Align::Center);
        table.add_column("Pin Code", 9, Table::Align::Center);
        table.add_column("Balance", 14, Table::Align::Center);

        if (clients.size() == 0) {
            table.panel(
                {Color::bright_red("No Clients Available In The System!")}, 95,
                Table::Align::Center, true);
        } else {
            for (BankClient client : clients) {
                table.add_row({
                    " " + client.getAccountNumber(),
                    " " + client.getFullName(),
                    " " + client.getPhone(),
                    " " + client.getEmail(),
                    " " + client.getPinCode(),
                    " " + ScreenHelper::format_number(client.getBalance()),
                });
            }
            table.print_table();
        }
    }

   private:
};

#endif  // CLASS_CLIENTS_LIST_SCREEN_HPP