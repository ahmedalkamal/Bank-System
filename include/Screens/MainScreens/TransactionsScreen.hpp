#ifndef CLASS_TRANSACTIONS_SCREEN_HPP
#define CLASS_TRANSACTIONS_SCREEN_HPP

#include <iomanip>
#include <iostream>

#include "../../Core/User.hpp"
#include "../../Global/Config.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"
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
        if (!has_permission(User::Permissions::Transacions)) {
            return;
        }

        system(Config::clear.c_str());
        draw_screen_header("console application", "", 39);

        std::cout << std::setw(37) << std::left << ""
                  << "========================================================="
                     "=========\n";
        std::cout << std::setw(57) << std::left << ""
                  << "Transactions Menu\n";
        std::cout << std::setw(37) << std::left << ""
                  << "========================================================="
                     "=========\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[1] Deposit.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[2] Withdraw.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[3] Transfer.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[4] Total Balances.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[5] Transfer Logs.\n";
        std::cout << std::setw(37) << std::left << ""
                  << "\t[6] Main Menu.\n";

        std::cout << std::setw(37) << std::left << ""
                  << "========================================================="
                     "=========\n";

        perform_transactions_menu_option(
            (TransactionsMenuOptions)read_transactions_menu_option());
    }

   private:
    static void back_to_transactions_menu() {
        // if (std::cin.fail() || std::cin.peek() != '\n') {
        Util::clear_buffer();
        // }
        std::cout << "Press enter to go back to Transactions Menu...";
        std::cin.get();
        show_transactions_menu();
    }

    static short read_transactions_menu_option() {
        bool valid = false;
        short choice;
        std::cout << std::setw(37) << std::left << ""
                  << "Choose what do you want to do [1 - 6]: ";
        while (!valid) {
            std::cin >> choice;
            valid = InputValidate::is_valid();
            if (!valid) {
                std::cout << std::setw(37) << std::left << ""
                          << "Invalid Input, Enter again [1 - 6]: ";
                continue;
            }
            if (!InputValidate::in_range<short>(choice, 1, 6)) {
                std::cout << std::setw(37) << std::left << ""
                          << "Input Out Of Range, Enter again [1 - 6]: ";
                valid = false;
            }
        }
        return choice - 1;
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