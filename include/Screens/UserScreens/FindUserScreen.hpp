#ifndef CLASS_FIND_USER_SCREEN_HPP
#define CLASS_FIND_USER_SCREEN_HPP

#include <iomanip>
#include <iostream>

#include "../../Core/User.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class FindUserScreen : protected Screen {
   public:
    static void show_find_user_screen() {
        draw_screen_header("Find User Screen.");

        std::string username = InputValidate::read_template<std::string>();
        while (!User::is_user_exist(username)) {
            std::cout << "\nUser is not found, choose another one: ";
            username = InputValidate::read_template<std::string>();
        }

        User user = User::find(username);
        if (user.is_empty()) {
            std::cout << "\nUser was not found! :(";
        } else {
            std::cout << "\nUser Found :)";
            print_user_card(user);
        }
    }

   private:
    static void print_user_card(const User& user) {
        std::cout << "\nUser Card"
                     "\n_________________________________________\n"
                  << std::endl;
        std::cout << "Full Name   : " << user.full_name << "\n"
                  << "Email       : " << user.email << "\n"
                  << "Phone       : " << user.phone << "\n"
                  << "User Name   : " << user.username << "\n"
                  << "Password    : " << user.password << "\n"
                  << "Permissions :  " << user.permissions;
        std::cout << "\n_________________________________________" << std::endl;
    }
};

#endif  // CLASS_FIND_USER_SCREEN_HPP