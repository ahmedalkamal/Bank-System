#ifndef CLASS_DATE_HPP
#define CLASS_DATE_HPP
// ^ is old style of #pragma once...

#include <cstdio>
#include <ctime>
#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <vector>

#include "../Utils/String.hpp"

enum class CompareResult {
    before = -1,
    equal = 0,
    after = 1,
};

// class DateInfo {};

class Date  // date management
{
   public:
    class DateInfo {
       public:
        DateInfo() {}
        // the default format %y%m%d
        DateInfo(std::string value) {
            std::vector<std::string> date = split_date(value);
            year = (std::stoi(date.at(0)));
            month = (std::stoi(date.at(1)));
            day = (std::stoi(date.at(2)));
        }
        DateInfo(short year, short month, short day) {
            this->year = (year);
            this->month = (month);
            this->day = (day);
        }
        short year = 1;
        short month = 1;
        short day = 1;
    };

    // system date
    Date() {
        DateInfo date = get_system_date();
        setYear(date.year);
        setMonth(date.month);
        setDay(date.day);
    }
    // the default format %y%m%d
    Date(std::string value) {
        std::vector<std::string> date = split_date(value);
        setYear(std::stoi(date.at(0)));
        setMonth(std::stoi(date.at(1)));
        setDay(std::stoi(date.at(2)));
    }
    Date(short year, short month, short day) {
        setYear(year);
        setMonth(month);
        setDay(day);
    }
    Date(short year, short days) {
        setYear(year);
        for (short i = days; i > 0; i--) {
            increment_one_day(_time_date);
        }
    }
    Date(DateInfo date) {
        setYear(date.year);
        setMonth(date.month);
        setDay(date.day);
    }

    // const DateInfo &get_date() const { return *this; }
    // setter and getter..
    void setYear(short year) { _time_date.year = year; }
    void setMonth(short month) { _time_date.month = month; }
    void setDay(short day) { _time_date.day = day; }

    short getYear() const { return _time_date.year; }
    short getMonth() const { return _time_date.month; }
    short getDay() const { return _time_date.day; }
    DateInfo getDate() const { return _time_date; }

    // ==================== Year ====================
    bool is_valid_year(std::optional<short> year = std::nullopt) {
        short target_year = year.has_value() ? *year : _time_date.year;
        return target_year >= min_year && target_year <= max_year;
    }

    void change_range_year(short min_year, short max_year) {
        if (min_year > max_year) {
            std::cout << "Invalid Year range...\n\n";
            return;
        }
        this->min_year = min_year;
        this->max_year = max_year;
    }

    bool is_leap_year(std::optional<short> year = std::nullopt) {
        short target_year = year.has_value() ? *year : _time_date.year;
        return target_year % 400 == 0 ||
               (target_year % 4 == 0 && target_year % 100 != 0);
    }

    short get_year_days(std::optional<short> year = std::nullopt) {
        return is_leap_year(year) ? 366 : 365;
    }

    int get_year_hours(std::optional<short> year = std::nullopt) {
        return get_year_days(year) * 24;
    }

    int get_year_minutes(std::optional<short> year = std::nullopt) {
        return get_year_hours(year) * 60;
    }

    int get_year_seconds(std::optional<short> year = std::nullopt) {
        return get_year_minutes(year) * 60;
    }

    // ==================== Month ====================

    bool is_valid_month(std::optional<short> month = std::nullopt) {
        short target_month = month.has_value() ? *month : _time_date.month;
        return target_month >= 1 && target_month <= 12;
    }
    short get_month_days(std::optional<short> year = std::nullopt,
                         std::optional<short> month = std::nullopt) {
        // return (month == 2) ? (is_leap_year (year) ? 29 : 28)
        //                     : 30 + ((month < 8) ? month % 2 : !(month % 2));

        short target_year = year.has_value() ? *year : _time_date.year;
        short target_month = month.has_value() ? *month : _time_date.month;

        if (target_month == 2) return 28 + is_leap_year(target_year);
        return 30 +
               ((target_month < 8) ? target_month % 2 : !(target_month % 2));
    }

    int get_month_hours(const std::optional<short> year = std::nullopt,
                        const std::optional<short> month = std::nullopt) {
        return get_month_days(year, month) * 24;
    }

    int get_month_minutes(const std::optional<short> year = std::nullopt,
                          const std::optional<short> month = std::nullopt) {
        return get_month_hours(year, month) * 60;
    }

    int get_month_seconds(const std::optional<short> year = std::nullopt,
                          const std::optional<short> month = std::nullopt) {
        return get_month_minutes(year, month) * 60;
    }

    // ==================== Day ====================
    bool is_valid_day(const std::optional<short> year = std::nullopt,
                      const std::optional<short> month = std::nullopt,
                      const std::optional<short> day = std::nullopt) {
        short target_day = day.has_value() ? *day : _time_date.day;
        short days = get_month_days(year, month);
        return target_day <= days && target_day >= 1;
    }

    // ==================== Date Comparison ====================

