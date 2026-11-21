#ifndef CLASS_BANK_CLIENT_HPP
#define CLASS_BANK_CLIENT_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../Global/Config.hpp"
#include "../Global/ResultStatus.hpp"
#include "../Utils/InputValidate.hpp"
#include "../Utils/String.hpp"
#include "Date.hpp"
#include "Files.hpp"
#include "Person.hpp"

class BankClient : public Person {
   private:
    enum ObjectMode { Empty = 0, Update = 1, AddNew = 2 };
    static std::map<std::string, std::string> ClientsMap;

   public:
    enum SaveStatus {
        Successful = 0,
        UnknownFalied = 1,
        FailedEmpty = 2,
        FailedAccountExist = 3,

    };
    struct TransferLog {
        std::string Time;
        std::string SenderAccountNumber;
        std::string RecipientAccountNumber;
        float amount;
        float SenderBalance;
        float RecipientBalance;
        std::string Username;
    };

    BankClient(const ObjectMode mode, const std::string& first_name,
               const std::string& last_name, const std::string& email,
               const std::string& phone, const std::string& account_number,
               const std::string& pin_code, const float& balance)
        : Person(first_name, last_name, email, phone),
          clients_file(Config::clients_file, false),
          transfer_log_file(Config::transfer_log_file, false) {
        this->mode_ = mode;
        setAccountNumber(account_number);
        setPinCode(pin_code);
        setBalance(balance);
    }

    // setter functions
    void setPinCode(std::string value) {
        if (value.empty()) {
            return;
        }
        if (this->pin_code_ != value) {
            this->pin_code_ = value;
        }
    }
    void setBalance(float value) {
        if (value < 0) {
            return;
        }
        if (this->balance_ != value) {
            this->balance_ = value;
        }
    }

    // getter functions
    std::string getAccountNumber() { return this->account_number_; }
    std::string getPinCode() { return this->pin_code_; }
    float getBalance() { return this->balance_; }
    static BankClient get_addnew_object(std::string account_number) {
        return {
            BankClient::ObjectMode::AddNew,  // mode
            "",                              // first name
            "",                              // last name
            "",                              // email
            "",                              // phone
            account_number,                  // account number
            "",                              // pin code
            .0f,                             // balance
        };
    }

    // functions
    static Status<std::vector<BankClient>> get_clients_list() {
        std::vector<BankClient> objects;

        for (const auto& pair : ClientsMap) {
            objects.push_back(convert_to_object(pair.second));
        }
        return {objects, StatusCode::None};
    }

    static Status<std::vector<TransferLog>> get_transfer_logs() {
        std::vector<TransferLog> logs;
        Files transfer_log_file{Config::transfer_log_file};
        Status<std::vector<std::string>> transfer_logs =
            transfer_log_file.load_data_list();

        if (transfer_logs.issuccessful()) {
            for (std::string& dataline : transfer_logs.response) {
                logs.push_back(convert_to_struct(dataline));
            }
            return {logs, StatusCode::None};
        }
        return {{}, transfer_logs.status_code};
    }

    static Status<double> get_total_balances() {
        Status<std::vector<BankClient>> clients = get_clients_list();
        double total_balance = 0;
        if (clients.issuccessful()) {
            for (BankClient& client : clients.response) {
                total_balance += client.getBalance();
            }
            return {total_balance, StatusCode::None};
        }
        return {0, clients.status_code};
    }

    static Status<BankClient> find(std::string account_number) {
        auto user = ClientsMap.find(account_number);

        if (user != ClientsMap.end()) {
            return {convert_to_object(ClientsMap.at(account_number)),
                    StatusCode::None};
        } else {
            return {get_empty_object(), StatusCode::ClientNotFound};
        }
    }

    static Status<BankClient> find(std::string account_number,
                                   std::string pin_code) {
        Status<BankClient> object = BankClient::find(account_number);
        if (object.response.getAccountNumber() == account_number) {
            if (object.response.getPinCode() == pin_code) {
                return object;
            }
        }
        return {get_empty_object(), object.status_code};
    }

    static bool is_client_exist(std::string account_number) {
        Status<BankClient> object = BankClient::find(account_number);
        return !object.response.is_empty();
    }

    bool is_empty() const { return this->mode_ == ObjectMode::Empty; }

    void save_transfer_log(float amount, const BankClient& recipient,
                           std::string username) {
        std::string record = get_transfer_log(amount, recipient, username);
        transfer_log_file.append_to_file(record);
    }

    SaveStatus save() {
        switch (this->mode_) {
            case ObjectMode::Empty: {
                return SaveStatus::FailedEmpty;
            }
            case ObjectMode::Update: {
                this->update();
                return SaveStatus::Successful;
            }
            case ObjectMode::AddNew: {
                if (is_client_exist(getAccountNumber())) {
                    return SaveStatus::FailedAccountExist;
                }
                this->add_new();
                this->mode_ = ObjectMode::Update;
                return SaveStatus::Successful;
            }
                // default:
                // return SaveStatus::Failed;
        }
        return SaveStatus::UnknownFalied;
    }

