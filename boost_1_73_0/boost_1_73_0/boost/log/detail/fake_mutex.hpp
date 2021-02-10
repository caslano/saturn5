/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   fake_mutex.hpp
 * \author Andrey Semashev
 * \date   31.07.2011
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_FAKE_MUTEX_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_FAKE_MUTEX_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! Fake mutex that doesn't do anything. Note: we're not using \c null_mutex from Boost.Thread in order not to introduce false dependencies on Boost.Thread and Boost.Chrono.
class fake_mutex
{
public:
    BOOST_DEFAULTED_FUNCTION(fake_mutex(), {})
    void lock() {}
    bool try_lock() { return true; }
    template< typename T >
    bool timed_lock(T const&) { return true; }
    void unlock() {}

    // Copying prohibited
    BOOST_DELETED_FUNCTION(fake_mutex(fake_mutex const&))
    BOOST_DELETED_FUNCTION(fake_mutex& operator=(fake_mutex const&))
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_FAKE_MUTEX_HPP_INCLUDED_

/* fake_mutex.hpp
VFFITbEa0FeuYnl3gsfNeWzU21Q96Z1N+l2XWq4p6xg5yBS00/FnQ1olK9p7xvYNsLRWH+ulzJeMimZJj6iYMRyvGHgOHSUwiNSAKBVr6vF0v8mYI7LdPbHXjuaPcPRtzE/OPk9ONwP3TNy3xGeTWUdoqxuNHza9+NSHFZrH/226RSbzVf9UxeUqwUthZQRzH8tle7zvuqKdiZBXKoqAI6C76RYpm3286K20TD+IPSNNt30rIsURVoNOlzqHBX3R0uUO00as8A5Tb8fsro11EYeCUTDGkn927e5j+wfU6ak0kh2aZzI9HgyDk8FZfzjSHiXE4KiIBnDzgx2KovtmoufEGQN9n6ROASUiPxSFWIfQJx1VjJew0xluuL9zdQBzVJRJDw2dMgrFaKXPYwg/4oVTH8iR/ba/r3eKLqsRlSfJfjnbrrEWYI6lNNbQj4/kfpuJRdUo5HU2JN0iNhGfCyrs5iRoinNFpR+g//RpsQfkYYJ9dh1WB/Ywjp+O698d2F3ZcV4m/JdOrhQMV0uMUdXg0mDiIh8lQjKP2Cujujtt15QhsyZ4an8iKS8DKL0cM/RIUWQorWz+Nkl7/wVQSwMECgAAAAgALWdKUmdt3yisAgAAnQUAAB4ACQBjdXJsLW1hc3Rlci9zcmMv
*/