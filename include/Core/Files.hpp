#ifndef CLASS_FILES_HPP
#define CLASS_FILES_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Property.hpp"

class Files {
   public:
    Files(std::string file_path, bool safety = false) {
        setFilePath(file_path);
        if (safety) {
            // std::vector<std::string> data = load_data_list();
            setBackup(load_data_list());
        }
    }

    // setter functions
    void setFilePath(std::string value) {
        if (!value.empty()) {
            this->file_path_ = value;
        }
    }
    // getter functions
    std::string getFilePath() { return this->file_path_; }
    std::vector<std::string> getBackUp() { return this->backup_; }

    // properties get and set
    Property<std::string> file_path{
        [this]() { return getFilePath(); },
        [this](const std::string& value) { setFilePath(value); }};
    Property<std::vector<std::string>> backup{[this]() { return getBackUp(); }};

    // functions
    bool change_safe_mode(bool value) {
        this->safety_mode_ = value;
        return value;
    }

    std::vector<std::string> load_data_list() {
        std::fstream file;
        std::vector<std::string> data;

        file.open(this->getFilePath(), std::ios::in);
        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                data.push_back(line);
            }
            file.close();
        }
        return data;
    }

    bool append_to_file(const std::string& line) {
        if (this->safety_mode_) {
            setBackup(load_data_list());
        }
        std::fstream file;
        file.open(this->getFilePath(), std::ios::out | std::ios::app);

        if (file.is_open()) {
            file << line << '\n';
            file.close();
            return true;
        }
        return false;
    }

    bool update_file(const std::vector<std::string>& data) {
        if (this->safety_mode_) {
            setBackup(data);
        }
        std::fstream file;
        file.open(this->getFilePath(), std::ios::out);

        if (file.is_open()) {
            for (const std::string& record_line : data) {
                file << record_line << '\n';
            }
            file.close();
            return true;
        }
        return false;
    }

    // resore last data before update or append..
    bool restore_backup() {
        if (!this->safety_mode_) {
            return false;
        }
        update_file(getBackUp());
        return true;
    }

   private:
    bool safety_mode_;
    std::string file_path_;
    std::vector<std::string> backup_;

    void setBackup(std::vector<std::string> data) { this->backup_ = data; }
};
#endif  // CLASS_FILES_HPP