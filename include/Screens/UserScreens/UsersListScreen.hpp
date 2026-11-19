#ifndef CLASS_USERS_LIST_SCREEN_HPP
#define CLASS_USERS_LIST_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <vector>

#include "../../Core/User.hpp"
#include "../../Utils/Color.hpp"
#include "../../Utils/Table.hpp"
#include "../Screen.hpp"

class UsersListScreen : protected Screen {
   public:
    static void show_users_list() {
        std::vector<User> users = User::get_users_list().response;
        std::string title = "Users List Screen.";
        std::string subtitle =
            "(" + std::to_string(users.size()) + ") User(s).";

        draw_screen_header(title, subtitle);

        Table table{title, subtitle};
        table.setAlignment(11);

        table.add_column("User Name", 11, Table::Align::Center);
        table.add_column("Full Name", 25, Table::Align::Center);
        table.add_column("Phone", 12, Table::Align::Center);
        table.add_column("Email", 20, Table::Align::Center);
        table.add_column("Password", 10, Table::Align::Center);
        table.add_column("Permissions", 12, Table::Align::Center);

        if (users.size() == 0) {
            table.panel(
                {Color::bright_red("No Users Available In The System!")}, 95,
                Table::Align::Center, true);

        } else {
            for (User user : users) {
                table.add_row(
                    {user.getUserName(), user.getFullName(), user.getPhone(),
                     user.getEmail(), user.getPassword(),
                     std::to_string(user.getPermissions())},
                    Table::Align::Center);
            }
            table.print_table();
        }
    }
};

#endif  // CLASS_USERS_LIST_SCREEN_HPPbb