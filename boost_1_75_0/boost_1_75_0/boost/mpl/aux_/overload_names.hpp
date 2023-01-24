
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
kB6cDlADYqZS5FKVnoXQTsz0El/gPH3IKpCxofMwUeBtNDdgexGJ6cF9Jg1WClAQzYMX5vTQgt/GNDPEumyGOf0BJWBeVaodXuLetbWvYyfJ+FJ1UF9rb8/BVWbvVqJDxfOTrO8Ry6VZhw2dmD7ZULxMupyjgj11JHlRUnckrC6PdJIkfUyZYOR5MYakdpihXYGVC6H9T7To3p2ffN8NUDO61vGSVNNGWe0Rx3zr7fIxuEDF2Qdf7WcyTeQiHd/7qVZdA99PLlEjhLsiy2t+u2Bo3nAnKtH3GFF/0KWRSFOhFe60aUfJ1I5Et5DUGN8m4xQukSu1H4rP6EfcEZ/GajE+xXcwQyXYJsfBXUU++c7N2R+fXvQlgNMV9Zp1mhrrZ6gZ3cApYZaZAOq+q+J0zsiYbOUXduMCawKW325M11gr3w8NzRKhCYa7zabII0I5OGbjs9RKQ42nw/iwfIOyP+edablEBMgnond8EHw0rTStOEurRhp2iSa8iV5jk/c6tbO97x+359dIwHw+Zds3i3Y2h01s/rEXgkSNwXP+p4Pf1odFZI6x7pDnFY2pPHJg5mperRVhraMOhMcivJ/nhB0/zRmyEpS3T778VrlvyfkQ+VryvRU7QLxUcDv1eythgGJp2+wPQi0uvzNjI5yi25j01PpnLJFjZTK6b+uw6w5H8O7uB6s75KOW3XQcX77tX1f4uWUbxeOd3fKe
*/