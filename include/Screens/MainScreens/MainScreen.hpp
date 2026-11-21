#ifndef CLASS_MAIN_SCREEN_HPP
#define CLASS_MAIN_SCREEN_HPP

#include <iomanip>
#include <iostream>

#include "../../Core/User.hpp"
#include "../../Global/Config.hpp"
#include "../../Utils/Color.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../../Utils/Table.hpp"
#include "../../Utils/Util.hpp"
#include "../ClientScreens/AddNewClientScreen.hpp"
#include "../ClientScreens/ClientsListScreen.hpp"
#include "../ClientScreens/DeleteClientScreen.hpp"
#include "../ClientScreens/FindClientScreen.hpp"
#include "../ClientScreens/UpdateClientScreen.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"
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
        draw_screen_header("Main Screen.");

        std::vector<std::string> menus{
            " Show Clients List.", " Add New Client.",
            " Delete Client.",     " Update Client.",
            " Find Client.",       " Transacions.",
            " Manage Users.",      " Login Records.",
            " Currency Exchange.", " Logout.",
        };

        Table table{"Menu"};
        table.add_column("No.", 4, Table::Align::Center);
        table.add_column("Options", 64, Table::Align::Center);

        table.setAlignment(25);
        for (short i = 0, p = 1; i < menus.size(); i++, p *= 2) {
            std::string num = String::zfill(std::to_string(i + 1), 2);
            if (i < menus.size() - 1) {
                num = (CurrentUser.check_access_permission((User::Permissions)p)
                               .issuccessful()
                           ? Color::bright_green(num)
                           : Color::bright_red(num));
            }
            table.add_row({num, menus[i]});
        }
        table.print_menu();

        perfrom_main_menu_option(
            (MainMenuOptions)ScreenHelper::read_option_enum(
                "Please choose option: ", menus.size()));
    }

   private:
    static void back_to_main_menu() {
        ScreenHelper::back_to_selected_screen(
            "Press enter to go back to Main Menu...", show_main_menu);
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
    static void logout() { CurrentUser = User::find("", "").response; }

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
                if (!CurrentUser
                         .check_access_permission(
                             User::Permissions::Transacions)
                         .issuccessful()) {
                    back_to_main_menu();
                    break;
                }

                show_main_menu();
                break;

            case MainMenuOptions::ManageUsers:
                show_manage_users_menu();
                if (CurrentUser.is_deleted()) {
                    logout();
                    break;
                }
                if (!CurrentUser
                         .check_access_permission(
                             User::Permissions::ManageUsers)
                         .issuccessful()) {
                    back_to_main_menu();
                    break;
                }

                show_main_menu();
                break;

            case MainMenuOptions::LoginRecordsList:
                show_login_records_screen();
                back_to_main_menu();
                break;

            case MainMenuOptions::CurrecnyExchange:
                show_currency_exchange_screen();
                if (!CurrentUser
                         .check_access_permission(
                             User::Permissions::CurrencyExchange)
                         .issuccessful()) {
                    back_to_main_menu();
                    break;
                }
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