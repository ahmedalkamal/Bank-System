#ifndef CLASS_SCREEN_HELPER_HPP
#define CLASS_SCREEN_HELPER_HPP

#include <iomanip>
#include <map>
#include <string>

#include "../Core/User.hpp"
#include "../Global/ResultStatus.hpp"
#include "../Utils/Color.hpp"
#include "../Utils/InputValidate.hpp"
#include "../Utils/Table.hpp"
#include "../Utils/Util.hpp"

class ScreenHelper {
   public:
    static void print_object_card(std::string title,
                                  std::map<std::string, std::string> rows) {
        Table table{title};
        table.add_column("", 16);
        table.add_column(title, 45, Table::Align::Center);

        for (const auto& pair : rows) {
            table.add_row({" " + pair.first, " " + pair.second});
        }

        table.setAlignment(25);
        table.print_table();
    }

    template <typename T>
    static void read_person_info(T& person) {
        std::cout << std::setw(30) << std::left << "";
        person.setFirstName(InputValidate::read_template<std::string>(
            "[+] Please Enter Firs Name: "));

        std::cout << std::setw(30) << std::left << "";
        person.setLastName(InputValidate::read_template<std::string>(
            "[+] Please Enter Last Name: "));

        std::cout << std::setw(30) << std::left << "";
        person.setEmail(InputValidate::read_template<std::string>(
            "[+] Please Enter Email: "));

        std::cout << std::setw(30) << std::left << "";
        person.setPhone(InputValidate::read_template<std::string>(
            "[+] Please Enter Phone: "));
    }

    static std::string format_number(double num) {
        std::string number = std::to_string(num);

        short zero = 0;
        for (short i = short(number.find(".")); i < number.size(); i++) {
            if (zero == 3) {
                return number.substr(0, i - 2);
            }
            if (number[i] == '0') {
                zero++;
            } else {
                zero = 0;
            }
        }
        if (num == 0) return "0.0";
        return number;
    };

    template <typename T>
    static std::string read_object_id(std::string title, bool is_exist,
                                      Status<T> (*func)(std::string)) {
        short attempt = 3;
        std::string object_id = "";

        std::cout << std::setw(30) << std::left << "";
        object_id = InputValidate::read_template<std::string>(
            "[+] Please enter " + title + ": ");

        while (func(object_id).response.is_empty() == is_exist) {
            std::cout << "\n" << std::setw(30) << std::left << "";
            if (attempt <= 0) {
                std::cout << "[!] "
                          << Color::bright_red(
                                 "Go and check the list, then try again!. \n");
                return "";
            }
            attempt--;
            object_id = InputValidate::read_template<std::string>(
                "[+] " +
                Color::bright_yellow(
                    title + (is_exist ? " is not found" : " is already used")) +
                ", choose another one: ");
        }

        return object_id;
    }

    static short read_option_enum(std::string message, short max) {
        bool valid = false;
        short choice;

        std::cout << std::setw(30) << std::left << "" << "[+] " + message;
        while (!valid) {
            std::cin >> choice;
            valid = InputValidate::is_valid();
            if (!valid) {
                std::cout << "\n"
                          << std::setw(30) << std::left << ""
                          << "[!] " + Color::bright_yellow("Invalid Input") +
                                 ", " + message;
                continue;
            }
            if (!InputValidate::in_range<short>(choice, 1, max)) {
                std::cout << "\n"
                          << std::setw(30) << std::left << ""
                          << "[!] " +
                                 Color::bright_yellow("Input Out Of Range") +
                                 ", " + message;
                valid = false;
            }
        }
        return choice - 1;
    }

    static void back_to_selected_screen(std::string message, void (*screen)()) {
        // if (std::cin.fail() || std::cin.peek() != '\n') {
        Util::clear_buffer();
        // }
        std::cout << "\n\n" + message;
        std::cin.get();
        screen();
    }

    static short read_permissions_to_set() {
        short permissions = 0;
        // char answer = 'n';

        std::cout << std::setw(30) << std::left << "";
        char answer = InputValidate::read_template<char>(
            "[?] Do you want to give Full access y/n ? ");
        if (std::tolower(answer) == 'y')
            return (short)User::Permissions::FullAccess;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Show clients list y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::ListClients;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Add new clients y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::AddNewClient;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Delete client y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::DeleteClient;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Update clients y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::UpdateClients;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Find client y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::FindClient;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Transactios y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::Transacions;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Manage users y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::ManageUsers;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Show Login Records y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::ListLoginRecords;

        std::cout << std::setw(30) << std::left << "";
        answer = InputValidate::read_template<char>(
            "[?] Give access to Currency Exchange Records y/n ? ");
        if (std::tolower(answer) == 'y')
            permissions += (short)User::Permissions::CurrencyExchange;

        return permissions;
    }

   private:
};

#endif  // CLASS_SCREEN_HELPER_HPP