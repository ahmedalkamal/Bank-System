#ifndef CLASS_USERS_LIST_SCREEN_HPP
#define CLASS_USERS_LIST_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <vector>

#include "../../Core/User.hpp"
#include "../Screen.hpp"

class UsersListScreen : protected Screen {
   public:
    static void show_users_list() {
        std::vector<User> users = User::get_users_list();
        std::string title = "users List Screen.";
        std::string subtitle =
            "(" + std::to_string(users.size()) + ") User(s).";
        draw_screen_header(title, subtitle, 29);

        std::cout
            << "\n"
            << std::setw(8) << ""
            << "__________________________________________________________"
               "____________________________________________\n\n";

        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(12)
                  << "User Name";
        std::cout << "| " << std::left << std::setw(25) << "Full Name";
        std::cout << "| " << std::left << std::setw(12) << "Phone";
        std::cout << "| " << std::left << std::setw(20) << "Email";
        std::cout << "| " << std::left << std::setw(10) << "Password";
        std::cout << "| " << std::left << std::setw(12) << "Permissions";
        std::cout
            << "\n"
            << std::setw(8) << ""
            << "__________________________________________________________"
               "____________________________________________\n\n";

        if (users.size() == 0) {
            std::cout << "No Users Available In The System!";
        } else {
            for (User user : users) {
                print_user_record_line(user);
                std::cout << std::endl;
            }
        }
        std::cout
            << "\n"
            << std::setw(8) << ""
            << "__________________________________________________________"
               "____________________________________________\n"
            << std::endl;
    }

   private:
    static void print_user_record_line(User& user) {
        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(12)
                  << user.getUserName();
        std::cout << "| " << std::setw(25) << std::left << user.getFullName();
        std::cout << "| " << std::setw(12) << std::left << user.getPhone();
        std::cout << "| " << std::setw(20) << std::left << user.getEmail();
        std::cout << "| " << std::setw(10) << std::left << user.getPassword();
        std::cout << "| " << std::setw(12) << std::left
                  << user.getPermissions();
    }
};

#endif  // CLASS_USERS_LIST_SCREEN_HPPbb