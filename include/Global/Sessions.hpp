#ifndef HEADER_SESSIONS_HPP
#define HEADER_SESSIONS_HPP

#include "../Core/User.hpp"

User CurrentUser = User::find("", "").response;

#endif  // HEADER_SESSIONS_HPP