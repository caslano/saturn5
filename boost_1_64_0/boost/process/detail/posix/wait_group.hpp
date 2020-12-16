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
ZIl7OzzeXCc7L3toaqJP22Su03aJpLsiYp5zsdHSHW4MdQ/2+PVd045440YE2sfrterXSd5Hw087nkJmtftUejTVBzd8QzreAv5a249SZl8p84S06XiA7fmLEtfNEc4bNLv19NaT/z5J83q4GZ+bOjxX4mXd3Eclfl24je21nP980sRaz3Vmdgqt0TrBPl+Tn3Xpzu8jbEzJW1nKbxxhlt8/NcNnIiFptpNmhaR5xlKHDL7vmZqaotLsJc39kmYzaextgXeQ5g5J82N4bacn1CxLjxNpTwHpzL5IHpCaPEh/Q2CR5N8YbmdHPOJbb9z1zD3lGCvI9Hk75I40LnXf7J5gvON2GYX6iqb627mE8qOk/LYRRdnploNXSpoaERc7nw+V8aL7dDhprOPfe5Z852gVZVvLzE7KSLHa7x6Ra7ZAn7M10pZ62pb8oOxXxYZ+nP4WRQ+px8/h+joOWOe3hMTfEvGRc4BxMjxUlx3zpVd+qR4Px+R6J16do8myPznUW+53Mp6lHeaapoeIZy9elZclfRzBGK/JOlwJKh0zkJTjQUI6fS666msoxF0PG2Rfe1Zy3C5SX2eEpQ8ZYInSVf7r8inph71qH8th6XdfGVspY6mU8Vy4xeZXr2t5Uvo4KaLQvKi+4zCX+PqSt5bEn5Z298/OzMvS42uGt/7sYY2rv9dxkeS5NuIdZ1sjCwXVaCyuD4WHGDY2tzIO1nKc+MLfkpBJLkddIzuJny1lbgtv4Ly/kE0uJenvUkyQNHvCC/ltDE3KTTXM79tmHlbnydre5Mx+Scm4kakxv4yyaklZ9Qv3S19f/GLim0t8XESEtkXN0P4WX8kxBkh7z0ifqeaY9s5qfN2i7Rw2yv5ioyEyNQbVeRyv+2CrpGkVer9xSYhpA5ucPdRiA1sOPibpOqh7l38sx4Tim0StyKvm/WdF3jv0KWTm+s45cmvxj+ufJU2U7r8IuU7KGbE6fXLm4MEsUmm1wTXzSH08kufa8+oTarSQ+ljOZ5qsLa2OvVryLTdC6Nuh/Gu2mW8OqTZXU2lXynx+H6OwlHExoQmhGyHbWw/y/VzW9+0QzMJ0Pa+QPPUNu/vkWTlv3kXhTVuUkf8UXyTX80YHZ0AeVTd135S6mXNjluSr6nrT0cwRODeabS9sxzxf6rbd8evzRJOYv5f1jU9uTzr/D9+qOUDlz5PjzTA+cPSgnoXtnNcpWsOY0oUo4UWVp8Biu7yZcJQ0S9UaqxD7Y23jS2Bf8ck4U3YbF8Eytb8criBkxzKX6TW9RSZxKwlPK/kzis/CBaXtwyqVZjV8jrCGsJbwPGEd4bHSRYcFqn4vxNmFX18z2i6MoF3rybulFO2L8ck2sP93VV5n4u+BHeCLyPIJyMTi6uFSNkH16UukiyfNG5ZvNqRfwDcboo6atszfHDrf1vUDZIG2rtuRBdq6PmrKtH1ulinTtrgppkzb4nY1ZdoW9xZTpm1xbzBlun71tKy+aS9tynT94k2ZtsUNM2W6zk5Tput84gst03Xebcp0/a48rGVSP/mm9xFt2ytpyh622v9euL1vPLJ8/T0I/ftW5AVarn8ninyVluvfWiJfq+X63it2aRNlnkBnV8lql1Z8uyt7+7Pir8X7e9mlRU3wyk+/0r7Tqviaz3bcMeXueqMfq1GUvVTx7aL+bPZk9nZjxbcvtLcbK9Lu0N6+8DfYjdnbERbfXrC49mdF2QseI6oclPcG6v1FAfSGKORssq5kNOwDy8GBcA8cBA/CdHgcDoMxFDICxsNRsDIcDavBO2FNOE59N3oCrA8nwqvhXbAJnAybwymwDZwKO8JpsBu8F/aG98FUOAMOhLNgNpwNh8G5cCw=
*/