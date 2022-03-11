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