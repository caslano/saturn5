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
Dsd0rFpx3eFh1lY011xz7UGqg+HxqMOvs+5vC7+mCr/W+r+R/loq/DprrPmr4deExEneg+7rsFzhvhYyiB+EXFfLjutTybIQCFqytuWaZ0SKgm5Yb5a0Jhj3da1c8ryeVUye17dczzxvYEVUFWN9kqEJo4rAKvfxGoynJJh1Jg7jZtAPw/Ot5qxJ5Nu4r6fmYelAvlzbD5I8ME2y2IebcWO6fJhniT2MO9PWBnciEX5tDh+0
*/