    static bool is_dates_equal(const DateInfo& date_one,
                               const DateInfo& date_two) {
        return date_one.year == date_two.year &&
               date_one.month == date_two.month && date_one.day == date_two.day;
    }

    static bool is_date_before(const DateInfo& date_one,
                               const DateInfo& date_two) {
        if (date_one.year != date_two.year)
            return date_one.year < date_two.year;

        if (date_one.month != date_two.month)
            return date_one.month < date_two.month;

        return date_one.day < date_two.day;
    }

    static bool is_date_after(const DateInfo& date_one,
                              const DateInfo& date_two) {
        return !is_date_before(date_one, date_two) &&
               !is_dates_equal(date_one, date_two);
    }

    static CompareResult compare_dates(const DateInfo& date_one,
                                       const DateInfo& date_two) {
        if (is_dates_equal(date_one, date_two))
            return CompareResult::equal;
        else if (is_date_before(date_one, date_two))
            return CompareResult::before;
        /*
        else if (is_date_after (date_one, date_two))
             return CompareResult::after;   */
        return CompareResult::after;
    }

    bool is_dates_equal(const DateInfo& date_two) {
        return is_dates_equal(_time_date, date_two);
    }
    bool is_date_before(const DateInfo& date_two) {
        return is_date_before(_time_date, date_two);
    }
    bool is_date_after(const DateInfo& date_two) {
        return is_date_after(_time_date, date_two);
    }
    CompareResult compare_dates(const DateInfo& date_two) {
        return compare_dates(_time_date, date_two);
    }

    // ==================== Date Information ====================

    bool is_last_day_in_month(
        const std::optional<DateInfo>& date = std::nullopt) {
        DateInfo target_date = date.has_value() ? *date : _time_date;
        return target_date.day ==
               get_month_days(target_date.year, target_date.month);
    }

    bool is_last_month_in_year(
        const std::optional<DateInfo>& date = std::nullopt) {
        DateInfo target_date = date.has_value() ? *date : _time_date;
        return target_date.month == 12;
    }

    bool is_valid_date(const std::optional<DateInfo>& date = std::nullopt) {
        DateInfo target_date = date.has_value() ? *date : _time_date;
        return is_valid_year(target_date.year) &&
               is_valid_month(target_date.month) &&
               is_valid_day(target_date.year, target_date.month,
                            target_date.day);
    }

    short get_days_since_beginning_year(
        const std::optional<DateInfo>& date = std::nullopt) {
        DateInfo target_date = date.has_value() ? *date : _time_date;
        short days = 0;

        for (short month = 1; month < target_date.month; month++)
            days += get_month_days(target_date.year, month);

        return days + target_date.day;
    }

    short get_remaining_year_days(
        const std::optional<DateInfo>& date = std::nullopt) {
        DateInfo target_date = date.has_value() ? *date : _time_date;
        return get_year_days(target_date.year) -
               get_days_since_beginning_year(date);
    }

    DateInfo get_latest_date(const DateInfo& date_one,
                             const DateInfo& date_two) {
        if (is_date_after(date_one, date_two))
            return date_one;
        else
            return date_two;
    }

    DateInfo get_earliest_date(const DateInfo& date_one,
                               const DateInfo& date_two) {
        if (is_date_before(date_one, date_two))
            return date_one;
        else
            return date_two;
    }

    // ==================== Calendar ====================

    short gregorian_calendar(const std::optional<short> year = std::nullopt,
                             const std::optional<short> month = std::nullopt,
                             const std::optional<short> day = std::nullopt) {
        short target_year = year.has_value() ? *year : _time_date.year;
        short target_month = month.has_value() ? *month : _time_date.month;
        short target_day = day.has_value() ? *day : _time_date.day;

        short a = (14 - target_month) / 12;
        short y = target_year - a;
        short m = target_month + (12 * a) - 2;

        return (target_day + y + (y / 4) - (y / 100) + (y / 400) +
                ((31 * m) / 12)) %
               7;
    }

    short gregorian_calendar(
        const std::optional<DateInfo>& date = std::nullopt) {
        DateInfo target_date = date.has_value() ? *date : _time_date;
        return gregorian_calendar(target_date.year, target_date.month,
                                  target_date.day);
    }

    std::string get_day_shortname(short day_index) {
        const std::string days[] = {
            "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat",
        };

        return days[day_index];
    }

    std::string get_month_shortname(short month_index) {
        const std::string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                      "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

        return months[month_index - 1];
    }

    // ==================== Date Operations ====================

    void swap_dates(DateInfo& date_one, DateInfo& date_two) {
        DateInfo temp_date = date_two;
        date_two = date_one;
        date_one = temp_date;
    }

    void increment_one_day(DateInfo& date) {
        if (is_last_day_in_month(date)) {
            date.day = 1;
            ++date.month;
            if (date.month > 12) date.year += (date.month %= 12);
            return;
        }
        ++date.day;
    }
    void increment_one_day() { increment_one_day(_time_date); }

    int calculate_difference_in_days(DateInfo date_one,
                                     const DateInfo& date_two,
                                     bool include_end_day = false) {
        int days = 0;

        while (is_date_before(date_one, date_two)) {
            increment_one_day(date_one);
            ++days;
        }

        return include_end_day ? days + 1 : days;
    }

