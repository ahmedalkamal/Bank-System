#ifndef CLASS_FIND_CLIENT_SCREEN_HPP
#define CLASS_FIND_CLIENT_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Core/User.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class FindClientScreen : protected Screen {
   public:
    static void show_find_client_screen() {
        if (!has_permission(User::Permissions::FindClient)) {
            return;
        }
        draw_screen_header("Find Client Screen.");
        std::string account_number = "";
        std::cout << "\nPlease Enter Account Number: ";
        account_number = InputValidate::read_template<std::string>();
        // while (!BankClient::is_client_exist(account_number)) {
        //     std::cout << "\nAccount Number is not found, choose another one:
        //     "; account_number = InputValidate::read_template<std::string>();
        // }
        BankClient client = BankClient::find(account_number);
        if (!client.is_empty()) {
            std::cout << "\nClient found ;)" << std::endl;
        } else {
            std::cout << "\nClient was not found :(" << std::endl;
        }
        print_client_card(client);
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
};

#endif  // CLASS_FIND_CLIENT_SCREEN_HPP