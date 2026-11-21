#ifndef CLASS_MANAGE_USERS_SCREEN_HPP
#define CLASS_MANAGE_USERS_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/User.hpp"
#include "../../Global/Config.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"
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
        draw_screen_header("Manage Users Screen.");
        if (!has_permission(User::Permissions::ManageUsers)) {
            return;
        }

        std::vector<std::string> menus{
            " List Users.", " Add New User.", " Delete User.", " Update User.",
            " Find User.",  " Setting.",      " Main Menu.",
        };

        Table table{"Menu"};
        table.add_column("No.", 4, Table::Align::Center);
        table.add_column(" Options", 64, Table::Align::Center);

        table.setAlignment(25);
        for (short i = 0; i < menus.size(); i++) {
            std::string num = String::zfill(std::to_string(i + 1), 2);
            table.add_row({num, menus[i]});
        }
        table.print_menu();

        perform_manage_user_menu_option(
            (ManageUsersOptions)ScreenHelper::read_option_enum(
                "Please choose option: ", menus.size()));
    }

   private:
    static void back_to_manage_users_menu() {
        ScreenHelper::back_to_selected_screen(
            "Press enter to go back to Manage Users Menu...",
            show_manage_users_menu);
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