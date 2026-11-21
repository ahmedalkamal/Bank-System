#ifndef CLASS_DELETE_MY_PROFILE_HPP
#define CLASS_DELETE_MY_PROFILE_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../../Core/User.hpp"
#include "../../../Utils/Color.hpp"
#include "../../../Utils/Table.hpp"
#include "../../Screen.hpp"

class DeleteProfileScreen : protected Screen {
   public:
    static void show_delete_profile_screen() {
        std::string title = "Delete Profile Screen.";
        draw_screen_header(title);

        Table table{title};
        table.setAlignment(11);

        table.panel(
            {
                "            [#]. full name : " + CurrentUser.getFullName() +
                    "    <" + CurrentUser.getUserName() + ">",
                "            [#]. email     : " + CurrentUser.getEmail(),
                "            [#]. phone     : " + CurrentUser.getPhone(),
            },
            95, Table::Align::Left, true);

        if (CurrentUser.is_admin()) {
            table.panel({Color::bright_red(
                            "The admin cannot delete their won account")},
                        95, Table::Align::Center, true);
            return;
        }

        char answer = 'n';
        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Are you sure you want delete your account! y/n: ");

        if (std::tolower(answer) == 'y') {
            if (CurrentUser.remove().response) {
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[#] " +
                                 Color::bright_green(
                                     "Your Account Deleted Successfully.\n");

                Util::clear_buffer();
                std::cout << "\n\nPress enter to continue...";
                std::cin.get();

            } else {
                std::cout << "\n" << std::setw(30) << std::left << "";
                std::cout << "[!] " +
                                 Color::bright_red(
                                     "Error your account was not Deleted!\n");
            }
        }
    }

   private:
};

#endif  // CLASS_DELETE_MY_PROFILE_HPP