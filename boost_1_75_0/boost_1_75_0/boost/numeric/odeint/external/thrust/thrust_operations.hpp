/*
 [auto_generated]
 boost/numeric/odeint/external/thrust/thrust_operations.hpp

 [begin_description]
 Operations of thrust zipped iterators. Is the counterpart of the thrust_algebra.
 [end_description]

 Copyright 2010-2013 Mario Mulansky
 Copyright 2010-2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_OPERATIONS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_OPERATIONS_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {

#include <thrust/tuple.h>
#include <thrust/iterator/zip_iterator.h>

/**ToDo extend to scale_sum13 for rk78 */

struct thrust_operations
{
    template< class Fac1 = double , class Fac2 = Fac1 >
    struct scale_sum2
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;

        scale_sum2( const Fac1 alpha1 , const Fac2 alpha2 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) + m_alpha2 * thrust::get<2>(t);
        }
    };

    template< class Fac1 = double , class Fac2 = Fac1 >
    struct scale_sum_swap2
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;

        scale_sum_swap2( const Fac1 alpha1 , const Fac2 alpha2 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            typename thrust::tuple_element<0,Tuple>::type tmp = thrust::get<0>(t);
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) + m_alpha2 * thrust::get<2>(t);
            thrust::get<1>(t) = tmp;
        }
    };

    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 >
    struct scale_sum3
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;

        scale_sum3( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) { }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) +
                    m_alpha2 * thrust::get<2>(t) +
                    m_alpha3 * thrust::get<3>(t);
        }
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 >
    struct scale_sum4
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;

        scale_sum4( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 , const Fac4 alpha4 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ){ }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) +
                    m_alpha2 * thrust::get<2>(t) +
                    m_alpha3 * thrust::get<3>(t) +
                    m_alpha4 * thrust::get<4>(t);
        }
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 ,
            class Fac4 = Fac3 , class Fac5 = Fac4 >
    struct scale_sum5
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;

        scale_sum5( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 ,
                const Fac4 alpha4 , const Fac5 alpha5 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) ,
          m_alpha4( alpha4 ) , m_alpha5( alpha5 ) { }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) +
                    m_alpha2 * thrust::get<2>(t) +
                    m_alpha3 * thrust::get<3>(t) +
                    m_alpha4 * thrust::get<4>(t) +
                    m_alpha5 * thrust::get<5>(t);
        }
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 ,
            class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 >
    struct scale_sum6
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;
        const Fac6 m_alpha6;

        scale_sum6( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 ,
                const Fac4 alpha4 , const Fac5 alpha5 , const Fac6 alpha6 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) ,
          m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) { }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) +
                    m_alpha2 * thrust::get<2>(t) +
                    m_alpha3 * thrust::get<3>(t) +
                    m_alpha4 * thrust::get<4>(t) +
                    m_alpha5 * thrust::get<5>(t) +
                    m_alpha6 * thrust::get<6>(t);
        }
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 ,
            class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 >
    struct scale_sum7
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;
        const Fac6 m_alpha6;
        const Fac7 m_alpha7;

        scale_sum7( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 ,
                const Fac4 alpha4 , const Fac5 alpha5 , const Fac6 alpha6 , const Fac7 alpha7 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) ,
          m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) { }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) +
                    m_alpha2 * thrust::get<2>(t) +
                    m_alpha3 * thrust::get<3>(t) +
                    m_alpha4 * thrust::get<4>(t) +
                    m_alpha5 * thrust::get<5>(t) +
                    m_alpha6 * thrust::get<6>(t) +
                    m_alpha7 * thrust::get<7>(t) ;
        }
    };




    template< class Fac1 = double >
    struct rel_error
    {
        const Fac1 m_eps_abs , m_eps_rel , m_a_x , m_a_dxdt;

        rel_error( const Fac1 eps_abs , const Fac1 eps_rel , const Fac1 a_x , const Fac1 a_dxdt )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt ) { }


        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            using std::abs;
            thrust::get< 0 >( t ) = abs( thrust::get< 0 >( t ) ) /
                    ( m_eps_abs + m_eps_rel * ( m_a_x * abs( thrust::get< 1 >( t ) + m_a_dxdt * abs( thrust::get< 2 >( t ) ) ) ) );
        }

        typedef void result_type;
    };


};

} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_OPERATIONS_HPP_INCLUDED

/* thrust_operations.hpp
eSGoommVghgi20+mhmx4Wmm4HtCXovc/oEtPp8/ri+h7ztU2FhuxSTSxcaWgiY3Zl2oDxEayXG+x2IjZhBAb545uVvQl4hl4Xpf03vqrCbzXB+K9Vsd7/cVAvDf8I7zXhsa7/LZm8Y5HXH+7v15TA1wxpC543VNpJ671N8ufIB1OKC3WK7kh9QOEx5331zengghVxC0tLKJ0bF3jIiwtKuLYvS3VxQWp+FJDZLs8VLacGw9Or9N0azlpdQGr2xwa9Bmp8oEKdd2iR2arkR9VBCxqaKnjLo/ynTnShNZHbFF77LknJOJEaW2z8F4NtchY3+Ij2tLcOw1lo5RdS1MvC0KZ6elyqZxTmlaBElT3iuenJuNGbGUZ3cRrsuCTAFGadyg+SGGRJ/TVasjbbPoXuj7y1/F1GpcffEedtpQ6e1rXk8nMTWm+QTdTElBLVR0O9Ft8h18J9Iu+qlf0sqZ0r9MG18ZX9Dxff0XXvY3rcqFxy8e3SH17e07LiP0TLIK7l3a9oDSjvcgPUdzJu1s6YwQRfihVq9R8tmotaJ08Y72uoZG6NtFoLZuguoUujmhmQ9cmOERyixSQWya3bESs7npBI7mBXes07cAVBxvqn1DLhUWJNPPfvy9o5g+qfijcuofGDcN8hpeptVFZ4PvrJV1zsbqLPnwKmZtUPwde0tU9O15qgpkktlTJPX9SSAxJtRfZpYkOSmyRHi4u
*/