/*
 [auto_generated]
 boost/numeric/odeint/algebra/default_operations.hpp

 [begin_description]
 Default operations. They work with the default numerical types, like float, double, complex< double> ...
 [end_description]

 Copyright 2010-2012 Karsten Ahnert
 Copyright 2010-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_DEFAULT_OPERATIONS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_DEFAULT_OPERATIONS_HPP_INCLUDED

#include <algorithm>

#include <boost/config.hpp>
#include <boost/array.hpp>

#include <boost/numeric/odeint/util/unit_helper.hpp>


namespace boost {
namespace numeric {
namespace odeint {



/*
 * Notes:
 *
 * * the results structs are needed in order to work with fusion_algebra
 */
struct default_operations
{

    template< class Fac1 = double >
    struct scale
    {
        const Fac1 m_alpha1;

        scale( Fac1 alpha1 ) : m_alpha1( alpha1 ) { }

        template< class T1 >
        void operator()( T1 &t1 ) const
        {
            t1 *= m_alpha1;
        }

        typedef void result_type;
    };

    template< class Fac1 = double >
    struct scale_sum1
    {
        const Fac1 m_alpha1;

        scale_sum1( Fac1 alpha1 ) : m_alpha1( alpha1 ) { }

        template< class T1 , class T2 >
        void operator()( T1 &t1 , const T2 &t2 ) const
        {
            t1 = m_alpha1 * t2;
        }

        typedef void result_type;
    };


    template< class Fac1 = double , class Fac2 = Fac1 >
    struct scale_sum2
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;

