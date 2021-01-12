/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/severity.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c severity keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_SEVERITY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_SEVERITY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass severity level to the severity logger methods
BOOST_PARAMETER_KEYWORD(tag, severity)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_SEVERITY_HPP_INCLUDED_

/* severity.hpp
3Fy54pB/0XN3yJl7LedVi1a2UsGOLbhN8co4h9upOlVriylb4sEt7IJIuWyhtGWZ7pWstzXu2NqlXPC89ZTStrUttirVtpxSynmwnmvc8lkva55BXvoXy66jskGBJE4C5cqlkpMzmbPSmDObuNXKpeLOlsBemZ93qG1ZLW9XKznejuXqtkn60m+Kt+X6iQe7I/JgDKZd3rbgmPuWhWLyvE22mvgXC65nnpElbUwYot+Zzp7f
*/