// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_WAIT_GROUP_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_WAIT_GROUP_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/windows/group_handle.hpp>
#include <boost/winapi/jobs.hpp>
#include <boost/winapi/wait.hpp>
#include <chrono>

namespace boost { namespace process { namespace detail { namespace windows {

struct group_handle;


inline bool wait_impl(const group_handle & p, std::error_code & ec, std::chrono::system_clock::rep wait_time)
{
    ::boost::winapi::DWORD_ completion_code;
    ::boost::winapi::ULONG_PTR_ completion_key;
    ::boost::winapi::LPOVERLAPPED_ overlapped;

    auto start_time = std::chrono::system_clock::now();

    while (workaround::get_queued_completion_status(
                                       p._io_port, &completion_code,
                                       &completion_key, &overlapped, static_cast<::boost::winapi::DWORD_>(wait_time)))
    {
        if (reinterpret_cast<::boost::winapi::HANDLE_>(completion_key) == p._job_object &&
             completion_code == workaround::JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO_)
        {

            //double check, could be a different handle from a child
            workaround::JOBOBJECT_BASIC_ACCOUNTING_INFORMATION_ info;
            if (!workaround::query_information_job_object(
                    p._job_object,
                    workaround::JobObjectBasicAccountingInformation_,
                    static_cast<void *>(&info),
                    sizeof(info), nullptr))
            {
                ec = get_last_error();
                return false;
            }
            else if (info.ActiveProcesses == 0)
                return false; //correct, nothing left.
        }
        //reduce the remaining wait time -> in case interrupted by something else
        if (wait_time != static_cast<int>(::boost::winapi::infinite))
        {
            auto now = std::chrono::system_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time);
            wait_time -= static_cast<std::chrono::system_clock::rep>(diff.count());
            start_time = now;
            if (wait_time <= 0)
                return true; //timeout with other source
        }

    }

    auto ec_ = get_last_error();
    if (ec_.value() == ::boost::winapi::wait_timeout)
        return true; //timeout

    ec = ec_;
    return false;
}

inline void wait(const group_handle &p, std::error_code &ec)
{
    wait_impl(p, ec, ::boost::winapi::infinite);
}

inline void wait(const group_handle &p)
{
    std::error_code ec;
    wait(p, ec);
    boost::process::detail::throw_error(ec, "wait error");
}

template< class Clock, class Duration >
inline bool wait_until(
        const group_handle &p,
        const std::chrono::time_point<Clock, Duration>& timeout_time,
        std::error_code &ec)
{
    std::chrono::milliseconds ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                    timeout_time - Clock::now());

    auto timeout = wait_impl(p, ec, ms.count());
    return !ec && !timeout;
}

template< class Clock, class Duration >
inline bool wait_until(
        const group_handle &p,
        const std::chrono::time_point<Clock, Duration>& timeout_time)
{
    std::error_code ec;
    bool b = wait_until(p, timeout_time, ec);
    boost::process::detail::throw_error(ec, "wait_until error");
    return b;
}

template< class Rep, class Period >
inline bool wait_for(
        const group_handle &p,
        const std::chrono::duration<Rep, Period>& rel_time,
        std::error_code &ec)
{
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(rel_time);
    auto timeout = wait_impl(p, ec, ms.count());
    return !ec && !timeout;
}

template< class Rep, class Period >
inline bool wait_for(
        const group_handle &p,
        const std::chrono::duration<Rep, Period>& rel_time)
{
    std::error_code ec;
    bool b = wait_for(p, rel_time, ec);
    boost::process::detail::throw_error(ec, "wait_for error");
    return b;
}

}}}}

#endif /* BOOST_PROCESS_DETAIL_WINDOWS_WAIT_GROUP_HPP_ */

