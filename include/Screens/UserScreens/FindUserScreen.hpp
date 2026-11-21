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

        std::string username =
            ScreenHelper::read_object_id("username", true, User::find);
        if (username.empty()) return;

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
        std::map<std::string, std::string> rows;

        rows.insert({"Full Name", user.getFullName()});
        rows.insert({"Email", user.getEmail()});
        rows.insert({"Phone", user.getPhone()});
        rows.insert({"User Name", user.getUserName()});
        if (CurrentUser.is_admin()) {
            rows.insert({"Password", Util::decrypt(user.getPassword(),
                                                   Config::encryptionKey)});
        }
        rows.insert({"Permissions", std::to_string(user.getPermissions())});

        ScreenHelper::print_object_card("User Card", rows);
    }
};

#endif  // CLASS_FIND_USER_SCREEN_HPP