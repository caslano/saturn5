/*
 [auto_generated]
 boost/numeric/odeint/algebra/array_algebra.hpp

 [begin_description]
 Algebra for Arrays. Highly specialized for odeint. Const arguments are
 introduce to work with odeint.
 The Array algebra can be used for Array structures with two template
 parameters: 
 Array<T, N>
 [end_description]

 Copyright 2011-2013 Mario Mulansky
 Copyright 2011-2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_ARRAY_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_ARRAY_ALGEBRA_HPP_INCLUDED

#include <algorithm>
#include <boost/array.hpp>

#include <boost/numeric/odeint/algebra/norm_result_type.hpp>

namespace boost {
namespace numeric {
namespace odeint {

struct array_algebra
{
    //template< typename T , size_t dim , class Op >
    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each1( Array< T, dim > &s1, Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] );
    }

    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each2( Array< T, dim > &s1, const Array< T, dim > &s2,
                           Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] );
    }

    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each3( Array< T , dim > &s1 ,
            const Array< T , dim > &s2 ,
            const Array< T , dim > &s3 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] );
    }

    /* different const signature - required for the scale_sum_swap2 operation */
    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each3( Array< T , dim > &s1 ,
            Array< T , dim > &s2 ,
            const Array< T , dim > &s3 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] );
    }

    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each4( Array< T , dim > &s1 ,
            const Array< T , dim > &s2 ,
            const Array< T , dim > &s3 ,
            const Array< T , dim > &s4 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] );
    }

    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each5( Array< T , dim > &s1 ,
            const Array< T , dim > &s2 ,
            const Array< T , dim > &s3 ,
            const Array< T , dim > &s4 ,
            const Array< T , dim > &s5 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] );
    }

    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each6( Array< T , dim > &s1 ,
            const Array< T , dim > &s2 ,
            const Array< T , dim > &s3 ,
            const Array< T , dim > &s4 ,
            const Array< T , dim > &s5 ,
            const Array< T , dim > &s6 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] );
    }

    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each7( Array< T , dim > &s1 ,
            const Array< T , dim > &s2 ,
            const Array< T , dim > &s3 ,
            const Array< T , dim > &s4 ,
            const Array< T , dim > &s5 ,
            const Array< T , dim > &s6 ,
            const Array< T , dim > &s7 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] );
    }

    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each8( Array< T , dim > &s1 ,
            const Array< T , dim > &s2 ,
            const Array< T , dim > &s3 ,
            const Array< T , dim > &s4 ,
            const Array< T , dim > &s5 ,
            const Array< T , dim > &s6 ,
            const Array< T , dim > &s7 ,
            const Array< T , dim > &s8 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] );
    }

    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each9( Array< T , dim > &s1 ,
            const Array< T , dim > &s2 ,
            const Array< T , dim > &s3 ,
            const Array< T , dim > &s4 ,
            const Array< T , dim > &s5 ,
            const Array< T , dim > &s6 ,
            const Array< T , dim > &s7 ,
            const Array< T , dim > &s8 ,
            const Array< T , dim > &s9 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] , s9[i] );
    }

    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each10( Array< T , dim > &s1 ,
            const Array< T , dim > &s2 ,
            const Array< T , dim > &s3 ,
            const Array< T , dim > &s4 ,
            const Array< T , dim > &s5 ,
            const Array< T , dim > &s6 ,
            const Array< T , dim > &s7 ,
            const Array< T , dim > &s8 ,
            const Array< T , dim > &s9 ,
            const Array< T , dim > &s10 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] , s9[i] , s10[i] );
    }

    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each11( Array< T , dim > &s1 ,
            const Array< T , dim > &s2 ,
            const Array< T , dim > &s3 ,
            const Array< T , dim > &s4 ,
            const Array< T , dim > &s5 ,
            const Array< T , dim > &s6 ,
            const Array< T , dim > &s7 ,
            const Array< T , dim > &s8 ,
            const Array< T , dim > &s9 ,
            const Array< T , dim > &s10 ,
            const Array< T , dim > &s11 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] , s9[i] , s10[i] , s11[i] );
    }

    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each12( Array< T , dim > &s1 ,
            const Array< T , dim > &s2 ,
            const Array< T , dim > &s3 ,
            const Array< T , dim > &s4 ,
            const Array< T , dim > &s5 ,
            const Array< T , dim > &s6 ,
            const Array< T , dim > &s7 ,
            const Array< T , dim > &s8 ,
            const Array< T , dim > &s9 ,
            const Array< T , dim > &s10 ,
            const Array< T , dim > &s11 ,
            const Array< T , dim > &s12 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] , s9[i] , s10[i] , s11[i] , s12[i] );
    }

    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each13( Array< T , dim > &s1 ,
            const Array< T , dim > &s2 ,
            const Array< T , dim > &s3 ,
            const Array< T , dim > &s4 ,
            const Array< T , dim > &s5 ,
            const Array< T , dim > &s6 ,
            const Array< T , dim > &s7 ,
            const Array< T , dim > &s8 ,
            const Array< T , dim > &s9 ,
            const Array< T , dim > &s10 ,
            const Array< T , dim > &s11 ,
            const Array< T , dim > &s12 ,
            const Array< T , dim > &s13 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] , s9[i] , s10[i] , s11[i] , s12[i] , s13[i] );
    }

    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each14( Array< T , dim > &s1 ,
            const Array< T , dim > &s2 ,
            const Array< T , dim > &s3 ,
            const Array< T , dim > &s4 ,
            const Array< T , dim > &s5 ,
            const Array< T , dim > &s6 ,
            const Array< T , dim > &s7 ,
            const Array< T , dim > &s8 ,
            const Array< T , dim > &s9 ,
            const Array< T , dim > &s10 ,
            const Array< T , dim > &s11 ,
            const Array< T , dim > &s12 ,
            const Array< T , dim > &s13 ,
            const Array< T , dim > &s14 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] , s9[i] , s10[i] , s11[i] , s12[i] , s13[i] , s14[i] );
    }

    template < template < typename, size_t > class Array, typename T,
               size_t dim, class Op >
    static void for_each15( Array< T , dim > &s1 ,
            const Array< T , dim > &s2 ,
            const Array< T , dim > &s3 ,
            const Array< T , dim > &s4 ,
            const Array< T , dim > &s5 ,
            const Array< T , dim > &s6 ,
            const Array< T , dim > &s7 ,
            const Array< T , dim > &s8 ,
            const Array< T , dim > &s9 ,
            const Array< T , dim > &s10 ,
            const Array< T , dim > &s11 ,
            const Array< T , dim > &s12 ,
            const Array< T , dim > &s13 ,
            const Array< T , dim > &s14 ,
            const Array< T , dim > &s15 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] , s9[i] , s10[i] , s11[i] , s12[i] , s13[i] , s14[i] , s15[i] );
    }


    template < template < typename, size_t > class Array, typename T,
               size_t dim>
    static typename norm_result_type< Array< T , dim > >::type norm_inf( const Array< T , dim > &s )
    {
        BOOST_USING_STD_MAX();
        using std::abs;
        typedef typename norm_result_type< Array< T , dim > >::type result_type;
        result_type init = static_cast< result_type >( 0 );
        for( size_t i=0 ; i<dim ; ++i )
            init = max BOOST_PREVENT_MACRO_SUBSTITUTION ( init , static_cast< result_type >(abs(s[i])) );
        return init;
    }

};

}
}
}

