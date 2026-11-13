#ifndef CLASS_MANAGE_USERS_SCREEN_HPP
#define CLASS_MANAGE_USERS_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/User.hpp"
#include "../../Global/Config.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"
#include "../UserScreens/AddNewUserScreen.hpp"
#include "../UserScreens/DeleteUserScreen.hpp"
#include "../UserScreens/FindUserScreen.hpp"
#include "../UserScreens/UpdateUserScreen.hpp"
#include "../UserScreens/UsersListScreen.hpp"

class ManageUsersScreen : protected Screen {
   private:
    enum class ManageUsersOptions {
        ListUsers,
        AddNewUser,
        DeleteUser,
        UpdateUser,
        FindUser,
        MainMenu,
    };

   public:
    static void show_manage_users_menu() {
        if (!has_permission(User::Permissions::ManageUsers)) {
            return;
        }

        system(Config::clear.c_str());
        draw_screen_header("console application", "", 39);

        std::cout << std::setw(37) << std::left << ""
                  << "========================================================="
                     "=========\n";
        std::cout << std::setw(57) << std::left << ""
                  << "Manage Users Menu\n";
        std::cout << std::setw(37) << std::left << ""
                  << "========================================================="
                     "=========\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[1] List Users.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[2] Add New User.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[3] Delete User.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[4] Update User.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[5] Find User.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[6] Main Menu.\n";

        std::cout << std::setw(37) << std::left << ""
                  << "========================================================="
                     "=========\n";

        perform_manage_user_menu_option(
            (ManageUsersOptions)read_manage_users_menu_option());
    }

   private:
    static void back_to_manage_users_menu() {
        // if (std::cin.fail() || std::cin.peek() != '\n') {
        Util::clear_buffer();
        // }
        std::cout << "Press enter to go back to Manage Users Menu...";
        std::cin.get();
        show_manage_users_menu();
    }

    static short read_manage_users_menu_option() {
        bool valid = false;
        short choice;
        std::cout << std::setw(37) << std::left << ""
                  << "Choose what do you want to do [1 - 6]: ";
        while (!valid) {
            std::cin >> choice;
            valid = InputValidate::is_valid();
            if (!valid) {
                std::cout << std::setw(37) << std::left << ""
                          << "Invalid Input, Enter again [1 - 6]: ";
                continue;
            }
            if (!InputValidate::in_range<short>(choice, 1, 6)) {
                std::cout << std::setw(37) << std::left << ""
                          << "Input Out Of Range, Enter again [1 - 6]: ";
                valid = false;
            }
        }
        return choice - 1;
    }

    static void show_list_users_screen() {
        // std::cout << "\nList Users Screen will be here. \n";
        UsersListScreen::show_users_list();
    }
    static void show_add_new_user_screen() {
        // std::cout << "\nAdd New User Screen will be here. \n";
        AddNewUserScreen::show_add_new_user_screen();
    }
    static void show_delete_user_screen() {
        // std::cout << "\nDelete User Screen will be here. \n";
        DeleteUserScreen::show_delete_user_screen();
    }
    static void show_update_user_screen() {
        // std::cout << "\nUpdate User Screen will be here. \n";
        UpdateUserScreen::show_update_user_screen();
    }
    static void show_find_user_screen() {
        // std::cout << "\nFine User Screen will be here. \n";
        FindUserScreen::show_find_user_screen();
    }

    static void perform_manage_user_menu_option(ManageUsersOptions option) {
        system(Config::clear.c_str());

        switch (option) {
            case ManageUsersOptions::ListUsers:
                show_list_users_screen();
                back_to_manage_users_menu();
                break;
            case ManageUsersOptions::AddNewUser:
                show_add_new_user_screen();
                back_to_manage_users_menu();
                break;
            case ManageUsersOptions::DeleteUser:
                show_delete_user_screen();
                back_to_manage_users_menu();
                break;
            case ManageUsersOptions::UpdateUser:
                show_update_user_screen();
                back_to_manage_users_menu();
                break;
            case ManageUsersOptions::FindUser:
                show_find_user_screen();
                back_to_manage_users_menu();
                break;
            case ManageUsersOptions::MainMenu:
                /* code */
            default:
                break;
        }
    }
};

#endif  // CLASS_MANAGE_USERS_SCREEN_HPP