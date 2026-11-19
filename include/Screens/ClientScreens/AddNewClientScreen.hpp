#ifndef CLASS_ADD_NEW_CLIENT_SCREEN_HPP
#define CLASS_ADD_NEW_CLIENT_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Core/User.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../../Utils/Table.hpp"
#include "../Screen.hpp"

class AddNewClientScreen : protected Screen {
   public:
    static void show_add_new_client_screen() {
        draw_screen_header("Add New Client Screen");
        if (!has_permission(User::Permissions::AddNewClient)) {
            return;
        }

        std::string account_number = "";

        std::cout << std::setw(30) << std::left << "";
        account_number = InputValidate::read_template<std::string>(
            "[+] Please Enter Account Number: ");
        while (BankClient::is_client_exist(account_number)) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            account_number = InputValidate::read_template<std::string>(
                "[+] " +
                Color::bright_yellow("Account Number is already used") +
                ", choose another one: ");
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
        std::cout << std::setw(30) << std::left << "";
        client.first_name = InputValidate::read_template<std::string>(
            "[+] Please Enter Firs Name: ");

        std::cout << std::setw(30) << std::left << "";
        client.last_name = InputValidate::read_template<std::string>(
            "[+] Please Enter Last Name: ");

        std::cout << std::setw(30) << std::left << "";
        client.email = InputValidate::read_template<std::string>(
            "[+] Please Enter Email: ");

        std::cout << std::setw(30) << std::left << "";
        client.phone = InputValidate::read_template<std::string>(
            "[+] Please Enter Phone: ");

        std::cout << std::setw(30) << std::left << "";
        client.pin_code = InputValidate::read_template<std::string>(
            "[+] Please Enter Pin Code: ");
        // std::cout << "[+] Please Enter Balance: ";

        client.balance = read_balance();
    }

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

#endif  // CLASS_ADD_NEW_CLIENT_SCREEN_HPP