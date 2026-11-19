#ifndef CLASS_SCREEN_HPP
#define CLASS_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../Core/Date.hpp"
#include "../Core/User.hpp"
#include "../Global/Sessions.hpp"
#include "../Utils/Color.hpp"
#include "../Utils/Table.hpp"

class Screen {
   protected:
    static void draw_screen_header(std::string title,
                                   std::string subtitle = "") {
        bool is_empty = CurrentUser.getUserName().empty();
        Table table;
        table.panel(
            {title, subtitle},
            {Date::date_format(Date::get_system_date(), "%y-%m-%d"),
             Date::get_system_time()},
            {(is_empty ? Color::red("NO USER") : Color::green("WELCOME")),
             (is_empty ? "please login" : CurrentUser.getUserName())},
            120, Table::Align::Center);
    }

    static bool has_permission(User::Permissions permission) {
        if (CurrentUser.check_access_permission(permission).issuccessful()) {
            return true;
        } else {
            Table table;
            table.panel(
                {"", Color::bright_red("Access Denied! Contact your admin."),
                 ""},
                120, Table::Align::Center);
            return false;
        }
    }
};

#endif  // CLASS_SCREEN_HPP