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
86FD7430xzg5tageeuRvxfxcdPsWDU/Q5mxDO+5qt9rn07qA8ln467E+M9knbMjOWBePmZkDl9O9vSJdhzXZgHSA3kG/lOGTLL5fC6f/WdN46XNMRjzStmIY1XMO5qLRiIdJOlsVnv8t+DL/NbSbZWZ1fRQPf9/IwhfVqMaW+XzFMhvG5Hs3FJWSembsKDkQS2RN4GoKL0d2fWJsxXoDv9F07oNTeOVadCzCbgwcEgOb7t/y
*/