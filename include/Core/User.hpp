#ifndef CLASS_USER_HPP
#define CLASS_USER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../Global/Config.hpp"
#include "../Utils/InputValidate.hpp"
#include "../Utils/String.hpp"
#include "../Utils/Util.hpp"
#include "Date.hpp"
#include "Files.hpp"
#include "Person.hpp"
#include "Property.hpp"

class User : public Person {
   private:
    enum class ObjectMode { Empty, Update, AddNew };

   public:
    enum class Permissions {
        // Admin = -2,
        FullAccess = -1,
        ListClients = 1,
        AddNewClient = 2,
        DeleteClient = 4,
        UpdateClients = 8,
        FindClient = 16,
        Transacions = 32,
        ManageUsers = 64,
        ListLoginRecords = 128,
        CurrencyExchange = 256,
    };
    enum class SaveStatus {
        Successful = 0,
        UnknownFalied = 1,
        FailedEmpty = 2,
        FailedAccountExist = 3,

    };
    struct LoginRecord {
        std::string Time;
        std::string Username;
        std::string Password;
        std::string Permission;
    };
    User(const ObjectMode mode, const std::string& first_name,
         const std::string& last_name, const std::string& email,
         const std::string& phone, const std::string& username,
         const std::string& password, const short& permissions)
        : Person(first_name, last_name, email, phone),
          users_file(Config::users_file, false),
          login_record_file(Config::login_log_file, false) {
        mode_ = mode;
        setUserName(username);
        setPassword(password);
        setPermissions(permissions);
    }

    // setter functions
    void setUserName(std::string value) {
        if (value.empty()) {
            return;
        }
        if (this->username_ != value) {
            this->username_ = value;
        }
    }
    void setPassword(std::string value) {
        if (value.empty()) {
            return;
        }
        if (this->password_ != value) {
            this->password_ = value;
        }
    }
    void setPermissions(short value) {
        // if (value) {
        //     return;
        // }
        if (this->permissions_ != value) {
            this->permissions_ = value;
        }
    }
    // Date::DateInfo setLoginDate(Date::DateInfo value) {
    //     this->login_date_ = value;
    // }Available

    // getter functions
    std::string getUserName() { return this->username_; }
    std::string getPassword() { return this->password_; }
    short getPermissions() { return this->permissions_; }
    // Date::DateInfo getLoginDate() { return this->login_date_; }

    // properties get and set
    Property<std::string> username{
        [this]() { return getUserName(); },
        [this](const std::string& value) { setUserName(value); }};
    Property<std::string> password{
        [this]() { return getPassword(); },
        [this](const std::string& value) { setPassword(value); }};
    Property<short> permissions{
        [this]() { return getPermissions(); },
        [this](const short& value) { setPermissions(value); }};

    // functions

    static User get_addnew_object(std::string username) {
        return {
            User::ObjectMode::AddNew,  // mode
            "",                        // first name
            "",                        // last name
            "",                        // email
            "",                        // phone
            username,                  // username
            "",                        // password
            0,                         // permissions
        };
    }

    static std::vector<LoginRecord> get_login_records() {
        std::vector<LoginRecord> record;
        Files login_record_file{Config::login_log_file};
        for (std::string& dataline : login_record_file.load_data_list()) {
            record.push_back(convert_to_struct(dataline));
        }
        return record;
    }
    static std::vector<User> get_users_list() {
        std::vector<User> objects;
        Files users_file{Config::users_file};
        for (std::string& dataline : users_file.load_data_list()) {
            objects.push_back(convert_to_object(dataline));
        }
        return objects;
    }

    static User find(std::string username) {
        std::fstream file;

        file.open(Config::users_file, std::ios::in);
        if (file.is_open()) {
            std::string object_line;
            while (getline(file, object_line)) {
                User user = convert_to_object(object_line);
                if (user.getUserName() == username) {
                    file.close();
                    return user;
                }
            }
            file.close();
        }
        return get_empty_object();
    }
    static User find(std::string username, std::string password) {
        User object = User::find(username);
        if (object.getUserName() == username) {
            if (object.getPassword() == password) {
                return object;
            }
        }
        return get_empty_object();
    }

