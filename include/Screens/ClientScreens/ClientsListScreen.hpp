#ifndef CLASS_CLIENTS_LIST_SCREEN_HPP
#define CLASS_CLIENTS_LIST_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <vector>

#include "../../Core/BankClient.hpp"
#include "../../Core/User.hpp"
#include "../Screen.hpp"

class ClientsListScreen : protected Screen {
   public:
    static void show_clients_list() {
        if (!has_permission(User::Permissions::ListClients)) {
            return;
        }
        std::vector<BankClient> clients = BankClient::get_clients_list();
        std::string title = "Clients List Screen.";
        std::string subtitle =
            "(" + std::to_string(clients.size()) + ") Client(s).";
        draw_screen_header(title, subtitle, 27);

        std::cout
            << "\n"
            << std::setw(8) << ""
            << "__________________________________________________________"
               "______________________________________\n\n";

        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(15)
                  << "Accout Number";
        std::cout << "| " << std::left << std::setw(20) << "Client Name";
        std::cout << "| " << std::left << std::setw(12) << "Phone";
        std::cout << "| " << std::left << std::setw(20) << "Email";
        std::cout << "| " << std::left << std::setw(10) << "Pin Code";
        std::cout << "| " << std::left << std::setw(12) << "Balance";
        std::cout
            << "\n"
            << std::setw(8) << ""
            << "__________________________________________________________"
               "______________________________________\n\n";

        if (clients.size() == 0) {
            std::cout << "No Clients Available In The System!";
        } else {
            for (BankClient client : clients) {
                print_client_record_line(client);
                std::cout << std::endl;
            }
        }
        std::cout
            << "\n"
            << std::setw(8) << ""
            << "__________________________________________________________"
               "______________________________________\n"
            << std::endl;
    }

   private:
    static void print_client_record_line(BankClient& client) {
        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(15)
                  << client.getAccountNumber();
        std::cout << "| " << std::setw(20) << std::left << client.getFullName();
        std::cout << "| " << std::setw(12) << std::left << client.getPhone();
        std::cout << "| " << std::setw(20) << std::left << client.getEmail();
        std::cout << "| " << std::setw(10) << std::left << client.getPinCode();
        std::cout << "| " << std::setw(12) << std::left << client.getBalance();
    }
};

#endif  // CLASS_CLIENTS_LIST_SCREEN_HPP