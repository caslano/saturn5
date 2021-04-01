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
LGFLGRk3jcb4TEjfVaf6p0+jLorMSVQqUjG0ZWhmaHpM6cyg1fwC38valuIsoBnGXbHXe1dpkH8TIWHk98n0UvMklThxbHqw+pcRoDkk45LZ7fl1bpFyr2GLxNXV8rL3SVGlunR8UxvEweyB0jTybgRnJ8yyuNgHoEOdK8Encd/Nnh1Uj0mV62XAe9Pl+hjjOE2pOF2jD9ac3wIhS+ltBf+ouU4K60hkP4O0DE4TNw7iBybZykDjFqiVWti/hoAaybPCl+GpQ0hLY0Y9qoqw5wI+g24GTR8iHijOUSMZgT24KUakckLXAplVuAtPRkz6JBBJxEJe4yLyBECVV9o2PL9dwaJo2bga7f44pwrPlFKM4DrswZ+kL7zQpEeVR3ThtarX6zh8hcffc4L72MR5euD5szyj0kiLmB2hRK6dny8LDQsebgnZq4gBBBcs/GJHVoHoFiitP2q+TuCGYNHr95BhUEbnrk8K8R8uOlZe7lXkafeG9yTqrVZnGA2cCTyJHbeAF3pUY/9usHfoNcsvSFqV6nm31SFXeFEefpu9CCHMbmSw0Q/KZW2ZAA==
*/