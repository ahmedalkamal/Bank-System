#ifndef CLASS_SETTING_MENU_SCREEN_HPP
#define CLASS_SETTING_MENU_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/User.hpp"
#include "../../Utils/Color.hpp"
#include "../../Utils/Table.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"
#include "./UserSettingScreen/DeleteMyProfile.hpp"
#include "./UserSettingScreen/UpdateProfile.hpp"

class SettingScreen : protected Screen {
   private:
    enum class SettingUserOptions {
        Update,
        Delete,
        ManageUsersMenu,
    };

   public:
    static void show_setting_user_menu() {
        system(Config::clear.c_str());
        draw_screen_header("Setting Profile Screen.");

        std::vector<std::string> menus{
            " Update Profile.",
            " Delete Profile.",
            " Manage User Menu.",
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
            (SettingUserOptions)ScreenHelper::read_option_enum(
                "Please choose option: ", menus.size()));
    }

   private:
    static void back_to_setting_user_menu() {
        ScreenHelper::back_to_selected_screen(
            "Press enter to go back to Setting Profile Menu...",
            show_setting_user_menu);
    }

    static void show_update_profile_screen() {
        // std::cout << "\nUpdate Profile Screen will be here. \n";
        UpdateProfileScreen::show_update_profie_screen();
    }
    static void show_delete_profile_screen() {
        // std::cout << "\nDelete Profile Screen will be here. \n";
        DeleteProfileScreen::show_delete_profile_screen();
    }

    static void perform_manage_user_menu_option(SettingUserOptions option) {
        system(Config::clear.c_str());

        switch (option) {
            case SettingUserOptions::Update:
                show_update_profile_screen();
                back_to_setting_user_menu();
                break;
            case SettingUserOptions::Delete:
                show_delete_profile_screen();
                if (!CurrentUser.is_deleted()) {
                    back_to_setting_user_menu();
                }
                break;
            case SettingUserOptions::ManageUsersMenu:
                /* code */
            default:
                break;
        }
    }
};

#endif  // CLASS_SETTING_MENU_SCREEN_HPP