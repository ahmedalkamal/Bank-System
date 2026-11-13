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
        if (!has_permission(User::Permissions::UpdateClients)) {
            return;
        }
        draw_screen_header("Update Client Screen");
        std::string account_number = "";
        std::cout << "\nPlease Enter Account Number: ";
        account_number = InputValidate::read_template<std::string>();
        while (!BankClient::is_client_exist(account_number)) {
            std::cout << "\nAccount Number is not found, choose another one: ";
            account_number = InputValidate::read_template<std::string>();
        }
        BankClient client = BankClient::find(account_number);
        print_client_card(client);

        char answer = 'n';
        std::cout << "\nAre you sure you want to update this client Y/N : ";
        std::cin >> answer;

        if (std::tolower(answer) == 'y') {
            std::cout << "\nUpdate Clinet Info: ";
            std::cout << "\n-------------------------------------\n";
            read_client_info(client);

            switch (client.save()) {
                case BankClient::SaveStatus::Successful:
                    std::cout << "\nAccount Added Successfully ;)\n";
                    print_client_card(client);
                    break;
                case BankClient::SaveStatus::FailedEmpty:
                    std::cout
                        << "\nError account was not saved because it's empty!";
                    break;
            }
        }
    }

   private:
    static void read_client_info(BankClient& client) {
        std::cout << "\nEnter Firs Name: ";
        client.first_name = InputValidate::read_template<std::string>();
        std::cout << "\nEnter Last Name: ";
        client.last_name = InputValidate::read_template<std::string>();
        std::cout << "\nEnter Email: ";
        client.email = InputValidate::read_template<std::string>();
        std::cout << "\nEnter Phone: ";
        client.phone = InputValidate::read_template<std::string>();
        std::cout << "\nEnter Pin Code: ";
        client.pin_code = InputValidate::read_template<std::string>();
        // std::cout << "\nEnter Balance: ";
        client.balance = InputValidate::input<float>("\nEnter Balance: ",
                                                     "Invalid Enter again : ");
    }

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

#endif  // CLASS_UPDATE_CLIENT_SCREEN_HPP