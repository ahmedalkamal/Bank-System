#ifndef CLASS_ADD_NEW_USER_SCREEN_HPP
#define CLASS_ADD_NEW_USER_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <map>

#include "../../Core/User.hpp"
#include "../../Utils/Color.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../../Utils/Table.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"

class AddNewUserScreen : protected Screen {
   public:
    static void show_add_new_user_screen() {
        draw_screen_header("Add New User Screen.");

        std::string username =
            ScreenHelper::read_object_id("username", false, User::find);
        if (username.empty()) return;

        User new_user = User::get_addnew_object(username);
        read_user_info(new_user);

        switch (new_user.save()) {
            case User::SaveStatus::Successful:
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[#] " + Color::bright_green(
                                          "User Added Successfully.\n")
                          << std::endl;

                print_user_card(new_user);
                break;
            case User::SaveStatus::FailedEmpty:
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[!] " + Color::bright_red(
                                          "Error user was not saved "
                                          "because it's empty!\n");
                break;
            case User::SaveStatus::FailedAccountExist:
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[!] " + Color::bright_red(
                                          "Error user was not saved because "
                                          "username is used!\n");
                break;
        }
    }

   private:
    static void read_user_info(User& user) {
        ScreenHelper::read_person_info<User>(user);

        std::cout << std::setw(30) << std::left << "";
        user.setPassword(InputValidate::read_template<std::string>(
            "[+] Please Enter Password: "));

        std::cout << std::setw(30) << std::left << "";
        std::cout << "[#] Please Enter Permissions: \n";
        user.setPermissions(ScreenHelper::read_permissions_to_set());
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

#endif  // CLASS_ADD_NEW_USER_SCREEN_HPP