/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/order.hpp
 * \author Andrey Semashev
 * \date   23.08.2009
 *
 * The header contains the \c order keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ORDER_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ORDER_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass the ordering predicate to sink frontends
BOOST_PARAMETER_KEYWORD(tag, order)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ORDER_HPP_INCLUDED_

/* order.hpp
nyH87wK+RODngVsivU+BTxTxrQNnn7Mj6wPwCbK9AD6Ywuu/tYHPFv6bA+8ncAV4isB7At8mcAf4SZH+scBzGED5BZ5b4OuAV7KEPgCvKuR/H3BbyP9p4LcF/deANxb68h7wpiv0438NvF25H3/W7uxzbi78FwUuC//VgVcW/G0MvJjAReBDlu+3H7sB7y/42Re4IuUBvLwIfwTwCkJfjweWx7yfBXy+JeQDfJ7ADwJ7Ir3n
*/