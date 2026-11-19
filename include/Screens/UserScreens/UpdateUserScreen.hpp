#ifndef CLASS_UPDATE_USER_SCREEN_HPP
#define CLASS_UPDATE_USER_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/User.hpp"
#include "../../Utils/Color.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../../Utils/Table.hpp"
#include "../Screen.hpp"

class UpdateUserScreen : protected Screen {
   public:
    static void show_update_user_screen() {
        draw_screen_header("Update User Screen");
        std::string username = "";

        std::cout << std::setw(30) << std::left << "";
        username = InputValidate::read_template<std::string>(
            "[+] Please enter username: ");
        while (!User::is_user_exist(username)) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            username = InputValidate::read_template<std::string>(
                "[+] " + Color::bright_yellow("Username is not found") +
                ", choose another one: ");
        }

        User user = User::find(username).response;
        print_user_card(user);

        char answer = 'n';
        std::cout << "\n" << std::setw(30) << std::left << "";
        std::cout << "[+] Are you sure you want to update this user Y/N : ";
        std::cin >> answer;
        read_user_info(user);

        if (std::tolower(answer) == 'y') {
            switch (user.save()) {
                case User::SaveStatus::Successful:
                    std::cout << "\n" << std::setw(30) << std::left << "";
                    std::cout << "[#] " + Color::bright_green(
                                              "User Updated Successfully.\n");
                    print_user_card(user);
                    break;
                case User::SaveStatus::FailedEmpty:
                    std::cout << "\n" << std::setw(30) << std::left << "";
                    std::cout << "[!] " + Color::bright_red(
                                              "Error user was not updated "
                                              "because it's empty!");
                    break;
            }
        }
    }

   private:
    static void read_user_info(User& user) {
        std::cout << std::setw(30) << std::left << "";
        user.setFirstName(InputValidate::read_template<std::string>(
            "[+] Please Enter Firs Name: "));

        std::cout << std::setw(30) << std::left << "";
        user.setLastName(InputValidate::read_template<std::string>(
            "[+] Please Enter Last Name: "));

        std::cout << std::setw(30) << std::left << "";
        user.setEmail(InputValidate::read_template<std::string>(
            "[+] Please Enter Email: "));

        std::cout << std::setw(30) << std::left << "";
        user.setPhone(InputValidate::read_template<std::string>(
            "[+] Please Enter Phone: "));

        std::cout << std::setw(30) << std::left << "";
        user.setPassword(InputValidate::read_template<std::string>(
            "[+] Please Enter Password: "));

        if (user.permissions != short(User::Permissions::Admin)) {
            std::cout << std::setw(30) << std::left << "";
            std::cout << "[#] Please Enter Permissions: \n";
            user.setPermissions(read_permissions_to_set());
        }
    }

    static void print_user_card(User user) {
        Table table{"User Card."};
        table.add_column("", 16);
        table.add_column(" info ", 45, Table::Align::Center);

        table.add_row({"Full Name   ", user.getFullName()},
                      Table::Align::Center);
        table.add_row({"Email       ", user.getEmail()}, Table::Align::Center);
        table.add_row({"Phone       ", user.getPhone()}, Table::Align::Center);
        table.add_row({"User Name   ", user.getUserName()},
                      Table::Align::Center);
        table.add_row({"Passowrd    ", user.getPassword()},
                      Table::Align::Center);
        table.add_row({"Permissions ", std::to_string(user.getPermissions())},
                      Table::Align::Center);

        table.setAlignment(25);
        table.print_table();
    }

    static short read_permissions_to_set() {
        short permissions = 0;
        // char answer = 'n';

        std::cout << std::setw(30) << std::left << "";
        char answer = InputValidate::read_template<char>(
            "[?] Do you want to give Full access y/n ? ");
        if (std::tolower(answer) == 'y')
            return (short)User::Permissions::FullAccess;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Show clients list y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::ListClients;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Add new clients y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::AddNewClient;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Delete client y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::DeleteClient;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Update clients y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::UpdateClients;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Find client y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::FindClient;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Transactios y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::Transacions;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Manage users y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::ManageUsers;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Show Login Records y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::ListLoginRecords;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Currency Exchange Records y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::CurrencyExchange;

        return permissions;
    }
};

#endif  // CLASS_UPDATE_USER_SCREEN_HPP