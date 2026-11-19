#ifndef CLASS_RESULT_STATUS_HPP
#define CLASS_RESULT_STATUS_HPP

enum class StatusCode {
    None,

    OutOfRange,
    InvalidInput,

    UserNotFound,
    CanntUpdateUser,

    InvalidUsername,
    InvalidPassword,

    AccessDenied,
    WrongPermission,

    ClientNotFound,
    ClientNotUpdated,

    InsufficientBalance,
    InvalidAmount,
    DepositFailed,
    WithdrawFailed,

    FileOpenFailed,
    FileReadFailed,
    FileWriteFailed,
};

template <typename TypeData>
struct Status {
    TypeData response;
    StatusCode status_code;

    bool issuccessful() { return status_code == StatusCode::None; }
};

#endif  // CLASS_RESULT_STATUS_HPP