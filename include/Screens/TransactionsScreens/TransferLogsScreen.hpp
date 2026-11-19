#ifndef CLASS_TRANSFER_LOGS_SCREEN_HPP
#define CLASS_TRANSFER_LOGS_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Utils/InputValidate.hpp"
#include "../Screen.hpp"

class TransferLogsScreen : protected Screen {
   public:
    static void show_transfer_logs_screen() {
        std::vector<BankClient::TransferLog> logs =
            BankClient::get_transfer_logs().response;

        std::string title = "Transfer Logs List Screen.";
        std::string subtitle = std::to_string(logs.size());

        draw_screen_header(title, subtitle);

        Table table{title, subtitle};
        table.setAlignment(11);

        table.add_column(" Date / Time", 23);
        table.add_column(" S. no.", 9);
        table.add_column(" R. no.", 9);
        table.add_column(" Amount", 11);
        table.add_column(" S. Balance.", 13);
        table.add_column(" R. Balance.", 13);
        table.add_column(" By User", 11);

        double TotalBalances = BankClient::get_total_balances().response;

        if (logs.size() == 0) {
            table.panel({Color::bright_red(
                            "No Transfer Logs Available In The System!")},
                        95, Table::Align::Center, true);
        }

        else {
            for (BankClient::TransferLog log : logs) {
                table.add_row(get_transfer_log(log));
            }
            table.print_table();
        }
    }

   private:
    static std::string format_balance(std::string balance) {
        short zero = 0;
        for (short i = short(balance.find(".")); i < balance.size(); i++) {
            if (zero == 3) {
                return balance.substr(0, i - 1);
            }
            if (balance[i] == '0') {
                zero++;
            } else {
                zero = 0;
            }
        }
        return "0.0";
    };

    static std::vector<std::string> get_transfer_log(
        BankClient::TransferLog log) {
        std::vector<std::string> record;
        record.push_back(" " + log.Time);
        record.push_back(" " + log.SenderAccountNumber);
        record.push_back(" " + log.RecipientAccountNumber);
        record.push_back(" " + format_balance(std::to_string(log.amount)));
        record.push_back(" " +
                         format_balance(std::to_string(log.SenderBalance)));
        record.push_back(" " +
                         format_balance(std::to_string(log.RecipientBalance)));
        record.push_back(" " + log.Username);

        return record;
    }
};

#endif  // CLASS_TRANSFER_LOGS_SCREEN_HPP