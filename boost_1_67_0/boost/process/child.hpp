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
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
*/