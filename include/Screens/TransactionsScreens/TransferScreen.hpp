#ifndef CLASS_TRANSFER_SCREEN_HPP
#define CLASS_TRANSFER_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"

class TransferScreen : protected Screen {
   public:
    static void show_transfer_screen() {
        draw_screen_header("Transfer Screen.");

        std::string saccount_number = ScreenHelper::read_object_id(
            "Account Number (sender)", true, BankClient::find);
        if (saccount_number.empty()) return;
        std::string raccount_number = ScreenHelper::read_object_id(
            "Account Number (recipent)", true, BankClient::find);
        if (raccount_number.empty()) return;

        if (saccount_number == raccount_number) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[!] " + Color::bright_red(
                                      "Cannot transfer to yourself!\n");

            return;
        }

        std::cout << std::endl;
        BankClient sender = BankClient::find(saccount_number).response;
        print_client_card(sender, "Sender Card");

        std::cout << std::endl;
        BankClient recipient = BankClient::find(saccount_number).response;
        print_client_card(recipient, "Recipient Card");

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
                print_client_card(sender, "Sender Card");
                print_client_card(recipient, "Recipient Card");

            } else {
                std::cout << std::setw(30) << std::left << "";
                std::cout << "[!] " + Color::bright_red("Transferss failed!\n");
            }
        }
    }

   private:
    static void print_client_card(BankClient client, std::string title) {
        std::map<std::string, std::string> rows;

        rows.insert({"Full Name", client.getFullName()});
        rows.insert({"Account Number", client.getAccountNumber()});
        rows.insert(
            {"Balance", ScreenHelper::format_number(client.getBalance())});

        ScreenHelper::print_object_card(title, rows);
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
};

#endif  // CLASS_TRANSFER_SCREEN_HPP