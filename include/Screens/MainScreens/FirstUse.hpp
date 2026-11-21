#ifndef CLASS_FIRST_USE_HPP
#define CLASS_FIRST_USE_HPP

#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include "../../Core/User.hpp"
#include "../../Utils/Color.hpp"
#include "../../Utils/Table.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"

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

        ScreenHelper::read_person_info<User>(user);

        std::cout << std::setw(30) << std::left << "";
        user.setPassword(InputValidate::read_template<std::string>(
            "[+] Please Enter Password: "));

        user.setPermissions(-2);

        return user;
    }

    static void print_user_card(User user) {
        std::map<std::string, std::string> rows;

        rows.insert({"Full Name", user.getFullName()});
        rows.insert({"Email", user.getEmail()});
        rows.insert({"Phone", user.getPhone()});
        rows.insert({"User Name", user.getUserName()});
        rows.insert({"Password", user.getPassword()});
        rows.insert({"Permissions", std::to_string(user.getPermissions())});

        ScreenHelper::print_object_card("User Card", rows);
    }
};

#endif  // CLASS_FIRST_USE_HPP