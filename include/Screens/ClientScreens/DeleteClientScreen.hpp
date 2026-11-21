#ifndef CLASS_DELETE_CLIENT_SCREEN_HPP
#define CLASS_DELETE_CLIENT_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Core/User.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"

class DeleteClientScreen : protected Screen {
   public:
    static void show_delete_client_screen() {
        draw_screen_header("Delete Client Screen.");
        if (!has_permission(User::Permissions::DeleteClient)) {
            return;
        }

        std::string account_number = ScreenHelper::read_object_id<BankClient>(
            "Account Number", true, BankClient::find);
        if (account_number.empty()) {
            return;
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
        std::map<std::string, std::string> rows;

        rows.insert({"Full Name", client.getFullName()});
        rows.insert({"Email", client.getEmail()});
        rows.insert({"Phone", client.getPhone()});
        rows.insert({"Account Number", client.getAccountNumber()});
        rows.insert({"Pin Code", client.getPinCode()});
        rows.insert(
            {"Balance", ScreenHelper::format_number(client.getBalance())});

        ScreenHelper::print_object_card("Client Card", rows);
    }
};

#endif  // CLASS_DELETE_CLIENT_SCREEN_HPP