#ifndef CLASS_UPDATE_PROFILE_HPP
#define CLASS_UPDATE_PROFILE_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../../Core/User.hpp"
#include "../../../Utils/Color.hpp"
#include "../../../Utils/Table.hpp"
#include "../../Screen.hpp"
#include "../../ScreenHelper.hpp"

class UpdateProfileScreen : protected Screen {
   private:
    enum class UpdateOptions {
        EditName,
        EditEmail,
        EditPhone,
        EditPassword,
        SaveChanges,
        ExitWithOutSave,
    };

   public:
    static void show_update_profie_screen() {
        User backup = CurrentUser;
        CurrentUser.setPassword(
            Util::decrypt(CurrentUser.getPassword(), Config::encryptionKey));

        std::string title = "Update Profile Screen.";
        draw_screen_header(title);

        Table table{title};
        table.setAlignment(11);

        table.panel(
            {"            [1]. full name   : " + CurrentUser.getFullName() +
                 "    <" + CurrentUser.getUserName() + ">",
             "            [2]. email       : " + CurrentUser.getEmail(),
             "            [3]. phone       : " + CurrentUser.getPhone(),
             "            [4]. password    : " + CurrentUser.getPassword(),
             "            [5]. save changes.",
             "            [6]. exit without save."},
            95, Table::Align::Left, true);

        UpdateOptions choice = (UpdateOptions)ScreenHelper::read_option_enum(
            "Please choose option: ", 6);

        while (true) {
            if (choice == UpdateOptions::SaveChanges) {
                if (is_modified(backup)) break;

                char answer = 'n';
                print_user_card(CurrentUser);
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[+] Are you sure you want to update y/n : ";
                std::cin >> answer;

                if (std::tolower(answer) == 'y') {
                    save_change(backup);
                } else {
                    CurrentUser = backup;
                }
                break;
            }
            if (choice == UpdateOptions::ExitWithOutSave) {
                break;
            }
            read_user_info(choice);
            choice = (UpdateOptions)ScreenHelper::read_option_enum(
                "Please choose option: ", 6);
        }
    }

   private:
    static bool is_modified(User backup) {
        if (Util::decrypt(backup.getPassword(), Config::encryptionKey) ==
            CurrentUser.getPassword()) {
            CurrentUser.setPassword(backup.getPassword());
        }
        return backup.getFullName() == CurrentUser.getFullName() &&
               backup.getEmail() == CurrentUser.getEmail() &&
               backup.getPhone() == CurrentUser.getPhone() &&
               backup.getPassword() == CurrentUser.getPassword();
    }
    static void save_change(const User& backup) {
        switch (CurrentUser.save()) {
            case User::SaveStatus::Successful:
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[#] " + Color::bright_green(
                                          "Your Account Updated "
                                          "Successfully.\n");
                break;

            default:
                CurrentUser = backup;
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[!] " + Color::bright_red(
                                          "Error your account was "
                                          "not updated!");
                break;
        }
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

    static void read_user_info(UpdateOptions choice) {
        switch (choice) {
            case UpdateOptions::EditName:
                std::cout << std::setw(30) << std::left << "";
                CurrentUser.setFirstName(
                    InputValidate::read_template<std::string>(
                        "[+] Please Enter Firs Name: "));

                std::cout << std::setw(30) << std::left << "";
                CurrentUser.setLastName(
                    InputValidate::read_template<std::string>(
                        "[+] Please Enter Last Name: "));
                break;

            case UpdateOptions::EditEmail:

                std::cout << std::setw(30) << std::left << "";
                CurrentUser.setEmail(InputValidate::read_template<std::string>(
                    "[+] Please Enter Email: "));
                break;

            case UpdateOptions::EditPhone:

                std::cout << std::setw(30) << std::left << "";
                CurrentUser.setPhone(InputValidate::read_template<std::string>(
                    "[+] Please Enter Phone: "));
                break;

            case UpdateOptions::EditPassword:
                std::cout << std::setw(30) << std::left << "";
                CurrentUser.setPassword(
                    InputValidate::read_template<std::string>(
                        "[+] Please Enter Password: "));
                break;

            default:
                break;
        }
    }
};
#endif  // CLASS_UPDATE_PROFILE_HPP