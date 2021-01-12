/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keyword_fwd.hpp
 * \author Andrey Semashev
 * \date   29.01.2012
 *
 * The header contains attribute keyword forward declaration.
 */

#ifndef BOOST_LOG_EXPRESSIONS_KEYWORD_FWD_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_KEYWORD_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

template< typename >
struct actor;

} // namespace phoenix

#endif // BOOST_LOG_DOXYGEN_PASS

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * \brief This class implements an expression template keyword
 */
template< typename DescriptorT, template< typename > class ActorT = phoenix::actor >
struct attribute_keyword;

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_EXPRESSIONS_KEYWORD_FWD_HPP_INCLUDED_

/* keyword_fwd.hpp
j/HAC/Bgu4BHmXysFiFzMjl6DXDfxfPx6OgzKyOYy4WXO26lRLdhfzrsZzR9Kq9Dk783G8m7jeRt2PgRcL9dfvqbDi9fBiXPG9XgCyx73lzufyxjRYgJEs0K8M6nsQ3lwjSlW4Bnrq/jvfO5/RZsxUTL45t1NBr0DgoUtTzeWZPBgWmrjWTz81k2PFMGVfVTNW+syBKg0OuyBJh7/hoP/h6zRCLA6P0lasM8Cz1/dG2uo+pn
*/