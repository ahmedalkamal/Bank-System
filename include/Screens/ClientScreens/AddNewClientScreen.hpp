#ifndef CLASS_ADD_NEW_CLIENT_SCREEN_HPP
#define CLASS_ADD_NEW_CLIENT_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Core/User.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class AddNewClientScreen : protected Screen {
   public:
    static void show_add_new_client_screen() {
        if (!has_permission(User::Permissions::AddNewClient)) {
            return;
        }
        draw_screen_header("Add New Client Screen");
        std::string account_number = "";

        account_number = InputValidate::read_template<std::string>(
            "\nPlease Enter Account Number: ");
        while (BankClient::is_client_exist(account_number)) {
            account_number = InputValidate::read_template<std::string>(
                "\nAccount Number is already used, choose another one: ");
        }
        BankClient new_client = BankClient::get_addnew_object(account_number);
        read_client_info(new_client);
        BankClient::SaveStatus status;
        status = new_client.save();
        switch (status) {
            case BankClient::SaveStatus::Successful:
                std::cout << "\nAccount Added Successfully ;)\n";
                print_client_card(new_client);
                break;
            case BankClient::SaveStatus::FailedEmpty:
                std::cout
                    << "\nError account was not saved because it's empty!";
                break;
            case BankClient::SaveStatus::FailedAccountExist:
                std::cout << "\nError account was not saved because it's "
                             "account number is used!";
                break;
        }
    }

   private:
    static void read_client_info(BankClient& client) {
        client.first_name =
            InputValidate::read_template<std::string>("\nEnter Firs Name: ");
        client.last_name =
            InputValidate::read_template<std::string>("\nEnter Last Name: ");
        client.email =
            InputValidate::read_template<std::string>("\nEnter Email: ");
        client.phone =
            InputValidate::read_template<std::string>("\nEnter Phone: ");
        client.pin_code =
            InputValidate::read_template<std::string>("\nEnter Pin Code: ");
        // std::cout << "\nEnter Balance: ";
        client.balance = InputValidate::input<float>("\nEnter Balance: ", "");
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

#endif  // CLASS_ADD_NEW_CLIENT_SCREEN_HPP