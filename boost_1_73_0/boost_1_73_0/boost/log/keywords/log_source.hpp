/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/log_source.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c log_source keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass event log source name to a sink backend
BOOST_PARAMETER_KEYWORD(tag, log_source)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_

/* log_source.hpp
wRzygL0hnb5TkeBZEdynNxmxYx5wcMNKt0Vhe0PS+PpVSBpfr4akB/i1kHQyvh6STsY3gF4P9Df43hbQN0Ny/f6tkDxWb19Ivhf2e6DNQP8A9E2gbwPdD/SPQD8C+i7QfwJ9DyhWij8BDQF9H2g7oB8ARR1/qBrEPdwg7qHK/zxjLzK2n7F3GWvjQHyWrwKUCvTCtjwQ3zKI4Urfl+vnVZW3ssv4KRVl5YKEPQTGhZnCRqN7iKiyQopYIUWO9nk=
*/