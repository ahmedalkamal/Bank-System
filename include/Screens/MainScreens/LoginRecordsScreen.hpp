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
        if (!has_permission(User::Permissions::ListLoginRecords)) {
            return;
        }

        std::vector<User::LoginRecord> records = User::get_login_records();

        std::string title = "Login Records List Screen.";
        std::string subtitle =
            "(" + std::to_string(records.size()) + ") Record(s).";

        draw_screen_header(title, subtitle);

        std::cout << std::setw(24) << std::left << ""
                  << "_________________________________________________________"
                     "_______________________________\n"
                  << std::endl;

        std::cout << std::setw(25) << std::left << "" << "| " << std::left
                  << std::setw(25) << "Date/Time";
        std::cout << "| " << std::left << std::setw(30) << "User Name";
        std::cout << "| " << std::left << std::setw(12) << "Password";
        std::cout << "| " << std::left << std::setw(12) << "Permissions"
                  << std::endl;

        std::cout << std::setw(24) << std::left << ""
                  << "_________________________________________________________"
                     "_______________________________\n"
                  << std::endl;

        if (records.size() == 0) {
            std::cout << "No Login Records Available In The System!";
        } else {
            for (User::LoginRecord record : records) {
                print_record_line(record);
                std::cout << std::endl;
            }
        }

        std::cout << std::setw(24) << std::left << ""
                  << "_________________________________________________________"
                     "_______________________________\n"
                  << std::endl;
    }

   private:
    static void print_record_line(User::LoginRecord record) {
        std::cout << std::setw(25) << std::left << "" << "| " << std::setw(25)
                  << std::left << record.Time;
        std::cout << "| " << std::setw(30) << std::left << record.Username;
        std::cout << "| " << std::setw(12) << std::left << record.Password;
        std::cout << "| " << std::setw(12) << std::left << record.Permission;
    }
};

#endif  // CLASS_LOGIN_RECORDS_SCREEN_HPP