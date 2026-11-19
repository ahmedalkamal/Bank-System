#ifndef CLASS_UPDATE_CLIENT_SCREEN_HPP
#define CLASS_UPDATE_CLIENT_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Core/User.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class UpdateClientScreen : protected Screen {
   public:
    static void show_update_client_screen() {
        draw_screen_header("Update Client Screen");
        if (!has_permission(User::Permissions::UpdateClients)) {
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
        client.setFirstName(InputValidate::read_template<std::string>(
            "[+] Please Enter Firs Name: "));

        std::cout << std::setw(30) << std::left << "";
        client.setLastName(InputValidate::read_template<std::string>(
            "[+] Please Enter Last Name: "));

        std::cout << std::setw(30) << std::left << "";
        client.setEmail(InputValidate::read_template<std::string>(
            "[+] Please Enter Email: "));

        std::cout << std::setw(30) << std::left << "";
        client.setPhone(InputValidate::read_template<std::string>(
            "[+] Please Enter Phone: "));

        std::cout << std::setw(30) << std::left << "";
        client.setPinCode(InputValidate::read_template<std::string>(
            "[+] Please Enter Pin Code: "));

        // client.balance = read_balance();
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

#endif  // CLASS_UPDATE_CLIENT_SCREEN_HPP