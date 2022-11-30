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
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
*/