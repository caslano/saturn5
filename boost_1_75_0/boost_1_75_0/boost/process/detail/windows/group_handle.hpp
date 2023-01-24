// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_GROUP_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_GROUP_HPP_

#include <boost/process/detail/windows/handler.hpp>
#include <boost/winapi/jobs.hpp>
#include <boost/process/detail/windows/child_handle.hpp>
#include <boost/process/detail/windows/job_workaround.hpp>
#include <system_error>

namespace boost { namespace process { namespace detail { namespace windows {

inline bool break_away_enabled(::boost::winapi::HANDLE_ h)
{
    workaround::JOBOBJECT_EXTENDED_LIMIT_INFORMATION_ info;

    if (!workaround::query_information_job_object(
                    h,
                    workaround::JobObjectExtendedLimitInformation_,
                    static_cast<void*>(&info),
                    sizeof(info),
                    nullptr))
        throw_last_error("QueryInformationJobObject() failed");

    return (info.BasicLimitInformation.LimitFlags & workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_) != 0;
}

inline void enable_break_away(::boost::winapi::HANDLE_ h)
{
    workaround::JOBOBJECT_EXTENDED_LIMIT_INFORMATION_ info;

    if (!workaround::query_information_job_object(
                    h,
                    workaround::JobObjectExtendedLimitInformation_,
                    static_cast<void*>(&info),
                    sizeof(info),
                    nullptr))
        throw_last_error("QueryInformationJobObject() failed");

    if ((info.BasicLimitInformation.LimitFlags & workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_) != 0)
        return;

    info.BasicLimitInformation.LimitFlags |= workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_;

    if (!workaround::set_information_job_object(
                h,
                workaround::JobObjectExtendedLimitInformation_,
                static_cast<void*>(&info),
                sizeof(info)))
        throw_last_error("SetInformationJobObject() failed");
}

inline void enable_break_away(::boost::winapi::HANDLE_ h, std::error_code & ec)
{
    workaround::JOBOBJECT_EXTENDED_LIMIT_INFORMATION_ info;


    if (!workaround::query_information_job_object(
                    h,
                    workaround::JobObjectExtendedLimitInformation_,
                    static_cast<void*>(&info),
                    sizeof(info),
                    nullptr))
    {
        ec = get_last_error();
        return;
    }

    if ((info.BasicLimitInformation.LimitFlags & workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_) != 0)
        return;

    info.BasicLimitInformation.LimitFlags |= workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_;

    if (!workaround::set_information_job_object(
                h,
                workaround::JobObjectExtendedLimitInformation_,
                static_cast<void*>(&info),
                sizeof(info)))
    {
        ec = get_last_error();
        return;
    }
}

inline void associate_completion_port(::boost::winapi::HANDLE_ job,
                                      ::boost::winapi::HANDLE_ io_port)
{
    workaround::JOBOBJECT_ASSOCIATE_COMPLETION_PORT_ port;
    port.CompletionKey  = job;
    port.CompletionPort = io_port;

    if (!workaround::set_information_job_object(
            job,
            workaround::JobObjectAssociateCompletionPortInformation_,
            static_cast<void*>(&port),
            sizeof(port)))
        throw_last_error("SetInformationJobObject() failed");
}

struct group_handle
{
    ::boost::winapi::HANDLE_ _job_object;
    ::boost::winapi::HANDLE_ _io_port;

    typedef ::boost::winapi::HANDLE_ handle_t;
    handle_t handle() const { return _job_object; }

    explicit group_handle(handle_t h) :
        _job_object(h),
        _io_port(::CreateIoCompletionPort(::boost::winapi::INVALID_HANDLE_VALUE_, nullptr, 0, 1))
    {
        enable_break_away(_job_object);
        associate_completion_port(_job_object, _io_port);
    }


