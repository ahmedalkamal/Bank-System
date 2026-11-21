#ifndef CLASS_FIND_CLIENT_SCREEN_HPP
#define CLASS_FIND_CLIENT_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Core/User.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"

class FindClientScreen : protected Screen {
   public:
    static void show_find_client_screen() {
        draw_screen_header("Find Client Screen.");
        if (!has_permission(User::Permissions::FindClient)) {
            return;
        }

        std::string account_number = ScreenHelper::read_object_id<BankClient>(
            "Account Number", true, BankClient::find);
        if (account_number.empty()) {
            return;
        }

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

#endif  // CLASS_FIND_CLIENT_SCREEN_HPP