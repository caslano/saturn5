/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/channel.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c channel keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_CHANNEL_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_CHANNEL_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing channel name to the channel logger constructor
BOOST_PARAMETER_KEYWORD(tag, channel)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_CHANNEL_HPP_INCLUDED_

/* channel.hpp
b7L7stizHnE94PqV1nfocg26bFFNWXbfHmIcstPueGCZHdqK64ckE7Pp1R1gO0raqOQ9JB0GQX4rnWUb+l9Ev3+9vvxT0sejLr9Vdl+FHiL2i+jP0uGsv6M+/cfT29HNYrcXmgKHXkdliv/E7woxXJpwCZITYyI81fnE+YPxC/7U2aL8fcG0g7/lXmjZ7pQtyhXq8eyO+iiFcljF5gAsJ6fVO0B/zmNhRX9F+Xhkk7ndG639
*/