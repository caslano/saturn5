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
piJLSzHrUpm/qxCqEqoRqhNqEGr60pNvLXiAdLVhHUJdQj1CfUIDwkWEiwkNCSfNuku9GyFrrPJsQkgiHxfBl09TQjNCc0IL2fbXqSVsRWgt22Y927B9iZJdKm024y6ztKet/2+xQLucsCrODMlst0vhb+VDIckM1EvaIyElXvpYh3jJx59ve8nfDOkp/tCBkEG4ReTqu16Ov/0Nla0PmT4ZblxhvsffXMkmW2TNlGy0RdZUyXItsiZKtnm5ljVpoWSXm7LGrZWsuUXWUsl2LzNlgfyyTVmjgF4biyxQ57oWWaDO5SyyQJ29FlmgjG+WmrLGSvahRdZIyV7QstbaX8IWU6Z9PFxhyrTvhstMmfaX8OOdWqZ9S+zSslY6v/tMmfbJMMmU6TIuN2Xa/0ILU6Z9QdQ0ZbrcZFOm/UN4tKylbu/ZO7RM1+9PpkzX77Ap0z4jrtWyFjq/MaZM53eNKdP59TRlOr8td2qZ7oPmpp7u51qmTPdLWVOm+yXKlOl++XmJlul++UrLmut2fGDKdDveMGW6HftMmW7H06ZMt+MBU6bbsdqU6XYsNmW6HXNNmW7HFFOm2zFay5qZvldMmW5HT1Om25Fhyv7K3nnAR1WkAfy93U2yqaQTQttDQBBEmoAU6RB6C0XBCwECREISITRBDEVBQBSlqaCIDcspKmJDiBV7oajHoUZFRQUPEQXFcv/9dnbey/pWyfW7H9Hhv++bb+qbNzNv3hSdjlaWTKejoSXT6ahhyXQ6qlgynQ6XJdPp+PZ6LdPpOKhlLay9VyyZTscOS6bT8ZAl0+m4w5LpdKy1ZDodSy2ZTsdcS6bTcYkl0+kYbcl0Oi7UMmu/mDaWTMevdF3FvWESkF15LzLb+VPyfeLv2HcluP+JnPWo5qSmI2uMbLbo6XlQIh/xG3u0HBV9/clK5MVaX8/jEPmy0L1blH4pcjlj0poLIPJr9R4w1nc44q6+/yCXb0IB3YHO52bpM1Rvb2PI3xVqzvhCzOf+OehsdqDmQ7PrZk6x9TXJ0OMtpoy3WHvv1d7slw1hvDfGaQ658tPU84xNQ3zU3zC/FfvL+T7AbFCMw9xy7UeFOSvcacN27mBDiUdvvmDEKBmjoyJrYEQjtY2B6X29qoj9GKM1Gv7++5ZWhNVavUexAUDoe3Wm0vG1UTpmDTm6rgFH1zmeW6f0u7UJnlvX9NfveFy7uU7V+1D9eg58Ypg58P77kSb3wyrb5DEyyeMK93xLW4M//MdEYq7yu/f5N3WQez6hMHdy3tTA8YjBaVJyzzLRYS+3QvsZj1eIm4V8hR/ueM/xU9/z72QMboL+XpUBnxP7c/Q4/hq5LjLORhY6Vpnuj6vYX+64X9pGscsLXGu/YiXsQSpsIq+/d24Q++GG/715Uxvu93ncHwKJ85hxZoT/dnoujmODB8f7qdykkpfd5X286q/uZ6bS6YZOD79OdJ04s6s+2zCsnxPR75n+22XkQ66z0mElyoj//qXJ/VNn1aryMKdDQHk7JgGzDdMA3cQHpTxMzp2Ul2MrE7bnV7zSz38L0Z9lTDHcTmVB+WeqsqTn8epvKfeJfaw+F7mRXN8WWnZ02asj9gv5ElJXl4HRQT/Uc79JrpW9vq4TWgdIWTxX7GYYhcHxdh2nmqFlSNcbPhWHToQZGkaC9W20wrhaL7FPlHrmMe71iPbI/Pc7ItkIHZ/KVDqL2wfHdGrHRUfGmSPD1zOifx/6vf1+xpauCx2fSFc6e9DpI+FOjvNGGU5jXqJ3Ar2+fr2YnLA6NToE67XmDmNCF0pZ6Icf/TEDMAPTT+0sZsl/WUCkyrGu16Ts2es1Nh8JOB6o2rIBmJ9oy960lWNmy+Y=
*/