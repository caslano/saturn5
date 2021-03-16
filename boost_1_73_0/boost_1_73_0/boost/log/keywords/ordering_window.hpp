/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/ordering_window.hpp
 * \author Andrey Semashev
 * \date   23.08.2009
 *
 * The header contains the \c ordering_window keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass the ordering window to sink frontends
BOOST_PARAMETER_KEYWORD(tag, ordering_window)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_

/* ordering_window.hpp
yT0mhU5Nd09OIXezi5be/UAHAYUycS8B+hDQeUAfxniAPuJIyxPiU5YnXrUTaK0+Q9hCddWOZs+S7wPm+5Kxw4wFVwo+ccyJhDRPB+6O1tdm7scas0d9+ANogaLYA0GnvToTe2oZFMb8VG3jjl8zHj//VUuPow3rM3Gyg+yHdEyQgukN8pR7cnUdifckj9eybCTO8lMl6YUkvLzTwW4YOUZ64ClI38GOOqaDKSSOrOeOtRkYDdkQHVd1oShrKUo=
*/