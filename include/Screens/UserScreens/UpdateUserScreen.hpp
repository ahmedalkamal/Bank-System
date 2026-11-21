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
        std::string username =
            ScreenHelper::read_object_id("username", true, User::find);
        if (username.empty()) return;

        User user = User::find(username).response;

        if (CurrentUser.getUserName() == user.getUserName()) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[!] " +
                             Color::bright_red(
                                 "You cannot update your account from here!") +
                             ", Go to setting.\n";
            return;
        }
        if (user.is_admin()) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            std::cout << "[!] " + Color::bright_red(
                                      "You cannot update the admin account!\n");
            return;
        }

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
                                              "Error user was not updated!\n");
                    break;
            }
        }
    }

   private:
    static void read_user_info(User& user) {
        ScreenHelper::read_person_info<User>(user);

        if (CurrentUser.is_admin()) {
            std::cout << std::setw(30) << std::left << "";
            user.setPassword(InputValidate::read_template<std::string>(
                "[+] Please Enter Password: "));
        } else {
            user.setPassword(
                Util::decrypt(user.getPassword(), Config::encryptionKey));
        }

        if ((!user.check_access_permission(User::Permissions::FullAccess)
                  .response &&
             CurrentUser.check_access_permission(User::Permissions::FullAccess)
                 .response) ||
            CurrentUser.is_admin()) {
            std::cout << std::setw(30) << std::left << "";
            std::cout << "[#] Please Enter Permissions: \n";
            user.setPermissions(ScreenHelper::read_permissions_to_set());
        }
    }

    static void print_user_card(User user) {
        std::map<std::string, std::string> rows;

        rows.insert({"Full Name", user.getFullName()});
        rows.insert({"Email", user.getEmail()});
        rows.insert({"Phone", user.getPhone()});
        rows.insert({"User Name", user.getUserName()});
        if (CurrentUser.is_admin()) {
            rows.insert({"Password", user.getPassword()});
        }
        rows.insert({"Permissions", std::to_string(user.getPermissions())});

        ScreenHelper::print_object_card("User Card", rows);
    }
};

#endif  // CLASS_UPDATE_USER_SCREEN_HPP