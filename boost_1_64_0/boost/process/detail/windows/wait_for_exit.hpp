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
YTqcBDPgDDgWPgYz4Uo4Hm6HE+HLMAt+ACfDQ3AKLIRT4c9wOrwMZ8AbkPBKvK/pb8LynFR/JUbqdZU/0AuGdeFwWB+mwAYq/A3hTHgXXALj4POwCdwNm8I9sDk8BlvC87A1vATbwuuwHbRz7/awJLwbloPxMAZ2hnfBLrAT7Arvh93gSJgAM+C9MBveB6fB7nA17Ak3wd7wJZgIXfm6sKLKdxb5+lk1Pn4OVoYboORDu/o+JNii8kttRz6EsoiFXiDsCRvCXrAz7A27waWwB+wLHfHsD6PgUlgJDoCN4RDYFg6DveFwKP1OOAKOgukwBWbBVDgdpsNlMAOug2PhJjgOvgrHwzfgRPg+zILHYDb8Rrm/CKfCUB/yDWwIH4IdYS68B86B3eBcOADOg4PgAjgMLoSZ8GGYAxfB5XAJfAY+AjdD4q37hfKtNvia/dZ+4YOqHM6BMXAebADXwmZwHWwJ8+CPcAk8D/Phb/ARlc+WwnC4HMbAFbABfAK2gU/CeLgW3gvXwe5wGRyh7FOV/XhlPxHmwU3K/iVl/6rYu9sT+e4XTLdoT14oSXmDL8FYuBXWhn+DcXAbbKbs74Evw65wJ0yA2+Foda3zd6z3/L1F5e+XYGW4FRbBXa5vHoEgeQ7qm9jK3efUm9XhCdgefgM7wpOwN/wW9oenYBr8Hj4Iz8GH4U/wCfgzfBFehNvhv+Df4WX4D/gr/BBegZ/Aq/BreB2egn/CH+ENeAHaVDs6yO76Pg19DFU+68g8kjrLgucRCDfCsnATDIfPw7ZwD7wPvgPvh3vhEPgCTIIvwlT4EhwPt8Ip8G9wNtwB8+HL8Gm4E26Br8JX4d/h+/A1eBS+Cb+E70JHvt8H34bvw31wP/wcHoDfwA/gFXgQXoMfwz/hJ7AC8T0CY+BRWBV+DuPgMdgcfgF7wa9hMvwWjoGFMBuegvPgabgUnoFr4PdQzW+ob0445twt5jfs1NfQhv5QB+A46AsnQj84D/rDPBgAt8HS8GNYBh6GZeH3MESV5zD4MywHL8Nw1V5EwIowGlaCFWB1WArWgTEwHlaGXWEsTIXlVHyyHGbq/PClKr/U53cqlPUqlV9+hiHwIqwG/wWbwxKqfi8Je8MA2B8WOdIV/gIz4a9wCrwCH4RX4RPwd7gZXocfwD/hF9AXf07AUvAfjroC7oXBcD8sDY/AMvALWBaegGHwHCwHL8BweBlGwGswEvoQzygYBKNhaRgDy8JKsDyMhY1gHRgHG8FW8C7YEzaBvWEz2B82hymwFcyErWEWbAPnw7ZwMWwHnf0udaY4rGs397u4j+qXxsE42Bg2gc1ha9gCtoetYU/YBt4P28IRsB1Mh+3hWHg3nAjj4VTYEebBTnAt7AM3w77wBdgPboED4A44EMo8FPwcdoYXYBdoJ+zdoC+8F4bA+2A47A5rw55Q1gf02dm0qRbrAwvUvOdCWB/mwebwMdgKPg5bw8WwI1wKeyvzRGU+CObD0cp8jDJ/UK7d88ZydjU8hZjnjQeXJD5wBCwPk2BVOBLWgpNgbTgK5sEUuBimwpUwE66DafB5mAG3wbHwZaX/GpwI34VZ8H3l7344Gn4Fx8BCMVfl1XVGMpypwh0EU1W4m6j5oxYwAraEsbAVbAxbw3jYBnaDbeH9yjwN3g1Hww7wAblW4yk8PaTuu03l15o28j+Us7RKUJ7gNlgBboeV4K+wKnwZ1oM7YSP4KuwC/w7vha/DAfBtOAruhZnwXTgVvgfnwM/ho7AIroa/wC3wMtyh7vcq3Af/AT+Cb8NP4HvwU3gUHoIn4FF4Xplfg4ehI5Jfw1LwNCwPv4OV4BnYEv4AW8OzMBu+DnPh53AZ/Bk=
*/