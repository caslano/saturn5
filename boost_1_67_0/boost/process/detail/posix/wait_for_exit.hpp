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
            ::waitpid(pid, &res, WNOHANG);
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