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
            get_exist_client("Please enter account number of sender: ");
        print_clietn_card(sender);
        BankClient recipient =
            get_exist_client("Please enter account number of recipient: ");
        print_clietn_card(recipient);

        float amount = read_transfer_amount(sender);
        char answer = InputValidate::read_template<char>(
            "\nAre ypu sure you want to perform this operation ? ");
        if (std::tolower(answer) == 'y') {
            if (sender.transfer(amount, recipient, CurrentUser.getUserName())) {
                std::cout << "\nTransfer done successfully!\n";
                print_clietn_card(sender);
                print_clietn_card(recipient);
            } else {
                std::cout << "\nTransfer failed!\n";
            }
        }
    }

   private:
    static void print_clietn_card(BankClient client) {
        std::cout << "\nClient Card: \n"
                     "-----------------------------\n"
                     "Full Name       : "
                  << client.full_name
                  << "\n"
                     "Account number  : "
                  << client.account_number
                  << "\n"
                     "Balance         : "
                  << client.balance
                  << "\n"
                     "-----------------------------\n"
                  << std::endl;
    }

    static float read_transfer_amount(const BankClient& sender) {
        float amount =
            InputValidate::input<float>("Enter Transfer Amount: ", "");
        bool valid = InputValidate::in_range<float>(amount, 0, sender.balance);

        while (!valid) {
            std::cout << "Amount Exceeds the avaliable Balance!\n";
            amount = InputValidate::input<float>("Enter Transfer Amount: ", "");
            valid = InputValidate::in_range<float>(amount, 0, sender.balance);
        }
        return amount;
    }

    static BankClient get_exist_client(std::string message) {
        std::cout << message;

        std::string account_number =
            InputValidate::read_template<std::string>();
        while (!BankClient::is_client_exist(account_number)) {
            std::cout << "\nAccount number not found!, enter again: ";
            account_number = InputValidate::read_template<std::string>();
        }
        return BankClient::find(account_number);
    }
};

#endif  // CLASS_TRANSFER_SCREEN_HPP