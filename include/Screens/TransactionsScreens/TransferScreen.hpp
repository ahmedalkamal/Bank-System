#ifndef CLASS_TRANSFER_SCREEN_HPP
#define CLASS_TRANSFER_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class TransferScreen : protected Screen {
   public:
    static void show_transfer_screen() {
        draw_screen_header("Transfer Screen.");

        BankClient sender =
            get_exist_client("[+] Please enter account number of sender: ");
        print_client_card(sender, "sender card");
        std::cout << std::endl;
        BankClient recipient =
            get_exist_client("[+] Please enter account number of recipient: ");
        print_client_card(recipient, "recipient card");

        if (sender.getAccountNumber() == recipient.getAccountNumber()) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[!] " + Color::bright_red(
                                      "Cannot transfer to yourself!\n");

            return;
        }

        float amount = read_transfer_amount(sender);
        std::cout << std::setw(30) << std::left << "";
        char answer = InputValidate::read_template<char>(
            "[?] Are ypu sure you want to perform this operation ? ");
        if (std::tolower(answer) == 'y') {
            if (sender.transfer(amount, recipient, CurrentUser.getUserName())
                    .response) {
                std::cout << std::setw(30) << std::left << "";
                std::cout << "[+] " + Color::bright_green(
                                          "Transfer done successfully.\n");
                print_client_card(sender, "sender card");
                print_client_card(recipient, "recipient card");

            } else {
                std::cout << std::setw(30) << std::left << "";
                std::cout << "[!] " + Color::bright_red("Transferss failed!\n");
            }
        }
    }

   private:
    static void print_client_card(BankClient client, std::string title) {
        Table table{"Client Card."};
        table.add_column("", 16);
        table.add_column(" " + title, 45, Table::Align::Center);

        table.add_row({" Full Name     ", " " + client.getFullName()});
        table.add_row({" Account Number", " " + client.getAccountNumber()});
        table.add_row(
            {" Balance       ", " " + std::to_string(client.getBalance())});

        table.setAlignment(25);
        table.print_table();
    }

    static float read_transfer_amount(BankClient sender) {
        std::string message = std::string(30, ' ');
        message += "[+] Enter Transfer Amount: ";

        float amount = InputValidate::input<float>(message, message);
        bool valid =
            InputValidate::in_range<float>(amount, 0, sender.getBalance());

        while (!valid) {
            std::cout << std::setw(30) << std::left << "";
            std::cout << "[!] " +
                             Color::bright_red(
                                 "Amount Exceeds the avaliable Balance!\n");

            amount = InputValidate::input<float>(message, message);
            valid =
                InputValidate::in_range<float>(amount, 0, sender.getBalance());
        }
        return amount;
    }

    static BankClient get_exist_client(std::string message) {
        std::cout << std::setw(30) << std::left << "";
        std::cout << message;

        std::string account_number =
            InputValidate::read_template<std::string>();
        while (!BankClient::is_client_exist(account_number)) {
            std::cout << std::setw(30) << std::left << "";
            std::cout << "[!] " +
                             Color::bright_yellow("Account number not found!") +
                             ", enter again: ";
            account_number = InputValidate::read_template<std::string>();
        }
        return BankClient::find(account_number).response;
    }
};

#endif  // CLASS_TRANSFER_SCREEN_HPP