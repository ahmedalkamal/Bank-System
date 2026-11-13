#ifndef CLASS_PERSON_HPP
#define CLASS_PERSON_HPP

#include <iostream>
#include <string>

#include "Property.hpp"

class Person {
   public:
    Person(const std::string& first_name, const std::string& last_name,
           const std::string& email, const std::string& phone,
           bool traffic = false) {
        this->traffic_ = traffic;
        setFirstName(first_name);
        setLastName(last_name);
        setEmail(email);
        setPhone(phone);
    }
    // setter functions
    void setFirstName(const std::string& value) {
        if (value.empty()) {
            if (this->traffic_) {
                std::cout << "[WARNING]: Attempted to set empty value for "
                             "first name, Ignored."
                          << std::endl;
            }
            return;
        }
        if (this->first_name_ != value) {
            this->first_name_ = value;
            if (this->traffic_) {
                std::cout << "[INFO SET]: First name update to: "
                          << this->first_name_ << std::endl;
            }
        }
    }
    void setLastName(const std::string& value) {
        if (value.empty()) {
            if (this->traffic_) {
                std::cout << "[WARNING]: Attempted to set empty value for "
                             "last name, Ignored."
                          << std::endl;
            }
            return;
        }
        if (this->last_name_ != value) {
            this->last_name_ = value;
            if (this->traffic_) {
                std::cout << "[INFO SET]: Last name update to: "
                          << this->last_name_ << std::endl;
            }
        }
    }
    void setEmail(const std::string& value) {
        if (value.empty()) {
            if (this->traffic_) {
                std::cout << "[WARNING]: Attempted to set empty value for "
                             "email, Ignored."
                          << std::endl;
            }
            return;
        }
        if (this->email_ != value) {
            this->email_ = value;
            if (this->traffic_) {
                std::cout << "[INFO SET]: Email update to: " << this->email_
                          << std::endl;
            }
        }
    }
    void setPhone(const std::string& value) {
        if (value.empty()) {
            if (this->traffic_) {
                std::cout << "[WARNING]: Attempted to set empty value for "
                             "phone, Ignored."
                          << std::endl;
            }
            return;
        }
        if (this->phone_ != value) {
            this->phone_ = value;
            if (this->traffic_) {
                std::cout << "[INFO SET]: Phone update to: " << this->phone_
                          << std::endl;
            }
        }
    }
    void setTraffic(const bool value) { this->traffic_ = value; }
    // getter functions
    std::string getFirstName() {
        if (this->traffic_) {
            std::cout << "[INFO GET] getFirstName accessed, returned value: "
                      << this->first_name_ << std::endl;
        }
        return this->first_name_;
    }
    std::string getLastName() {
        if (this->traffic_) {
            std::cout << "[INFO GET] getLastName accessed, returned value: "
                      << this->last_name_ << std::endl;
        }
        return this->last_name_;
    }
    std::string getFullName() {
        if (this->traffic_) {
            std::cout << "[INFO GET] getFullName accessed, returned value: "
                      << (this->first_name_ + " " + this->last_name_)
                      << std::endl;
        }
        return this->first_name_ + " " + this->last_name_;
    }
    std::string getEmail() {
        if (this->traffic_) {
            std::cout << "[INFO GET] getEmail accessed, returned value: "
                      << this->email_ << std::endl;
        }
        return this->email_;
    }
    std::string getPhone() {
        setTraffic(false);
        if (this->traffic_) {
            std::cout << "[INFO GET] getPhone accessed, returned value: "
                      << this->phone_ << std::endl;
        }
        return this->phone_;
    }
    bool getTraffic() { return this->traffic_; }

    // properties get and set
    Property<std::string> first_name{
        [this]() { return getFirstName(); },
        [this](const std::string& value) { setFirstName(value); }};
    Property<std::string> last_name{
        [this]() { return getLastName(); },
        [this](const std::string& value) { setLastName(value); }};
    Property<std::string> full_name{[this]() { return getFullName(); }};
    Property<std::string> email{
        [this]() { return getEmail(); },
        [this](const std::string& value) { setEmail(value); }};
    Property<std::string> phone{
        [this]() { return getPhone(); },
        [this](const std::string& value) { setPhone(value); }};
    Property<bool> traffic{[this]() { return getTraffic(); },
                           [this](const bool& value) { setTraffic(value); }};

   private:
    bool traffic_ = false;
    std::string first_name_;
    std::string last_name_;
    std::string email_;
    std::string phone_;
};

#endif  // CLASS_PERSON_HPP