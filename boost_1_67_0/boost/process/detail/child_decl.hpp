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

    explicit child(pid_t & pid) : _child_handle(pid), _attached(false) {};
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
    child() {}
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