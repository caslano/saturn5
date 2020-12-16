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
zuCyri1VdsBzuhtE3aG1JC4q6yrnna49EZ/T62PusFCX+cfW3FwyiecTPUoHKdQlzCV1YAqyJ35r6tOWdi/eIOMJ/pZx5lQzzpxGe9vIPvsJ2tsn1Ry5UsVE/bRZn5yexs+sT84gj88ID5QrPD5neGxK42d4nEkeZxl5N5r+8XnSnUO6xO8c/bAx950j3cvbxYXaiHkvMHW6EOnzKSv+9d8/ZAwHTu7t4l/v12zw9v7aJWn1/cTo4VJdFucYzauNczn+9f57Ml87PPo90tHvRluNPBhj6OdNn2audUuK5Z50VWQd1djRFDn3y6IzYBzg+Hi1Hh/7cW4ZlrUtLd9oCo0L7tNrT7d7zlfaS0Ol3a5lu80oxCvbnTWMNCi/pr2efGax/te5uqkiOZbcU+L00LEOo2iYvsGtI3McEV+FZ7o3Kt0M9rbXnXdHZLKfvgLh4DBvQS1O0+e73EmIfD1uMnP1zU4Oji08i651cw3HQye2zNVfjc15Yezo8KAVPLz0FujKLqj/hsbGnq4GFCR1F5Do/1bK/Vgv4/vEUPdmHM86/dsxn+N7fr0ksOIg25L7nrMdecsCShN5vxuRPzLudDufr8LMi1jL+3fLOU+MN/NE7v3p2/Rc2U97rO7HGzYr6hZOVxurQsi8fu8Q+6Z+xb5z+rkzLX2cNNDtGjylhsjhtO9c/PC7tH3vQp815WfwGQtmqde4bXi5rYUyUQbAGrs6vF5Z/t26/H7aWeJc3FvfpO7upe70WHqfme/uT8t57j3078U4q2IPMyaCOd8J8B1c+MZjlH4DsMRxchf6ZliHb6r99CNcK0zJ++RK2TdIvXy8BD9nwX5kDfIdM6d/1+x1HpN5x+GyJp7G98jzJsXzCcPzB4bnk8ITOOG5kXPz0+T5tRLh+Yzh+azh+SPhCZzw/BDl/Ilq00kSy406kjb9meKzQ3QosUIp2/Wqvr8yNrUI+Z4z+Z7X8g2N33l7QeE/lBDX5EW13rjP1P2ltH4T28u8g2+c9xRFzw1+T5tNx20W80tcrlekXIwp0bvdf1Qyr0vI+2el83dUfI3zTD/6K3V6q9LpDtPer6Wjd6t3StkY++P3kt8gPeZ+6kjiYOv0DYL3/Khf5IveA5A1GvDSv7TPzdusx7WqHv829XjX1OM9ptG3mBY5rktYd+42VuRA+Yn3RfYYKzxAE7sfMwB4ygO8iWcw1qehU6Z1eck+1h8wNEk+1oPJNyvlyDezdOG7Jvsw39xhUfmyefmkLs8Z3Q6VMpkW/33NC/0xki5V9FqP241NjLR6Nvhyg7c2OlrLx3bR9BMNfdrgIXcEX2XwNs7peOBn9LE+Xbms/ihZmipY7k2Psd6ee51/ZWcnaeaf4PKLnB9BGm0dmVP2G8t3Jz0t7URoS/nTY8gBzDPJ5RF7RB70kfj3ncmkP4j0P+Jbqv4uTTjtZrr8VPx6Pr5dUQ4u72i4c7ZBOXhbU/68Z7Cc97iYn8X6jVyuf8uCpsyahtCZInoW9OGxPhahXktVJKyv0gnrq/H59ZWcF00I4HyEtuxEkL2Wbufg0rK2JRuhmajOryai/Mlcb/O9V6e/qQJznij5ckE/3a3FgVG+aTMJI7WDTwHtbFlfhxny9PMjcPFpC/fviwM+9eT5uzF4aZB7Zwk8uH9bZvZvw8K3+McqC+3DRvUc/Ijpzx8bq+02PjYfzP68h6Q1PWzF3PMweHvvZ6aMbcCbt/KZhm4i6RtMGvkYD0D3o8Jx8uYZmew6ZIHB9xgdLAJM970p7LN6nlxiaCYm0BxpyrFri6MM3sbzrzFlxL9zok8bmgMT5FgeKUfObu7jWnWFzGOMJ+d/PUE0VtzRoNN7hRHufCY=
*/