/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   unused_variable.hpp
 * \author Andrey Semashev
 * \date   10.05.2008
 *
 * The header contains definition of a macro to suppress compiler warnings about unused variables.
 */

#ifndef BOOST_LOG_UTILITY_UNUSED_VARIABLE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_UNUSED_VARIABLE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__GNUC__)

//! The macro suppresses compiler warnings for \c var being unused
#define BOOST_LOG_UNUSED_VARIABLE(type, var, initializer) __attribute__((unused)) type var initializer

#else

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
BOOST_FORCEINLINE void no_unused_warnings(T const&) BOOST_NOEXCEPT {}

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

//! The macro suppresses compiler warnings for \c var being unused
#define BOOST_LOG_UNUSED_VARIABLE(type, var, initializer) type var initializer; ::boost::log::aux::no_unused_warnings(var)

#endif

#endif // BOOST_LOG_UTILITY_UNUSED_VARIABLE_HPP_INCLUDED_

/* unused_variable.hpp
YT7NP8C/wN8snCd+IE6RzofGXCGtlp6UNkBCGfnH8ir5Ufk52JecWq6NMaqNqJGCrbHAeMM6yBfxLYf+Y7aUEJ8VI8KKeIuz+DP4R/i3+QOEMsIVcZM4RLpR6oA8zVPmQ6YWKouUy5UnlTjmWZX2gmbp8/Wb9I36xVgjX4HVfEde5v9oMtZx1iXWC9Y/LR5WEfWrURk8hK3CyjCD/QF7KZWU8ejFDfxX/NHCeGEhRmUl2j1A
*/