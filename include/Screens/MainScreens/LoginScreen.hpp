#ifndef CLASS_LOGIN_SCREEN_HPP
#define CLASS_LOGIN_SCREEN_HPP

#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/User.hpp"
#include "../../Global/Config.hpp"
#include "../../Global/Sessions.hpp"
#include "../../Utils/Color.hpp"
#include "../../Utils/Table.hpp"
#include "../Screen.hpp"
#include "FirstUse.hpp"
#include "MainScreen.hpp"

class LoginScreen : protected Screen {
   public:
    static bool launcher;

    static void show_login_screen() {
        while (User::get_users_list().response.empty()) {
            FirstUse::show_first_use_screen();
        }

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
            std::cout << std::setw(40) << std::left << ""
                      << Color::bright_yellow("[!] You have ") + "("
                      << --attempt
                      << ")" + Color::bright_yellow(" attempt to login.\n\n");
            return true;
        } else {
            reset_launcher();
            return false;
        }
    }

    static void login() {
        bool login_failed = false;
        bool is_locked = false;
        Status<User> session = User::find("", "");
        std::string username = "", password = "";

        do {
            if (login_failed) {
                if (session.status_code == StatusCode::InvalidUsername)
                    std::cout << std::setw(40) << std::left << ""
                              << Color::bright_red("[!] Invalid Username\n\n");

                if (session.status_code == StatusCode::InvalidPassword)
                    std::cout << std::setw(40) << std::left << ""
                              << Color::bright_red("[!] Invalid Password\n\n");

                is_locked = !can_attempt();
                if (is_locked) {
                    std::cout << Color::bright_red(
                        "\n[!] You are Locked after 3 failed attempt!.\n");
                    return;
                }
            }
            std::cout << std::setw(40) << std::left << ""
                      << "[+] Please Enter Username: ";
            std::cin >> username;

            std::cout << std::setw(40) << std::left << ""
                      << "[+] Please Enter Password: ";
            std::cin >> password;

            session = User::find(username, password);
            login_failed = !session.issuccessful();

        } while (login_failed);

        attempt = 3;
        CurrentUser = session.response;
        CurrentUser.save_login_record();
        MainScreen::show_main_menu();
    }
};

bool LoginScreen::launcher = false;
short LoginScreen::attempt = 3;

#endif  // CLASS_LOGIN_SCREEN_HPP