/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/capacity.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c capacity keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue capacity to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, capacity)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_

/* capacity.hpp
heTZn/kX+YIulCtFFZf/z9x/9s2zr59d8ZFdDxd5X+K48uOi4FSd2SFvGdzPp7uFbVkrqEX9db0KA376r0d3S/35lkWLFGIVzVlyRdtawaFJW9r5qyby8ZlZh7dXEDP0nDeaydMfPRjvGPp0DDycN7K3DuhzNQHLsguuZbNRDnoubVleTb1Y27py83ZeulvED+6bgMcG7stm1jwEbrwHHYaGVwEjy66x5nq77rGJvfuyK+1q
*/