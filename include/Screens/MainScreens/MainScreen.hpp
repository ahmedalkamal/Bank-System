#ifndef CLASS_MAIN_SCREEN_HPP
#define CLASS_MAIN_SCREEN_HPP

#include <iomanip>
#include <iostream>

#include "../../Core/User.hpp"
#include "../../Global/Config.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../../Utils/Util.hpp"
#include "../ClientScreens/AddNewClientScreen.hpp"
#include "../ClientScreens/ClientsListScreen.hpp"
#include "../ClientScreens/DeleteClientScreen.hpp"
#include "../ClientScreens/FindClientScreen.hpp"
#include "../ClientScreens/UpdateClientScreen.hpp"
#include "../Screen.hpp"
#include "CurrencyExchangeScreen.hpp"
#include "LoginRecordsScreen.hpp"
#include "ManageUserScreen.hpp"
#include "TransactionsScreen.hpp"

class MainScreen : protected Screen {
   private:
    enum class MainMenuOptions {
        ListClients,
        AddNewClient,
        DeleteClient,
        UpdateClient,
        FindClient,
        TransactionsMenu,
        ManageUsers,
        LoginRecordsList,
        CurrecnyExchange,
        Exit,
    };

   public:
    static void show_main_menu() {
        system(Config::clear.c_str());
        draw_screen_header("console application", "", 39);

        std::cout << std::setw(37) << std::left << ""
                  << "========================================================="
                     "=========\n";
        std::cout << std::setw(57) << std::left << "" << "\tMain Menu\n";
        std::cout << std::setw(37) << std::left << ""
                  << "========================================================="
                     "=========\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[1] Show Clients List.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[2] Add New Client.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[3] Delete Client.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[4] Update Client Info.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[5] Find Client.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[6] Transactions.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[7] Manage Users.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[8] Login Records.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[9] Currency Exchange.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[10] Logout.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "========================================================="
                     "=========\n";

        perfrom_main_menu_option((MainMenuOptions)read_main_menu_option());
    }

   private:
    static void back_to_main_menu() {
        // if (std::cin.fail() || std::cin.peek() != '\n') {
        Util::clear_buffer();
        // }
        std::cout << "Press enter to go back to Main Menu...";
        std::cin.get();
        show_main_menu();
    }

    static short read_main_menu_option() {
        bool valid = false;
        short choice;
        std::cout << std::setw(37) << std::left << ""
                  << "Choose what do you want to do [1 - 10]: ";
        while (!valid) {
            std::cin >> choice;
            valid = InputValidate::is_valid();
            if (!valid) {
                std::cout << std::setw(37) << std::left << ""
                          << "Invalid Input, Enter again [1 - 10]: ";
                continue;
            }
            if (!InputValidate::in_range<short>(choice, 1, 10)) {
                std::cout << std::setw(37) << std::left << ""
                          << "Input Out Of Range, Enter again [1 - 10]: ";
                valid = false;
            }
        }
        return choice - 1;
    }

    static void show_all_clients_screen() {
        // std::cout << "\nClients List Screen Will be here...\n";
        ClientsListScreen::show_clients_list();
    }
    static void show_add_new_clients_screen() {
        // std::cout << "\nAdd New Clients Screen Will be here...\n";
        AddNewClientScreen::show_add_new_client_screen();
    }
    static void show_delete_client_screen() {
        // std::cout << "\nDelete Client Screen Will be here...\n";
        DeleteClientScreen::show_delete_client_screen();
    }
    static void show_update_client_screen() {
        // std::cout << "\nUpdate Client Screen Will be here...\n";
        UpdateClientScreen::show_update_client_screen();
    }
    static void show_find_clients_creen() {
        // std::cout << "\nFind Client Screen Will be here...\n";
        FindClientScreen::show_find_client_screen();
    }
    static void show_transactions_menu() {
        // std::cout << "\nTransactions Menu Will be here...\n";
        TransactionsScreen::show_transactions_menu();
    }
    static void show_manage_users_menu() {
        // std::cout << "\nManage Users Menu Will be here...\n";
        ManageUsersScreen::show_manage_users_menu();
    }
    static void show_login_records_screen() {
        LoginRecordsScreen::show_login_records();
    }
    static void show_currency_exchange_screen() {
        CurrencyExchangeScreen::show_currency_exchange_menu();
    }
    static void show_end_screen() {
        std::cout << "\nEnd Screen Will be here...\n";
    }
    static void logout() { CurrentUser = User::find("", ""); }

    static void perfrom_main_menu_option(MainMenuOptions option) {
        system(Config::clear.c_str());
        switch (option) {
            case MainMenuOptions::ListClients:
                show_all_clients_screen();
                back_to_main_menu();
                break;
            case MainMenuOptions::AddNewClient:
                show_add_new_clients_screen();
                back_to_main_menu();
                break;
            case MainMenuOptions::DeleteClient:
                show_delete_client_screen();
                back_to_main_menu();
                break;
            case MainMenuOptions::UpdateClient:
                show_update_client_screen();
                back_to_main_menu();
                break;
            case MainMenuOptions::FindClient:
                show_find_clients_creen();
                back_to_main_menu();
                break;
            case MainMenuOptions::TransactionsMenu:
                show_transactions_menu();
                if (!CurrentUser.check_access_permission(
                        User::Permissions::Transacions))
                    back_to_main_menu();
                else
                    show_main_menu();
                break;
            case MainMenuOptions::ManageUsers:
                show_manage_users_menu();
                if (!CurrentUser.check_access_permission(
                        User::Permissions::ManageUsers))
                    back_to_main_menu();
                else
                    show_main_menu();
                break;
            case MainMenuOptions::LoginRecordsList:
                show_login_records_screen();
                back_to_main_menu();
                break;
            case MainMenuOptions::CurrecnyExchange:
                show_currency_exchange_screen();
                if (!CurrentUser.check_access_permission(
                        User::Permissions::CurrencyExchange))
                    back_to_main_menu();
                else
                    show_main_menu();
                break;
            case MainMenuOptions::Exit:
                // show_end_screen();
                logout();
                break;
            default:
                break;
        }
    }
};

#endif  // CLASS_MAIN_SCREEN_HPP