/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/iteration.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c iteration keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ITERATION_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ITERATION_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing scope iteration direction to the \c named_scope formatter
BOOST_PARAMETER_KEYWORD(tag, iteration)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ITERATION_HPP_INCLUDED_

/* iteration.hpp
SsT0fRJQ4t9UP3IfK/E+Utg2xpoYSzrRQIV5k1bsBvN8CsNKPSqgsNOFHMdQaee2qDCchc0rW7JodmlZUbIF/oSqYsM9w+DEeFuqTetZEesp06sZa2Tseze0EW1qaP1aVEnJospYRbytuvDvdWh7Q1vLqlnLDW0tN7S1P0w1F/pUc6OwhwNTNSd6072AarCHLokt/p/0QsKqOcnUcxur5zZHOwEltpGxxNpJoBxviy1GP8qnnDphNyX0RnYV0qs=
*/