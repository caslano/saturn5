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
snt9TA1gcZ2E7bG/YuwCNydgDt75Gi9L6F7GEDLsdQ43OWpdVn+Dl8vbdbFoj3ifHtOtUSAu5KccCB2u33KGkxQCOHzbZzA5cANPF8ShXfAttDHkX7rQdgnu9ohtYx6Mff1392N5KF2hAodvogwmyx8FrszroAqYla5FeLrDjC8vtjoljQh40RDU/49LbauCFQG8cTj69eInkZdYUMDb4qHf1Q1g69MujQP8nqFg3QGrJHjWqKjjkaE4V5h9aWgdKVfx6rH897D6uXKkWXtp3iLv9CNxIyrsNV67j+fJx/E7N1A+o6sCqtAJeubaISiH85EAUJhFkSZ+IM49zq9c6LObVvvoSJRwNfCbEnDmMWZqaDmBDvbD5qHQI149X89VLguzgY2HzpX7IJsn6fLUX041hhq3t54vdVkcLut/VmGu9Pgrc7IFeBrGkfzbJRyuKtHmKRhcAf6Uv53J4QYVBQfqPZT8upzJEyktoR3xvZBhZO0uf5iCQI5UsnXk6tGiPAjKkL1/4zJExPD4sFUbTExXdN2XRZq0YeCJ+/7M04XGQNqkQUg7tqTEUeulopYqJ1yhwd5C+xCU45lPK9xcaAO2H4dS5GQfrEQcNB72J7Yyvrv+q7miripR/8SyjyIvL+Zl6K4hwrazbgT0mLUXBPRziEi7i+mPwC8dhrFwcCXDCYqvmHcsWXpdjbBgYHmxObD+IItLFx+wEa0c
*/