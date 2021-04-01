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
qBnTDc9sBo1BIo6E+spLl6+aqcZHDGtXONhAyrVP+nWk1/Vbv7xqNRHe0vgzgqfjdsHOFCQ6wGFiCHM2G5c7+S4s++/tWqMyVkpIDRaexd9oBBc5d0eaArrIvFlovT/43fK5Qw0Xka+A+jdCS7w+ysKloxjN0YFRdGwx87WZ+tWAEyEiglWRoD07AUP/DURfpL1gKgIGGJZwDJjZkZ6TqWETYDZMKOPAdQOX84UeLS2qAdvJFuur+zyABn/waU5CCYyU5/TnaaoffRpw3j0hIk2qXc4AtwNGIHbNGUhs8Gc+OZvY0xdr+xTNZdil2CSO6UxfYg7KAussB1UfJsUdVgKcel61XvH9A3IR1sZjLeIU2TValGNI9Pi9NQ/G0tsW053PfSPl2JGif2tk2fGpiUz15VW/070odA0SjT+xpmmTWSjG7X0PU0imGGZqZV3x3wl7Dtf2V8mwIPsuDrfCMg0zOoJvTMOQLhUpyUSzsBJ9Qls3DYvsQ2Bm7qr42Pn8I1oO2v5d3mJDJAqCKrDrBtGaMu9OZrxFIW83t36tQ/0H12BXMp7YvHPbZQ==
*/