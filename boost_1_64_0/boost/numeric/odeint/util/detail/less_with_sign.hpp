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
8d3zGxXx46HK/tw+TJivfPYMoy4LxioN8V7WmNyHnS4GVt/bsqF4LRl/0PS3ezjcvVBFxFfp184UNXT6c7Kiq8cvmL88yTC6O+b8BXSy+EftRJ1wuZJMh/dHzGG/wBesC81vJbYkBy+KGs95ZSGwxNqvD49Yvby6sjVHGlQuHC6BhfB4QtxHrE1sT+fMsI7ZlmA0hWfNIepZ4/SAm398EHT2M4RZDmiiotd9YD2PuTp0TX7qcxqYMiJyRbExgp7YtzTh5qvq5IE1HAXEbF3aFO3tzOSmVJ2UJvF9mxb1H5KIVnuAR2Cc9rZ73Kn/OieiurAVtSVTVr3TDwPCI+FKKu2ABS+Pb0fmfyZzCY2vlOVt8jJ8RYDG9Uhrj46lNpTeK2fNI28qBPCUmJzZNsdaPdSwsCSzXq1Gpv7lYyx+R0Y7KiPZDYrPVbFtWbk845ejt/XCoG2L+UyakMgBxTb4bSqU3325SMiH+8j2yHGW+mbnI1KDRNVuKYaMr09D9DF4qI9yjdBSeu7u12C5bp5lzQsvDKqPMSMibDy5ojFnxZnao06qQdwtTuVWAg==
*/