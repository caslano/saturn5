/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/target.hpp
 * \author Andrey Semashev
 * \date   21.03.2009
 *
 * The header contains the \c target keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_TARGET_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_TARGET_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass the target address to send log records to
BOOST_PARAMETER_KEYWORD(tag, target)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_TARGET_HPP_INCLUDED_

/* target.hpp
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
*/