        scale_sum2( Fac1 alpha1 , Fac2 alpha2 ) : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }

        template< class T1 , class T2 , class T3 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3;
        }

        typedef void result_type;
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 >
    struct scale_sum3
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;

        scale_sum3( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) { }

        template< class T1 , class T2 , class T3 , class T4 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4;
        }

        typedef void result_type;
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 >
    struct scale_sum4
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;

        scale_sum4( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5;
        }

        typedef void result_type;
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 >
    struct scale_sum5
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;

        scale_sum5( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 , Fac5 alpha5 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6;
        }

        typedef void result_type;
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 >
    struct scale_sum6
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;
        const Fac6 m_alpha6;

        scale_sum6( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 , Fac5 alpha5 , Fac6 alpha6 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ){ }

        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 ,const T7 &t7) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7;
        }

        typedef void result_type;
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 >
    struct scale_sum7
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;
        const Fac6 m_alpha6;
        const Fac7 m_alpha7;

        scale_sum7( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8;
        }

        typedef void result_type;
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 , class Fac8 = Fac7 >
    struct scale_sum8
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;
        const Fac6 m_alpha6;
        const Fac7 m_alpha7;
        const Fac8 m_alpha8;

        scale_sum8( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9;
        }

        typedef void result_type;
    };

    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 , class Fac8 = Fac7 , class Fac9 = Fac8 >
    struct scale_sum9
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;
        const Fac6 m_alpha6;
        const Fac7 m_alpha7;
        const Fac8 m_alpha8;
        const Fac9 m_alpha9;

        scale_sum9( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10;
        }

        typedef void result_type;
    };

    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 , class Fac8 = Fac7 , class Fac9 = Fac8 , class Fac10 = Fac9 >
    struct scale_sum10
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;
        const Fac6 m_alpha6;
        const Fac7 m_alpha7;
        const Fac8 m_alpha8;
        const Fac9 m_alpha9;
        const Fac10 m_alpha10;

        scale_sum10( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 , Fac10 alpha10 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11;
        }

        typedef void result_type;
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 , class Fac8 = Fac7 , class Fac9 = Fac8 , class Fac10 = Fac9 , class Fac11 = Fac10 >
    struct scale_sum11
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;
        const Fac6 m_alpha6;
        const Fac7 m_alpha7;
        const Fac8 m_alpha8;
        const Fac9 m_alpha9;
        const Fac10 m_alpha10;
        const Fac11 m_alpha11;

        scale_sum11( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 ,
                Fac10 alpha10 , Fac11 alpha11 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) , m_alpha11( alpha11 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 , const T12 &t12 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11 + m_alpha11 * t12;
        }

        typedef void result_type;
    };

    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 , class Fac8 = Fac7 , class Fac9 = Fac8 , class Fac10 = Fac9 , class Fac11 = Fac10 , class Fac12 = Fac11 >
    struct scale_sum12
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;
        const Fac6 m_alpha6;
        const Fac7 m_alpha7;
        const Fac8 m_alpha8;
        const Fac9 m_alpha9;
        const Fac10 m_alpha10;
        const Fac11 m_alpha11;
        const Fac12 m_alpha12;

        scale_sum12( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 ,
                Fac10 alpha10 , Fac11 alpha11 , Fac12 alpha12 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) , m_alpha11( alpha11 ) , m_alpha12( alpha12 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 , const T12 &t12 , const T13 &t13 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11 + m_alpha11 * t12 + m_alpha12 * t13;
        }

        typedef void result_type;
    };

    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 , class Fac8 = Fac7 , class Fac9 = Fac8 , class Fac10 = Fac9 , class Fac11 = Fac10 , class Fac12 = Fac11 , class Fac13 = Fac12 >
    struct scale_sum13
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;
        const Fac6 m_alpha6;
        const Fac7 m_alpha7;
        const Fac8 m_alpha8;
        const Fac9 m_alpha9;
        const Fac10 m_alpha10;
        const Fac11 m_alpha11;
        const Fac12 m_alpha12;
        const Fac13 m_alpha13;

        scale_sum13( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 ,
                Fac10 alpha10 , Fac11 alpha11 , Fac12 alpha12 , Fac13 alpha13 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) , m_alpha11( alpha11 ) , m_alpha12( alpha12 ) , m_alpha13( alpha13 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 , const T12 &t12 , const T13 &t13 , const T14 &t14 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11 + m_alpha11 * t12 + m_alpha12 * t13 + m_alpha13 * t14;
        }

        typedef void result_type;
    };

    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 , class Fac8 = Fac7 , class Fac9 = Fac8 , class Fac10 = Fac9 , class Fac11 = Fac10 , class Fac12 = Fac11 , class Fac13 = Fac12 , class Fac14 = Fac13 >
    struct scale_sum14
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;
        const Fac6 m_alpha6;
        const Fac7 m_alpha7;
        const Fac8 m_alpha8;
        const Fac9 m_alpha9;
        const Fac10 m_alpha10;
        const Fac11 m_alpha11;
        const Fac12 m_alpha12;
        const Fac13 m_alpha13;
        const Fac14 m_alpha14;

        scale_sum14( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 ,
                Fac10 alpha10 , Fac11 alpha11 , Fac12 alpha12 , Fac13 alpha13 , Fac14 alpha14 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) , m_alpha11( alpha11 ) , m_alpha12( alpha12 ) , m_alpha13( alpha13 ) , m_alpha14( alpha14 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 , const T12 &t12 , const T13 &t13 , const T14 &t14 , const T15 &t15 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11 + m_alpha11 * t12 + m_alpha12 * t13 + m_alpha13 * t14 + m_alpha14 * t15;
        }

        typedef void result_type;
    };

    template< class Fac1 = double , class Fac2 = Fac1 >
    struct scale_sum_swap2
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;

        scale_sum_swap2( Fac1 alpha1 , Fac2 alpha2 ) : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }

        template< class T1 , class T2 , class T3 >
        void operator()( T1 &t1 , T2 &t2 , const T3 &t3) const
        {
            const T1 tmp( t1 );
            t1 = m_alpha1 * t2 + m_alpha2 * t3;
            t2 = tmp;
        }

        typedef void result_type;
    };

    /*
     * for usage in for_each2
     *
     * Works with boost::units by eliminating the unit
     */
    template< class Fac1 = double >
    struct rel_error
    {
        const Fac1 m_eps_abs , m_eps_rel , m_a_x , m_a_dxdt;

        rel_error( Fac1 eps_abs , Fac1 eps_rel , Fac1 a_x , Fac1 a_dxdt )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt ) { }


        template< class T1 , class T2 , class T3 >
        void operator()( T3 &t3 , const T1 &t1 , const T2 &t2 ) const
        {
            using std::abs;
            set_unit_value( t3 , abs( get_unit_value( t3 ) ) / ( m_eps_abs + m_eps_rel * ( m_a_x * abs( get_unit_value( t1 ) ) + m_a_dxdt * abs( get_unit_value( t2 ) ) ) ) );
        }

        typedef void result_type;
    };


    /*
     * for usage in for_each3
     *
     * used in the controller for the rosenbrock4 method
     *
     * Works with boost::units by eliminating the unit
     */
    template< class Fac1 = double >
    struct default_rel_error
    {
        const Fac1 m_eps_abs , m_eps_rel ;

        default_rel_error( Fac1 eps_abs , Fac1 eps_rel )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) { }


        /*
         * xerr = xerr / ( eps_abs + eps_rel * max( x , x_old ) )
         */
        template< class T1 , class T2 , class T3 >
        void operator()( T3 &t3 , const T1 &t1 , const T2 &t2 ) const
        {
            BOOST_USING_STD_MAX();
            using std::abs;
            Fac1 x1 = abs( get_unit_value( t1 ) ) , x2 = abs( get_unit_value( t2 ) );
            set_unit_value( t3 , abs( get_unit_value( t3 ) ) / ( m_eps_abs + m_eps_rel * max BOOST_PREVENT_MACRO_SUBSTITUTION ( x1 , x2 ) ) );
        }

        typedef void result_type;
    };



    /*
     * for usage in reduce
     */

    template< class Value >
    struct maximum
    {
        template< class Fac1 , class Fac2 >
        Value operator()( Fac1 t1 , const Fac2 t2 ) const
        {
            using std::abs;
            Value a1 = abs( get_unit_value( t1 ) ) , a2 = abs( get_unit_value( t2 ) );
            return ( a1 < a2 ) ? a2 : a1 ;
        }

        typedef Value result_type;
    };


    template< class Fac1 = double >
    struct rel_error_max
    {
        const Fac1 m_eps_abs , m_eps_rel;

        rel_error_max( Fac1 eps_abs , Fac1 eps_rel )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel )
        { }

        template< class Res , class T1 , class T2 , class T3 >
        Res operator()( Res r , const T1 &x_old , const T2 &x , const T3 &x_err )
        {
            BOOST_USING_STD_MAX();
            using std::abs;
            Res tmp = abs( get_unit_value( x_err ) ) / ( m_eps_abs + m_eps_rel * max BOOST_PREVENT_MACRO_SUBSTITUTION ( abs( x_old ) , abs( x ) ) );
            return max BOOST_PREVENT_MACRO_SUBSTITUTION ( r , tmp );
        }
    };


    template< class Fac1 = double >
    struct rel_error_max2
    {
        const Fac1 m_eps_abs , m_eps_rel , m_a_x , m_a_dxdt;

        rel_error_max2( Fac1 eps_abs , Fac1 eps_rel , Fac1 a_x , Fac1 a_dxdt )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt )
        { }

        template< class Res , class T1 , class T2 , class T3 , class T4 >
        Res operator()( Res r , const T1 &x_old , const T2 &/*x*/ , const T3 &dxdt_old , const T4 &x_err )
        {
            BOOST_USING_STD_MAX();
            using std::abs;
            Res tmp = abs( get_unit_value( x_err ) ) /
                    ( m_eps_abs + m_eps_rel * ( m_a_x * abs( get_unit_value( x_old ) ) + m_a_dxdt * abs( get_unit_value( dxdt_old ) ) ) );
            return max BOOST_PREVENT_MACRO_SUBSTITUTION ( r , tmp );
        }
    };




    template< class Fac1 = double >
    struct rel_error_l2
    {
        const Fac1 m_eps_abs , m_eps_rel;

        rel_error_l2( Fac1 eps_abs , Fac1 eps_rel )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel )
        { }

        template< class Res , class T1 , class T2 , class T3 >
        Res operator()( Res r , const T1 &x_old , const T2 &x , const T3 &x_err )
        {
            BOOST_USING_STD_MAX();
            using std::abs;
            Res tmp = abs( get_unit_value( x_err ) ) / ( m_eps_abs + m_eps_rel * max BOOST_PREVENT_MACRO_SUBSTITUTION ( abs( x_old ) , abs( x ) ) );
            return r + tmp * tmp;
        }
    };




    template< class Fac1 = double >
    struct rel_error_l2_2
    {
        const Fac1 m_eps_abs , m_eps_rel , m_a_x , m_a_dxdt;

        rel_error_l2_2( Fac1 eps_abs , Fac1 eps_rel , Fac1 a_x , Fac1 a_dxdt )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt )
        { }

        template< class Res , class T1 , class T2 , class T3 , class T4 >
        Res operator()( Res r , const T1 &x_old , const T2 &/*x*/ , const T3 &dxdt_old , const T4 &x_err )
        {
            using std::abs;
            Res tmp = abs( get_unit_value( x_err ) ) /
                    ( m_eps_abs + m_eps_rel * ( m_a_x * abs( get_unit_value( x_old ) ) + m_a_dxdt * abs( get_unit_value( dxdt_old ) ) ) );
            return r + tmp * tmp;
        }
    };






};


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_DEFAULT_OPERATIONS_HPP_INCLUDED

