#ifndef CLASS_ADD_NEW_USER_SCREEN_HPP
#define CLASS_ADD_NEW_USER_SCREEN_HPP

#include <iomanip>
#include <iostream>

#include "../../Core/User.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class AddNewUserScreen : protected Screen {
   public:
    static void show_add_new_user_screen() {
        draw_screen_header("Add New User Screen.");

        std::string username = "";
        std::cout << "\nPlease enter username: ";
        username = InputValidate::read_template<std::string>();
        while (User::is_user_exist(username)) {
            std::cout << "\nUsername Is Already Used, Choose another one: ";
            username = InputValidate::read_template<std::string>();
        }

        User new_user = User::get_addnew_object(username);
        read_user_info(new_user);

        switch (new_user.save()) {
            case User::SaveStatus::Successful:
                std::cout << "\nUser Added Successfully ;)\n";
                print_user_card(new_user);
                break;
            case User::SaveStatus::FailedEmpty:
                std::cout << "\nError User was not saved because it's empty!";
                break;
            case User::SaveStatus::FailedAccountExist:
                std::cout
                    << "\nError User was not saved because username is used!\n";
                break;

            default:
                break;
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

#endif  // CLASS_ADD_NEW_USER_SCREEN_HPP