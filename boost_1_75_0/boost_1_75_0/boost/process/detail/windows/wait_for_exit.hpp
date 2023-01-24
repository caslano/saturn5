// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_WAIT_FOR_EXIT_HPP
#define BOOST_PROCESS_WINDOWS_WAIT_FOR_EXIT_HPP

#include <boost/process/detail/config.hpp>
#include <system_error>
#include <boost/winapi/synchronization.hpp>
#include <boost/winapi/process.hpp>
#include <boost/process/detail/windows/child_handle.hpp>
#include <chrono>

namespace boost { namespace process { namespace detail { namespace windows {

inline void wait(child_handle &p, int & exit_code, std::error_code &ec) noexcept
{
    ::boost::winapi::DWORD_ _exit_code = 1;

    if (::boost::winapi::WaitForSingleObject(p.process_handle(),
        ::boost::winapi::infinite) == ::boost::winapi::wait_failed)
            ec = std::error_code(
                ::boost::winapi::GetLastError(),
                std::system_category());
    else if (!::boost::winapi::GetExitCodeProcess(p.process_handle(), &_exit_code))
            ec = std::error_code(
                ::boost::winapi::GetLastError(),
                std::system_category());
    else
        ec.clear();

    ::boost::winapi::CloseHandle(p.proc_info.hProcess);
    p.proc_info.hProcess = ::boost::winapi::INVALID_HANDLE_VALUE_;
    exit_code = static_cast<int>(_exit_code);
}

inline void wait(child_handle &p, int & exit_code)
{
    std::error_code ec;
    wait(p, exit_code, ec);
    boost::process::detail::throw_error(ec, "wait error");
}

template< class Clock, class Duration >
inline bool wait_until(
        child_handle &p,
        int & exit_code,
        const std::chrono::time_point<Clock, Duration>& timeout_time,
        std::error_code &ec) noexcept
{
    std::chrono::milliseconds ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                    timeout_time - Clock::now());

    ::boost::winapi::DWORD_ wait_code;
    wait_code = ::boost::winapi::WaitForSingleObject(p.process_handle(),
                    static_cast<::boost::winapi::DWORD_>(ms.count()));

    if (wait_code == ::boost::winapi::wait_failed)
        ec = std::error_code(
            ::boost::winapi::GetLastError(),
            std::system_category());
    else if (wait_code == ::boost::winapi::wait_timeout)
        return false;

    ::boost::winapi::DWORD_ _exit_code;
    if (!::boost::winapi::GetExitCodeProcess(p.process_handle(), &_exit_code))
        ec = std::error_code(
            ::boost::winapi::GetLastError(),
            std::system_category());
    else
        ec.clear();

    exit_code = static_cast<int>(_exit_code);
    ::boost::winapi::CloseHandle(p.proc_info.hProcess);
    p.proc_info.hProcess = ::boost::winapi::INVALID_HANDLE_VALUE_;
    return true;
}

template< class Clock, class Duration >
inline bool wait_until(
        child_handle &p,
        int & exit_code,
        const std::chrono::time_point<Clock, Duration>& timeout_time)
{
    std::error_code ec;
    bool b = wait_until(p, exit_code, timeout_time, ec);
    boost::process::detail::throw_error(ec, "wait_until error");
    return b;
}

template< class Rep, class Period >
inline bool wait_for(
        child_handle &p,
        int & exit_code,
        const std::chrono::duration<Rep, Period>& rel_time,
        std::error_code &ec) noexcept
{
    return wait_until(p, exit_code, std::chrono::steady_clock::now() + rel_time, ec);
}

template< class Rep, class Period >
inline bool wait_for(
        child_handle &p,
        int & exit_code,
        const std::chrono::duration<Rep, Period>& rel_time)
{
    std::error_code ec;
    bool b = wait_for(p, exit_code, rel_time, ec);
    boost::process::detail::throw_error(ec, "wait_for error");
    return b;
}

}}}}

#endif

/* wait_for_exit.hpp
S7kOix7LWXdF4aJ5qnaU1+4Ur6gdRpmIKyKoB/i7wtKu8gSLlpuwTzHrtl1eloC6dsbjyvkkP7yXnImi3+MUtVDusEweVrPOqdhCkFnRC7fPfFZVGlCDQiWNSRuW2ikKoLENND2lPxlBPfnlWgWfhYrcVOUbqZy7krWRj5/03trh7wQ3z3Jm2OOIMVbOTY3+4RWnvER/gbu2/nwcy5zSaoLG44GCK9P4ttpBqiqdKrPWrPF2akhXhku39g9694MEOjkC7xf630zppPEfy/+k1TndZ1D6q1yLIW2d88JVMidGqf2H3rpv1Lh31eZECSVJFMlOchf/A3yFGVrv+YO+Noj5rRO18XjIDttmy2hbrtvpWuKWMQanfWS6MPMYewV/mswldJmV8ZTxUPb9lMYKP0HWDzwOGTFHN5t++zDwBUHnNtFKJMUo8VZ/U35yUaIvv/ZzyPkF5/A96Jsxo4MHBiNdrpw7IbBxmvb2e+yQg7BHxeuEkfcTRYNLf3IqLWnC4VAUVEvzEKF6suZ3+JPSSZm0Ywq8mEfnkdE92ac8Tm0aSUa8H9gW8QiNWEJ1X0ueYO9/OEGlR8yCc75JoIiJveJmf14/XeNesz+SVlvmETdcUn74gGAmvroUuVv9Ih6goHsgWP0Hp2nwjPqhFekQg0TA1cSbgCeGpAsarQuauG16bZc1OXJx/8+DTHlaLqPHf/xhUPG74fSP9PgV
*/