#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_ARRAY_ALGEBRA_HPP_INCLUDED

/* array_algebra.hpp
2YdpypaFCGxAC1Htt+qF16Xn9sOMkB5RmlxfKe5DlQUHp2pmCMA+vuJxZi8SMULV8tiYplgrmdNC5MBImbYQ5ybqN+XXCJjjuIVsdxjzjsBExIaecmS4IKm+qCLRLohboWH1awkVl1bbAkVx1XEeU1HR5JW82ndUBcmnqqmp9IzaN0+g5ZTS3R5ARYIkWH82bamFD1N6ECj996EaSjuNm0O2zugAQpX4mKFDHAGWpL5e1WFHPIPZ0hEPbb6KdloWD7sgtNhZRo/BDrJCMahrAQ+DNdh3UkUbDD0a8wz/156sCrsJ0lhClfD3V+sqQtEFinUl4rhtxWlam3zUvHp0aFeDesYNIWMnj+sSm0Pj6XhBL19hQJ5OR+fy9eNwvJiN5peT30eVjbdoRO2j4GFOR4g3nW6/368Rv/nkhnXfHc8EsvlfCQcpk0Qp1JGgoyKL58vPBiEMmGYY2RgoBpChk9tDQPfI8X/h1C1GHLnmWGXElSUKk14neBzmk3tF3IWQdGw+2K1q+X+wSPqMSnu3M1R6rwxF33KkeijWxndZR8jEYKZk4Wg2iy4+TBbj8GRtESvxK0F9MeU2ZOV/s+pOlH7lltjMrchTRsfaK34LcDUo1UN4Fm+3yHCKV766za0w/Vf1iy+JLt47amtu
*/