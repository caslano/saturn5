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
1/TlmmXjBxLr95+45vI3DvE5rgSrJTT9MDXEThFR0V0lzDXG02es/RsMG/v7znT27T8RQrIxgx2ik6WrtrBfqK+PiC/hnunVJ8G+m9UgoolD0CQBc68Lqr1JE2IcvYi5tOKlnJklug1w0QktL1SHzDls2Q0dy4gNAjUO3tbN/RVS0QzPvq2RzQrZ/n8/oT/o9EVRwB0zA0Gk865y9PAYlVqixSC28dYkFhArKAs/g2ODKRplbK4Q0BaYlygNACCspnrS5IrMPuErD+irzWUgrtPaBJAmoSIFKJYqt0qQxqDCKVS4/Lkl+SVt48F/LloVk4R52VZOu8+73VC+VjJAvi1b0ZhnI2t/IejHbqD5cb2WqyQStQycmjIdzuWk2w9kiIh7SjjOtMbf6Zab3JOcBBIj0lxAMQeAhtWhn5NBu7l20DDHccY8I68+lE8/4C3B0CxmmZAsNWoMwUPLr+o9/M8stfSE4KQbbSbia8z7AH2Qx/A1rRoi0W8BVQJepb05oJlIC3cUb3kS9OwS3/T4/VU0rwQuHrUOW83ImYFJsMhF2y0iVHdwUkqr4A==
*/