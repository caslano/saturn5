/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/operations_fwd.hpp
 *
 * This header contains forward declaration of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPERATIONS_FWD_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPERATIONS_FWD_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< std::size_t Size, std::size_t Alignment, bool Signed >
struct emulated_operations;

template< std::size_t Size, bool Signed >
struct operations;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPERATIONS_FWD_HPP_INCLUDED_

/* operations_fwd.hpp
xFBThYDRahPY7R0OLR0iNlHGRc5uCFcQv4p8ulNpRIfQXRZe67cWE8nQYRwV9Jo69tmzL8/qV3GEF/z+rIWVDh/3nOgzAsBcGTbEtgDUDmmBE2nENUw60OgRKwmFRhUDruHk4sNlMB3M5v3pnGl62rKd85BWO4rdppC/QXSR1MLW0FKusWYDZz0VCQN/Gzyv+DV8gTYC1SwrjTsvj+n1a0KmyNtODKPR+WaDwftgNph7Xqtu1lzH0ZPyH0wjvhZA+G1QnGvAg+CqPxzVkK0XiBbQfGufkXGiyswpy0OaKrigym9zjmlNMd3IfST1Zvx+PPk4hj/Y17+3nmyYvLcu1lUYItsOWMzvlhUPyLIlhU8xv+h4lCl1C46lt3KPKK4M2LNBc7YTJqKkw8KUfvOev7Y/8pVcLRrOOHc70uitNBOqSLIBHLlAxTEfYyXWO0/J5aR8nV21NCxZQzhyFlpnv555HdaNjLLgPM+etBpZyQ6Ft8WG93FRQl3cQaVEqvjURg+ijzWZvmtblwdXk+mH/jywz5Orq2De2k1caKIbg3yNSzRzrkCf87bv1HoNdo7dVikixQauRJpby1GYQiSj9fchftw5R7pcZdRn9S/rARSUxkVJxE9wW4U5lWNp1QdpHiur2InktbPtLyuu
*/