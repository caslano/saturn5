
#ifndef BOOST_MPL_AUX_OVERLOAD_NAMES_HPP_INCLUDED
#define BOOST_MPL_AUX_OVERLOAD_NAMES_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/ptr_to_ref.hpp>
#include <boost/mpl/aux_/config/operators.hpp>

#if defined(BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING)

#   include <boost/mpl/aux_/static_cast.hpp>

#   define BOOST_MPL_AUX_OVERLOAD_VALUE_BY_KEY  operator/
#   define BOOST_MPL_AUX_OVERLOAD_ITEM_BY_ORDER operator|
#   define BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY  operator||
#   define BOOST_MPL_AUX_OVERLOAD_IS_MASKED     operator%

#   define BOOST_MPL_AUX_OVERLOAD_CALL_VALUE_BY_KEY(T, x)   BOOST_MPL_AUX_PTR_TO_REF(T) / x
#   define BOOST_MPL_AUX_OVERLOAD_CALL_ITEM_BY_ORDER(T, x)  BOOST_MPL_AUX_PTR_TO_REF(T) | x
#   define BOOST_MPL_AUX_OVERLOAD_CALL_ORDER_BY_KEY(T, x)   BOOST_MPL_AUX_PTR_TO_REF(T) || x
#   define BOOST_MPL_AUX_OVERLOAD_CALL_IS_MASKED(T, x)      BOOST_MPL_AUX_PTR_TO_REF(T) % x

#else

#   define BOOST_MPL_AUX_OVERLOAD_VALUE_BY_KEY  value_by_key_
#   define BOOST_MPL_AUX_OVERLOAD_ITEM_BY_ORDER item_by_order_
#   define BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY  order_by_key_
#   define BOOST_MPL_AUX_OVERLOAD_IS_MASKED     is_masked_

#   define BOOST_MPL_AUX_OVERLOAD_CALL_VALUE_BY_KEY(T, x)   T::BOOST_MPL_AUX_OVERLOAD_VALUE_BY_KEY( BOOST_MPL_AUX_PTR_TO_REF(T), x )
#   define BOOST_MPL_AUX_OVERLOAD_CALL_ITEM_BY_ORDER(T, x)  T::BOOST_MPL_AUX_OVERLOAD_ITEM_BY_ORDER( BOOST_MPL_AUX_PTR_TO_REF(T), x )
#   define BOOST_MPL_AUX_OVERLOAD_CALL_ORDER_BY_KEY(T, x)   T::BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY( BOOST_MPL_AUX_PTR_TO_REF(T), x )
#   define BOOST_MPL_AUX_OVERLOAD_CALL_IS_MASKED(T, x)      T::BOOST_MPL_AUX_OVERLOAD_IS_MASKED( BOOST_MPL_AUX_PTR_TO_REF(T), x )

#endif

#endif // BOOST_MPL_AUX_OVERLOAD_NAMES_HPP_INCLUDED

/* overload_names.hpp
44z+BKF1hSYrYgvW9jVLrbrTPdiRbDUEAq+/5uORuSsSrve3SRPZ0v8f9bugFo6gKGL9Y1sk3VZ/PwJ2nPFWCT/XpbvC8zal+gSdC/ELCDHOpX1w86X0dup/R+Q/ypiWSh7HBqo6MjksgVRFS4CoeEeUyoM5F0RIMXGRuq0lEJH5r8E1+IFkHk0kxFi0UI98c2dXmIT1cdi82ZDWRGPPgTN7RgA9T9UJNMkVM3mh1+OUCaVS8FxQ/rOk/leLftaxve9fyqBl9Fgd1V9GrnYvDTqEOEBZMA9EszCXyqVzAkWtOyLwGu6M2t542kXXkCZ3l0hrrsegx8mfqgUk+TWcSChXhDdy8ygkCz2t0hGxLo2zGJbh3VJFA+KwXaUQOgjtyba0XUuw73LIm6Ez4AlyjNLQDsubB6VO0aOxVNuM9p4WDE/R1n+lXOxdPwg56yZzj2Em1gK9q8ZjQ1ASnBzzeB0SsvvEKdHnYEJ4+oVRlpYwTiu/9SPafrKx1vtvu/ahoRVz4X3xrIUYHGMWLSTGxf8LBSb+MBuV5tV/mXpJM91FKSe/FvZDAbBXIQ==
*/