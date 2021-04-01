/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2012 Hartmut Kaiser
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/config.hpp
 *
 * This header defines macros for linking with compiled library of Boost.Atomic
 */

#ifndef BOOST_ATOMIC_DETAIL_LINK_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_LINK_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

///////////////////////////////////////////////////////////////////////////////
//  Set up dll import/export options
#if (defined(BOOST_ATOMIC_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && \
    !defined(BOOST_ATOMIC_STATIC_LINK)

#if defined(BOOST_ATOMIC_SOURCE)
#define BOOST_ATOMIC_DECL BOOST_SYMBOL_EXPORT
#define BOOST_ATOMIC_BUILD_DLL
#else
#define BOOST_ATOMIC_DECL BOOST_SYMBOL_IMPORT
#endif

#endif // building a shared library

#ifndef BOOST_ATOMIC_DECL
#define BOOST_ATOMIC_DECL
#endif

///////////////////////////////////////////////////////////////////////////////
//  Auto library naming
#if !defined(BOOST_ATOMIC_SOURCE) && !defined(BOOST_ALL_NO_LIB) && \
    !defined(BOOST_ATOMIC_NO_LIB)

#define BOOST_LIB_NAME boost_atomic

// tell the auto-link code to select a dll when required:
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_ATOMIC_DYN_LINK)
#define BOOST_DYN_LINK
#endif

#include <boost/config/auto_link.hpp>

#endif  // auto-linking disabled

#endif

/* link.hpp
DMt6lnUkzsAHKbuaRYtiDW9HzEznJQzDKcRElq9QnN7u/JYMmVufYr0nH6Cq9L3oVuuf0FtoK1ruANBgfN9lAtQzcF20RluZBhhuX4xaMD3OOs9SA1e9RdqMO6jSL4YMJl/GXGMTXOjLXAlvGkndYbmNldUujhLksvh5TS5+ytfi7NzoQUCOj90WhblNcS2vPVRoeEtHX0xXFDSk301uUvlpBEEIeAqmn9CErZLP1k09M9D023Agz8FMCok3l766zhmxlKFuQ+02r0y7rFhhXQcu4LL3pSRyN7zsoJbNYKwB+sGo9/GfhLYX8x4DllGVHGeiV+7PCNxwoPpz1h1cC/KFZA60OEE0Vb6Gg2JIkTHsPyLqRNPyTESub/D3LOYqkDDDzKTvSOvEXiXpBfxewAnuJccPEXCYPniEbV3/j8liJwRpNq8ocwm4x6T5q74/RbOyVwqwyIiZA/04Oq0d9SYjnxwHqwZF8I/1V/a5Q1Xjpx7oL/9qSz9/8YouqjiLjBvBo1V6RJysLUvTfnNEVnIasQF4O/nExZESB4ItN/cCmq41LK+GvvKwTQ==
*/