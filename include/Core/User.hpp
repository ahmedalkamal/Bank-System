#ifndef CLASS_USER_HPP
#define CLASS_USER_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../Global/Config.hpp"
#include "../Global/ResultStatus.hpp"
#include "../Utils/InputValidate.hpp"
#include "../Utils/String.hpp"
#include "../Utils/Util.hpp"
#include "Date.hpp"
#include "Files.hpp"
#include "Person.hpp"

class User : public Person {
   private:
    enum class ObjectMode { Empty, Update, AddNew };
    static std::map<std::string, std::string> UsersMap;

   public:
    enum class Permissions {
        Admin = -2,
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
        if (this->permissions_ != value) {
            this->permissions_ = value;
        }
    }

    // getter functions
    std::string getUserName() { return this->username_; }
    std::string getPassword() { return this->password_; }
    short getPermissions() { return this->permissions_; }
    bool is_deleted() { return this->was_deleted; }
    bool is_admin() { return getPermissions() == (short)Permissions::Admin; }

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

    static Status<std::vector<LoginRecord>> get_login_records() {
        std::vector<LoginRecord> record;
        Files login_record_file{Config::login_log_file};
        Status<std::vector<std::string>> login_logs =
            login_record_file.load_data_list();

        if (login_logs.issuccessful()) {
            for (std::string& dataline : login_logs.response) {
                record.push_back(convert_to_struct(dataline));
            }
            return {record, StatusCode::None};
        }
        return {{}, login_logs.status_code};
    }

    static Status<std::vector<User>> get_users_list() {
        std::vector<User> objects;

        for (const auto& pair : UsersMap) {
            objects.push_back(convert_to_object(pair.second));
        }
        return {objects, StatusCode::None};
    }

    static Status<User> find(std::string username) {
        auto user = UsersMap.find(username);

        if (user != UsersMap.end()) {
            return {convert_to_object(UsersMap.at(username)), StatusCode::None};
        } else {
            return {get_empty_object(), StatusCode::UserNotFound};
        }
    }

    static Status<User> find(std::string username, std::string password) {
        Status<User> object = User::find(username);
        if (object.issuccessful()) {
            if (object.response.getUserName() == username) {
                if (Util::decrypt(object.response.getPassword(),
                                  Config::encryptionKey) == password) {
                    return object;
                }
            }
        } else {
            return {object.response, StatusCode::InvalidUsername};
        }
        return {get_empty_object(), StatusCode::InvalidPassword};
    }

    static bool is_user_exist(std::string username) {
        User object = User::find(username).response;
        return !object.is_empty();
    }

    Status<bool> check_access_permission(Permissions permission) {
        if (this->getPermissions() == (short)Permissions::Admin) {
            return {true, StatusCode::None};
        }
        if (this->getPermissions() == (short)Permissions::FullAccess) {
            return {true, StatusCode::None};
        }
        if (Permissions(this->getPermissions() & (short)permission) ==
            permission) {
            return {true, StatusCode::None};
        } else {
            return {false, StatusCode::AccessDenied};
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
    Status<bool> remove() {
        auto user = UsersMap.find(getUserName());

        if (user != UsersMap.end()) {
            User user = convert_to_object(UsersMap.at(getUserName()));
            if (user.getPermissions() == (short)Permissions::Admin) {
                return {false, StatusCode::UserDeletionFailed};
            }
            UsersMap.erase(getUserName());
            users_file.update_file(get_users_dataline());
            *this = get_empty_object();
            this->was_deleted = true;
            return {true, StatusCode::None};

        } else {
            return {false, StatusCode::UserNotFound};
        }
    }

   private:
    Files users_file;
    Files login_record_file;
    ObjectMode mode_;

    std::string username_;
    std::string password_;
    short permissions_;

    bool was_deleted = false;

    static User get_empty_object() {
        return {
            User::ObjectMode::Empty, "", "", "", "", "", "", 0,
            // false,
        };
    }

    static User convert_to_object(std::string line,
                                  std::string sep = Config::separator) {
        std::vector<std::string> client_info = String::split(line, sep);

        return User{
            User::ObjectMode::Update,             // mode
            client_info.at(0),                    // first name
            client_info.at(1),                    // last name
            client_info.at(2),                    // email
            client_info.at(3),                    // phone
            client_info.at(4),                    // username
            client_info.at(5),                    // password
            (short)std::stoi(client_info.at(6)),  // permissions
        };
    }
    static std::vector<std::string> convert_to_vector(User object) {
        return {
            object.getFirstName(),
            object.getLastName(),
            object.getEmail(),
            object.getPhone(),
            object.getUserName(),
            Util::encrypt(object.getPassword(), Config::encryptionKey),
            std::to_string(object.getPermissions()),
        };
    }
    static std::string convert_to_dataline(
        User object, std::string sep = Config::separator) {
        if (object.is_empty()) {
            return "";
        }
        return String::join(convert_to_vector(object), sep);
    }

    static LoginRecord convert_to_struct(std::string record,
                                         std::string sep = Config::separator) {
        std::vector<std::string> record_info = String::split(record, sep);

        return {
            record_info.at(0),  // time
            record_info.at(1),  // username
            record_info.at(2),  // password
            record_info.at(3),  // permissions
        };
    }
    std::string get_login_record(std::string sep = Config::separator) {
        std::vector<std::string> record = convert_to_vector(*this);
        std::vector<std::string>::iterator iter = record.begin();
        record.erase(iter, iter + 4);
        record.insert(iter, Date::get_time_string());

        return String::join(record, sep);
    }

    static std::vector<std::string> get_users_dataline() {
        std::vector<std::string> datalines;
        for (const auto& pair : UsersMap) {
            datalines.push_back(pair.second);
        }
        return datalines;
    }

    void update() {
        if (UsersMap.find(getUserName()) != UsersMap.end()) {
            UsersMap.at(getUserName()) = convert_to_dataline(*this);
            users_file.update_file(get_users_dataline());
        }
    }
    void add_new() {
        std::string line = convert_to_dataline(*this);
        users_file.append_to_file(line);
        UsersMap.insert({getUserName(), line});
    }

    static std::string _get_username_for_map(std::string line) {
        return convert_to_object(line).getUserName();
    }

    static std::map<std::string, std::string> load_users_map() {
        std::map<std::string, std::string> users;
        std::fstream file;

        file.open(Config::users_file, std::ios::in);
        if (file.is_open()) {
            std::string object_line;
            while (getline(file, object_line)) {
                std::string username = _get_username_for_map(object_line);
                // std::cout << username;
                users.insert({username, object_line});
            }
            file.close();
            return users;
        }
        return {{}};
    }
};

std::map<std::string, std::string> User::UsersMap = User::load_users_map();

#endif  // CLASS_USER_HPP