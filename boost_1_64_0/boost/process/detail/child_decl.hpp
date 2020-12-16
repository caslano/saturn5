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
ToMU16j6L5Dh40UeXe+pZg2zQ9MPb3/5qydXvbhazi5AXuq99MgxN3T508fhs3IqVO25lD3Ni/jlTzwwoveGkJNHXl1W6eKShXcs41kQ+fmPtoUtvnXG/A7vnx2WNbjiMU3j3FzkLVIyz94yZGR196SRkdO/yjyIXPTbd09P+mzAmRrhOcnHbmtwbouEFfnMpx589/M3U1NnvNlnStZdT37LXuwN/HL3lpiM4eNrPr5k1XP9L5TbnS5nyCLPTZrz44xeSwb9uVr/R6Lrhx+nPIT55UufXfLagV3jz02LfclXPeynbny7i9y1LKtchVvPNkk6lxRT/IXhH9BO6eyX92s39Y2adYaea79z8N5n9Pn7OUtC9F/3xm1Kq19/e3NP9SbjS7ejPbBL5KmpT/Q9ceDXxN6HpyX3fiR5p5wRh3x8maopGxIWPvvL1Bfv2Dsnv7ecBYu8x4tPdz96cU2n71fevyhiVcWH5SwR5AemHXzr4o/3nJk6t0zC+nmDSfuNul8e783otLfXt2OrVXxgzvSpK3/kbCfRb/pTlcp9z06fvbrDoMRvi8y9Tc5KRP7Xez97q3Vm1qMzTt88/LlyK5A1lPS8MPzJUTuSK1+zr9/msI37nmc+wCxxx3Mm4eexPUZd/0FE5bty7p0RRXhEf/uBAd+sGFPyy4sLHmv7Qfn1bFI/xOWXn2rdI/mmKnfP25zY9O7wYxe+Zu6GyFcNvHnAt6F3P3Hr03HHdj957w7a5OJ+0mvT550vP+DV2VM6Pztr49rdcuY+8hWPPtH2TyHuC63TG63M/rQR78cT9f3yl/avf+/Xkh2mvd5ywt436m+/m7mYov/iPeP/UmPeSyM+Sfht9Y9VyqI7S+Tfzkt5sOaO7PMz8pe/fPvyMmt4PiX8OfvGzvrxVOW3Di5ok1zjs8aUq6qSPus+G1h28dCVEX+O3K3Hn33qZcb4xZ3p8/rnLK33cdaatce7rFp+8wCN58Yvvzn2gW3bxiddt+/xG184VnVwQ9lrH/n6Fl3PnL+m4cH7vvrkzXQ9/R3m46PfFcOf9PUfhsMwa+L4DT/VAmvfX8L+A/xeafv9jKUj7Z0UtZ4oH9PT2DsItNMC94rAtsqvMSGcaQDHwRSYAyvD8bCWkjeHE2FbmAvz4VZjrxr4jXK3ONyg3F1Gxa/Dp2BRuAL64EpYEq6CNeE6WBc+C1vDV2Fv+BrsA5+Dg+EGOEfdX6zuL4EvwUfhy/Ap+Ap8Uem9qfR2wk1wl5J/qeT5cKiu9m9Re82kYKryuy/kT84wd8FZ0Avnwmg4D5aFd8FG8B7YEt4L28OFcCh8AKbDbTADLobT4BJ4L3wQPggfhg/DR+ATcCNcreytgY/D9XAp3AyXwa3wCbhT6e9V+vvg0/A9uAJ+DzfDX+AW6NbJPxgOX4NF4TYYBdfAeLgRllLyMnAdrKTkNZS8JlwP26rrdvBFOFzpjYLIJZ3zjP1AYI4qL0Vhriovd+ukM7wXxsAFsDj8CywJH4PJ8D5YDt4Pm8PFsCVcAjvAB+EN8GGYBR+F45T9fLjT2PMCfqzCEQ83YfiTs71D4HUwBvaDFWB/WB0OgLXUdaq6bgIHwi5KfzBMh6NhBpwGM+EcOALeA7PgfDgILoSD4Sp4A9wC0+AeOBQeVPp/haPgEXWdD6voat8EtSdECsafPsmq/L6vzoT5ECbCj2B5eAQ2h0dhR3gM9oSfwQHwOBwFT8Ab4RdwCvwSzoJfwfnwJLwPfgdfgD/AzTAfboOn4T54Br4Pf4Qfw1/hCXgWfgN/gqeU/Bw8By/Cn2GIjhx64W+wFLwAq8CLsAXU/fUF9IdrCHRzfSMMgROhR+X/YWPtPKys0ss=
*/