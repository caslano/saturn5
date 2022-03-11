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