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

typedef int pid_t;

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
        return static_cast<int>(proc_info.dwProcessId);
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
+MOJOEpeY39cpN2qZWzX8wQCS1YVaWZhuo/u6SIEwxcUkc24GCFeFWkKTsupxws7cYt4Ap/U+0fLlzl4y2MsvpK86H0pW8o98UueU/WVyczFdD4taR7Fk+uLr7kpPI6g2mZzSGVYSfPFlGbKo6mnHLpDGW19ewM47rv3Cw1WmB803Z0SNWZn7cwfZO/offb0/m5lI39H2hEdieYFWYNf+vim8S5txlCzO2tsdhxQSV1vL+MzStSawRfkS3Ph16LgszyH9ZEnwXzyzVgnujMhEgWvkADUN9fayHIyvVLanSJOOOcmg2/ts6KDcj7PdxsrwPxeaLm263uG5xZ5QRMTfvnqlTx4jYkc2UpnFhXtVaHUUkkJ9hpbtn6Dq6/MB1rEiWslSE2jybiTmBLL1AGVx/v4sSDdvASLsq2DsMg76B5tl277Z4ge7bhe5/49b7KPCTverzGMMdnwM1hHJTMOcD3vRO649FXTWL1Bd0qWkJwWujxKJFN1CX0uTa7hU+1F93uEvB/C32l5hmZofiEsixfOqhx9//lA6AyxLPIScJAGTWQ7KVJqSuu9omte9t7OtYXtq8iDXu5uzXZ/SFh8QboJEOYY3JkSuzkNcWKFF2NFxiXr+cCR6qFqkmN7CGRF7YQj/QIURCP9gbsp3iRK8AQjF6emR97+yuydTtKlF7wRwtKTshmzyfWINfML0gPpVaf94vO5A26jMPSG
*/