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
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
*/