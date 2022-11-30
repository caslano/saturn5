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
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
*/