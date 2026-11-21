#ifndef CLASS_WITHDRAW_SCREEN_HPP
#define CLASS_WITHDRAW_SCREEN_HPP

#include <iostream>
#include <map>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"

class WithdrawScreen : protected Screen {
   public:
    static void show_withdraw_screen() {
        draw_screen_header("Withdraw Screen.");

        std::string account_number = ScreenHelper::read_object_id(
            "Account Number", true, BankClient::find);
        if (account_number.empty()) return;

        BankClient client = BankClient::find(account_number).response;
        print_client_card(client);

        float amount = 0;
        std::string message =
            std::string(30, ' ') + "[+] Please enter withdraw amount: ";
        amount = InputValidate::input<float>(message, message);

        char answer = 'n';
        std::cout << std::setw(30) << std::left << "";
        std::cout << "[?] Are you sure you want to perform this transactions? ";
        std::cin >> answer;

        if (std::tolower(answer) != 'y') {
            std::cout << std::setw(30) << std::left << "";
            std::cout << "[#] Operation was cancelled.\n";
            return;
        }

        if (client.withdraw(amount).response) {
            std::cout << std::setw(30) << std::left << "";
            std::cout << "[#] " + Color::bright_green(
                                      "Amount Withdraw Successfully.\n");

            std::cout << std::setw(30) << std::left << "";
            std::cout << "[#] New Balance is : " << client.getBalance()
                      << std::endl;
        } else {
            std::cout << std::setw(30) << std::left << "";
            std::cout << "[!] " +
                             Color::bright_red(
                                 "Cannot Withdraw, Insuffecient Balance!\n");
            std::cout << std::setw(30) << std::left << "";
            std::cout << "[!] " + Color::bright_yellow("Amount to withdraw is:")
                      << amount;
            std::cout << std::setw(30) << std::left << "";
            std::cout << "[!] " + Color::bright_yellow("Your Balance is: ")
                      << client.getBalance() << std::endl;
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

#endif  // CLASS_WITHDRAW_SCREEN_HPP