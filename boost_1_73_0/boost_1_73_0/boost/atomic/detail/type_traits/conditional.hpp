/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/conditional.hpp
 *
 * This header defines \c conditional type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/conditional.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
using std::conditional;
#else
using boost::conditional;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_

/* conditional.hpp
NZefTeklBnWWYHuWsuAoX2ahtSy7qxYwkyiviInw5TL4bISPvR3KpOy9uUT8t4OoDdF8gVXLMocUrQmqFq45I92r7E60AWoOzBAllO4Gvc00cNqOhmJkYn9sJoJezcRPKB2O1iwU0teb+cVFrvDc1DQMsq3TMPjo2KZhOitX7mgMtC+Xsyx8/TsrX96b2XRdU9S7QJ6kwdmWw/pQykRkYr3JcohYZ9HZ46XZqrABUGmxioEDNnEmdBCEWIUGQ6g=
*/