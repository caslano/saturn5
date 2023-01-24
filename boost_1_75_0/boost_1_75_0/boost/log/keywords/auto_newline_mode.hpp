/*
 *             Copyright Andrey Semashev 2019.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/auto_newline_mode.hpp
 * \author Andrey Semashev
 * \date   23.06.2019
 *
 * The header contains the \c auto_newline_mode keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_AUTO_NEWLINE_MODE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_AUTO_NEWLINE_MODE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing automatic trailing newline insertion mode to a sink backend initialization
BOOST_PARAMETER_KEYWORD(tag, auto_newline_mode)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_AUTO_NEWLINE_MODE_HPP_INCLUDED_

/* auto_newline_mode.hpp
7Rfb+Sf3HG2fGjwEHt0ZTXxsd3t4q6Pr0im9ObByxfQqZjT08xJ8a3LL9wSQpiSCG+iHIPwznOIQqatwA7PnqsvdcIeABnspv427U7Ul/1eR1SqTbQQtXMzEZPLRvoP6BFP8l7Pe8Uep+x5IGvzBsnNZdGt28TtlvcqKqEOUdpnDwVh9Cumcm8V0k16fcS1l818gtm9tqgQ/OXYik2mezgNX+PSzDnpxPZTactZl50TUEf4Vsr6Npg65a5ZPKirhQymx3ECELZbjdSf1g+pWNj3C17m3FvUF4fJj3qgLfRKB99kPAgTfknAH0CHAv36/QZi4t7+zuRPw4n9OhH/bq9ILBOYeFVmPBMwiiu93N6KC7ILintflxvv1Z3VfwHRAs87rC+QXFmaE/VZrwF+mgRZw3pvgB4TSg5we/jUt46hftj2W5HEA++Ux6quvxRi3PoKZNeCl8WUxv2tR5+xsDOG0t8K2uP04KqWS/Pz9YhjRt/i60URyiaeb8oqIK0N/XM+HZ6tfk54A2Dhq99OI6LqiWO5TmjmbczsWvV5BYFRJg+R1Melok7PsfbnhLnAy3kbll/LXdejl2DCC9u9Wpj2rwVrE/RuFuf74H1Zm/08r8/yFV+RfXOb9dy5TYNlTKcAmVg7VdvJVdw4Qy8IlNx47bQ+EkEfh+9OCGEIhz+xCJWfBu8FO104J6F2icK47Do4ULLmRHv2Lms4X
*/