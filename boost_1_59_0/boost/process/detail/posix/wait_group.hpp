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
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
*/