/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   record.hpp
 * \author Andrey Semashev
 * \date   25.07.2012
 *
 * The header contains implementation of a log record placeholder in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_RECORD_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_RECORD_HPP_INCLUDED_

#include <boost/phoenix/core/argument.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * Log record placeholder type in formatter template expressions.
 */
typedef phoenix::expression::argument< 1 >::type record_type;

/*!
 * Log record placeholder in formatter template expressions.
 */
const record_type record = {};

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_RECORD_HPP_INCLUDED_

/* record.hpp
kmfEomdDNnmu0V5M4OQ73E54O/Mctpexyab4NV/lNmLjjrzPs27yvvay0Ybmo4fer721R9vPuu1DDqW49GZHUUx4/f3DvKEhPChI/1a7tepeTagDkdNWPHhTfoQwZKujRXZ7ll82Wh5bw8iSR6+F2Ak/hhmiXKgctDbxsAIPX5uHGnL+ijMPhE+YSb+SImAylky4WWrZaClegZ4mkbEsT5sTUj5aCr0o6NrE9Sr0Qrp8TA5L
*/