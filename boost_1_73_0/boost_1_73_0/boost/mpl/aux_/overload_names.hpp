
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
b3o+dQ1WMR1sVkS2FLeVdZTRzCebFb2ypqwpXgxLDn8AcQGfmATxRwCao5aRT0HQNX0ZBRF2An6yAQkSMPx44ZvmqvCRl54ce2cd79R1d1y3uLTd3eLuIHL33M+1U73jnuM3O2136WOJSyF/uq8HB9HmIig5FxReDU2BR4mNsYRNjzI2WWLUI7Kj+V0sMCqrSTUHAqM+5HCZFksgGLPK2JO5t5hbC3V3HbEkivkN2WXcObvQS+PVL5Nh5t0yzFjIsKtIwAiBeBbBCkCnCJOMiC6SF+EjaAWPyCfTEM7vJxlO08k6eC6juDkRpiEIDoC/LLhveTXvQQDzpxPgmwtt3SmJVhLAXCCA+e0S+7g58ATLrLlQZs07ldlHLhM3ltrvLhN25a6l1pyX2n06YpANK0vtqkyz7pFp1tPLtNqPZZq1kGnXkbiZSY9abx6WSfU7M8maF+z9JLyNSKt6tn0PItlPj0iNHyOSvUAk+549+5Hr93369kIYfkz8iz9id/9HbdJ/ob3kH7Lr+eM2L79jj/0dY3qoOvJ0+tu0p8FodoD7HO2kiVAnz3X9YgA7mpBgPmIk31IEiEqvd6Q86/W6bRCdv3JkkFtKzPkQ3syGDqc03VLSpC+2O4xwNoG38qGCnAwPiGysxXaIsuSr
*/