/* default_operations.hpp
uWmvk0rtZaMjxdOvwAewj0abjM2abloAkAQde78Xbcy/1TK8U1xuU9fAGSExt3V+5RiySlrEuBVoXWWDur2yLjrJmNjNLv0oB8uJDI1lI8wuXhYCcImvHZYQgWgC+qh/DT7D8p470rfLc5q0g2DOBMwvEqOttQUwuD/Du8HCWv2QiuedBw2PBWiIxY8kfGFkHd8T6x+YS1J69/eD7odxI2/bE4hcWCD/pbg2sYYucRG/G6Hi7tIHPwO5LBGGr2niIWf8+g9B+lYLDibE6Picf1Epyecwgn/RtO0/blOwvhmFfq+1Zm4mHBm+gFLyl25Qsa8xn3tfFyjH6cdMO8hJzmfvQF+r+MzfZ63A/ZZg4c+CsTSidxo43rJ2mn2uqg3tTr50u4xHAfaM3feEBylOzTgGj6IvRtWSttNMWR3lEAyPH2+AH+nV3y/nS33lX6bzyDO/g0eS/7JE6cX6n5OHNS3EkNd8kPS9zvHrbAhopRpQRVf42aWRGb5sCn31xBX+sr404r3W9Km6fDuSRMIk30RNzJ2ZnDQQjqHLXmfE1sJV6sjElDi6mqlBrEYzYqSqgYkKTl5sxHJ8ciwMs+Jxy4Yc8oKAXAIzJG50WGlvj0iqwLsNHOBjcRi6k3Hnf4niZljyQQFuWh8jwLeyAdrIb2+SBON0jFbB31VpGfhOFCrBgKWz77XGdmaQDu9pJxcTV+BNxBw7Gnyg/N7JI8Qwb13fmiivmAjpzgEccqhEYIGqa9UcXk/Ug9nvukhJCIyTNWfqAgx+h06J+t0NMaarLFJZ0psvbNwZSGluAsYUqCK+pBHAsNp48TVctrJBdAJf+qHMNGTh7WqDVyse4uPSkRZVKfo8m2Hon9cV+olf151a08aLgBPXzJJXylgB02e2Wi6FD6HhjuuVicrGDUEMudT3n9uOA9zGaSqnaerMdBMDYqFkUWr3fQFF+KiOlT0jYejh47vEZH4sMj9l/BEkdXPW8cOAMtGMXAsW/LJgra4IoUTfOTbN/xJRhf+r2Waa/NRIlMzl3IOg1anmqO64Nik3tFSPB8HnoxoVMgmWLrtJB06X6B+rsHwP+SDgyaGRL5+T+hcJy6G5Qhbe3AIRYpnoJO48ccRNEQMfka3L85VpC62dI1JrUBrrOEFYrzJ3Zcq1j4TT5Bl1uJRIcqJf4dV+eD0q2ljN65lSSsOQWs8WOuokQCQRp5RLEDnbOBQWvKVpIZ41PjGYb5s5kTC8dR6WtoKDM+Q7EU0q9UV7ABU89e9ZYw+ghAc4tEeroGhPxAI3rLbInlxRH8h54r2KnvgIgk3vESMmLCH8A4GBkz8qMP8Cc9xhhVWtaBn3NROYIVxjiCmxyFGN1lsCr3fX2eL9+VJQd2nbTHzISkqD5M3kZ7TmtZgICqJ0i12ChK52NNT9dTTbIH0jayY5C9HRjV5qJ8JNtmhgPIDi876XyB+U6Owa3MPrt4fuH9yBdDK9DrCx+f2R0Oy9s86B7NenujbZiXTU5dDRm6wy8qjLAOr10H6iAWMOakl/gxYc5qT2uY2L3PnXdYwJMc1iuRbcz0uAQo6CV6F5V9o4RYwlMVJNRh9zVqyAVbP2s3Aq14jZ0Pni7M0n4XshSKBKxowsmG4pUV9rlM2GFDSdHmRxlEGAploLpjl+mZbSujXwJ+qRGHK2q6JzSUIBE0zETLYcoQIVquttaFAShcU0+22cm3jF8vjVZRblB/NoPQS25DJ13tgTfBbsuSehpV4/tQxKA4Rryyq+aR15W7LpXq/j4H7fZYRuNQm0LFXUxYzyg6vEIqQXP58QuikZHCecRY1vuniAP3QadT9e4BW6DtlDIP+by6g6XNbiRla28REswfIrMVsmW+Zdd1a2sqpIADXsTjOnIdRZzFAc+rrNjoW9QEHmImEs0crZ4ES36GzhdqcObtcNuAYPpeVKFg4EpZyhmsfifllS2QOgBsdlRCXuGDrCBRVFuTlBVpF0tahZbGhHkeVFhB2pk6sh+IhwKD6hmavOmrauh1JV+xfUvdf0msgueqa6Hsznu4h7t2GVnuDEk0ljNQ8isNbxGIl2ksGrum3UZ1lDSiuqSfbEDpjJ5sellZyKMfvZbUXl8r2FD4clkhZ5roprNbnV8W6TSdRYOQhxjLgNW0NdGZ3W8itLcthWBxlthkDtAw+BcwLgtNWeSPZt6KRq08NcW5TwO7sp9CHbIbC+Pr6AmncSTAgR9xafqXCCwzKS4O2AZAtQ2MCO01jgwZWZC/t+N/2MFzF781aZP5gs6b3Iq9TnyBXUJpvrCYRvXdk/bBFhLUHivpe5CqgrMoaiaQnz4ks03s0f98R+BTN+yRjnWgFElWjfRzDt/brVsrMrSbQuMXanZ3eKXCmzHs86O4yB88bXRXw/kbEcW7BvnWSydBJTm6EkG6K53BiRB4NjhuW4Z1aF5CqK3F52WlIVISfToEUdPlYi0N/jlpHIXLbS4qmHu7R4q7ULGLRIk611rN6oVkT2RLEZ9lzlTwV1VQamFshC3WEP5fvCSNV722jdYT6xUeX4IjUHWBXq8NqBaVYFnIoIUIVhkX5QwkOFVXeJLv9ZwE8SnxofZNKBQ8Me18O+xuVdKl+uFyK4SJo3u/KxNW+/KZ4jRQOXxjyE3A30ph7SeAYEo+s1vmhJYyUI55UlQpsGBmDv+DaCI7Bs+U+zirnOB6D3Xlb3t6Qqt0F/INU4y3dKZHOHfIdjZvTehr5W6EP1ZaAFLSkM3AJQfdcgu7fy+C7FYj/Q8x6nyU3xYv4PgNg9/3aiOwX3IJTWiMnyDDMFpWWiiDRkQXRs2PfH3KHpJCM2ZasfBhssWHI1ixYgJTI+Kt7F9vvCO+9Q7H2aztlEPfGbdmF2iK9To5DT3onI6dtA6aoIdnFNhHzYAFp+FA7hUssy9jNrtCYhXJRPien7VYr9PjKhfpGTflq3lXvAcEG5UZ99AlU4EyX7fjialtQNiTookxZjyPI6ZdMeo9uJLoOpdVxtbQOEAT2D1JML+MLcbiye5mU+2o7tf8MPwDSoHRhVREXe1h9577HSdTSTvwAl7j1nRisK/T3sO3XLU8E/Df5RFDDG0hb4RpJA6jyqcr5nmRAT3kwlM/euKrRHGm/if7e4pVpkEzqnG21NzH/x1KY5F9P5WnNFC3Yhdz1nBaoby2NEm/vRBux5EzVIysuVoNXG3y31msThpwP0v2TVZTuvc51EeN/U7QxiYI1FjGmddBflSktTFTLp0uCh+msYG6Z4a7XGFozGApYEetXlwDjBC9TKUE3WyzOcmNdhtnvQ58TuRIlr9C/9iXmPhkVrMM1EiYmeqkM3zp0WG6vlnCJ/8usbLCpKGGa1DpMc8vos+Wo+jkv3tXG08HT5wJ7j+EcG4USZVFdn31T1KYhHtegEMyQcmXMEqCUEXiYb+VnfFntP4H8a9QGQ8vQZJ1cb4vEBZx7d2qafFTwmm9DMeC4LNWpkre8mJzVBkAGg8tSqK/yTGybDijt1Ggcn7kOGpG8ikgVeyb64v6bDD2Otfi7ZPzbPweXzdGNFuibc8BSDpzERV3XsvnukB2C2yi7aaPtg9uoOJtMveiVseUjnAJrv40nquPpv7ppr8Q070Axx8wzpDv120MQfoOzpIUno7/5JYCJXzLuL9OgnYHzx8jN+cvE7TM5lEeOZ9OTgG6RsOHgPyr510BswjJDWOjIRJoxgV0PJy/EK+kok5Rls8ukwyiFTgFwOJi7GhmtJYlQdIRNL8ukqyrOUFacU/z8wKIUUV2AZUa+8cybiEAwWoZRBQ+PYqmyGe/urlUj8nrUI6Py3Myj8fB9ePverDtc7HTqqflvWnDLz852uUkqnoZryJc4YiboL+pf6Wffjq2h3p2vhH6/XeLRouz2ztKld0DaZMyemkkwaKsL4D7snSu+vp5PKgvW4cP0J1zvzufR+n0M2DlFgwb7LJhJAQVsgegPKO4+oCir0IsvT6KBUcBGUFHAhQ1NT403Tei1m0G39EinHARnypW7xoMXQiPaTw5oZhaqTLRyshsnSyXzysZV0tb647vH4v5MQZeuM6uZrfinJnUlwVt50jo1c1F0DSB75K4/rjx4vqfgg6RJiqXYNOrEsZu5Qyjm40cxZTFpMg60yV2eRn3oOLiPaOwUoGBQz5ee1I9HDY1cgYoKnjiIZ4Thl1XoKWx9cEi1JKB7l89SV3ZR0h53Bvis6JFVYSzGBS/kk7Uf6GJcmViMhySdRpXCwT+ASl7N0ZIjeXDYoBGO65xWqXbUSq5yVVhQEElq64yuvh9Lx8dR6Sk/OMJVC9gm/ulhScs1UUB26cEv0PUpxJKdGI8EGu3MnjPHl/olQ/6cr8lamLlzM8zO/Xrylugj5PSII76jz/cUY3sJjzQaOj9OWrhOVMNPg6tHR68TZKBJTfHJV4WP17dPfbghJucKpWYG7ILcWzW4g5xeE9GInoUAdsA6Jc22mITY4sdzHJ1MikLD7Kmc445v4SMyrhm6oc5sF0+Ugi3139Lg8CNnu2nye1zJmfTGXotlkaLXr7jsDzox2bTkQ32geGfeCqhRIREbDg2hJfu1WilG9QIKyC3/pka45G0l0yWG+c7j/WLbORgyzmJL9GK37cKZl0jGua2WeBJBx3TFWSnoNYCS65OvAm/Kb/eK3wC9zT7LCz/N1yg6zhJd4wCy/yfU3laIOWeQFSCDALB38hkwllQjNJKZV6nqWIpfjqCYar+zfl7SbqAM6ucQ3VAStSVBECkgN5+Jw48EeOcfjqZyHjuMcxMJBvX9O3z7Cef56Hiz5g1xm1RdsuegOhuo4DGwxtY6CO/Gh8vE6E6LL7rzZXzD/LLDoO/JdIULRh39lX/D3vifmkqmCSHarawL+BtDl9SYNUlfIhPT67vNv/XeCxQTNMOhF7c2LzfRGEsplVHrCqaEug4f3ePLJ0LP2+gY2iLaiK/rtUCRxCrC25zqnIegCJfqjE6i+6cjtOgcgaAMP9+N2LWZA0g8JOsJHqy4WSsenBN3ndpJ+wXL2cM+GalRyOOK8XLp/FzH0Llp4fb/N28DzWM7jXDPSeqo7j9s/hXHcOMhNsY928MkF5DzN3wUFv6EMZ4oW6LCGPR8OyHTTWDclJPfkBUDR+E3aYp/cWY5HG1yLnfdXKqnqBga1ljR8rKCjHWrN8Ztau2pyFgmZQ0o+v8QAkjjS9OtOl97xvTlqftXm0fmz5xGEQg8UIZY5xjme7BYsG8XDroBzju2ZcNVSjPRQkyxWNUgCTrQKG1WF6zMEmzdsgJ+v8pDbbE2cd2I9WMK5JVKbAlrZN4gAaAlXId1GEhuFnaQm6UyLc03L1woyxD+3kHeLKqgPLuoahN+YxGiYeUqLe3jBb1BHGf6xt//EWDPpkK6h45ZI2X8Jdqlb8HIbupVRAGfwnHKsCyCAGHu6X9pmLS13WNxZ4RlVSOtdN6VuwTSVPq6kkW2RDrC7Mc1xYkUnRNB4MbW5IXF5NMM9PNJNwzOUQ061Qhza0WceV2dwoC+NqM+UUB2DzT/Hq41/MTUZ1lVwWjLc9EWrL5qWm7CMxEQ25F4rvDKJRBUv8hU94sWhMFSkYYaWik/0JSLiXMB2X/FPtternfVBj74XsrRXlV/p1cRMK+PmmbK3+4djNV1hckyDs/sn8AZ6J8eZssmYE3pd+/F0N+EAKl9oekWI8KJ6yh0fw1IZN5k1zZvFfAodj3MNLVdg9O9/c50dKfUqLo2NFAwM9vd+6U/589jCsy3enyynXRacQUGV1bxOBBxiiJQakSjQITMBlA8tUwaePPnStmCGjhY0NPIfVTsDTnTevRcYspJPZ6XVzExibDUySJZhD6baFp2H7v3XEmrgkVw6qdLhV7HKsIKvMcM1NkwVMds6TiZjlRn7iyQ9KthpCswzyXkD0klHCTG5dX/Kken2i32MNLvCU77idZD9jgkU8zav+ewWiOpE9yCgMk7Si9fTzVpOWJlmsV3FaAUNHqvCD0XqrE81C38gHR870eZ8pURs5MPo/gliW7QAcMFXk9fcPT+RoRZk/l49OZ9vbMysRvAB4NipxU9TaQYjr3BO5Uqo3C+LoxSsxqDe8/oiAQgGCYLkf0Vh7Hujn8PtKaEi99/AAQdZqcPWvQ+OYgP1OOwb3RSIo6AGj25potpAdfO5mWy5B7yLRJXZcLWbLdx2M/SC6OUY/Wb2382VZVUO81ndjjFAz9X6zw7xxWALoVeSj/7sNoS9mV07s7r2Gx2tZV6lZd5kUrOnlLB0AsfnvtfC/odeJF46Tb2Nh3zPN56f9pabuEiH+RuIQVSMDUvIjuJpkAqZ3bq8Je0XRBLmJVCvrChpsmjXl1udIToxHkdQYXcRm3GllBlwUuL9w3drWIuNs/Q68e0vKil4qjTBGR5KdDLTq05Eo6vVXDMI1aTs6Yy67pa4dAA+44VpBRJN8JE/T3FsXitpSMM+dR9JdwEXekq30MzgJuU9FYI0sYDtpiuoTBiq6WI/k76Ls2LayNe3oNaiTR2e7P98DrrLpqGwRJtQ28ds7vchF/6tQaai49FCpnXT1lJsF9BFoJXGVeXQe0Mk3h5dwYFDFfKpJt+F/BkVolU5GEZe4Ex3pMCw84vBtDMbg36LhzvsvusliXdrhRTVWriEWEm1PFrxsP5Wvx4bW+nf7ooLI33FvoBPwEQAMx/EfoTAM6cYkXnjJxfb2Mu7ikyEV9WOry6s/6tr2FnxlCaH13u69OTex7/y/AvwyKLGus7zv/cNun3gvJWX639tXZFQ1bf+EwgIEB1GhlFnUV+ntRSmLaLBckVinbcMa2mZnhyU9NteFmncnz3ZfT4KQSYAjvSnvC5MbrE4toiDD8jDkowgMIQhbb5P5qWT2QDzQQ4QfmVjOt3qdEv8r6X31deb19r1ttfpJovDyfRkyhtMCXnJBLeq00FY58eN0w/FCF2VevXA55tpyS66n7JabOnzzYLLy/cSe8u2RDAhGaYL3en91n4OPNuqh5zZPszaznOWNeJGvVUKeN6QAEqMg1aH2+AMpEd7WZ0BTYD2qm8DLNn9RYNba2KWNhfALLasFrrYqLicWgbMXyVsKe4br1DXculkaV095gi+DENgoO+XZ5RI2yx6H590wr/lR2MrbNZVuVYQzYbELIYM0XCqXrW+JlgFlsqRVd1dZObgInzNNXHDiTO7cz2T4j+8oTIgnyuXbXB/KrSWJ7KJG1RXwcWDYlbiYym8gXV61IewKgu05zwNknc4J/38kxyHZCQ4t2yrSpa7LADMvCrm4VW0QLhbodjT2l8sUqRViSCi7y88ZIvD5jMDoGTgV222gtfMYNjxm20UhV4YGyM9Lz/EQekq1xPcPsFrsWUKI3J+nmS9BTJahfOERHcJbBig1QUXW5QlwLaYGrBu0i1T//j5F4sJM8LdUE7+/u0K39NGZ55EFwtNUzld3XEcwJO5wpZBCTjd4440WGZzUFt4pjevMtWu2koU2OMwipMcP4BsMBoxh5ebNy1Omxp9EtKtr119sryR6rslzAlBoxvYVJvnpjel4y9kVKx55Yjnqe2r4RrmfEwBI//3imxuemnY5w7CH6ysfuZfZ8xYWRvutKVsAhfO4phl/gDYir31hHB63FmF45Sn65AD
*/