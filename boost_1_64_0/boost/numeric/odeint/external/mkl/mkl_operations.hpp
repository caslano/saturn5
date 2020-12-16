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
Tr4XfqtovyTaJbWf+f2v02DXYJua4PeevgW/jwGv8D9vOIzmpYsg50lIEzy+hPYsOwi0ZwfL3DEXenc0fL8e6Fk7xmDo1kHD8N/OgezhN4egYxfBtl69HPK+ATZ4T+gJxsL9UMbdsKE/gU05coaf5i/B14XLhK9xrD/9hCxsMXj641iyhdC9cIjWg9G2b1apkv49civGgaXW2jfqMi+UH/9Y+CwFfcNx4Av2ow31e2E28YJ2O/p2yASyO/kDGGO2w0bjeakV/Q/24dsdyDcM2wX7sqECMuqELE9DewhbGoqTPp0t+jXGuqvA52TIT6G8mwr4tUdfgPZpstbbIOvfXg1bCn2YsTf4hfxrDkSbwF7W1sHeQr9/CL1/rga26pPQj23Q40NhG/HocUDRGvpy0s33wYZNxEP6sx1+0cBif5knR8Gj1U/+ci7an3yV28Pm78axheX7pDU32mj5+V3Q27NusPQIvK0cp/7/73/sH/aj486JWvXGn3a+p2acOho6O17FhzMDZld8IByJuWn7IW2SSRvAdrwHd9zUMgPHobxMOqIMfDHwyw0843yozcFvULvVYKgdewzSPD9KxVMhYMWHUKCae0xjn3hfskTtocZUOv5/BfJMVpPKU+PNjKCxXCFtbHmT8xdj5VzQxshkab4TXtTV2dmuCbsvS5aARydvC+WdjDKcjOPG60eXM04vdY1VS6mcZYTblL+cxubettWNvW2IXmru7OhtXdtrigzCUbpDr43oLS3EN4dFtXX09DZ2NLe6lQimEM2VVn3ay4P1WUX16TC4+L1b5XQtUcjE/T2Gf08b+6edS9W4SqdNu5AHVHGUdGkuoaM/lG7rYzW8K5bOoKERZu/qRreBp+ObwtkY6C9EXcHH2B5uf+jbUbmE8zH76MHZ8IbFuo4+COo2jcqfblYVh8IbMsp579V0Mmj7CTWo74S+8rz0em16T/jorTY3XZPetmoaXdgZNnWbr/W+2YQILEsncykDXw54mQ/eHE5EYkPNiFrqxzEokoGWf7nqRk9qGRqiMlYgb7VqjGQdwaDo5mQiiz11XadOpE1RS+PYXo9v06keRZ13NdKnqpxaAVlOgizXCFnWFwinO4Q1J5hm+lj5Ka4OQDfWFe1T8cRCfQ5fE3VfdJ9Kk1wrNF7GSRsID8eHtiqyIQoMG7gTqqTcNhhPuPjgsRNMouHHa7lnvMJc3CkGlokkU85HslUT2ZQTWA6Qj3N3gZMt5OBubtiYSRkZBOFO/Rvy98HO1a3d7Y1dXa0tOq94p/52kpGT/l3r/N5ufq+3+mEY72GyX1la2e6nfhgRNI738o2rgax0fSfBlZTv1XhPjDFyNq5oLDQc3hCPSBkDFukfSnm2W8sYsJTy3ic47+mhiMSZpHHC6UHI24Xt4dB3tHEo6cMt0+VuCcAnA57JcDnlzrsot9IpI5MblnmqAYsLnFqNw+9T8D40EAa3DNsbsOSmRNKlM6D7RQzBfBmP9xkOTmwYWsJlzTQwT882IN8sk6+BaIFH+HGmTMTmqp2LoR9VEOug0LElKtS2qnFZa6ilsye0vLWxpbVba0kAqvUL7WVsAf5FD+GxU7975WbN+6F4h82dAIiacLK2R0ODoc6u1o6envZQc09vd1vHMufujOGt2rwVStR9cnZe3XYOeGaymmHz0xsTh4wOeuPuMOntOFqJS5DeJgnvyLz0Y1tCETJbbjkCJMs7xSovbZWXofKyhJe/Poi6dsvBT5d+LeTOcs05geVR1w9BWWM3+8ah5e5oGgppQuId1AqM09Tajb2NoZa27tbm3s7udTp33hTQcfry1nLTl1GdnQPjZF9epXuy816vwCDeT06m2+M=
*/