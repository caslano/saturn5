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
9Qh59guDa1pVtc+1lv4THb0o/S5T3E94Ozy0MKKoo6DWCHs78ruehWyML8DcBtymMUV+kyiTkHovgm2l/yymUI1692Lb7myMr4NruRydWA/BdG+grjeq+ra+3kTwWmm26e8X4v7sFHysdRXgRFv1jcNoF/8lXqu2eo32bFPNXC0918fMGW3XBpq56nr7s1e/1nP1pTvX6K4r3YuM7jrSXc01Dhr0VMcKYzth/VqOFaxHcrIejdwUyUlKtdfE9uT67br8Zajjejpxz3nPqUwrx/nA4YQhqRnWQ4f+bC7601vty2H4tQyTpIUyJpttjXG6Hwt4TrblOHxN+je2O44wrHW/V21vZZhtCzmOu94bCmn+NscNu2kzfLJm26aktWywXjbFtk1J97Lq+Ga+Z92S/q1t25hUwxr1Se0PsT6j7JT0j9MK8H8w278nuU1q2/7gMdoI1LcR57gLG+vKesyR+jeOOS2knKpXcoF6OVVX5NTyq1yK5NRy2R+vogpo8ndKbQMniTXO45WsrxzXQ2RdjStKPUyOkO2ChP3xiuHc2gHj+G9pl66H9N+pDaP0dsJuW7KOI03eA2VyttsNZd3PK4z2+Z6Vfh/zPuGpbSPM9yTnmaC5X2RIuSVaJa02w5KjK0FyG7QAsgO11pZhqVfLNjBCys3XSqlhQ41ht2qFyQ7SWsl5y8b8HCsDVJtfXkFy3lIrwNfL7rwlTJXPDlDtXHlWCvDJ93A7V8Gq3Fy9nE+Zh8qUo9tZp5vZHrcQW4mzZltg6jj8+NvqZDlOyfp3azOL9WzZVllv5Cimtjf9PDVJjXiYg7KYhc8zzqhvZXtLSKfV5GQauMxKHhCXwtm6eSyTfc84Bxkq5UMdNtugGpfDvf1AWV/VpF+Cw2a7M4YLNo5Brs9lmmW6MVKmge226D68prla67S2C9dFyvQ02oWb+p3tebGUXS5lz1nLureRRzWZ52q9pbwf9Z3PaL8uUXIVHOY8JcVlJcWmJSeYwzWT8ZbmOBbkXC5pb89y/iYrNkyVvS/jq0p95Xd+xjLaaasr4/CWeYuS6WQyb2kyvluMz5y+M+2afoQa5w0ZZyMtP2ONJKIJo704c3zOGZf8bfKN2a4Lkt3G9ryd2CHbtRnW3DDivkuCnNreAx5je5djs7Htsb1b2/21ngtathXyUoeSz1PfQVIXUZKX+jHaK1XjIGWWvW2WlWW3fq5YHqzJX3l1L11Z3OdsU1PWQ86AxLTEzDiesa4+rRunB2ZbjnzqsD/nZBzmdhxFwqE+89u3W2qWl+e1W8pL2+uPOG4vtmzLnxTVn0trHld/lf5fs414GPOhabRr3J9Slv0p63tnuS6a+axeJjqAJ2dbzltipUyBPNt2SZl3aWHe2Lefl3LJ8jxzP73tJMn5aM3Z3grR/axqr/b7YMQ/MZz4kG3tEP0+wrmBdONd/BgX4qlg1zbn9RifL2X7UutHb1ua5SdnrocIte0NkbxZ39btT9qYNupDve+r4/COUNeEpxAO5WfFWAZZ3pykxOGJafHpCTItsw1xaeXSaPf7gZStorq53+WEs9tXPht4afq4Jhvr3cxZ2xaXmTbOE49J//FaHynDZwyb8fhaxlNcP0559TXmuXyDBn1r8B8J89qEzFs5s21jy/tJKN6U8TWy9I/PsLaXflv1N7czhpdZN4+jJ6RMX847W+rng7ItbHzMtlzluTgyn4HWzybWXC3N2E5Uu+JqnQRb2yA36jRA6ma5XANz1oZqy17Gp2mHw/OeC64trMnfbsKD2EXM55jSV8rnpKTHJVg+u1o/j5rnd/2l7FatFGtpsZbP7vjC+Gw/bxrnbUnSfxtry4OzMofelql8Vjw=
*/