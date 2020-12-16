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

#ifndef BOOST_PROCESS_CHILD_HPP
#define BOOST_PROCESS_CHILD_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/child_decl.hpp>
#include <boost/process/detail/execute_impl.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/posix.hpp>
#endif

namespace boost {

///The main namespace of boost.process.
namespace process {

template<typename ...Args>
child::child(Args&&...args)
    : child(::boost::process::detail::execute_impl(std::forward<Args>(args)...)) {}


///Typedef for the type of an pid_t
typedef ::boost::process::detail::api::pid_t pid_t;

#if defined(BOOST_PROCESS_DOXYGEN)
/** The main class to hold a child process. It is simliar to [std::thread](http://en.cppreference.com/w/cpp/thread/thread),
 * in that it has a join and detach function.
 *
 * @attention The destructor will call terminate on the process if not joined or detached without any warning.
 *
 */

class child
{
    /** Type definition for the native process handle. */
    typedef platform_specific native_handle_t;

    /** Construct the child from a pid.
     *
     * @attention There is no guarantee that this will work. The process need the right access rights, which are very platform specific.
     */
    explicit child(pid_t & pid) : _child_handle(pid) {};

    /** Move-Constructor.*/
    child(child && lhs);

    /** Construct a child from a property list and launch it
     * The standard version is to create a subprocess, which will spawn the process.
     */
    template<typename ...Args>
    explicit child(Args&&...args);

    /** Construct an empty child. */
    child() = default;

    /** Move assign. */
    child& operator=(child && lhs);

    /** Detach the child, i.e. let it run after this handle dies. */
    void detach();
    /** Join the child. This just calls wait, but that way the naming is similar to std::thread */
    void join();
    /** Check if the child is joinable. */
    bool joinable();

    /** Destructor.
     * @attention Will call terminate (without warning) when the child was neither joined nor detached.
     */
    ~child();

    /** Get the native handle for the child process. */
    native_handle_t native_handle() const;

    /** Get the exit_code. The return value is without any meaning if the child wasn't waited for or if it was terminated. */
    int exit_code() const;
    /** Get the Process Identifier. */
    pid_t id()      const;

    /** Get the native, uninterpreted exit code. The return value is without any meaning if the child wasn't waited
     *  for or if it was terminated. */
    int native_exit_code() const;

    /** Check if the child process is running. */
    bool running();
    /** \overload void running() */
    bool running(std::error_code & ec) noexcept;

    /** Wait for the child process to exit. */
    void wait();
    /** \overload void wait() */
    void wait(std::error_code & ec) noexcept;

    /** Wait for the child process to exit for a period of time.
     * \return True if child exited while waiting.
     */
    template< class Rep, class Period >
    bool wait_for  (const std::chrono::duration<Rep, Period>& rel_time);
    /** \overload bool wait_for(const std::chrono::duration<Rep, Period>& rel_time) */
    bool wait_for  (const std::chrono::duration<Rep, Period>& rel_time, std::error_code & ec) noexcept;

    /** Wait for the child process to exit until a point in time.
      * \return True if child exited while waiting.*/
    template< class Clock, class Duration >
    bool wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time );
    /** \overload bool wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time )*/
    bool wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time, std::error_code & ec) noexcept;

    /** Check if this handle holds a child process.
     * @note That does not mean, that the process is still running. It only means, that the handle does or did exist.
     */
    bool valid() const;
    /** Same as valid, for convenience. */
    explicit operator bool() const;

    /** Check if the the chlid process is in any process group. */
    bool in_group() const;

    /** \overload bool in_group() const */
    bool in_group(std::error_code & ec) const noexcept;

    /** Terminate the child process.
     *
     *  This function will cause the child process to unconditionally and immediately exit.
     *  It is implement with [SIGKILL](http://pubs.opengroup.org/onlinepubs/009695399/functions/kill.html) on posix
     *  and [TerminateProcess](https://technet.microsoft.com/en-us/library/ms686714.aspx) on windows.
     *
     */
    void terminate();

    /** \overload void terminate() */
    void terminate(std::error_code & ec) noexcept;
};

#endif

}}
#endif


