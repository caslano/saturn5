// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_WAIT_FOR_EXIT_HPP
#define BOOST_PROCESS_DETAIL_POSIX_WAIT_FOR_EXIT_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/posix/child_handle.hpp>
#include <system_error>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {

inline void wait(const child_handle &p, int & exit_code, std::error_code &ec) noexcept
{
    pid_t ret;
    int status;

    do
    {
        ret = ::waitpid(p.pid, &status, 0);
    } 
    while (((ret == -1) && (errno == EINTR)) || 
           (ret != -1 && !WIFEXITED(status) && !WIFSIGNALED(status)));

    if (ret == -1)
        ec = boost::process::detail::get_last_error();
    else
    {
        ec.clear();
        exit_code = status;
    }
}

inline void wait(const child_handle &p, int & exit_code) noexcept
{
    std::error_code ec;
    wait(p, exit_code, ec);
    boost::process::detail::throw_error(ec, "waitpid(2) failed in wait");
}

template< class Clock, class Duration >
inline bool wait_until(
        const child_handle &p,
        int & exit_code,
        const std::chrono::time_point<Clock, Duration>& time_out,
        std::error_code & ec) noexcept
{
    ::sigset_t  sigset;

    //I need to set the signal, because it might be ignore / default, in which case sigwait might not work.

    using _signal_t = void(*)(int);
    static thread_local _signal_t sigchld_handler = SIG_DFL;

    struct signal_interceptor_t
    {
        static void handler_func(int val)
        {
            if ((sigchld_handler != SIG_DFL) && (sigchld_handler != SIG_IGN))
                sigchld_handler(val);
        }
        signal_interceptor_t()  { sigchld_handler = ::signal(SIGCHLD, &handler_func); }
        ~signal_interceptor_t() { ::signal(SIGCHLD, sigchld_handler); sigchld_handler = SIG_DFL;}

    } signal_interceptor{};

    if (sigemptyset(&sigset) != 0)
    {
        ec = get_last_error();
        return false;
    }
    if (sigaddset(&sigset, SIGCHLD) != 0)
    {
        ec = get_last_error();
        return false;
    }

    auto get_timespec = 
            [](const Duration & dur)
            {
                ::timespec ts;
                ts.tv_sec  = std::chrono::duration_cast<std::chrono::seconds>(dur).count();
                ts.tv_nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count() % 1000000000;
                return ts;
            };

    int ret;
    int status{0};

    struct ::sigaction old_sig;
    if (-1 == ::sigaction(SIGCHLD, nullptr, &old_sig))
    {
        ec = get_last_error();
        return false;
    }

    bool timed_out;

#if defined(BOOST_POSIX_HAS_SIGTIMEDWAIT)
    do
    {
        auto ts = get_timespec(time_out - Clock::now());
        auto ret_sig = ::sigtimedwait(&sigset, nullptr, &ts);
        errno = 0;
        ret = ::waitpid(p.pid, &status, WNOHANG);

        if ((ret_sig == SIGCHLD) && (old_sig.sa_handler != SIG_DFL) && (old_sig.sa_handler != SIG_IGN))
            old_sig.sa_handler(ret);

        if (ret == 0)
        {
            timed_out = Clock::now() >= time_out;
            if (timed_out)
                return false;
        }
    }
    while ((ret == 0) ||
          (((ret == -1) && errno == EINTR) ||
           ((ret != -1) && !WIFEXITED(status) && !WIFSIGNALED(status))));
#else
    //if we do not have sigtimedwait, we fork off a child process  to get the signal in time
    pid_t timeout_pid = ::fork();
    if (timeout_pid  == -1)
    {
        ec = boost::process::detail::get_last_error();
        return true;
    }
    else if (timeout_pid == 0)
    {
        auto ts = get_timespec(time_out - Clock::now());
        ::timespec rem;
        while (ts.tv_sec > 0 || ts.tv_nsec > 0)
        {
            if (::nanosleep(&ts, &rem) != 0)
            {
                auto err = errno;
                if ((err == EINVAL) || (err == EFAULT))
                    break;
            }
            ts = get_timespec(time_out - Clock::now());
        }
        ::exit(0);
    }

    struct child_cleaner_t
    {
        pid_t pid;
        ~child_cleaner_t()
        {
            int res;
            ::kill(pid, SIGKILL);
            ::waitpid(pid, &res, 0);
        }
    };
    child_cleaner_t child_cleaner{timeout_pid};

    do
    {
        int sig_{0};
        if ((::waitpid(timeout_pid, &status, WNOHANG) != 0)
            && (WIFEXITED(status) || WIFSIGNALED(status)))

            return false;

        ret = ::sigwait(&sigset, &sig_);
        errno = 0;

        if ((sig_ == SIGCHLD) &&
            (old_sig.sa_handler != SIG_DFL) && (old_sig.sa_handler != SIG_IGN))
            old_sig.sa_handler(ret);

        ret = ::waitpid(p.pid, &status, WNOHANG);
        if (ret == 0) // == > is running
        {
            timed_out = Clock::now() >= time_out;
            if (timed_out)
                return false;
        }
    }
    while ((ret == 0) ||
           (((ret == -1) && errno == EINTR) ||
            ((ret != -1) && !WIFEXITED(status) && !WIFSIGNALED(status))));
#endif

    if (ret == -1)
        ec = boost::process::detail::get_last_error();
    else
    {
        ec.clear();
        exit_code = status;
    }

    return true;
}

template< class Clock, class Duration >
inline bool wait_until(
        const child_handle &p,
        int & exit_code,
        const std::chrono::time_point<Clock, Duration>& time_out)
{
    std::error_code ec;
    bool b = wait_until(p, exit_code, time_out, ec);
    boost::process::detail::throw_error(ec, "waitpid(2) failed in wait_until");
    return b;
}

template< class Rep, class Period >
inline bool wait_for(
        const child_handle &p,
        int & exit_code,
        const std::chrono::duration<Rep, Period>& rel_time,
        std::error_code & ec) noexcept
{
    return wait_until(p, exit_code, std::chrono::steady_clock::now() + rel_time, ec);
}

template< class Rep, class Period >
inline bool wait_for(
        const child_handle &p,
        int & exit_code,
        const std::chrono::duration<Rep, Period>& rel_time)
{
    std::error_code ec;
    bool b = wait_for(p, exit_code, rel_time, ec);
    boost::process::detail::throw_error(ec, "waitpid(2) failed in wait_for");
    return b;
}

}}}}

#endif

/* wait_for_exit.hpp
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
*/