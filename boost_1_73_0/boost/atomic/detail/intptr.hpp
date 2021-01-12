/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/intptr.hpp
 *
 * This header defines (u)intptr_t types.
 */

#ifndef BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_

#include <boost/cstdint.hpp>
#if defined(BOOST_HAS_INTPTR_T)
#include <cstddef>
#endif
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_HAS_INTPTR_T)
using boost::uintptr_t;
using boost::intptr_t;
#else
typedef std::size_t uintptr_t;
typedef std::ptrdiff_t intptr_t;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_

/* intptr.hpp
opGkyqyWo7RWKconbtnkqv4Y+VvXKHv6HfjiFsGprDziQYOFpi31nU7BMRIcATO/y6kUxygcwCtZYKAB9Dbd8/B6Ff4CcsruINPr8XcSKb3vMPR1W5Kg7q0+MqrvOwS3IaUk87L7y4wx3d+9tci4rntM13dvLTZWSb687q348gi56d5a2r01NDTbrbjy6a2OFQ0G3bek6eHfhWMvi2mkC+bKC3ebK0+oXDRXqG+j8d1PpUnv
*/