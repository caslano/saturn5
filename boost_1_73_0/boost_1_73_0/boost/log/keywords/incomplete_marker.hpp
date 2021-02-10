/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/incomplete_marker.hpp
 * \author Andrey Semashev
 * \date   15.03.2014
 *
 * The header contains the \c incomplete_marker keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_INCOMPLETE_MARKER_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_INCOMPLETE_MARKER_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing incomplete marker for the list of scopes to the \c named_scope formatter
BOOST_PARAMETER_KEYWORD(tag, incomplete_marker)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_INCOMPLETE_MARKER_HPP_INCLUDED_

/* incomplete_marker.hpp
0UXnxx9++qFZaPPDs2fUpoc72JG/AneV8me7eraf9vUJff3an7M3YPSDDHB88/yU+70JhjTZdZQfTyp++z19K2E5RmavNZyEM+3t0VN9jTxlbbGTRZvyLeUf+itMRLonWxkcWO4fiA177rmYYLi3h4FNPLsEhGke4lq64xY/LQWfcdsDnq23KS6yuzCam2AwyIthn6MkOKDQsPLoUuzbz9Q2O/rT6G8yUpqpBeZW37SfBjdhFIFJd2h8ZTaZDM+HpywN10D6hPk8o1lGasXmDx2NYR8AfzoZh/tPJhBc8BmdRkMEErGzSYjgLmZwG8ZbQWq0TASxTRi8L5Agmhu1JEqIZSVFjDkanQOMDZY8Li/2OoRZpISsaKosZyFw/1kuc+oKnYrFXBOCW2ztlFugo1Fqlb4EoaTrCmWAHDEwrvDr75uaRMs/FMIN/pfdbzAld3UvJydg2KnIpqc9S0wkusOtYEzW9/kBBAnGX1PGCgYgUkpQATUC3IA7nGg64bYlz0ZdHzLWXq3Y958+UUp0akBJglyFaOygMYMpDC6kLPis9ja0EBL/VvMTueWByTYiUuc0XnLj8kyDCl9YPESncMgWthUXz5wQvdGmgfaFzAPUsv3EH+u//u1FLvoxLzN30vY5Crh6cD9C4K95
*/