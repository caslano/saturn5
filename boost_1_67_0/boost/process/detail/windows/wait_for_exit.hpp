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