    Status<bool> remove() {
        auto client = ClientsMap.find(getAccountNumber());

        if (client != ClientsMap.end()) {
            BankClient client =
                convert_to_object(ClientsMap.at(getAccountNumber()));

            ClientsMap.erase(getAccountNumber());
            clients_file.update_file(get_clients_dataline());
            *this = get_empty_object();
            return {true, StatusCode::None};

        } else {
            return {false, StatusCode::ClientNotFound};
        }
    }

    Status<bool> deposit(float amount) {
        // if ()
        if (amount > 0) {
            balance_ += amount;
            save();
            return {true, StatusCode::None};
        }
        return {false, StatusCode::DepositFailed};
    }
    Status<bool> withdraw(float amount) {
        if (InputValidate::in_range<float>(amount, .0f, balance_)) {
            balance_ -= amount;
            save();
            return {true, StatusCode::None};
        }
        return {false, StatusCode::InsufficientBalance};
    }

    Status<bool> transfer(float amount, BankClient& recipient,
                          std::string username) {
        if (getAccountNumber() == recipient.getAccountNumber()) {
            return {false, StatusCode::TransferFailed};
        }

        Status<bool> status = withdraw(amount);
        if (status.issuccessful()) {
            status = recipient.deposit(amount);
            if (status.issuccessful()) {
                save_transfer_log(amount, recipient, username);
                return {true, status.status_code};
            } else {
                status = deposit(amount);
                return {false, StatusCode::TransferFailed};
            }
        }
        return {false, status.status_code};
    }

   private:
    Files clients_file;
    Files transfer_log_file;
    ObjectMode mode_;

    std::string account_number_;
    std::string pin_code_;
    float balance_;

    void setAccountNumber(std::string value) {
        if (value.empty()) {
            return;
        }
        if (this->account_number_ != value) {
            this->account_number_ = value;
        }
    }
    static BankClient get_empty_object() {
        return {
            BankClient::ObjectMode::Empty, "", "", "", "", "", "", .0f,
        };
    }

    static BankClient convert_to_object(std::string line,
                                        std::string sep = Config::separator) {
        std::vector<std::string> client_info = String::split(line, sep);

        return BankClient{
            BankClient::ObjectMode::Update,  // mode
            client_info.at(0),               // first name
            client_info.at(1),               // last name
            client_info.at(2),               // email
            client_info.at(3),               // phone
            client_info.at(4),               // account number
            client_info.at(5),               // pin code
            std::stof(client_info.at(6)),    // balance
        };
    }
    static std::vector<std::string> convert_to_vector(BankClient object) {
        return {
            object.getFirstName(),
            object.getLastName(),
            object.getEmail(),
            object.getPhone(),
            object.getAccountNumber(),
            object.getPinCode(),
            std::to_string(object.getBalance()),
        };
    }
    static std::string convert_to_dataline(BankClient object) {
        if (object.is_empty()) {
            return "";
        }
        return String::join(convert_to_vector(object), Config::separator);
    }

    static TransferLog convert_to_struct(std::string line,
                                         std::string sep = Config::separator) {
        std::vector<std::string> log = String::split(line, sep);
        return {
            log.at(0),
            log.at(1),
            log.at(2),
            std::stof(log.at(3)),
            std::stof(log.at(4)),
            std::stof(log.at(5)),
            log.at(6),
        };
    }
    std::string get_transfer_log(float amount, BankClient recipient,
                                 std::string username,
                                 std::string sep = Config::separator) {
        std::vector<std::string> record;
        record.push_back(Date::get_time_string());
        record.push_back(getAccountNumber());
        record.push_back(recipient.getAccountNumber());
        record.push_back(std::to_string(amount));
        record.push_back(std::to_string(getBalance()));
        record.push_back(std::to_string(recipient.getBalance()));
        record.push_back(username);

        return String::join(record, sep);
    }

    static std::vector<std::string> get_clients_dataline() {
        std::vector<std::string> datalines;
        for (const auto& pair : ClientsMap) {
            datalines.push_back(pair.second);
        }
        return datalines;
    }

    void update() {
        if (ClientsMap.find(getAccountNumber()) != ClientsMap.end()) {
            ClientsMap.at(getAccountNumber()) = convert_to_dataline(*this);
            clients_file.update_file(get_clients_dataline());
        }
    }

    void add_new() {
        std::string line = convert_to_dataline(*this);
        clients_file.append_to_file(line);
        ClientsMap.insert({getAccountNumber(), line});
    }

    static std::string _get_account_number_for_map(std::string line) {
        return convert_to_object(line).getAccountNumber();
    }

    static std::map<std::string, std::string> load_clients_map() {
        std::map<std::string, std::string> clients;
        std::fstream file;

        file.open(Config::clients_file, std::ios::in);
        if (file.is_open()) {
            std::string object_line;
            while (getline(file, object_line)) {
                std::string account_number =
                    _get_account_number_for_map(object_line);

                clients.insert({account_number, object_line});
            }
            file.close();
            return clients;
        }
        return {{}};
    }
};

std::map<std::string, std::string> BankClient::ClientsMap =
    BankClient::load_clients_map();

#endif  // CLASS_BANK_CLIENT_HPP