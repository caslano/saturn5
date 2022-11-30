// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_CHILD_HPP
#define BOOST_PROCESS_WINDOWS_CHILD_HPP

#include <boost/move/move.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/process.hpp>
#include <boost/winapi/jobs.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

typedef ::boost::winapi::DWORD_ pid_t;

struct child_handle
{
    ::boost::winapi::PROCESS_INFORMATION_ proc_info{nullptr, nullptr, 0,0};

    explicit child_handle(const ::boost::winapi::PROCESS_INFORMATION_ &pi) :
                                  proc_info(pi)
    {}

    explicit child_handle(pid_t pid) :
                                  proc_info{nullptr, nullptr, 0,0}
    {
        auto h = ::boost::winapi::OpenProcess(
                ::boost::winapi::PROCESS_ALL_ACCESS_,
                static_cast<::boost::winapi::BOOL_>(0),
                 pid);

        if (h == nullptr)
            throw_last_error("OpenProcess() failed");
        proc_info.hProcess = h;
        proc_info.dwProcessId = pid;
    }

    child_handle() = default;
    ~child_handle()
    {
        ::boost::winapi::CloseHandle(proc_info.hProcess);
        ::boost::winapi::CloseHandle(proc_info.hThread);
    }
    child_handle(const child_handle & c) = delete;
    child_handle(child_handle && c) : proc_info(c.proc_info)
    {
        c.proc_info.hProcess = ::boost::winapi::invalid_handle_value;
        c.proc_info.hThread  = ::boost::winapi::invalid_handle_value;
    }
    child_handle &operator=(const child_handle & c) = delete;
    child_handle &operator=(child_handle && c)
    {
        ::boost::winapi::CloseHandle(proc_info.hProcess);
        ::boost::winapi::CloseHandle(proc_info.hThread);
        proc_info = c.proc_info;
        c.proc_info.hProcess = ::boost::winapi::invalid_handle_value;
        c.proc_info.hThread  = ::boost::winapi::invalid_handle_value;
        return *this;
    }

    pid_t id() const
    {
        return static_cast<pid_t>(proc_info.dwProcessId);
    }

    typedef ::boost::winapi::HANDLE_ process_handle_t;
    process_handle_t process_handle() const { return proc_info.hProcess; }

    bool valid() const
    {
        return (proc_info.hProcess != nullptr) &&
               (proc_info.hProcess != ::boost::winapi::INVALID_HANDLE_VALUE_);
    }
    bool in_group() const
    {
        ::boost::winapi::BOOL_ value;
        if (!::boost::winapi::IsProcessInJob(proc_info.hProcess, nullptr, &value))
            throw_last_error("IsProcessinJob Failed");
        return value!=0;
    }
    bool in_group(std::error_code &ec) const noexcept
    {
        ::boost::winapi::BOOL_ value;
        if (!::boost::winapi::IsProcessInJob(proc_info.hProcess, nullptr, &value))
            ec = get_last_error();
        return value!=0;
    }
};

}}}}

#endif

/* child_handle.hpp
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
*/