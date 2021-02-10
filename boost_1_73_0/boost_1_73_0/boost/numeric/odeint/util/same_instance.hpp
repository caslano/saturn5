/*
 [auto_generated]
 boost/numeric/odeint/util/same_instance.hpp

 [begin_description]
 Basic check if two variables are the same instance
 [end_description]

 Copyright 2012 Karsten Ahnert
 Copyright 2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_SAME_INSTANCE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_SAME_INSTANCE_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {

template< class T1 , class T2 , class Enabler=void >
struct same_instance_impl
{ 
    static bool same_instance( const T1& /* x1 */ , const T2& /* x2 */ )
    {
        return false;
    }
};

template< class T >
struct same_instance_impl< T , T >
{ 
    static bool same_instance( const T &x1 , const T &x2 )
    {
        // check pointers
        return (&x1 == &x2);
    }
};


template< class T1 , class T2 >
bool same_instance( const T1 &x1 , const T2 &x2 )
{
    return same_instance_impl< T1 , T2 >::same_instance( x1 , x2 );
}


} // namespace odeint
} // namespace numeric
} // namespace boost

#endif

/* same_instance.hpp
kzl2FWez3rf4Y0X7vXnPoRf1PHhcgstvZWt9Hj9B8AFLQOACB6vemJvaTsIKCbv58j6oCwxvaQznn1ftaGpiK/RCre2mgssLC/VR+q1n28Bi3afDwag/G/6GjDVjra5bD4y3LZXBap6Q77Pp5NdLB6f1ha1VHGQOniJxPhtMzy76G4KvniLYO5+/f3BalXGSbQpmcsdz9NknWr73h+8wX9Ypb3uzIb5bSiTsma5snGSdInzfLWdYM3Fo1VP46ACpatt6XAHmAh956Fh5w2dJ3JHcclAFPoeFG5eUg/ttFhnJD/asWTLxKEjEXYDJSHuHh9YS1Xr2zQ1UePUk2aAX5QIf2jqdkR2EeKby7GSZy3DwucBHKo7lRe18ZUUsNEaOVsupw7rt2KnOePOz0zLKWMq02W1ZK8JuDWjIvW6H/GqLrc82NqSg+ay2VCVuAQg+WmlfowdqD0/77m+D6aT5osSoGvBrVIvYl2SLXx1FGWbgA2sbZI33iyXgtQSeLNS1JB9Vq8N+qpEIp8oE3q8LkeEEJ5ffC9dQykMdTYpTDKcaNUJ73f1lMPiEw/e+xbJZ6nlJ3W3+VKBvzQhvWA1L5N1OFembatbiAwIZpoq6PFnjs9zc46R91qv84zp2S6gymegb+WWNbzBVCm1r
*/