#ifndef CLASS_DELETE_CLIENT_SCREEN_HPP
#define CLASS_DELETE_CLIENT_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Core/User.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class DeleteClientScreen : protected Screen {
   public:
    static void show_delete_client_screen() {
        draw_screen_header("Delete Client Screen.");
        if (!has_permission(User::Permissions::DeleteClient)) {
            return;
        }

        std::string account_number = "";

        std::cout << std::setw(30) << std::left << "";
        std::cout << "[+] Please Enter Account Number: ";
        account_number = InputValidate::read_template<std::string>();
        while (!BankClient::is_client_exist(account_number)) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            account_number = InputValidate::read_template<std::string>(
                "[+] " + Color::bright_yellow("Account Number is not found") +
                ", choose another one: ");
        }
        BankClient client = BankClient::find(account_number).response;
        print_client_card(client);

        char answer = 'n';
        std::cout << "\n" << std::setw(30) << std::left << "";
        std::cout << "[+] Are you sure want to delete this client Y/N : ";
        std::cin >> answer;

        if (std::tolower(answer) == 'y') {
            if (client.remove().response) {
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[#] " + Color::bright_green(
                                          "Client Deleted Successfully.\n");
                // print_client_card(client);
            } else {
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[!] " + Color::bright_red(
                                          "Error Client was not Deleted!\n");
            }
        }
    }

   private:
    static void print_client_card(BankClient client) {
        Table table{"Client Card."};
        table.add_column("", 16);
        table.add_column(" info ", 45, Table::Align::Center);

        table.add_row({"Full Name     ", client.getFullName()},
                      Table::Align::Center);
        table.add_row({"Email         ", client.getEmail()},
                      Table::Align::Center);
        table.add_row({"Phone         ", client.getPhone()},
                      Table::Align::Center);
        table.add_row({"Account Number", client.getAccountNumber()},
                      Table::Align::Center);
        table.add_row({"Pin Code      ", client.getPinCode()},
                      Table::Align::Center);
        table.add_row({"Balance       ", std::to_string(client.getBalance())},
                      Table::Align::Center);

        table.setAlignment(25);
        table.print_table();
    }
};

#endif  // CLASS_DELETE_CLIENT_SCREEN_HPP