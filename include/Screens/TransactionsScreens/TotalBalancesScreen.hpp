#ifndef CLASS_TOTAL_BALANCES_SCREEN_HPP
#define CLASS_TOTAL_BALANCES_SCREEN_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "../../Core/BankClient.hpp"
#include "../../Utils/NumberToWords.hpp"
#include "../../Utils/Util.hpp"
#include "../Screen.hpp"

class TotalBalancesScreen : protected Screen {
   public:
    static void show_total_balances() {
        std::vector<BankClient> clients = BankClient::get_clients_list();

        std::string title = "Balances List Screen.";
        std::string subtitle =
            "(" + std::to_string(clients.size()) + ") Client(s).";

        draw_screen_header(title, subtitle, 24);

        std::cout << std::setw(24) << std::left << ""
                  << "_________________________________________________________"
                     "____________\n"
                  << std::endl;

        std::cout << std::setw(25) << std::left << "" << "| " << std::left
                  << std::setw(15) << "Accout Number";
        std::cout << "| " << std::left << std::setw(40) << "Client Name";
        std::cout << "| " << std::left << std::setw(12) << "Balance"
                  << std::endl;

        std::cout << std::setw(24) << std::left << ""
                  << "_________________________________________________________"
                     "____________\n"
                  << std::endl;

        double TotalBalances = BankClient::get_total_balances();

        if (clients.size() == 0)
            std::cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (BankClient Client : clients) {
                PrintClientRecordBalanceLine(Client);
                std::cout << std::endl;
            }

        std::cout << std::setw(24) << std::left << ""
                  << "_________________________________________________________"
                     "____________\n"
                  << std::endl;
        std::cout << std::setw(8) << std::left << ""
                  << "\t\t  Total Balances = " << TotalBalances << std::endl;
        std::cout << std::setw(8) << std::left << "" << "\t\t\t( "
                  << NumberToWords::conver_number_to_words(TotalBalances)
                  << ")\n\n";
    }

   private:
    static void PrintClientRecordBalanceLine(BankClient Client) {
        std::cout << std::setw(25) << std::left << "" << "| " << std::setw(15)
                  << std::left << Client.getAccountNumber();
        std::cout << "| " << std::setw(40) << std::left << Client.getFullName();
        std::cout << "| " << std::setw(12) << std::left << Client.getBalance();
    }
};

#endif  // CLASS_TOTAL_BALANCES_SCREEN_HPP