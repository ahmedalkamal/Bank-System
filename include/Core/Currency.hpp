#ifndef CLASS_CURRENCY_HPP
#define CLASS_CURRENCY_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../Global/Config.hpp"
#include "../Global/ResultStatus.hpp"
#include "../Utils/String.hpp"
#include "Files.hpp"
#include "Property.hpp"

class Currency {
   private:
    enum class ObjectMode { Empty, Update };

   public:
    enum class FindBy { Country, CurrencyCode };

    Currency(const ObjectMode& mode, const std::string& country,
             const std::string& currency_code, const std::string& currency_name,
             const float& rate)
        : currency_file(Config::currencies_file, false) {
        mode_ = mode;
        country_ = country;
        currency_code_ = currency_code;
        currency_name_ = currency_name;
        this->rate_ = rate;
    }

    // getter functions
    std::string getCountry() { return country_; }
    std::string getCurrencyCode() { return currency_code_; }
    std::string getCurrencyName() { return currency_name_; }
    float getRate() { return rate_; }

    // properties function
    Property<std::string> country{[this]() { return getCountry(); }};
    Property<std::string> currency_code{[this]() { return getCurrencyCode(); }};
    Property<std::string> currency_name{[this]() { return getCurrencyName(); }};
    Property<float> rate{[this]() { return getRate(); }};

    // functions
    bool is_empty() { return mode_ == ObjectMode::Empty; }

    static Currency get_empty_object() {
        return {Currency::ObjectMode::Empty, "", "", "", .0f};
    }

    bool update_rate(float rate) {
        if (rate > .0f) {
            rate_ = rate;
            update();
            return true;
        }
        return false;
    }
    float convert_to_USD(float amount) { return amount / getRate(); }
    float convert_to_other_currency(float amount, Currency currency) {
        float in_usd = convert_to_USD(amount);
        return in_usd * currency.getRate();
    }

    static Status<Currency> find_by_code(std::string currency_code) {
        return find(currency_code, Currency::FindBy::CurrencyCode);
    }
    static Status<Currency> find_by_country(std::string country) {
        return find(country, Currency::FindBy::Country);
    }

    static bool is_currency_exist(std::string currency_code) {
        Status<Currency> currency = Currency::find_by_code(currency_code);
        return !currency.response.is_empty();
    }

    static Status<std::vector<Currency>> get_currency_list() {
        return load_currencies_object_data();
    }

   private:
    Files currency_file;
    ObjectMode mode_;

    std::string country_;
    std::string currency_code_;
    std::string currency_name_;
    float rate_;

    static Currency convert_to_currency_object(
        std::string line, std::string sep = Config::separator) {
        std::vector<std::string> currency_date = String::split(line, sep);

        return Currency{
            Currency::ObjectMode::Update,    // mode
            currency_date.at(0),             // country
            currency_date.at(1),             // currency code
            currency_date.at(2),             // currency name
            std::stof(currency_date.at(3)),  // rate
        };
    }

    static std::string convert_to_currency_line(
        Currency currency, std::string sep = Config::separator) {
        std::string currency_record = "";

        currency_record += currency.getCountry() + sep;
        currency_record += currency.getCurrencyCode() + sep;
        currency_record += currency.getCurrencyName() + sep;
        currency_record += std::to_string(currency.getRate());

        return currency_record;
    }

    static std::vector<std::string> convert_to_currencies_line(
        std::vector<Currency> currencies) {
        std::vector<std::string> currencies_records;
        for (Currency& currency : currencies) {
            currencies_records.push_back(convert_to_currency_line(currency));
        }
        return currencies_records;
    }

    static Status<std::vector<Currency>> load_currencies_object_data() {
        std::vector<Currency> currencies;
        Files currency_file{Config::currencies_file};
        Status<std::vector<std::string>> currency_data =
            currency_file.load_data_list();

        if (currency_data.issuccessful()) {
            for (std::string& currency_line : currency_data.response) {
                currencies.push_back(convert_to_currency_object(currency_line));
            }
            return {currencies, StatusCode::None};
        }
        return {{}, currency_data.status_code};
    }

    void update() {
        Status<std::vector<Currency>> currencies =
            load_currencies_object_data();
        if (currencies.issuccessful()) {
            for (Currency& currency : currencies.response) {
                if (currency.getCurrencyCode() == getCurrencyCode()) {
                    // currency = *this;
                    // break;
                    currency.rate_ = getRate();
                }
            }
            currency_file.update_file(
                convert_to_currencies_line(currencies.response));
        }
    }

    static Status<Currency> find(std::string target, FindBy by) {
        target = String::upper(target);
        Files currency_file{Config::currencies_file};
        Status<std::vector<std::string>> currency_data =
            currency_file.load_data_list();

        if (currency_data.issuccessful()) {
            for (std::string& currency_line : currency_data.response) {
                std::string container =
                    String::split(currency_line, Config::separator)
                        .at((short)by);

                container = String::upper(container);

                if (target == container) {
                    return {convert_to_currency_object(currency_line),
                            StatusCode::None};
                }
            }
        } else
            return {get_empty_object(), currency_data.status_code};

        return {get_empty_object(),
                (by == FindBy::CurrencyCode ? StatusCode::CurrencyCodeInvalid
                                            : StatusCode::CountryInvalid)};
    }
};

#endif  // CLASS_CURRENCY_HPP