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
            BankClient::get_transfer_logs();

        std::string title = "Transfer Logs List Screen.";
        std::string subtitle = std::to_string(logs.size());

        draw_screen_header(title, subtitle);

        std::cout << std::setw(8) << std::left << ""
                  << "_________________________________________________________"
                     "_________________________________________________\n"
                  << std::endl;
        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(25)
                  << "Date / Time";
        std::cout << "| " << std::setw(12) << "s. accnum";
        std::cout << "| " << std::setw(12) << "r. accnum";
        std::cout << "| " << std::setw(10) << "amount";
        std::cout << "| " << std::setw(12) << "s. balance";
        std::cout << "| " << std::setw(12) << "r. balance";
        std::cout << "| " << std::setw(10) << "by user" << std::endl;
        std::cout << std::setw(8) << std::left << ""
                  << "_________________________________________________________"
                     "_________________________________________________\n"
                  << std::endl;

        if (logs.size() == 0) {
            std::cout << "No Transfer Logs Available In The System!";
        } else {
            for (BankClient::TransferLog log : logs) {
                print_log_line(log);
                std::cout << std::endl;
            }
        }

        std::cout << std::setw(8) << std::left << ""
                  << "_________________________________________________________"
                     "_________________________________________________\n"
                  << std::endl;
    }

   private:
    static void print_log_line(BankClient::TransferLog log) {
        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(25)
                  << log.Time;
        std::cout << "| " << std::setw(12) << log.SenderAccountNumber;
        std::cout << "| " << std::setw(12) << log.RecipientAccountNumber;
        std::cout << "| " << std::setw(10) << log.amount;
        std::cout << "| " << std::setw(12) << log.SenderBalance;
        std::cout << "| " << std::setw(12) << log.RecipientBalance;
        std::cout << "| " << std::setw(10) << log.Username;
    }
};

#endif  // CLASS_TRANSFER_LOGS_SCREEN_HPP