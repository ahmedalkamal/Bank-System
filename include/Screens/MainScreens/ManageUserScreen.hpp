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
#include "../UserScreens/SettingScreen.hpp"
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
        Setting,
        MainMenu,
    };

   public:
    static void show_manage_users_menu() {
        system(Config::clear.c_str());
        draw_screen_header("console application");
        if (!has_permission(User::Permissions::ManageUsers)) {
            return;
        }

        std::vector<std::string> menus{
            " List Users.", " Add New User.", " Delete User.", " Update User.",
            " Find User.",  " Setting.",      " Main Menu.",
        };

        Table table{"Manage Users Menu"};
        table.add_column("#", 4, Table::Align::Center);
        table.add_column(" Options", 64, Table::Align::Center);

        table.setAlignment(25);
        for (short i = 0; i < menus.size(); i++) {
            table.add_row({std::to_string(i + 1), menus[i]});
        }
        table.print_menu();

        perform_manage_user_menu_option(
            (ManageUsersOptions)read_manage_users_menu_option(menus.size()));
    }

   private:
    static void back_to_manage_users_menu() {
        // if (std::cin.fail() || std::cin.peek() != '\n') {
        Util::clear_buffer();
        // }
        std::cout << "\n\nPress enter to go back to Manage Users Menu...";
        std::cin.get();
        show_manage_users_menu();
    }

    static short read_manage_users_menu_option(short max) {
        bool valid = false;
        short choice;
        std::cout << std::setw(37) << std::left << ""
                  << "[+] Choose what do you want to do [1 - " << max << "]: ";
        while (!valid) {
            std::cin >> choice;
            valid = InputValidate::is_valid();
            if (!valid) {
                std::cout << std::setw(37) << std::left << ""
                          << Color::yellow("[!] Invalid Input") +
                                 ", Enter again [1 - "
                          << max << "]: ";
                continue;
            }
            if (!InputValidate::in_range<short>(choice, 1, max)) {
                std::cout << std::setw(37) << std::left << ""
                          << Color::yellow("[!] Input Out Of Range") +
                                 ", Enter again [1 - "
                          << max << "]: ";
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
    static void show_setting_menu_screen() {
        // std::cout << "\Setting User Screen will be here. \n";
        SettingScreen::show_setting_user_menu();
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
            case ManageUsersOptions::Setting:
                show_setting_menu_screen();
                if (!CurrentUser.is_deleted()) {
                    show_manage_users_menu();
                }
                break;
            case ManageUsersOptions::MainMenu:
                /* code */
            default:
                break;
        }
    }
};

#endif  // CLASS_MANAGE_USERS_SCREEN_HPP