    static bool is_user_exist(std::string username) {
        // User object = User::find(username);
        // return !object.is_empty();
        return !User::find(username).is_empty();
    }

    bool check_access_permission(Permissions permission) {
        if (permission == Permissions::FullAccess) {
            return true;
        } else if (Permissions(this->getPermissions() & (short)permission) ==
                   permission) {
            return true;
        } else {
            return false;
        }
    }
    bool is_empty() const { return this->mode_ == ObjectMode::Empty; }

    void save_login_record() {
        std::string record = get_login_record();
        login_record_file.append_to_file(record);
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
                if (User::is_user_exist(getUserName())) {
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
        std::vector<User> objects = get_users_list();
        for (User& client : objects) {
            if (client.getUserName() == this->getUserName()) {
                client.marked_for_delete_ = true;
                break;
            }
        }

        remove_marked(objects);
        users_file.update_file(convert_to_datalines(objects));
        *this = get_empty_object();
        return true;
    }

   private:
    Files users_file;
    Files login_record_file;
    ObjectMode mode_;

    std::string username_;
    std::string password_;
    short permissions_;
    // Date::DateInfo login_date_;

    bool marked_for_delete_ = false;

    static User get_empty_object() {
        return {
            User::ObjectMode::Empty, "", "", "", "", "", "", 0,
            // false,
        };
    }

    static User convert_to_object(std::string line, std::string sep = "#//#") {
        std::vector<std::string> client_info = String::split(line, sep);

        return User{
            User::ObjectMode::Update,              // mode
            client_info.at(0),                     // first name
            client_info.at(1),                     // last name
            client_info.at(2),                     // email
            client_info.at(3),                     // phone
            client_info.at(4),                     // username
            Util::decrypt(client_info.at(5), 12),  // password
            (short)std::stoi(client_info.at(6)),   // permissions
        };
    }
    static std::vector<std::string> convert_to_vector(User object) {
        // if (object.is_empty()) {
        //     return {};
        // }
        return {
            object.getFirstName(),
            object.getLastName(),
            object.getEmail(),
            object.getPhone(),
            object.getUserName(),
            Util::encrypt(object.getPassword(), 12),
            std::to_string(object.getPermissions()),
        };
    }
    static std::string convert_to_dataline(User object,
                                           std::string sep = "#//#") {
        if (object.is_empty()) {
            return "";
        }
        return String::join(convert_to_vector(object), sep);
    }

    static LoginRecord convert_to_struct(std::string record,
                                         std::string sep = "#//#") {
        std::vector<std::string> record_info = String::split(record, sep);

        return {
            record_info.at(0),  // time
            record_info.at(1),  // username
            record_info.at(2),  // password
            record_info.at(3),  // permissions
        };
    }
    std::string get_login_record(std::string sep = "#//#") {
        std::vector<std::string> record = convert_to_vector(*this);
        std::vector<std::string>::iterator iter = record.begin();
        record.erase(iter, iter + 4);
        record.insert(iter, Date::get_time_string());

        return String::join(record, sep);
    }

    static std::vector<std::string> convert_to_datalines(
        std::vector<User>& objects) {
        std::vector<std::string> datalines;
        for (User& user : objects) {
            datalines.push_back(convert_to_dataline(user));
        }
        return datalines;
    }

    void update() {
        std::vector<std::string> date = users_file.load_data_list();
        for (std::string& item : date) {
            User user = convert_to_object(item);
            if (user.getUserName() == this->getUserName()) {
                item = convert_to_dataline(*this);
                break;
            }
        }
        users_file.update_file(date);
    }
    void add_new() { users_file.append_to_file(convert_to_dataline(*this)); }
    void remove_marked(std::vector<User>& objects) {
        std::vector<User>::iterator iter = objects.begin();
        for (int index = 0; index < objects.size(); index++) {
            if (objects.at(index).marked_for_delete_) {
                objects.erase(iter + index);
            }
        }
    }
};

#endif  // CLASS_USER_HPP