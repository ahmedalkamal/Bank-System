#ifndef HEADER_FILE_CONFIG_HPP
#define HEADER_FILE_CONFIG_HPP

#include <string>

#include "../Utils/String.hpp"

#if defined(__linux__) || (defined(__APPLE__) && defined(__MACH__))
#define OS_UNIX 1
#else
#define OS_UNIX 0
#endif

#ifdef _WIN32
#define OS_WINDOWS 1
#else
#define OS_WINDOWS 0
#endif

bool is_linux() { return OS_UNIX; }
bool is_windows() { return OS_WINDOWS; }

struct Config {
    static short encryptionKey;
    static std::string const separator;
    static std::string const clear;
    static std::string const drive_letter;

    // the path depend on location of main.hpp
    static std::string const clients_file;
    static std::string const users_file;
    static std::string const currencies_file;

    static std::string const login_log_file;
    static std::string const transfer_log_file;
};

short Config::encryptionKey = 12;

std::string const Config::separator = "#//#";
std::string const Config::clear = (is_windows() ? "cls" : "clear");
std::string const Config::drive_letter = (is_windows() ? "\\" : "/");

std::string const Config::clients_file =
    String::join({".", "data", "clients.txt"}, Config::drive_letter);
std::string const Config::users_file =
    String::join({".", "data", "users.txt"}, Config::drive_letter);
std::string const Config::currencies_file =
    String::join({".", "data", "currencies.txt"}, Config::drive_letter);

std::string const Config::login_log_file = String::join(
    {".", "data", "log", "login-record.txt"}, Config::drive_letter);
std::string const Config::transfer_log_file = String::join(
    {".", "data", "log", "transfer-logs.txt"}, Config::drive_letter);

#endif  // HEADER_FILE_CONFIG_HPP