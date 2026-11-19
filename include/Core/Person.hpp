#ifndef CLASS_PERSON_HPP
#define CLASS_PERSON_HPP

#include <iostream>
#include <string>

#include "Property.hpp"

class Person {
   public:
    Person(const std::string& first_name, const std::string& last_name,
           const std::string& email, const std::string& phone) {
        setFirstName(first_name);
        setLastName(last_name);
        setEmail(email);
        setPhone(phone);
    }
    // setter functions
    void setFirstName(const std::string& value) {
        if (value.empty()) {
            return;
        }
        if (this->first_name_ != value) {
            this->first_name_ = value;
        }
    }
    void setLastName(const std::string& value) {
        if (value.empty()) {
            return;
        }
        if (this->last_name_ != value) {
            this->last_name_ = value;
        }
    }
    void setEmail(const std::string& value) {
        if (value.empty()) {
            return;
        }
        if (this->email_ != value) {
            this->email_ = value;
        }
    }
    void setPhone(const std::string& value) {
        if (value.empty()) {
            return;
        }
        if (this->phone_ != value) {
            this->phone_ = value;
        }
    }
    // getter functions
    std::string getFirstName() { return this->first_name_; }
    std::string getLastName() { return this->last_name_; }
    std::string getFullName() {
        return this->first_name_ + " " + this->last_name_;
    }
    std::string getEmail() { return this->email_; }
    std::string getPhone() { return this->phone_; }

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

   private:
    std::string first_name_;
    std::string last_name_;
    std::string email_;
    std::string phone_;
};

#endif  // CLASS_PERSON_HPP