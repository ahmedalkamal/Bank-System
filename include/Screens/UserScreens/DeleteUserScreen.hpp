#ifndef CLASS_DELETE_USER_SCREEN_HPP
#define CLASS_DELETE_USER_SCREEN_HPP

#include <iomanip>
#include <iostream>

#include "../../Core/User.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class DeleteUserScreen : protected Screen {
   public:
    static void show_delete_user_screen() {
        draw_screen_header("Delete User Screen.");
        std::string username = "";
        std::cout << "\nPlease Enter Username: ";
        username = InputValidate::read_template<std::string>();
        while (!User::is_user_exist(username)) {
            std::cout << "\nUsername is not found, choose another one: ";
            username = InputValidate::read_template<std::string>();
        }
        User user = User::find(username);
        print_user_card(user);

        char answer = 'n';
        std::cout << "\nAre you sure want to delete this user Y/N : ";
        std::cin >> answer;

        if (std::tolower(answer) == 'y') {
            if (user.remove()) {
                std::cout << "\nUser Deleted Successfully ;).\n";
                // print_user_card(user);
            } else {
                std::cout << "\nError user was not Deleted!\n";
            }
        }
    }

   private:
    static void print_user_card(User user) {
        std::cout << "user Card: \n";
        std::cout << std::string(40, '_') << std::endl;
        std::cout << "Full Name   : "
                  << user.getFirstName() + " " + user.getLastName()
                  << std::endl;
        std::cout << "Email       : " << user.getEmail() << std::endl;
        std::cout << "Phone       : " << user.getPhone() << std::endl;
        std::cout << "Username    : " << user.getUserName() << std::endl;
        std::cout << "Password    : " << user.getPassword() << std::endl;
        std::cout << "Permissions : " << user.getPermissions() << std::endl;
        std::cout << std::string(40, '_') << std::endl;
    }
};

#endif  // CLASS_DELETE_USER_SCREEN_HPP