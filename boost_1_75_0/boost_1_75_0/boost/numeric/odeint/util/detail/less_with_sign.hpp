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
NW/H59xuuOlrew+9Qavf7MRbUNv1b/raMvev0Lpf5jj38bl/52s7J/+ITvkFP9znOZcteB+CzK8F3rLLDO/4y0ZvTLStqWF0vc6753pdacW9HjLvCdz1HPcbJu4rNjq5iFa+4Af7+cZlSz87rigodMXWJ9oVez+Xu6QLwIr7YEN2or4cmk12KroicI4E4BFIC67webLRmCfTrrB58tsrRu232vTjp4jcCPPk9g/2/fYrlvrvh8y5K7b53hhV/3l8mt/F95gn8lWBMwmAzpDyrvL6H4ie572v2rG/bEzvuT9Q76lXrfwPMn++KvjfVc7/rho9k2zjT49TgjmA4J1t1/+QFfcJyPxT4D7PcV8xcS+yzcc+lD999oP8Kf0bK/+DzMPfCP73Ded/35g2fVvdu8uUPxF8se26z7fiXg6ZV76x0d+6b+xrdAGtch/yg/191or3EmTatXC8t3mdHS1GnQfY+mQRlWXW31OWyWmxrn/I/FrgLmvh69/EfdS2Rh+nskyvH1yja6z4N0LmQ4F/O8e/18T/hp1nU/py4p705YYVt+MarP9rNhuqds3e3820yut/mCYWX7OsyzGQmSnwspVDpMnX7CvnmgvW5VrGftqsa52OcysAr0P67Bpfl58b6/Lda2xd/vWa0SNP2ehKd75Al+MfmuPqdUv9kyHzk+u8/unXWf37XDdKOGEr4R3akPn35KOTddwzAPhP
*/