/*
 [auto_generated]
 boost/numeric/odeint/external/mkl/mkl_operations.hpp

 [begin_description]
 Wrapper classes for intel math kernel library types.
 Get a free, non-commercial download of MKL at
 http://software.intel.com/en-us/articles/non-commercial-software-download/
 [end_description]

 Copyright 2010-2011 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_MKL_MKL_OPERATIONS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_MKL_MKL_OPERATIONS_HPP_INCLUDED

#include <iostream>

#include <mkl_cblas.h>
#include <boost/numeric/odeint/algebra/default_operations.hpp>

/* exemplary example for writing bindings to the Intel MKL library
 * see test/mkl for how to use mkl with odeint
 * this is a quick and dirty implementation showing the general possibility.
 * It works only with containers based on double and sequential memory allocation.
 */

namespace boost {
namespace numeric {
namespace odeint {

/* only defined for doubles */
struct mkl_operations
{
    //template< class Fac1 , class Fac2 > struct scale_sum2;

    template< class F1 = double , class F2 = F1 >
    struct scale_sum2
    {
        typedef double Fac1;
        typedef double Fac2;
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;

        scale_sum2( const Fac1 alpha1 , const Fac2 alpha2 ) : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }

        template< class T1 , class T2 , class T3 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3) const
        {   // t1 = m_alpha1 * t2 + m_alpha2 * t3;
            // we get Containers that have size() and [i]-access

            const int n = t1.size();
            //boost::numeric::odeint::copy( t1 , t3 );
            if( &(t2[0]) != &(t1[0]) )
            {
                cblas_dcopy( n , &(t2[0]) , 1 , &(t1[0]) , 1 );
            }
            cblas_dscal( n , m_alpha1 , &(t1[0]) , 1 );
            cblas_daxpy( n , m_alpha2 , &(t3[0]) , 1 , &(t1[0]) , 1 );
            //daxpby( &n , &m_alpha2 , &(t3[0]) , &one , &m_alpha1 , &(t1[0]) , &one );
        }
    };

    template< class F1 = double , class F2 = F1 , class F3 = F2 >
    struct scale_sum3
    {
        typedef double Fac1;
        typedef double Fac2;
        typedef double Fac3;
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;

        scale_sum3( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 )
            : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) { }

        template< class T1 , class T2 , class T3 , class T4 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 ) const
        {   // t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4;
            // we get Containers that have size() and [i]-access

            const int n = t1.size();
            //boost::numeric::odeint::copy( t1 , t3 );
            if( &(t2[0]) != &(t1[0]) )
            {
                cblas_dcopy( n , &(t2[0]) , 1 , &(t1[0]) , 1 );
            }
            cblas_dscal( n , m_alpha1 , &(t1[0]) , 1 );
            cblas_daxpy( n , m_alpha2 , &(t3[0]) , 1 , &(t1[0]) , 1 );
            //daxpby( &n , &m_alpha2 , &(t3[0]) , &one , &m_alpha1 , &(t1[0]) , &one );
            cblas_daxpy( n , m_alpha3 , &(t4[0]) , 1 , &(t1[0]) , 1 );
        }
    };

    template< class F1 = double , class F2 = F1 , class F3 = F2 , class F4 = F3 >
    struct scale_sum4
    {
        typedef double Fac1;
        typedef double Fac2;
        typedef double Fac3;
        typedef double Fac4;
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;

        scale_sum4( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 , const Fac4 alpha4 )
            : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 ) const
        {   // t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5;
            // we get Containers that have size() and [i]-access

            const int n = t1.size();
            //boost::numeric::odeint::copy( t1 , t3 );
            if( &(t2[0]) != &(t1[0]) )
            {
                cblas_dcopy( n , &(t2[0]) , 1 , &(t1[0]) , 1 );
            }

            cblas_dscal( n , m_alpha1 , &(t1[0]) , 1 );
            cblas_daxpy( n , m_alpha2 , &(t3[0]) , 1 , &(t1[0]) , 1 );
            //daxpby( &n , &m_alpha2 , &(t3[0]) , &one , &m_alpha1 , &(t1[0]) , &one );
            cblas_daxpy( n , m_alpha3 , &(t4[0]) , 1 , &(t1[0]) , 1 );
            cblas_daxpy( n , m_alpha4 , &(t5[0]) , 1 , &(t1[0]) , 1 );
        }
    };


    template< class F1 = double , class F2 = F1 , class F3 = F2 , class F4 = F3 , class F5 = F4 >
    struct scale_sum5
    {
        typedef double Fac1;
        typedef double Fac2;
        typedef double Fac3;
        typedef double Fac4;
        typedef double Fac5;
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;

        scale_sum5( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 , const Fac4 alpha4 , const Fac5 alpha5 )
            : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6   >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 ) const
        {   // t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6;
            // we get Containers that have size() and [i]-access

            const int n = t1.size();
            //boost::numeric::odeint::copy( t1 , t3 );
            if( &(t2[0]) != &(t1[0]) )
            {
                cblas_dcopy( n , &(t2[0]) , 1 , &(t1[0]) , 1 );
            }

            cblas_dscal( n , m_alpha1 , &(t1[0]) , 1 );
            cblas_daxpy( n , m_alpha2 , &(t3[0]) , 1 , &(t1[0]) , 1 );
            //daxpby( &n , &m_alpha2 , &(t3[0]) , &one , &m_alpha1 , &(t1[0]) , &one );
            cblas_daxpy( n , m_alpha3 , &(t4[0]) , 1 , &(t1[0]) , 1 );
            cblas_daxpy( n , m_alpha4 , &(t5[0]) , 1 , &(t1[0]) , 1 );
            cblas_daxpy( n , m_alpha5 , &(t6[0]) , 1 , &(t1[0]) , 1 );
        }
    };

};

} // odeint
} // numeric
} // boost

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_MKL_MKL_OPERATIONS_HPP_INCLUDED

/* mkl_operations.hpp
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
*/