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
        std::string username =
            ScreenHelper::read_object_id("username", true, User::find);
        if (username.empty()) return;

        User user = User::find(username).response;

        if (CurrentUser.getUserName() == user.getUserName()) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[!] " +
                             Color::bright_red(
                                 "You cannot delete your account from here!") +
                             ", Go to setting.\n";
            return;
        }
        if (user.is_admin()) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[!] " + Color::bright_red(
                                      "You cannot delete the admin account!\n");
            return;
        }

        if (user.check_access_permission(User::Permissions::FullAccess)
                .response &&
            !CurrentUser.is_admin()) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout
                << "[!] " +
                       Color::bright_red(
                           "You don't have access to delete this account!\n");
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

#endif  // CLASS_DELETE_USER_SCREEN_HPP