/* child.hpp
fBQa82wLjnkqCscWu7LtIsOA3m9eNsNdXyr+ByP8b0T4J84M98+O8AfODx9XfWaozwDXkQx553fTEUe3b5D+6hkzXy1YUfb4s4f/LueV6Y7c90521eMPXll/8kdXvnRy/ksFsd69Hevd4bHeyX3478aO9e7t/FMd+eIW5z5b+H7bou/KGky4/9QZX3JOtXPkD+y694VvGvW6YGuXymcfb/fY4ljvzI71jvNY79I+/HefR3/Xe6x3h8d6R3usd6gf/ru9o79zPdY77A//Xfix3ln+WgdHPuHoYn9mq9tLbx27Y8tFiRcuiPWu98N/d3v0d6jHegd/rHfnx3oHfOx38zds78gDG9OLxkw56ZZlq9YO/77p9rGx38F/xVGO/LV7Pum69te33z7yw53DRt349ptcH8naau38jqUf2Ut9X+yXfXHlncv5yB+zvrdJD34ni8zhDH7HjPF73+k9ve8rsTkfe9fw/Vbr+z3W9+XW9/7YSSQNvYk/wPp+Ct8PED6F+qHYkeue9rrf/gGYjftW83JhipldC14EG8I58Dh4CewI58JT4TzYF14Kz4O3wLHwVlgMF8I58HJ4DbwC3gAXwdVwMXwYXgmfhUvgm2rnPbXzPrwa/hn+BhofeYVp8Fp4FLwOtoXL4FnwFtgX3gr7w5vgULgclmt4lYY75XFnaH91iF/KIwN3g5YHU85mOyyBdWEpPBZOgK3gRNgOlsE8OAkWwHI4CVbAOXAqvB1Og6vhbPg7OBPeB8+Hj8ML4ItwFvwIXgQ/Uf1P4UGf7kGu+6IfgKfhPtLr8iv8KE8VP+UA/wzPg/thKTwAz4efwDnwU3gP/Aw+CjE9+ynYGb4KT4Fvw1Phl/A0mMSxTodN4BmwOewCT4ZdYXvYDZ4Ku8OusAfsB3vCQfBLH/UCD8Jq+DWcBr+Bs+C38Er4PVwKDfGuhT54M/TDFTAAfwdrwHUwAW6ANeHbsBY8CGvDb2Ea5LtJh3VhHdgc1oWtYD14JqwPz4IN4ACYBUfDbHg+zIFLYC5cBo+Cd6t8I2wG34LN4XvwWPg1bAF/gMfDWtTfCbAePAm2gC1hS3gyPAO2ggNhG63/GaF9k+HH2l5TcGXaXtfTrh3/g7Ax/APsCB+Ci+FWeD18At4MH4ar4Ea4Bm6Cm+Fm+Ef4KPxA9T+Fg4zuLwxH6fETcD30+LvR88EXYBp8ER4F98C28BU4EP4JjoSvqd3xoT104aVqNwl3rtodqnaHqd0RMBcWwmGwGFbBc+A0OAFOh+PgLFgK56lcy1H3dCWPUcpxBXoO74SJ8C493kpYpf7z4Rq4CP4eXg3XwqVwFbwGrtby/R3crOGfwt6hvU/hKXr8GrjT9PhPaX6fhnXhDpgDn4XHw52wM9yl9vb4dQ9S3ev0AByB2657IM6oaWY3gpfAY+ClsDVcAE+DC+FAeDkcBhfBMXAxLIFXwenwangBXAoXwmvgjfAGeBu8Ca6DN8MH4bXwSXgdfA4ugy/B5fBNeCt8D66A0h/Dr+FdMN5H+4V14UPwePgwbA8fgQPgZjgYPgonwa1wHnwaLoPPwJvgs3AV3A0fgi/ALfBFuA3ugW/CV+EB+Cf4pcb7Bu6EqX7KG9aBe2Fj+AY8Br4FO8J3YDf4LuwD34Mj4T5YCt+Hc+AHcBn8EN4LP4Lb4J/hLvgJ3Ac/hYbz/y8wBX4Gs+AXsDn8EraDX8GB8Fs4Bn4HS+H3cCb8AV4BTRLnPYyHd8JEuBrWhJthLbgDpsI3YG2YFkd/CZvADHgSrAO7w7rwHFgPlsJMeAdsBFfCxnA1bAI3wGy4E+bAT2AujKO9NoX14THwBNgctoLHwuD5ontYgo5RzpcT0PPDk2E=
*/