#ifndef CLASS_LOGIN_SCREEN_HPP
#define CLASS_LOGIN_SCREEN_HPP

#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/User.hpp"
#include "../../Global/Config.hpp"
#include "../../Global/Sessions.hpp"
#include "../Screen.hpp"
#include "MainScreen.hpp"

class LoginScreen : protected Screen {
   public:
    static bool launcher;

    static void show_login_screen() {
        system(Config::clear.c_str());
        draw_screen_header("Login Screen.");
        login();
        if (launcher) {
            show_login_screen();
        }
    }

   private:
    static short attempt;

    static void reset_launcher() { launcher = false; }

    static bool can_attempt() {
        if (attempt > 1) {
            std::cout << "You have " << --attempt << " attempt to login.\n";
            return true;
        } else {
            reset_launcher();
            return false;
        }
    }

    static void login() {
        bool login_failed = false;
        bool is_locked = false;
        std::string username = "", password = "";

        do {
            if (login_failed) {
                std::cout << "\nInvalid Username / Password1\n\n";
                is_locked = !can_attempt();
                if (is_locked) {
                    std::cout << "\nYou are Locked after 3 failed attempt!.\n";
                    return;
                }
            }
            std::cout << "Enter Username: ";
            std::cin >> username;

            std::cout << "Enter Password: ";
            std::cin >> password;

            CurrentUser = User::find(username, password);
            login_failed = CurrentUser.is_empty();

        } while (login_failed);

        attempt = 3;
        CurrentUser.save_login_record();
        MainScreen::show_main_menu();
    }
};

bool LoginScreen::launcher = false;
short LoginScreen::attempt = 3;

#endif  // CLASS_LOGIN_SCREEN_HPP