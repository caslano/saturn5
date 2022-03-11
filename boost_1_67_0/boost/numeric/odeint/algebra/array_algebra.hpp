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