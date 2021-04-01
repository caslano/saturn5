// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_WAIT_GROUP_HPP
#define BOOST_PROCESS_DETAIL_POSIX_WAIT_GROUP_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/posix/group_handle.hpp>
#include <chrono>
#include <system_error>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {

inline void wait(const group_handle &p, std::error_code &ec) noexcept
{
    pid_t ret;
    siginfo_t  status;

    do
    {
        ret = ::waitpid(-p.grp, &status.si_status, 0);
        if (ret == -1)
        {
            ec = get_last_error();
            return; 
        }

        //ECHILD --> no child processes left.
        ret = ::waitid(P_PGID, p.grp, &status, WEXITED | WNOHANG);
    } 
    while ((ret != -1) || (errno != ECHILD));
   
    if (errno != ECHILD)
        ec = boost::process::detail::get_last_error();
    else
        ec.clear();
}

inline void wait(const group_handle &p) noexcept
{
    std::error_code ec;
    wait(p, ec);
    boost::process::detail::throw_error(ec, "waitpid(2) failed in wait");
}

template< class Clock, class Duration >
inline bool wait_until(
        const group_handle &p,
        const std::chrono::time_point<Clock, Duration>& time_out,
        std::error_code & ec) noexcept
{

    ::siginfo_t siginfo;

    bool timed_out = false;
    int ret;

    ::timespec sleep_interval;
    sleep_interval.tv_sec = 0;
    sleep_interval.tv_nsec = 100000000;


    while (!(timed_out = (Clock::now() > time_out)))
    {
        ret = ::waitid(P_PGID, p.grp, &siginfo, WEXITED | WSTOPPED | WNOHANG);
        if (ret == -1)
        {
            if ((errno == ECHILD) || (errno == ESRCH))
            {
                ec.clear();
                return true;
            }
            ec = boost::process::detail::get_last_error();
            return false;
        }
        //we can wait, because unlike in the wait_for_exit, we have no race condition regarding eh exit code.
        ::nanosleep(&sleep_interval, nullptr);
    }
    return !timed_out;
}

template< class Clock, class Duration >
inline bool wait_until(
        const group_handle &p,
        const std::chrono::time_point<Clock, Duration>& time_out) noexcept
{
    std::error_code ec;
    bool b = wait_until(p, time_out, ec);
    boost::process::detail::throw_error(ec, "waitpid(2) failed in wait_until");
    return b;
}

template< class Rep, class Period >
inline bool wait_for(
        const group_handle &p,
        const std::chrono::duration<Rep, Period>& rel_time,
        std::error_code & ec) noexcept
{
    return wait_until(p, std::chrono::steady_clock::now() + rel_time, ec);
}

template< class Rep, class Period >
inline bool wait_for(
        const group_handle &p,
        const std::chrono::duration<Rep, Period>& rel_time) noexcept
{
    std::error_code ec;
    bool b = wait_for(p, rel_time, ec);
    boost::process::detail::throw_error(ec, "waitpid(2) failed in wait_for");
    return b;
}

}}}}

#endif

/* wait_group.hpp
WSCZ5Al/tXQyuxfTRWvZjNJvxvZLUu5QKEt84/Ft/kbR+wQnIPHvlQvlA63Cebkvl/52lQ6A49zMtkcydUv76nGDAtdMHye3sPT6RMCPq19K29E61wHO84LBUx7sHzLf/o0L+z2NEjk6HEZ6zq9e62FvUMnsX0S8iA7mUeg2vtOqEzfP6GXqTcJyIT8LNt7IIvfVyLG1H7/pJ9Y9/y14lH49YXf9U1zUSrfGBrvOOrXwo/miAfknx2TPC7U21vX4roS1mxFlkk5j48PGtgFkdUYfeE8Gbc0gBemfLTsRhwsb7SO2hpFeDyqOWDKr4ay7L52TNRivsEagYrAP0Ii5Gcb4detSzO9tbyPfL8Z44cKfqvMZclVAoHGNQ2Dm5INDZGYUSDKRd/xXyzd4lLWrSz1BIoK0e6kMc9hqtDVNNyNiEuPRdr19PEKJJyAYGBJSzQzh0C2/BITIy4d90NbxQqG2YMAFDrfb0Dh+pkHCqBC58PO3ewdryI/X5cd10oj832CWI74jgTEQ/yehi1Hq+cb2jobs0HQxIWJoBBJAgadkrN/xep9CipPfIQ==
*/