#ifndef CLASS_SCREEN_HPP
#define CLASS_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../Core/Date.hpp"
#include "../Core/User.hpp"
#include "../Global/Sessions.hpp"

class Screen {
   protected:
    static void draw_screen_header(std::string title, std::string subtitle = "",
                                   short width = 37) {
        std::cout << std::setw(width) << std::left << ""
                  << "\t_______________________________________________"
                     "_________";
        std::cout << "\n\n"
                  << std::setw(width + 20) << std::left << "" << title << "\n";
        if (!subtitle.empty()) {
            std::cout << std::setw(width + 20) << std::left << "" << subtitle
                      << "\n";
        }
        std::cout << std::setw(width) << std::left << ""
                  << "\t_____________________________________________"
                     "___________\n\n";

        std::cout << std::setw(width + 3) << std::left << ""
                  << "User: "
                  << (CurrentUser.getUserName().empty()
                          ? "Login Please!"
                          : CurrentUser.getUserName())
                  << "\n";
        std::cout << std::setw(width + 3) << std::left << ""
                  << "Date: " << Date::date_format(Date::get_system_date())
                  << "\n"
                  << std::endl;
        ;
    }

    static bool has_permission(User::Permissions permission) {
        if (CurrentUser.check_access_permission(permission)) {
            return true;
        } else {
            // std::string title = "Access Denied!";
            // std::string subtitle = "Contact your admin.";

            std::cout << std::setw(37) << std::left << ""
                      << "\t_______________________________________________"
                         "_________";
            std::cout << "\n\n"
                      << std::setw(37) << std::left << ""
                      << "\t\tAccess Denied! Contact your admin."
                      << "\n";

            std::cout << std::setw(37) << std::left << ""
                      << "\t_____________________________________________"
                         "___________\n\n";

            return false;
            // std::cout << ""
        }
    }
};

#endif  // CLASS_SCREEN_HPP