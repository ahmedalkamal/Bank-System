#ifndef CLASS_DELETE_USER_SCREEN_HPP
#define CLASS_DELETE_USER_SCREEN_HPP

#include <iomanip>
#include <iostream>

#include "../../Core/User.hpp"
#include "../../Utils/Color.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../../Utils/Table.hpp"
#include "../Screen.hpp"

class DeleteUserScreen : protected Screen {
   public:
    static void show_delete_user_screen() {
        draw_screen_header("Delete User Screen.");
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

        if (CurrentUser.getUserName() == user.getUserName()) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[!] " +
                             Color::bright_red("Cannot delete your account!") +
                             ", go to setting.\n";
            return;
        }
        if (user.is_admin()) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[!] " + Color::bright_red(
                                      "Cannot delete Admin account!\n");
            return;
        }

        print_user_card(user);

        char answer = 'n';
        std::cout << "\n" << std::setw(30) << std::left << "";
        std::cout << "[+] Are you sure want to delete this user Y/N : ";
        std::cin >> answer;

        if (std::tolower(answer) == 'y') {
            if (user.remove().response) {
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[#] " + Color::bright_green(
                                          "User Deleted Successfully.\n");
                // print_user_card(user);
            } else {
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[!] " + Color::bright_red(
                                          "Error user was not Deleted!\n");
            }
        }
    }

   private:
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
};

#endif  // CLASS_DELETE_USER_SCREEN_HPP