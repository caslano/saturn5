// Copyright (c) 2106 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_IS_RUNNING_HPP
#define BOOST_PROCESS_DETAIL_POSIX_IS_RUNNING_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/posix/child_handle.hpp>
#include <system_error>
#include <sys/wait.h>

namespace boost { namespace process { namespace detail { namespace posix {

// Use the "stopped" state (WIFSTOPPED) to indicate "not terminated".
// This bit arrangement of status codes is not guaranteed by POSIX, but (according to comments in
// the glibc <bits/waitstatus.h> header) is the same across systems in practice.
constexpr int still_active = 0x017f;
static_assert(WIFSTOPPED(still_active), "Expected still_active to indicate WIFSTOPPED");
static_assert(!WIFEXITED(still_active), "Expected still_active to not indicate WIFEXITED");
static_assert(!WIFSIGNALED(still_active), "Expected still_active to not indicate WIFSIGNALED");
static_assert(!WIFCONTINUED(still_active), "Expected still_active to not indicate WIFCONTINUED");

inline bool is_running(int code)
{
    return !WIFEXITED(code) && !WIFSIGNALED(code);
}

inline bool is_running(const child_handle &p, int & exit_code, std::error_code &ec) noexcept
{
    int status;
    auto ret = ::waitpid(p.pid, &status, WNOHANG);

    if (ret == -1)
    {
        if (errno != ECHILD) //because it no child is running, than this one isn't either, obviously.
            ec = ::boost::process::detail::get_last_error();
        return false;
    }
    else if (ret == 0)
        return true;
    else
    {
        ec.clear();

        if (!is_running(status))
            exit_code = status;

        return false;
    }
}

inline bool is_running(const child_handle &p, int & exit_code)
{
    std::error_code ec;
    bool b = is_running(p, exit_code, ec);
    boost::process::detail::throw_error(ec, "waitpid(2) failed in is_running");
    return b;
}

inline int eval_exit_status(int code)
{
    if (WIFEXITED(code))
    {
        return WEXITSTATUS(code);
    }
    else if (WIFSIGNALED(code))
    {
        return WTERMSIG(code);
    }
    else
    {
        return code;
    }
}

}}}}

#endif

/* is_running.hpp
3edPTw9h2MJ8Sn2ueZXaW/rT4p+fnvkqVMR5ffCyOhWWEOBi0nD/7EG62tgJv8l/8tLuZZiGPJKtambxzz+j4lt4gs13ma8k6aeRA/oGs7aJ8CyCjPEsAtDxjgIGaKdfp5P5Gbqkdn2v9PFgQOld4Wsh2mmCAKldvWt8PAuHP2ADMGwHCKfwuk2YqM/h4NxbrRaQzuM9fomNab126cOlyViek5sbTyBT8hVgPlHkndgyMQwndGhoXWV5oOzE8IELUL7pLwObgkdoTkWf0Z9tHpCeydJ/mMBcBYUGEnIIrjMCkxUUT9V+zYyAmMx4AH8+zTt3mFC1tukFJ+R7UXKpmvNmdNsyzv4WyCUs/9yQuz4yaWUlUn5dLLjes3dzkQPkBJHXCqF99nlCGjXwf9OQQRV4fk8Z2PWX81FBROcJBIiIbCOHB/Tu/X7JJQLduijClV2XFIzFfiU7K7mVuXFFRDddC+bjjv+K0rjOTzT/aqXIYXtrw7gH5Hy21fal8JGkEKlaSAsD+JPcbZyH9NPLCsfX97eev+7m34PgJY7Ipa6FoBooyF/1PTF1AUZj8LD54mp1Y1L/Dz0vRGCJxQflYBd8f0KebQ96XaQHB5VndBWG/He0RUcNJ1ib9DE1Knk1c/kz656ofmlbRdkrzykrhiOQTC+iTghT5JtlXAEXpsR54DT8QNcPwbpsSDKfpi5q8XQSoHXWGZ3mdl6j
*/