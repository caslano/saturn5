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
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
*/