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
 * \file boost/process/system.hpp
 *
 * Defines a system function.
 */

#ifndef BOOST_PROCESS_SYSTEM_HPP
#define BOOST_PROCESS_SYSTEM_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/on_exit.hpp>
#include <boost/process/child.hpp>
#include <boost/process/detail/async_handler.hpp>
#include <boost/process/detail/execute_impl.hpp>
#include <boost/asio/post.hpp>
#include <type_traits>
#include <mutex>
#include <condition_variable>

#if defined(BOOST_POSIX_API)
#include <boost/process/posix.hpp>
#endif

namespace boost {

namespace process {

namespace detail
{

struct system_impl_success_check : handler
{
    bool succeeded = false;

    template<typename Exec>
    void on_success(Exec &) { succeeded = true; }
};

template<typename IoService, typename ...Args>
inline int system_impl(
        std::true_type, /*needs ios*/
        std::true_type, /*has io_context*/
        Args && ...args)
{
    IoService & ios = ::boost::process::detail::get_io_context_var(args...);

    system_impl_success_check check;

    std::atomic_bool exited{false};

    child c(std::forward<Args>(args)...,
            check,
            ::boost::process::on_exit(
                [&](int, const std::error_code&)
                {
                    boost::asio::post(ios.get_executor(), [&]{exited.store(true);});
                }));
    if (!c.valid() || !check.succeeded)
        return -1;

    while (!exited.load())
        ios.poll();

    return c.exit_code();
}

template<typename IoService, typename ...Args>
inline int system_impl(
        std::true_type,  /*needs ios */
        std::false_type, /*has io_context*/
        Args && ...args)
{
    IoService ios;
    child c(ios, std::forward<Args>(args)...);
    if (!c.valid())
        return -1;

    ios.run();
    if (c.running())
        c.wait();
    return c.exit_code();
}


template<typename IoService, typename ...Args>
inline int system_impl(
        std::false_type, /*needs ios*/
        std::true_type, /*has io_context*/
        Args && ...args)
{
    child c(std::forward<Args>(args)...);
    if (!c.valid())
        return -1;
    c.wait();
    return c.exit_code();
}

template<typename IoService, typename ...Args>
inline int system_impl(
        std::false_type, /*has async */
        std::false_type, /*has io_context*/
        Args && ...args)
{
    child c(std::forward<Args>(args)...
#if defined(BOOST_POSIX_API)
            ,::boost::process::posix::sig.dfl()
#endif
            );
    if (!c.valid())
        return -1;
    c.wait();
    return c.exit_code();
}

}

/** Launches a process and waits for its exit.
It works as std::system, though it allows
all the properties boost.process provides. It will execute the process and wait for it's exit; then return the exit_code.

\code{.cpp}
int ret = system("ls");
\endcode

\attention Using this function with synchronous pipes leads to many potential deadlocks.

When using this function with an asynchronous properties and NOT passing an io_context object,
the system function will create one and run it. When the io_context is passed to the function,
the system function will check if it is active, and call the io_context::run function if not.

*/
template<typename ...Args>
inline int system(Args && ...args)
{
    typedef typename ::boost::process::detail::needs_io_context<Args...>::type
            need_ios;
    typedef typename ::boost::process::detail::has_io_context<Args...>::type
            has_ios;
    return ::boost::process::detail::system_impl<boost::asio::io_context>(
            need_ios(), has_ios(),
            std::forward<Args>(args)...);
}


}}
#endif


/* system.hpp
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
*/