    group_handle() : group_handle(::boost::winapi::CreateJobObjectW(nullptr, nullptr))
    {

    }
    ~group_handle()
    {
        ::boost::winapi::CloseHandle(_job_object);
        ::boost::winapi::CloseHandle(_io_port);
    }
    group_handle(const group_handle & c) = delete;
    group_handle(group_handle && c) : _job_object(c._job_object),
        _io_port(c._io_port)
    {
        c._job_object = ::boost::winapi::invalid_handle_value;
        c._io_port    = ::boost::winapi::invalid_handle_value;
    }
    group_handle &operator=(const group_handle & c) = delete;
    group_handle &operator=(group_handle && c)
    {
        ::boost::winapi::CloseHandle(_io_port);
        _io_port = c._io_port;
        c._io_port = ::boost::winapi::invalid_handle_value;

        ::boost::winapi::CloseHandle(_job_object);
        _job_object = c._job_object;
        c._job_object = ::boost::winapi::invalid_handle_value;
        return *this;
    }

    void add(handle_t proc)
    {
        if (!::boost::winapi::AssignProcessToJobObject(_job_object, proc))
            throw_last_error();
    }
    void add(handle_t proc, std::error_code & ec) noexcept
    {
        if (!::boost::winapi::AssignProcessToJobObject(_job_object, proc))
            ec = get_last_error();
    }

    bool has(handle_t proc)
    {
        ::boost::winapi::BOOL_ is;
        if (!::boost::winapi::IsProcessInJob(proc, _job_object,  &is))
            throw_last_error();

        return is!=0;
    }
    bool has(handle_t proc, std::error_code & ec) noexcept
    {
        ::boost::winapi::BOOL_ is;
        if (!::boost::winapi::IsProcessInJob(proc, _job_object,  &is))
            ec = get_last_error();
        return is!=0;
    }

    bool valid() const
    {
        return _job_object != nullptr;
    }

};

inline void terminate(const group_handle &p)
{
    if (!::boost::winapi::TerminateJobObject(p.handle(), EXIT_FAILURE))
        boost::process::detail::throw_last_error("TerminateJobObject() failed");
}

inline void terminate(const group_handle &p, std::error_code &ec) noexcept
{
    if (!::boost::winapi::TerminateJobObject(p.handle(), EXIT_FAILURE))
        ec = boost::process::detail::get_last_error();
    else
        ec.clear();
}

inline bool in_group()
{
    ::boost::winapi::BOOL_ res;
    if (!::boost::winapi::IsProcessInJob(boost::winapi::GetCurrentProcess(), nullptr, &res))
        throw_last_error("IsProcessInJob failed");

    return res!=0;
}



}}}}


#endif /* BOOST_PROCESS_DETAIL_WINDOWS_GROUP_HPP_ */

/* group_handle.hpp
aGmpgEtuKbx1umOL6iWmiDUfLBjF728uXb1czMO6GqCgSyuqrb/+VFAqVUKrRj+CfbV35TD9ct8dtPGXXtGMho+Px0tIKvxHfXDN++qiY6VtdaVrTuH+VxfVqmETZrojVgJtJ6cT9pkXrfQqVFS94zPi83OS08NDOysKWXNJO/mDp8d7p1z5+tz6I60EsFtjj8VcweDwTQAFEprkZ3DFMF9qErpm/h+T+wZT6Ldvdh117avbtX9XRUdSdk7W2IzYPwxMuL9sNrf4a20f+Hz+DNwzNTjKEg8+g33aPGZa0hxPS0PB/1GY12PV26v+8hLWntE6PDPLseqVy9PZqLquSbr0R0LNhAJGoemlz3qacaWz9OxfKK7feiPuJZKt1Q/Ox2WQmaIjGCKiVEiEVn3PM9sF/vA79wiZzK2wzC+knDlfPBxo7+pr7Woz1lRb1zNrSyHmD1o3fLM7ZprRP7VoFVp0a6860bIbrO+IPgnUVSds9ayv0HWQl7+Sd3GoDx7ZDh3Y7yocmEus+5bFzi9AW76pKDW9sFWQsY3UUFBAPBEeNqZKe7rm+WdqxVrx8Ho6r18LATI5rDBerRyZhrjkdn7lf2x7HSW8EnhJJ6xEvtcnJWkSWvQyfuyJQvIR81gDlrrWNpTw5ZboqaoX0s+rqUF4N8onRhRkpRTzxSHDQiTxF4TKdcByZ7H4rer7xRoGCop7W+DvHfgN4eQM
*/