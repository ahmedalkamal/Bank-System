#ifndef CLASS_UPDATE_CLIENT_SCREEN_HPP
#define CLASS_UPDATE_CLIENT_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Core/User.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"

class UpdateClientScreen : protected Screen {
   public:
    static void show_update_client_screen() {
        draw_screen_header("Update Client Screen");
        if (!has_permission(User::Permissions::UpdateClients)) {
            return;
        }

        std::string account_number = ScreenHelper::read_object_id<BankClient>(
            "Account Number", true, BankClient::find);
        if (account_number.empty()) {
            return;
        }

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
        std::cout << "[+] Are you sure you want to update this client Y/N : ";
        std::cin >> answer;
        read_client_info(client);

        if (std::tolower(answer) == 'y') {
            switch (client.save()) {
                case BankClient::SaveStatus::Successful:
                    std::cout << "\n" << std::setw(30) << std::left << "";
                    std::cout
                        << "[#] " + Color::bright_green(
                                        "Account Updated Successfully.\n");
                    print_client_card(client);
                    break;
                case BankClient::SaveStatus::FailedEmpty:
                    std::cout << "\n" << std::setw(30) << std::left << "";
                    std::cout << "[!] " + Color::bright_red(
                                              "Error account was not updated "
                                              "because it's empty!");
                    break;
            }
        }
    }

   private:
    static void read_client_info(BankClient& client) {
        ScreenHelper::read_person_info<BankClient>(client);

        std::cout << std::setw(30) << std::left << "";
        client.setPinCode(InputValidate::read_template<std::string>(
            "[+] Please Enter Pin Code: "));
    }

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

#endif  // CLASS_UPDATE_CLIENT_SCREEN_HPP