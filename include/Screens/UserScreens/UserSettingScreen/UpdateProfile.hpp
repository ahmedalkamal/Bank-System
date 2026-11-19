#ifndef CLASS_UPDATE_PROFILE_HPP
#define CLASS_UPDATE_PROFILE_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../../Core/User.hpp"
#include "../../../Utils/Color.hpp"
#include "../../../Utils/Table.hpp"
#include "../../Screen.hpp"

class UpdateProfileScreen : protected Screen {
   private:
    enum class UpdateOptions {
        EditName = 1,
        EditEmail = 2,
        EditPhone = 3,
        EditPassword = 4,
        SaveChanges = 5,
        ExitWithOutSave = 6,
    };

   public:
    static void show_update_profie_screen() {
        User backup = CurrentUser;

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

        UpdateOptions choice = (UpdateOptions)read_option_to_edit(6);
        while (true) {
            if (choice == UpdateOptions::SaveChanges) {
                char answer = 'n';
                print_user_card(CurrentUser);
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[+] Are you sure you want to update y/n : ";
                std::cin >> answer;

                if (std::tolower(answer) == 'y') {
                    switch (CurrentUser.save()) {
                        case User::SaveStatus::Successful:
                            std::cout << "\n"
                                      << std::setw(30) << std::left << "";
                            std::cout << "[#] " + Color::bright_green(
                                                      "Your Account Updated "
                                                      "Successfully.\n");
                            break;

                        default:
                            CurrentUser = backup;
                            std::cout << "\n"
                                      << std::setw(30) << std::left << "";
                            std::cout << "[!] " + Color::bright_red(
                                                      "Error your account was "
                                                      "not updated!");
                            break;
                    }
                } else {
                    CurrentUser = backup;
                }
                break;
            }
            if (choice == UpdateOptions::ExitWithOutSave) {
                break;
            }
            read_user_info(choice);
            choice = (UpdateOptions)read_option_to_edit(6);
        }
    }

   private:
    static void print_user_card(User user) {
        Table table{"User Card."};
        table.add_column("", 16);
        table.add_column(" info ", 45, Table::Align::Center);

        table.add_row({"Full Name   ", user.getFullName()},
                      Table::Align::Center);
        table.add_row({"Email       ", user.getEmail()}, Table::Align::Center);
        table.add_row({"Phone       ", user.getPhone()}, Table::Align::Center);
        table.add_row({"User Name   ", user.getUserName()},
                      Table::Align::Center);
        table.add_row({"Passowrd    ", user.getPassword()},
                      Table::Align::Center);
        table.add_row({"Permissions ", std::to_string(user.getPermissions())},
                      Table::Align::Center);

        table.setAlignment(25);
        table.print_table();
    }

    static short read_option_to_edit(short max) {
        bool valid = false;
        short choice;
        std::cout << std::setw(30) << std::left << ""
                  << "[+] Choose what you want to update [1 - " << max << "]: ";
        while (!valid) {
            std::cin >> choice;
            valid = InputValidate::is_valid();
            if (!valid) {
                std::cout << std::setw(30) << std::left << ""
                          << Color::yellow("[!] Invalid Input") +
                                 ", Enter again [1 - "
                          << max << "]: ";
                continue;
            }
            if (!InputValidate::in_range<short>(choice, 1, max)) {
                std::cout << std::setw(30) << std::left << ""
                          << Color::yellow("[!] Input Out Of Range") +
                                 ", Enter again [1 - "
                          << max << "]: ";
                valid = false;
            }
        }
        return choice;
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