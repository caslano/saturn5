/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/start_thread.hpp
 * \author Andrey Semashev
 * \date   14.07.2009
 *
 * The header contains the \c start_thread keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_START_THREAD_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_START_THREAD_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows enable/disable spawning a dedicated thread in the asynchronous sink frontend
BOOST_PARAMETER_KEYWORD(tag, start_thread)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_START_THREAD_HPP_INCLUDED_

/* start_thread.hpp
EgHyLnC1uKVl8Z0Ise3hKZaFu+uVt6s6209xiIyVd7aYshVJyDwbhhhvmZ1S9GqVatkr58pF1vtClRggceDZzRaL5R1rOFW9Wspu59QKpRrS4XAlt5bL5rZ2aka87IYQnlPdMptzNC6Wc9lirVBZ+yd4XY1BmSwmq+etoTBFp6b1zXF1GCRf26pY3gIROUlOv7w1s+JslU+UOVFYeq5Wy1WlgJazU4WKFCZyaqmy3zJbKJZL
*/