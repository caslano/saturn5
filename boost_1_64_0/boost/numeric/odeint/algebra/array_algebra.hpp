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
M3bJZ85f/MWZg9cPn8jYj6D/dsRPA15/MmMPwfhsPCX9D+e/1Z7J2E36MbR9lT+89PmiTsZOofrMHb6/PZ9RDFT+paP/t/+WsT9SfdwXM/beQPs5+L888i9n7NaUm3dfRXn5Hxn7Lbx/8nrGnqX8xG7GbkkvOV9iuPH/tubn/33fYfzf+jsZXRf8K3HrgfN1/p2xvSn/XxztPw/viPeT/SS+PcWHP8jYWNp/Ko72m/jxIF/7MMPxUfHHeqTTXf6RvIs1yH4Sx/wN8YjsF/GNaP0gxTwW34vmJ/GDYP9XsyfL9ZnF16T6TuJ30fpEb9a2JP3Sl12cf+N6fvHvUvwrk7XlYH+B5bJa318yvoeZ38vLZO0SyYdD5L9/9JD5+XPZxfabK/9bfDLlBy2bxf4bi+9I40+c4o/lEVnOXxT/MrRfIr4D8Mrns7Yd8Lr4ztT/xOn+4XJZmwr9s7t81i6E92utkLUDaH/3ilnbE+KPDfHjKX49Mmsb0v5o8avAvq6ulLW7iX8hy/l94hsCb4r/BvZf1Uepf1J+5MpZu83c5+vZKhr/cP2K+A9AviuO6yurZm0fqp8nPpL8I/FHYP5phlnMT6+tlrVfGtTfWj1rMYz/RHxXqt+wRtZOoviw+KbpJedbDGMfNtfK4vqCrZ21TWj+Ed+K8mPEt4T9n13xCL5/bXTWLgP7r7KO3o/6p/gE2v8nvnxqSV8dZvxWv6T+D/ZxqM3VW8P9Y3F6/7b4TiAfanP2NIp/id/yv/4xTHy0ub70M80/G/D81BLfjepDVbLWSLvPZ482ztoN8PzVTbI2i+xf8c0+Yz9dHw3Jn9gia9fQ/s8ts7Yf6O94a40/OH+tOkb2GfgHle2zdlHm0+dnbDhuSPxml6ydn9V1XPU19s7axino//tm7Y8pd/2B5v5ZexnO1yofmLWxer7RjvhLt5a1P0B9gnBy1k7vhfjAVJ5/Ox7e9XCbxrzs4aF4Ue832eEfxbNlX6t9Zg/hE88aXF+0U7P2vX79NYRfMYRX52XtYzX+JUN4dwivXyj7Ja37uPyzS3R9PJ8iu9S/KQwzP9XFjzT3/GU/yWJ+UFP8vkXxD0f/rF2e5f3f4jN7Je+aH6/W/Av7j9u/yNoFsL+y/ausnQH6N74ma6PSS+Ijw9nXLY1f8VGu+N11WbsTzr9KfitO+lXBvxnpJeuvw+jXzg2yvwfez2Hf3pTV/lSwb27OWt+i+J2D12/N2hYU3xT/yGB/dDtrR5B932b7o9vm/hHeLv8rredw7I+r3sXysTj5jw2PfNsj3xH/J6z/RPdkLRn4vo742f1ZW5bspz9mbRzwmngFeFP8AKzPKP+D6heLvwDPHyaL7AfQHw9n7SzQz23xb//Pvxomf7L9qOwr6N/h4wP6yxlfajyZtUPofLans/Z8WnOyIz7aXZi18RDfb/xF9ifkj9Wf0/MH2v/u4J1XsnYY5F83X8vaOmB/hF3Nz5/x39Y6Y3D9oi3+U8pvfSNrX0+5ef2trH2yZP5bczj75j3ND/B96+8v9i97HfL1f2t8gHzjA81/pP/Fj6X41oeyjyk//j9Zmw68+7H0L4yf6JOsfQniBw3x66k+g+6K/q+SD3ag+lPiLyrAd+IQ/pevD4mPl3N28MpmT7nyMzb1XF/8ebr+2JztSfVpxdcH/Wg7Ma96eN3D2+Lk35XH5WwNys/x8Fj8AOAd8XWhfcKdc1jfK949h/W9ylEO63d1Ds3Zgn79/1KO9d0pObsXeOekHNbvik/L2Z9GLsmvG4a3L5W8nv98x/pKclnOopIN+Ni54eTn5zB+n4ivR/ll14uDfCS+DcWvxCn/oi1+HNg/0e90f7I/xEeR/SE=
*/