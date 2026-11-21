#ifndef CLASS_LOGIN_RECORDS_SCREEN_HPP
#define CLASS_LOGIN_RECORDS_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/User.hpp"
#include "../../Utils/Util.hpp"
#include "../Screen.hpp"

class LoginRecordsScreen : protected Screen {
   public:
    static void show_login_records() {
        std::vector<User::LoginRecord> records =
            User::get_login_records().response;
        std::string title = "Login Records List Screen.";
        std::string subtitle =
            "(" + std::to_string(records.size()) + ") Record(s).";
        draw_screen_header(title, subtitle);

        if (!has_permission(User::Permissions::ListLoginRecords)) {
            return;
        }

        Table table{title, subtitle};
        table.setAlignment(11);

        if (records.size() == 0) {
            table.panel({Color::bright_red(
                            "No Login Records Available In The System!")},
                        95, Table::Align::Center, true);
            return;
        }

        table.add_column("Date / Time", 32, Table::Align::Center);
        table.add_column("User Name", 20, Table::Align::Center);
        table.add_column("Password", 20, Table::Align::Center);
        table.add_column("Permissions", 20, Table::Align::Center);

        for (User::LoginRecord record : records) {
            table.add_row({
                " " + record.Time,
                " " + record.Username,
                " " + record.Password,
                " " + record.Permission,
            });
        }
        table.print_table();
    }
};

#endif  // CLASS_LOGIN_RECORDS_SCREEN_HPP