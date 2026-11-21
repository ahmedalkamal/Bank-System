# Bank System – Project Reader

## 1. About the project

A console-based banking management system written in C++. It provides tools to manage bank clients, users, transactions, and currency exchange. The application stores its data in text files.

## 2. Main features

- **Clients:** add, list, search, update, and delete clients.
- **Transactions:** deposit, withdraw, transfer money, and view total balances.
- **Transfer logs:** keep a record of transfers and the user who performed them.
- **Users:** add, list, search, update, and delete system users.
- **Permissions:** control which operations each user can access.
- **Login records:** record successful login activity.
- **Currency:** list currencies, search and update exchange rates, and calculate conversions.
- **User profile:** update or delete the current user's profile.

## 3. Project structure

```text
BankSystem/
│
├── main.cpp
├── data/
│   ├── clients.txt
│   ├── users.txt
│   ├── currencies.txt
│   └── log/
│       ├── login-record.txt
│       └── transfer-logs.txt
│
└── include/
    ├── Core/
    ├── Global/
    ├── Screens/
    └── Utils/
```

### `main.cpp`

The application entry point. It starts the login screen.

### `include/Core/`

Contains the main data classes and their operations, such as `BankClient`, `User`, `Currency`, `Person`, `Date`, and `Files`.

### `include/Global/`

Contains shared application settings and state, including file paths, configuration, current session, result statuses, and Unicode definitions.

### `include/Screens/`

Contains the console screens and menus. Screens are grouped by their purpose:

- `MainScreens/` – login, first-time setup, main menu, and main sections.
- `ClientScreens/` – client management screens.
- `UserScreens/` – user management and profile settings.
- `TransactionsScreens/` – deposits, withdrawals, transfers, balances, and transfer logs.
- `CurrencyScreens/` – currency management and conversion screens.

`Screen.hpp` and `ScreenHelper.hpp` provide shared screen behavior and input/display helpers.

### `include/Utils/`

Reusable helper utilities for strings, validation, formatting, colors, tables, and number-to-words conversion.

### `data/`

Stores application records. The file paths are configured in `include/Global/Config.hpp`.

## 4. First run and login

1. Build and run the application.
2. If there are no users in `data/users.txt`, the application opens the first-use setup screen.
3. Create the first account. **The first account is assigned administrator permissions.**
4. Use the username and password you created to log in.

The login screen allows up to three failed attempts before locking that login attempt.

## 5. Build and run

The project uses C++ source and header files. From the project root, compile `main.cpp` with a C++ compiler such as g++:

```bash
g++ -std=c++17 main.cpp -o BankSystem
```

Run on Linux/macOS:

```bash
./BankSystem
```

On Windows, run the generated `BankSystem.exe` from the project folder. Keep the `data/` directory alongside the executable's working directory because the configured data paths are relative to the project directory.

## 6. Important notes

- Back up the `data/` directory before manually editing or replacing its files.
- `Config.hpp` controls the data file paths and the record separator (`#//#`).
- Currency rates are read from `data/currencies.txt`; they are the values supplied with the project and should not be assumed to be live market rates.
- The project is a local console application and uses text files for storage.
