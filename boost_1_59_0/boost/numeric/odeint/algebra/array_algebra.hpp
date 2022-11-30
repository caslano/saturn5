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
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
*/