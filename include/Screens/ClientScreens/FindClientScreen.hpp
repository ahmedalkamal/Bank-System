#ifndef CLASS_FIND_CLIENT_SCREEN_HPP
#define CLASS_FIND_CLIENT_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Core/User.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class FindClientScreen : protected Screen {
   public:
    static void show_find_client_screen() {
        draw_screen_header("Find Client Screen.");
        if (!has_permission(User::Permissions::FindClient)) {
            return;
        }

        std::string account_number = "";

        std::cout << std::setw(30) << std::left << "";
        std::cout << "[+] Please Enter Account Number: ";
        account_number = InputValidate::read_template<std::string>();
        // while (!BankClient::is_client_exist(account_number)) {
        //     std::cout << "\n" << std::setw(30) << std::left << "";
        //     account_number = InputValidate::read_template<std::string>(
        //         "[+] " +
        //         Color::bright_yellow("Account Number is not found") +
        //         ", choose another one: ");
        // }

        BankClient client = BankClient::find(account_number).response;
        if (!client.is_empty()) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[#] " + Color::bright_green("Client found.")
                      << std::endl;
            print_client_card(client);
        } else {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[!] " + Color::bright_red("Client was not found!")
                      << std::endl;
        }
    }

   private:
    static void print_client_card(BankClient client) {
        Table table{"Client Card."};
        table.add_column("", 16);
        table.add_column(" info ", 45, Table::Align::Center);

        table.add_row({" Full Name     ", " " + client.getFullName()});
        table.add_row({" Email         ", " " + client.getEmail()});
        table.add_row({" Phone         ", " " + client.getPhone()});
        table.add_row({" Account Number", " " + client.getAccountNumber()});
        table.add_row({" Pin Code      ", " " + client.getPinCode()});
        table.add_row(
            {" Balance       ", " " + std::to_string(client.getBalance())});

        table.setAlignment(25);
        table.print_table();
    }
};

#endif  // CLASS_FIND_CLIENT_SCREEN_HPP