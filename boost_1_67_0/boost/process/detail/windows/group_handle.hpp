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
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
*/