/* wait_group.hpp
FsCLcAskXHodTs6ahQst1uEeK6HWpWAAXK7Sbw2sDp+DNeB6WFdd14PPwkbqughS96vzUWnb1fNy1Nsx6nn9QjBKQx+17uYLa8NA2B4Gw0RYGvaHZWAqLAvHwxCYDdvCKTAczoNRcDGsAF+AMXAnrATfgpXhSVgVnobV4QVYE5ZwjCVgJVgXVoX1YGNYH7aADWBX2BD2gY3gCNgYpsEmcApsCufCZnA+bAEXw5bwGdgGboJt9bqlOvcTDrOol6qqclUDloc1YSVYC1aFd8FqsDZsBOvAJrAubA7rwRawAewEG8KBsBEcKu7d4/zYOBUOi3F+JxWOLjAQdoURMEHdpzvsCnsof3tCV/87V/mbb9H/ftwPf+ETsDJcCePgKtgFrob94Bo4CD4JR8N18AH4NFwC10O9Dt6Y+8E3LdbBH0LPB86G5WEurAfnwFbwUZgAl8H74AI4FC6EyfBhOBXmwflwEVwEF8NVMB++pPzZLf64y98hFa4XLcrfVJW+02BpOEM93wdgd5gL+8E58AG4EM6FD8MX4GKo4i8ZwA4LLOKfSngczIBl4ViVDuNgUzgRtoRZsDOcBLvDbDgA5sBM+ADMhlPgZDgVzoXT4FI4Ha5XekUwD5GzxWCKClcZOEuF63VHOw7fhKXhWzAU7oHRcC+Mge/CqvAIrAbfg83hftgdfggT4SewP/wUDoeH4Shx5x6nLVPhwb1pnAZLkc9hLdgU1jPOV/+Fu7bKXXvlrqNy18p1zhMMs1i/+VM9l5swANpV/H2h3NeOKPdfqf5ydcd9obzvUYJyA3vAYbAnnAMTYT7sA9fDBXATvB++BQfAL+BAeBkOgiH4ORjWgimwNxwN0+EYOBUugA/CsfBROA5uhJlwOxwP31F6B2A2LIJTYJgP+QVWgtNgHTgdtoYLYDycCYfBWXAWfBA+DB+C6+BsuBnmwl3K3W44D74DF0Lpb+nzcXjeFuv0j6p+7nI4DK6Ac+AquBiuhk/BV+EGuA6+CZ+Cx+AGeBNuhtH4/QIk3US/HnwJtoNbYV+4DQ6H2+EEpZcNd8Jp8O9QzcuoM1cIi8W8THlHusHKsCesAofAWDge3gOzYWf4MKwB18OacBesBT+BDeBp2BD+ABvBC/AuaHfkOVgCNoFlYVNYATaD1WBL2Bq2gu1ha9gdtoH3w/ZwErwbToOER+9DkHMy4GSLfQjDHf13mAZHwjEwF6bDPJgB18KxsABOgK/DSfATOBWehtPgD3A6vAxnwCtwFgy0k69gJfgQrAJzYS04BzaG82BnOB92hQtgAsyDveAi2B8u0fWKOqcBRlrUD2+q+Z/PYAQ8Cl3rLoXK3S6LdZeegTwP2Au2hn1hf9gPDoTD4SDYG06G98NZcCBco+yfhIPhDjgMvibm7najoJ16Hhbtxk1f7g9tfoz7gR3WhgGwASwFG0If2A76wgRl31PZ94J+cDj0hxnKfoKyz4IlYY661u2Gei/4qkW70Ry9QNgaVoL3wOqwLawP28FG6rqJuu4G28M+sANcrMxfgR3hXtgJ7lf+fSR67n6SvP8Lm1n0k75Q6XQVxsDrsBL8DdaCv8OG8A/YVOzd5X2k8reBRXn/WvVbvoUhsBDGw1OwHzwNB8Pv4DD4u0rnH+BM+CPMh2fhk/AcfFrprYc/wU3wPHwD/gyPwIvwDLwEL8N/wZuwCAYQxl9gMPwdloZXYG34G6wv5u79j/LuLEy02P9YqNa5T8FAeBpWgN/BevAMbAO/hz3hD7A3/BG65scKlf+HLfb/PKvS7zlYCm6CpeELsCJ8EdaDW2Aj+DfYFW6DPeBuOAS+D1PgfjgGHoDpcCecBv8OF8DX4Aq4C66Gb8Dtyp8=
*/