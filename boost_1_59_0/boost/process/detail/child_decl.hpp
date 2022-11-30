// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 * \file boost/process/child.hpp
 *
 * Defines a child process class.
 */

#ifndef BOOST_PROCESS_CHILD_DECL_HPP
#define BOOST_PROCESS_CHILD_DECL_HPP

#include <boost/process/detail/config.hpp>
#include <chrono>
#include <memory>

#include <boost/none.hpp>
#include <atomic>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/child_handle.hpp>
#include <boost/process/detail/posix/terminate.hpp>
#include <boost/process/detail/posix/wait_for_exit.hpp>
#include <boost/process/detail/posix/is_running.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/child_handle.hpp>
#include <boost/process/detail/windows/terminate.hpp>
#include <boost/process/detail/windows/wait_for_exit.hpp>
#include <boost/process/detail/windows/is_running.hpp>

#endif
namespace boost {

namespace process {

using ::boost::process::detail::api::pid_t;

class child
{
    ::boost::process::detail::api::child_handle _child_handle;
    std::shared_ptr<std::atomic<int>> _exit_status = std::make_shared<std::atomic<int>>(::boost::process::detail::api::still_active);
    bool _attached = true;
    bool _terminated = false;

    bool _exited()
    {
        return _terminated || !::boost::process::detail::api::is_running(_exit_status->load());
    };
public:
    typedef ::boost::process::detail::api::child_handle child_handle;
    typedef child_handle::process_handle_t native_handle_t;
    explicit child(child_handle &&ch, std::shared_ptr<std::atomic<int>> &ptr) : _child_handle(std::move(ch)), _exit_status(ptr) {}
    explicit child(child_handle &&ch, const std::shared_ptr<std::atomic<int>> &ptr) : _child_handle(std::move(ch)), _exit_status(ptr) {}
    explicit child(child_handle &&ch) : _child_handle(std::move(ch)) {}

    explicit child(pid_t pid) : _child_handle(pid), _attached(false) {};
    child(const child&) = delete;
    child(child && lhs) noexcept
        : _child_handle(std::move(lhs._child_handle)),
          _exit_status(std::move(lhs._exit_status)),
          _attached (lhs._attached),
          _terminated (lhs._terminated)
    {
        lhs._attached = false;
    }

    template<typename ...Args>
    explicit child(Args&&...args);
    child() { } // Must be kept non defaulted for MSVC 14.1 & 14.2 #113
    child& operator=(const child&) = delete;
    child& operator=(child && lhs)
    {
        _child_handle= std::move(lhs._child_handle);
        _exit_status = std::move(lhs._exit_status);
        _attached    = lhs._attached;
        _terminated  = lhs._terminated;
        lhs._attached = false;
        return *this;
    };

    void detach() {_attached = false; }
    void join() {wait();}
    bool joinable() { return _attached;}

    ~child()
    {
        std::error_code ec;
        if (_attached && !_exited() && running(ec))
            terminate(ec);
    }
    native_handle_t native_handle() const { return _child_handle.process_handle(); }


    int exit_code() const {return ::boost::process::detail::api::eval_exit_status(_exit_status->load());}
    pid_t id()      const {return _child_handle.id(); }

    int native_exit_code() const {return _exit_status->load();}

    bool running()
    {
        std::error_code ec;
        bool b = running(ec);
        boost::process::detail::throw_error(ec, "running error");
        return b;
    }

    void terminate()
    {
        std::error_code ec;
        terminate(ec);
        boost::process::detail::throw_error(ec, "terminate error");
    }

    void wait()
    {
        std::error_code ec;
        wait(ec);
        boost::process::detail::throw_error(ec, "wait error");
    }

    template< class Rep, class Period >
    bool wait_for (const std::chrono::duration<Rep, Period>& rel_time)
    {
        std::error_code ec;
        bool b = wait_for(rel_time, ec);
        boost::process::detail::throw_error(ec, "wait_for error");
        return b;
    }

    template< class Clock, class Duration >
    bool wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time )
    {
        std::error_code ec;
        bool b = wait_until(timeout_time, ec);
        boost::process::detail::throw_error(ec, "wait_until error");
        return b;
    }

    bool running(std::error_code & ec) noexcept
    {
        ec.clear();
        if (valid() && !_exited() && !ec)
        {
            int exit_code = 0;
            auto res = boost::process::detail::api::is_running(_child_handle, exit_code, ec);
            if (!ec && !res && !_exited())
                _exit_status->store(exit_code);

            return res;
        }
        return false;
    }

    void terminate(std::error_code & ec) noexcept
    {
        if (valid() && running(ec) && !ec)
            boost::process::detail::api::terminate(_child_handle, ec);

        if (!ec)
            _terminated = true;
    }

    void wait(std::error_code & ec) noexcept
    {
        if (!_exited() && valid())
        {
            int exit_code = 0;
            boost::process::detail::api::wait(_child_handle, exit_code, ec);
            if (!ec)
                _exit_status->store(exit_code);
        }
    }

    template< class Rep, class Period >
    bool wait_for (const std::chrono::duration<Rep, Period>& rel_time, std::error_code & ec) noexcept
    {
        return wait_until(std::chrono::steady_clock::now() + rel_time, ec);
    }

    template< class Clock, class Duration >
    bool wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time, std::error_code & ec) noexcept
    {
        if (!_exited())
        {
            int exit_code = 0;
            auto b = boost::process::detail::api::wait_until(_child_handle, exit_code, timeout_time, ec);
            if (!b || ec)
                return false;
            _exit_status->store(exit_code);
        }
        return true;
    }


    bool valid() const
    {
        return _child_handle.valid();
    }
    operator bool() const {return valid();}

    bool in_group() const
    {
        return _child_handle.in_group();
    }
    bool in_group(std::error_code &ec) const noexcept
    {
        return _child_handle.in_group(ec);
    }
};



}}
#endif


/* child_decl.hpp
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
*/