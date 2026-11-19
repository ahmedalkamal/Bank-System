#ifndef CLASS_FIND_USER_SCREEN_HPP
#define CLASS_FIND_USER_SCREEN_HPP

#include <iomanip>
#include <iostream>

#include "../../Core/User.hpp"
#include "../../Utils/Color.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../../Utils/Table.hpp"
#include "../Screen.hpp"

class FindUserScreen : protected Screen {
   public:
    static void show_find_user_screen() {
        draw_screen_header("Find User Screen.");

        std::string username = "";

        std::cout << std::setw(30) << std::left << "";
        std::cout << "[+] Please Enter Account Number: ";
        username = InputValidate::read_template<std::string>();
        // while (!User::is_user_exist(username)) {
        //     std::cout << "\n" << std::setw(30) << std::left << "";
        //     username = InputValidate::read_template<std::string>(
        //         "[+] " + Color::bright_yellow("User is not found") +
        //         ", choose another one: ");
        // }

        User user = User::find(username).response;
        if (!user.is_empty()) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[#] " + Color::bright_green("User found.")
                      << std::endl;
            print_user_card(user);
        } else {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[!] " + Color::bright_red("User was not found!")
                      << std::endl;
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

#endif  // CLASS_FIND_USER_SCREEN_HPP