    // ==================== System Date ====================

    static std::string get_time_string() {
        time_t current_time = time(0);
        tm* now = localtime(&current_time);

        short day, month, year, hour, minute, second;

        year = now->tm_year + 1900;
        month = now->tm_mon + 1;
        day = now->tm_mday;
        hour = now->tm_hour;
        minute = now->tm_min;
        second = now->tm_sec;

        return std::to_string(year) + "/" + std::to_string(month) + "/" +
               std::to_string(day) + " - " + std::to_string(hour) + ":" +
               std::to_string(minute) + ":" + std::to_string(second);
    }
    static DateInfo get_system_date() {
        time_t current_time = time(0);
        tm* time_now = localtime(&current_time);
        return DateInfo{short(time_now->tm_year + 1900),
                        short(time_now->tm_mon + 1), short(time_now->tm_mday)};
    }

    // DateInfo get_system_date() {
    //     time_t current_time = time(0);
    //     tm* time_now = localtime(&current_time);
    //     return DateInfo{short(time_now->tm_year + 1900),
    //                     short(time_now->tm_mon + 1),
    //                     short(time_now->tm_mday)};
    // }

    int calculate_age_in_days(DateInfo birth, bool include_end_day = false) {
        return calculate_difference_in_days(birth, get_system_date(),
                                            include_end_day);
    }

    // ==================== Read Date ====================

    short read_year() {
        short year;
        get_number_in_range(year, 1000, 9999, "Please enter a year? ");
        return year;
    }

    short read_month() {
        short month;
        get_number_in_range(month, 1, 12, "Please enter a month? ");
        return month;
    }

    short read_day(short year, short month) {
        short day;
        short month_days = get_month_days(year, month);
        get_number_in_range(day, 1, month_days, "Please enter a day? ");
        return day;
    }

    DateInfo read_full_date() {
        DateInfo date;
        date.year = read_year();
        date.month = read_month();
        date.day = read_day(date.year, date.month);

        return date;
    }

    // ==================== Calendar Printing ====================

    void print_month_calendar(std::optional<short> year = std::nullopt,
                              std::optional<short> month = std::nullopt) {
        short target_month = month.has_value() ? *month : _time_date.month;

        printf("\n -------------------[ %s ]-------------------\n",
               get_month_shortname(target_month).c_str());

        printf(" %-7s%-7s%-7s%-7s%-7s%-7s%s\n", "Sun", "Mon", "Tue", "Wed",
               "Thu", "Fri", "Sat");

        short day_index = gregorian_calendar(year, month, 1);
        short days_in_month = get_month_days(year, month);

        for (short day = 1; day <= days_in_month; day++) {
            if (day == 1) printf(" %*s", 7 * day_index, "");

            day_index++;

            printf("%3d%*s", day, (day_index % 7 == 0 ? 0 : -4),
                   (day_index % 7 == 0 ? "\n " : ""));
        }

        printf("\n ---------------------------------------------\n");
    }

    void print_year_calendar(std::optional<short> year = std::nullopt) {
        short target_year = year.has_value() ? *year : _time_date.year;

        printf("\n =============================================\n");
        printf("               Calendar - %d", target_year);
        printf("\n =============================================\n");

        for (short month = 1; month <= 12; month++)
            print_month_calendar(year, month);
    }

    // ====================== Date Formating =====================
    static std::vector<std::string> split_date(std::string date,
                                               std::string sep = "/") {
        std::vector<std::string> stdate = String::split(date, sep);
        return stdate;
    }
    static std::string date_format(DateInfo date,
                                   std::string format = "%y/%m/%d") {
        String st;
        format = st.replace(format, "%y", std::to_string(date.year), 1);
        format = st.replace(format, "%m", std::to_string(date.month), 1);
        format = st.replace(format, "%d", std::to_string(date.day), 1);
        return format;
    }
    std::string date_format(std::string format = "%y/%m/%d") {
        return date_format(_time_date, format);
    }

    void print_date(std::optional<DateInfo> date = std::nullopt) {
        DateInfo target_date = date.has_value() ? *date : _time_date;
        std::cout << date_format(target_date) << std::endl;
    }

   private:
    DateInfo _time_date = {};
    short min_year = 1000;
    short max_year = 9999;

    bool is_valid_number(const bool& trace = true) {
        bool valid = true;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            valid = false;
        }
        if (std::cin.peek() != '\n' && valid) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            valid = false;
        }
        if (trace) {
            std::cout << "Invalid input, Enter a valid one...\n\n";
        }
        return valid;
    }
    void get_number_in_range(short& variable, const short min, const short max,
                             const std::string& message) {
        bool valid = false;
        do {
            valid = true;
            std::cout << message;
            std::cin >> variable;

            valid = is_valid_number(true);
            if ((variable < min || variable > max) && valid) {
                printf("Out of range, Input must be between %d - %d\n\n", min,
                       max);
                valid = false;
            }
        } while (!valid);
    }
};
// Date::CompareResult;
#endif  // CLASS_DATE_HPP