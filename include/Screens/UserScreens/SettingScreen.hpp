#ifndef CLASS_SETTING_MENU_SCREEN_HPP
#define CLASS_SETTING_MENU_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/User.hpp"
#include "../../Utils/Color.hpp"
#include "../../Utils/Table.hpp"
#include "../Screen.hpp"
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
        draw_screen_header("Setting User Menu.");

        std::vector<std::string> menus{
            " Update Profile.",
            " Delete Profile.",
            " Manage User Menu.",
        };

        Table table{"Setting User Menu."};
        table.add_column("#", 4, Table::Align::Center);
        table.add_column(" Options", 64, Table::Align::Center);

        table.setAlignment(25);
        for (short i = 0; i < menus.size(); i++) {
            table.add_row({std::to_string(i + 1), menus[i]});
        }
        table.print_menu();

        perform_manage_user_menu_option(
            (SettingUserOptions)read_setting_user_menu_option(menus.size()));
    }

   private:
    static void back_to_setting_user_menu() {
        // if (std::cin.fail() || std::cin.peek() != '\n') {
        Util::clear_buffer();
        // }
        std::cout << "\n\nPress enter to go back to Setting User Menu...";
        std::cin.get();
        show_setting_user_menu();
    }

    static short read_setting_user_menu_option(short max) {
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