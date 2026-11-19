#ifndef CLASS_DEPOSIT_SCREEN_HPP
#define CLASS_DEPOSIT_SCREEN_HPP

#include <iostream>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class DepositScreen : protected Screen {
   public:
    static void show_deposit_screen() {
        draw_screen_header("Deposit Screen.");

        std::string account_number = read_account_number();

        while (!BankClient::is_client_exist(account_number)) {
            std::cout << std::setw(30) << std::left << "";
            std::cout << "[!]" + Color::bright_yellow(
                                     "Client with [" +
                                     Color::bright_red(account_number) +
                                     "] does not exist.\n");
            account_number = read_account_number();
        }
        BankClient client = BankClient::find(account_number).response;
        print_client_card(client);

        float amount = 0;
        std::string message =
            std::string(30, ' ') + "[+] Please enter deposit amount: ";
        amount = InputValidate::input<float>(message, message);

        char answer = 'n';
        std::cout << std::setw(30) << std::left << "";
        std::cout << "[?] Are you sure you want to perform this transactions? ";
        std::cin >> answer;

        if (std::tolower(answer) == 'y') {
            if (client.deposit(amount).response) {
                std::cout << std::setw(30) << std::left << "";
                std::cout << "[#] " + Color::bright_green(
                                          "Amount Deposit Successfully.\n");

                std::cout << std::setw(30) << std::left << "";
                std::cout << "[#] New Balance is : " << client.getBalance()
                          << std::endl;
            } else {
                std::cout << std::setw(30) << std::left << "";
                std::cout << "[!] " +
                                 Color::bright_red(
                                     "Cannot Deposit with negative balance!\n");
                std::cout << std::setw(30) << std::left << "";
                std::cout << "[!] " +
                                 Color::bright_yellow("Amount to deposit is:")
                          << amount;
            }
        } else {
            std::cout << std::setw(30) << std::left << "";
            std::cout << "[#] Operation was cancelled.\n";
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

    static std::string read_account_number() {
        std::string account_number = "";
        std::cout << std::setw(30) << std::left << "";
        std::cout << "[+] Please enter account number: ";
        std::cin >> account_number;
        return account_number;
    }
};

#endif  // CLASS_DEPOSIT_SCREEN_HPP