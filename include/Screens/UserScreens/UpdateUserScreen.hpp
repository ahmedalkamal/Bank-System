#ifndef CLASS_UPDATE_USER_SCREEN_HPP
#define CLASS_UPDATE_USER_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/User.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class UpdateUserScreen : protected Screen {
   public:
    static void show_update_user_screen() {
        draw_screen_header("Update User Screen");
        std::string username = "";
        std::cout << "\nPlease Enter Username: ";
        username = InputValidate::read_template<std::string>();
        while (!User::is_user_exist(username)) {
            std::cout << "\nUsername is not found, choose another one: ";
            username = InputValidate::read_template<std::string>();
        }
        User user = User::find(username);
        print_user_card(user);

        char answer = 'n';
        std::cout << "\nAre you sure you want to update this user Y/N : ";
        std::cin >> answer;

        if (std::tolower(answer) == 'y') {
            std::cout << "\nUpdate User Info: ";
            std::cout << "\n-------------------------------------\n";
            read_user_info(user);

            switch (user.save()) {
                case User::SaveStatus::Successful:
                    std::cout << "\nUser Updated Successfully ;)\n";
                    print_user_card(user);
                    break;
                case User::SaveStatus::FailedEmpty:
                    std::cout
                        << "\nError user was not saved because it's empty!";
                    break;
            }
        }
    }

   private:
    static void read_user_info(User& user) {
        std::cout << "\nEnter First Name : ";
        user.first_name = InputValidate::read_template<std::string>();
        std::cout << "\nEnter Last Name  : ";
        user.last_name = InputValidate::read_template<std::string>();
        std::cout << "\nEnter Email      : ";
        user.email = InputValidate::read_template<std::string>();
        std::cout << "\nEnter Phone      : ";
        user.phone = InputValidate::read_template<std::string>();
        std::cout << "\nEnter Password   : ";
        user.password = InputValidate::read_template<std::string>();
        std::cout << "\nEnter Permissions : ";
        user.permissions = read_permissions_to_set();
    }

    static void print_user_card(const User& user) {
        std::cout << "\nUser Card"
                     "\n_________________________________________\n"
                  << std::endl;
        std::cout << "Full Name   : " << user.full_name << "\n"
                  << "Email       : " << user.email << "\n"
                  << "Phone       : " << user.phone << "\n"
                  << "User Name   : " << user.username << "\n"
                  << "Password    : " << user.password << "\n"
                  << "Permissions :  " << user.permissions;
        std::cout << "\n_________________________________________" << std::endl;
    }

    static short read_permissions_to_set() {
        short permissions = 0;
        // char answer = 'n';

        char answer = InputValidate::read_template<char>(
            "\n [?] Do you want to give Full access           y/n ? ");
        if (std::tolower(answer) == 'y')
            return (short)User::Permissions::FullAccess;

        answer = InputValidate::read_template<char>(
            " [?] Give access to Show clients list            y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::ListClients;

        answer = InputValidate::read_template<char>(
            " [?] Give access to Add new clients              y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::AddNewClient;

        answer = InputValidate::read_template<char>(
            " [?] Give access to Delete client                y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::DeleteClient;

        answer = InputValidate::read_template<char>(
            " [?] Give access to Update clients               y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::UpdateClients;

        answer = InputValidate::read_template<char>(
            " [?] Give access to Find client                  y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::FindClient;

        answer = InputValidate::read_template<char>(
            " [?] Give access to Transactios                  y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::Transacions;

        answer = InputValidate::read_template<char>(
            " [?] Give access to Manage users                 y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::ManageUsers;

        answer = InputValidate::read_template<char>(
            " [?] Give access to Show Login Records           y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::ListLoginRecords;

        answer = InputValidate::read_template<char>(
            " [?] Give access to Currency Exchange Records    y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::CurrencyExchange;

        return permissions;
    }
};

#endif  // CLASS_UPDATE_USER_SCREEN_HPP