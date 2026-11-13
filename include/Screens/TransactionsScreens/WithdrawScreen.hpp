#ifndef CLASS_WITHDRAW_SCREEN_HPP
#define CLASS_WITHDRAW_SCREEN_HPP

#include <iostream>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class WithdrawScreen : protected Screen {
   public:
    static void show_withdraw_screen() {
        draw_screen_header("Withdraw Screen.");
        std::string account_number = read_account_number();
        while (!BankClient::is_client_exist(account_number)) {
            std::cout << "\nClient with [" + account_number +
                             "] does not exist.\n";
            account_number = read_account_number();
        }
        BankClient client = BankClient::find(account_number);
        print_client_card(client);

        float amount = 0;
        std::string message = "\nPlease enter withdraw amount: ";
        amount = InputValidate::input<float>(message, message);

        char answer = 'n';
        std::cout << "\nAre you sure you want to perform this transactions? ";
        std::cin >> answer;

        if (std::tolower(answer) == 'y') {
            if (client.withdraw(amount)) {
                std::cout << "\nAmount Withdraw Successfully.\n";
                std::cout << "\nNew Balance is : " << client.getBalance()
                          << std::endl;
            } else {
                std::cout << "\nCannot Withdraw, Insuffecient Balance!\n";
                std::cout << "\nAmount to withdraw is:" << amount;
                std::cout << "\nYour Balance is: " << client.getBalance()
                          << std::endl;
            }
        } else {
            std::cout << "\nOperation was cancelled.\n";
        }
    }

   private:
    static void print_client_card(BankClient client) {
        std::cout << "Client Card: \n";
        std::cout << std::string(40, '_') << std::endl;
        std::cout << "Full Name      : "
                  << client.getFirstName() + " " + client.getLastName()
                  << std::endl;
        std::cout << "Email          : " << client.getEmail() << std::endl;
        std::cout << "Phone          : " << client.getPhone() << std::endl;
        std::cout << "Account number : " << client.getAccountNumber()
                  << std::endl;
        std::cout << "Pin Code       : " << client.getPinCode() << std::endl;
        std::cout << "Balance        : " << client.getBalance() << std::endl;
        std::cout << std::string(40, '_') << std::endl;
    }

    static std::string read_account_number() {
        std::string account_number = "";
        std::cout << "\nPlease enter account number: ";
        std::cin >> account_number;
        return account_number;
    }
};

#endif  // CLASS_WITHDRAW_SCREEN_HPP