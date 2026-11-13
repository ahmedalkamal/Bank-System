#ifndef CLASS_BANK_CLIENT_HPP
#define CLASS_BANK_CLIENT_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../Global/Config.hpp"
#include "../Utils/InputValidate.hpp"
#include "../Utils/String.hpp"
#include "Date.hpp"
#include "Files.hpp"
#include "Person.hpp"
#include "Property.hpp"

class BankClient : public Person {
   private:
    enum ObjectMode { Empty = 0, Update = 1, AddNew = 2 };

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
               const std::string& pin_code, const float& balance,
               bool traffic = false)
        : Person(first_name, last_name, email, phone, traffic),
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
            if (this->getTraffic()) {
                std::cout << "[WARNING]: Attempted to set empty value for "
                             "pin code, Ignored."
                          << std::endl;
            }
            return;
        }
        if (this->pin_code_ != value) {
            this->pin_code_ = value;
            if (this->getTraffic()) {
                std::cout << "[INFO SET]: Pin code update to: "
                          << this->pin_code_ << std::endl;
            }
        }
    }
    void setBalance(float value) {
        if (value < 0) {
            if (this->getTraffic()) {
                std::cout << "[WARNING]: Attempted to set negative value for "
                             "balance, Ignored."
                          << std::endl;
            }
            return;
        }
        if (this->balance_ != value) {
            this->balance_ = value;
            if (this->getTraffic()) {
                std::cout << "[INFO SET]: Balance update to: " << this->balance_
                          << std::endl;
            }
        }
    }

    // getter functions
    std::string getAccountNumber() {
        if (this->getTraffic()) {
            std::cout
                << "[INFO GET] getAccountNumber accessed, returned value: "
                << this->account_number_ << std::endl;
        }
        return this->account_number_;
    }
    std::string getPinCode() {
        if (this->getTraffic()) {
            std::cout << "[INFO GET] getPinCode accessed, returned value: "
                      << this->pin_code_ << std::endl;
        }
        return this->pin_code_;
    }
    float getBalance() {
        if (this->getTraffic()) {
            std::cout << "[INFO GET] getBalance accessed, returned value: "
                      << this->balance_ << std::endl;
        }
        return this->balance_;
    }
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
            false,                           // traffic
        };
    }

    // properties get and set
    Property<std::string> account_number{
        [this]() { return getAccountNumber(); }};
    Property<std::string> pin_code{
        [this]() { return getPinCode(); },
        [this](const std::string& value) { setPinCode(value); }};
    Property<float> balance{[this]() { return getBalance(); },
                            [this](const float& value) { setBalance(value); }};

    // functions

    static std::vector<BankClient> get_clients_list() {
        std::vector<BankClient> objects;
        Files clients_file{Config::clients_file};
        for (std::string& dataline : clients_file.load_data_list()) {
            objects.push_back(convert_to_object(dataline));
        }
        return objects;
    }

    static std::vector<TransferLog> get_transfer_logs() {
        std::vector<TransferLog> logs;
        Files transfer_log_file{"transfer-logs.txt", false};
        for (std::string& dataline : transfer_log_file.load_data_list()) {
            logs.push_back(convert_to_struct(dataline));
        }
        return logs;
    }

    static double get_total_balances() {
        std::vector<BankClient> clients = get_clients_list();
        double total_balance = 0;
        for (BankClient& client : clients) {
            total_balance += client.getBalance();
        }
        return total_balance;
    }
    static BankClient find(std::string account_number) {
        std::fstream file;

        file.open(Config::clients_file, std::ios::in);
        if (file.is_open()) {
            std::string object_line;
            while (getline(file, object_line)) {
                BankClient client = convert_to_object(object_line);
                if (client.getAccountNumber() == account_number) {
                    file.close();
                    return client;
                }
            }
            file.close();
        }
        return get_empty_object();
    }
    static BankClient find(std::string account_number, std::string pin_code) {
        BankClient object = BankClient::find(account_number);
        if (object.getAccountNumber() == account_number) {
            if (object.getPinCode() == pin_code) {
                return object;
            }
        }
        return get_empty_object();
    }

    static bool is_client_exist(std::string account_number) {
        BankClient object = BankClient::find(account_number);
        return !object.is_empty();
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
    bool remove() {
        std::vector<BankClient> objects = get_clients_list();
        for (BankClient& client : objects) {
            if (client.getAccountNumber() == this->getAccountNumber()) {
                client.marked_for_delete_ = true;
                break;
            }
        }

        remove_marked(objects);
        clients_file.update_file(convert_to_datalines(objects));
        *this = get_empty_object();
        return true;
    }

    bool deposit(float amount) {
        if (amount > 0) {
            balance_ += amount;
            save();
            return true;
        }
        return false;
    }
    bool withdraw(float amount) {
        if (InputValidate::in_range<float>(amount, .0f, balance_)) {
            balance_ -= amount;
            save();
            return true;
        }
        return false;
    }
    bool transfer(float amount, BankClient& recipient, std::string username) {
        if (withdraw(amount)) {
            if (recipient.deposit(amount)) {
                save_transfer_log(amount, recipient, username);
                return true;
            }
        }
        return false;
    }

   private:
    Files clients_file;
    Files transfer_log_file;
    ObjectMode mode_;

    std::string account_number_;
    std::string pin_code_;
    float balance_;
    bool marked_for_delete_ = false;

    void setAccountNumber(std::string value) {
        if (value.empty()) {
            if (this->getTraffic()) {
                std::cout << "[WARNING]: Attempted to set empty value for "
                             "account number, Ignored."
                          << std::endl;
            }
            return;
        }
        if (this->account_number_ != value) {
            this->account_number_ = value;
            if (this->getTraffic()) {
                std::cout << "[INFO SET]: Account number update to: "
                          << this->account_number_ << std::endl;
            }
        }
    }
    static BankClient get_empty_object() {
        return {
            BankClient::ObjectMode::Empty, "", "", "", "", "", "", .0f,
            // false,
        };
    }

    static BankClient convert_to_object(std::string line,
                                        std::string sep = "#//#") {
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
            // false,                           // traffic
        };
    }
    static std::vector<std::string> convert_to_vector(BankClient object) {
        // if (object.is_empty()) {
        //     return {};
        // }
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
        return String::join(convert_to_vector(object), "#//#");
    }
    static std::vector<std::string> convert_to_datalines(
        std::vector<BankClient>& objects) {
        std::vector<std::string> datalines;
        for (BankClient& client : objects) {
            datalines.push_back(convert_to_dataline(client));
        }
        return datalines;
    }

    static TransferLog convert_to_struct(std::string line,
                                         std::string sep = "#//#") {
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
    std::string get_transfer_log(float amount, const BankClient& recipient,
                                 std::string username,
                                 std::string sep = "#//#") {
        std::vector<std::string> record;  // = convert_to_vector(*this);
        // std::vector<std::string>::iterator iter = record.begin();
        // record.erase(iter, iter + 4);
        record.push_back(Date::get_time_string());
        record.push_back(account_number);
        record.push_back(recipient.account_number);
        record.push_back(std::to_string(amount));
        record.push_back(std::to_string(balance));
        record.push_back(std::to_string(recipient.balance));
        record.push_back(username);

        return String::join(record, sep);
    }

    void update() {
        std::vector<std::string> date = clients_file.load_data_list();
        for (std::string& item : date) {
            BankClient client = convert_to_object(item);
            if (client.getAccountNumber() == this->getAccountNumber()) {
                item = convert_to_dataline(*this);
                break;
            }
        }
        clients_file.update_file(date);
    }
    void add_new() { clients_file.append_to_file(convert_to_dataline(*this)); }
    void remove_marked(std::vector<BankClient>& objects) {
        std::vector<BankClient>::iterator iter = objects.begin();
        for (int index = 0; index < objects.size(); index++) {
            if (objects.at(index).marked_for_delete_) {
                objects.erase(iter + index);
            }
        }
    }
};

#endif  // CLASS_BANK_CLIENT_HPP