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
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
*/