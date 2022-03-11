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