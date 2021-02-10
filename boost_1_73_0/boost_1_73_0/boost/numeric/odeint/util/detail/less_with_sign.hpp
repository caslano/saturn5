/*
 [auto_generated]
 boost/numeric/odeint/util/detail/less_with_sign.hpp

 [begin_description]
 Helper function to compare times taking into account the sign of dt
 [end_description]

 Copyright 2012-2015 Mario Mulansky
 Copyright 2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_LESS_WITH_SIGN_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_LESS_WITH_SIGN_HPP_INCLUDED

#include <limits>

#include <boost/numeric/odeint/util/unit_helper.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

/**
 * return t1 < t2 if dt > 0 and t1 > t2 if dt < 0 with epsilon accuracy
 */
template< typename T >
bool less_with_sign( T t1 , T t2 , T dt )
{
    if( get_unit_value(dt) > 0 )
        //return t1 < t2;
        return t2-t1 > std::numeric_limits<T>::epsilon();
    else
        //return t1 > t2;
        return t1-t2 > std::numeric_limits<T>::epsilon();
}

/**
 * return t1 <= t2 if dt > 0 and t1 => t2 if dt < 0 with epsilon accuracy
 */
template< typename T >
bool less_eq_with_sign( T t1 , T t2 , T dt )
{
    if( get_unit_value(dt) > 0 )
        return t1-t2 <= std::numeric_limits<T>::epsilon();
    else
        return t2-t1 <= std::numeric_limits<T>::epsilon();
}

template< typename T >
T min_abs( T t1 , T t2 )
{
    BOOST_USING_STD_MIN();
    BOOST_USING_STD_MAX();
    if( get_unit_value(t1)>0 )
        return min BOOST_PREVENT_MACRO_SUBSTITUTION ( t1 , t2 );
    else
        return max BOOST_PREVENT_MACRO_SUBSTITUTION ( t1 , t2 );
}

template< typename T >
T max_abs( T t1 , T t2 )
{
    BOOST_USING_STD_MIN();
    BOOST_USING_STD_MAX();
    if( get_unit_value(t1)>0 )
        return max BOOST_PREVENT_MACRO_SUBSTITUTION ( t1 , t2 );
    else
        return min BOOST_PREVENT_MACRO_SUBSTITUTION ( t1 , t2 );
}
} } } }

#endif

/* less_with_sign.hpp
TU7H9XAfgzpToROGHUd4Px3HdUKK31FEhqaJe2HgdwLeLR8hAd4MQRBiU7lOp9MpnweBU49hkr2/MmQLXmAR0N4bXKO14BUSpkLoC68r7H6n53A35D7qmNGXu5iLbscTuEGn2xNzQ/QcceROKLZlr+f7AjoICR4ccRf5rvSB5GoX7gvFqzsmwbodr9t1Q7E5Ox2Sp0famk7H77nSlIiNRHRAKXMmvJSe6wQOxbcuggKz5fuuH/AeydMuQNqHNBVE+9CmDGgf4pTwrEOdIpp1yFMAsw591ljWIdAKyj4UIuwGr+sFPOgKLeN2hcHyQiwa6VOhxeoQGtcRTpVwL73ARSOUPhE48LnvOT3ZY98PenjU0qfhep7wMHq90OWBsLSESKZPgnUdx+HCFXIDz+1Rops+BdUREvAdrxd4nocHkCVUYMqEZRBScHmXEE4WMYHJcoQd63BhzkiIvL0ovoJoH82XAe2j+hKedXRfRLOO8gtg1tH+Gss66l9B/edG/2Cx6aq5Wanpuh/qUtPa9walplVaeZCaVpqWRKOoNK0RVg5JVeLTVprWm4KVpstTQYs6U0Xn6oJ8kjrTZectqkzXEM1rTI3OURP7c9SkvtfyS986M1Cud1GSH4HkHYz8LUgeIOTpFUcdefk+tELP
*/