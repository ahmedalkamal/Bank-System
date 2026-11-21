#ifndef CLASS_ADD_NEW_CLIENT_SCREEN_HPP
#define CLASS_ADD_NEW_CLIENT_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Core/User.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../../Utils/Table.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"

class AddNewClientScreen : protected Screen {
   public:
    static void show_add_new_client_screen() {
        draw_screen_header("Add New Client Screen");
        if (!has_permission(User::Permissions::AddNewClient)) {
            return;
        }

        std::string account_number = ScreenHelper::read_object_id<BankClient>(
            "Account Number", false, BankClient::find);
        if (account_number.empty()) {
            return;
        }

        BankClient new_client = BankClient::get_addnew_object(account_number);
        read_client_info(new_client);
        BankClient::SaveStatus status;
        status = new_client.save();
        switch (status) {
            case BankClient::SaveStatus::Successful:
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[#] " + Color::bright_green(
                                          "Account Added Successfully.\n")
                          << std::endl;

                print_client_card(new_client);
                break;
            case BankClient::SaveStatus::FailedEmpty:
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[!] " + Color::bright_red(
                                          "Error account was not saved "
                                          "because it's empty!\n");
                break;
            case BankClient::SaveStatus::FailedAccountExist:
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[!] " + Color::bright_red(
                                          "Error account was not saved because "
                                          "account number is used!\n");
                break;
        }
    }

   private:
    static float read_balance() {
        std::cout << std::setw(30) << std::left << "";
        float balance = InputValidate::input<float>(
            "[+] Please Enter Balance: ",
            Color::bright_red(std::string(30, ' ') +
                              "[+] Please Enter Balance: "));
        if (balance < 0) {
            return 0;
        }
        return balance;
    }

    static void read_client_info(BankClient& client) {
        ScreenHelper::read_person_info<BankClient>(client);

        std::cout << std::setw(30) << std::left << "";
        client.setPinCode(InputValidate::read_template<std::string>(
            "[+] Please Enter Pin Code: "));

        client.setBalance(read_balance());
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

#endif  // CLASS_ADD_NEW_CLIENT_SCREEN_HPP