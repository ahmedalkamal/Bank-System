#ifndef CLASS_TRANSACTIONS_SCREEN_HPP
#define CLASS_TRANSACTIONS_SCREEN_HPP

#include <iomanip>
#include <iostream>

#include "../../Core/User.hpp"
#include "../../Global/Config.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"
#include "../ScreenHelper.hpp"
#include "../TransactionsScreens/DepositScreen.hpp"
#include "../TransactionsScreens/TotalBalancesScreen.hpp"
#include "../TransactionsScreens/TransferLogsScreen.hpp"
#include "../TransactionsScreens/TransferScreen.hpp"
#include "../TransactionsScreens/WithdrawScreen.hpp"

class TransactionsScreen : protected Screen {
   private:
    enum class TransactionsMenuOptions {
        Deposit,
        Withdraw,
        Transfer,
        TotalBalance,
        TransferLogs,
        MainMenu,
    };

   public:
    static void show_transactions_menu() {
        system(Config::clear.c_str());
        draw_screen_header("Transactions Screen.");
        if (!has_permission(User::Permissions::Transacions)) {
            return;
        }

        std::vector<std::string> menus{
            " Deposit.",        " Withdraw.",     " Transfer.",
            " Total Balances.", " Trasfer Logs.", " Main Menu",
        };

        Table table{"Menu"};
        table.add_column("No.", 4, Table::Align::Center);
        table.add_column(" Options", 64, Table::Align::Center);

        table.setAlignment(25);
        for (short i = 0; i < menus.size(); i++) {
            std::string num = String::zfill(std::to_string(i + 1), 2);
            table.add_row({num, menus[i]});
        }
        table.print_menu();
        perform_transactions_menu_option(
            (TransactionsMenuOptions)ScreenHelper::read_option_enum(
                "Please choose option: ", menus.size()));
    }

   private:
    static void back_to_transactions_menu() {
        ScreenHelper::back_to_selected_screen(
            "Press enter to go back to Transactions Menu...",
            show_transactions_menu);
    }

    static void show_deposit_screen() {
        // std::cout << "\nDeposit Screen will be here. \n";
        DepositScreen::show_deposit_screen();
    }
    static void show_withdraw_screen() {
        // std::cout << "\nWithdraw Screen will be here. \n";
        WithdrawScreen::show_withdraw_screen();
    }
    static void show_tranfer_screen() {
        // std::cout << "Transfer Screen will be here. \n";
        TransferScreen::show_transfer_screen();
    }
    static void show_total_balances_screen() {
        // std::cout << "Total Balances Screen will be here. \n";
        TotalBalancesScreen::show_total_balances();
    }
    static void show_transfer_logs_screen() {
        // std::cout << "Transfer Logs Screen will be here. \n";
        TransferLogsScreen::show_transfer_logs_screen();
    }

    static void perform_transactions_menu_option(
        TransactionsMenuOptions option) {
        system(Config::clear.c_str());

        switch (option) {
            case TransactionsMenuOptions::Deposit:
                show_deposit_screen();
                back_to_transactions_menu();
                break;
            case TransactionsMenuOptions::Withdraw:
                show_withdraw_screen();
                back_to_transactions_menu();
                break;
            case TransactionsMenuOptions::Transfer:
                show_tranfer_screen();
                back_to_transactions_menu();
                break;
            case TransactionsMenuOptions::TotalBalance:
                show_total_balances_screen();
                back_to_transactions_menu();
                break;
            case TransactionsMenuOptions::TransferLogs:
                show_transfer_logs_screen();
                back_to_transactions_menu();
                break;
            case TransactionsMenuOptions::MainMenu:
                /* code */
            default:
                break;
        }
    }
};

#endif  // CLASS_TRANSACTIONS_SCREEN_HPP