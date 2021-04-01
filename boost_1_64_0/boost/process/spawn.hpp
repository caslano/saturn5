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
 * \file boost/process/spawn.hpp
 *
 * Defines the spawn function.
 */

#ifndef BOOST_PROCESS_SPAWN_HPP
#define BOOST_PROCESS_SPAWN_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/child_decl.hpp>
#include <boost/process/detail/execute_impl.hpp>
#include <boost/process/detail/async_handler.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/posix.hpp>
#endif

namespace boost {

namespace process {

namespace detail {

}

/** Launch a process and detach it. Returns no handle.

This function starts a process and immediately detaches it. It thereby prevents the system from creating a zombie process,
but will also cause the system to be unable to wait for the child to exit.

\note This will set `SIGCHLD` to `SIGIGN` on posix.

\warning This function does not allow asynchronous operations, since it cannot wait for the end of the process.
It will fail to compile if a reference to `boost::asio::io_context` is passed.

 */
template<typename ...Args>
inline void spawn(Args && ...args)
{
    typedef typename ::boost::process::detail::has_async_handler<Args...>::type
            has_async;


    static_assert(
            !has_async::value,
            "Spawn cannot wait for exit, so async properties cannot be used");

    auto c = ::boost::process::detail::execute_impl(
#if defined(BOOST_POSIX_API)
            ::boost::process::posix::sig.ign(),
#endif
             std::forward<Args>(args)...);
    c.detach();
}

}}
#endif


/* spawn.hpp
tLJ0ndcgw0zJgkbDls9/jr8UsYLSoX05dBkVWexg8QINp8ofxC/HzGSMcoeQq/YV7lPccXEOpDka6tli0HJqTR72vCFL3zCV8kFtNv9EwzXr1H6BuZ5wHxf/LUtV9bX5gBHYpvD2AXU5t/Xsj4FD5MPdVvOE/hek5mNrExNRTb5p9KHQQB/SvpVqYAVk2ZPJJeMZIaaKgftbNyKSZflFZZIecKe00QTEUnLFGehh/uA36e6TdPZWdA5WUZQ8s8LxgmDpIkDC8rXbzFXsWLSr05WSQkXkLvdHVWW5SV4UwPTiMpPA8j052j0pjtt8rCbVFUtRAtN5kiBcDKzqNwiKZsuaXjMQjXLKyy9j1t5zbMrEGwGhblOG8kyxQ9GMNJNE1RrRwxxF8i0QtRxUqPJOiO2ytesdU6gCnDPxK8ihJeEiw9X0qpbAEfu/8/IF/f2BwmH7vI0+l+XxTDZ+3XapiF3ih7Ag8j6eh84EC9ZWfPoSFZoSNaZ4nKJ7xrjHRWSPGJ9fRUGkxjpLVfTl1Q4mbED10g7GfALx/04V6Ie377chA43vsR/eM/dQlA==
*/