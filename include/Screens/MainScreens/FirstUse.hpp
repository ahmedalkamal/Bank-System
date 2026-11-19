#ifndef CLASS_FIRST_USE_HPP
#define CLASS_FIRST_USE_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/User.hpp"
#include "../../Utils/Color.hpp"
#include "../../Utils/Table.hpp"
#include "../Screen.hpp"

// First account created will become the Admin.

class FirstUse : protected Screen {
   public:
    static bool launcher;

    static void show_first_use_screen() {
        system(Config::clear.c_str());
        draw_screen_header("Setup Screen.",
                           "First account created will become the Admin.");
        User user = setup();

        switch (user.save()) {
            case User::SaveStatus::Successful:
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[#] " + Color::bright_green(
                                          "Admin Added Successfully.\n")
                          << std::endl;

                print_user_card(user);
                break;
            case User::SaveStatus::FailedEmpty:
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[!] " + Color::bright_red(
                                          "Error admin was not saved "
                                          "because it's empty!\n");
                break;
        }

        Util::clear_buffer();
        std::cout << "\n> Press enter to continue...";
        std::cin.get();
    }

   private:
    static User setup() {
        std::string username = "", password = "";

        std::cout << std::setw(30) << std::left << ""
                  << "[+] Please Enter Username: ";
        std::cin >> username;
        User user = User::get_addnew_object(username);

        std::cout << std::setw(30) << std::left << "";
        user.first_name = InputValidate::read_template<std::string>(
            "[+] Please Enter Firs Name: ");

        std::cout << std::setw(30) << std::left << "";
        user.last_name = InputValidate::read_template<std::string>(
            "[+] Please Enter Last Name: ");

        std::cout << std::setw(30) << std::left << "";
        user.email = InputValidate::read_template<std::string>(
            "[+] Please Enter Email: ");

        std::cout << std::setw(30) << std::left << "";
        user.phone = InputValidate::read_template<std::string>(
            "[+] Please Enter Phone: ");

        std::cout << std::setw(30) << std::left << "";
        user.password = InputValidate::read_template<std::string>(
            "[+] Please Enter Password: ");

        user.permissions = -2;

        return user;
    }

    static void print_user_card(User user) {
        Table table{"User Card."};
        table.add_column("", 16);
        table.add_column(" info ", 45, Table::Align::Center);

        table.add_row({" Full Name   ", " " + user.getFullName()});
        table.add_row({" Email       ", " " + user.getEmail()});
        table.add_row({" Phone       ", " " + user.getPhone()});
        table.add_row({" User Name   ", " " + user.getUserName()});
        table.add_row({" Passowrd    ", " " + user.getPassword()});
        table.add_row(
            {" Permissions ", " " + std::to_string(user.getPermissions())});

        table.setAlignment(25);
        table.print_table();
    }
};

#endif  // CLASS_FIRST_USE_HPP