/*
 [auto_generated]
 boost/numeric/odeint/stepper/implicit_euler.hpp

 [begin_description]
 Impementation of the implicit Euler method. Works with ublas::vector as state type.
 [end_description]

 Copyright 2010-2012 Mario Mulansky
 Copyright 2010-2012 Karsten Ahnert
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_IMPLICIT_EULER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_IMPLICIT_EULER_HPP_INCLUDED


#include <utility>

#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>

#include <boost/numeric/odeint/util/ublas_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>

namespace boost {
namespace numeric {
namespace odeint {








template< class ValueType , class Resizer = initially_resizer >
class implicit_euler
{

public:

    typedef ValueType value_type;
    typedef value_type time_type;
    typedef boost::numeric::ublas::vector< value_type > state_type;
    typedef state_wrapper< state_type > wrapped_state_type;
    typedef state_type deriv_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;
    typedef boost::numeric::ublas::matrix< value_type > matrix_type;
    typedef state_wrapper< matrix_type > wrapped_matrix_type;
    typedef boost::numeric::ublas::permutation_matrix< size_t > pmatrix_type;
    typedef state_wrapper< pmatrix_type > wrapped_pmatrix_type;
    typedef Resizer resizer_type;
    typedef stepper_tag stepper_category;
    typedef implicit_euler< ValueType , Resizer > stepper_type;

    implicit_euler( value_type epsilon = 1E-6 )
    : m_epsilon( epsilon ) 
    { }


    template< class System >
    void do_step( System system , state_type &x , time_type t , time_type dt )
    {
        typedef typename odeint::unwrap_reference< System >::type system_type;
        typedef typename odeint::unwrap_reference< typename system_type::first_type >::type deriv_func_type;
        typedef typename odeint::unwrap_reference< typename system_type::second_type >::type jacobi_func_type;
        system_type &sys = system;
        deriv_func_type &deriv_func = sys.first;
        jacobi_func_type &jacobi_func = sys.second;

        m_resizer.adjust_size( x , detail::bind( &stepper_type::template resize_impl<state_type> , detail::ref( *this ) , detail::_1 ) );

        for( size_t i=0 ; i<x.size() ; ++i )
            m_pm.m_v[i] = i;

        t += dt;

        // apply first Newton step
        deriv_func( x , m_dxdt.m_v , t );

        m_b.m_v = dt * m_dxdt.m_v;

        jacobi_func( x , m_jacobi.m_v  , t );
        m_jacobi.m_v *= dt;
        m_jacobi.m_v -= boost::numeric::ublas::identity_matrix< value_type >( x.size() );

        solve( m_b.m_v , m_jacobi.m_v );

        m_x.m_v = x - m_b.m_v;

        // iterate Newton until some precision is reached
        // ToDo: maybe we should apply only one Newton step -> linear implicit one-step scheme
        while( boost::numeric::ublas::norm_2( m_b.m_v ) > m_epsilon )
        {
            deriv_func( m_x.m_v , m_dxdt.m_v , t );
            m_b.m_v = x - m_x.m_v + dt*m_dxdt.m_v;

            // simplified version, only the first Jacobian is used
            //            jacobi( m_x , m_jacobi , t );
            //            m_jacobi *= dt;
            //            m_jacobi -= boost::numeric::ublas::identity_matrix< value_type >( x.size() );

            solve( m_b.m_v , m_jacobi.m_v );

            m_x.m_v -= m_b.m_v;
        }
        x = m_x.m_v;
    }

    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
    }


private:

    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_x , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_b , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_jacobi , x , typename is_resizeable<matrix_type>::type() );
        resized |= adjust_size_by_resizeability( m_pm , x , typename is_resizeable<pmatrix_type>::type() );
        return resized;
    }


    void solve( state_type &x , matrix_type &m )
    {
        int res = boost::numeric::ublas::lu_factorize( m , m_pm.m_v );
        if( res != 0 ) std::exit(0);
        boost::numeric::ublas::lu_substitute( m , m_pm.m_v , x );
    }

private:

    value_type m_epsilon;
    resizer_type m_resizer;
    wrapped_deriv_type m_dxdt;
    wrapped_state_type m_x;
    wrapped_deriv_type m_b;
    wrapped_matrix_type m_jacobi;
    wrapped_pmatrix_type m_pm;


};


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_IMPLICIT_EULER_HPP_INCLUDED

/* implicit_euler.hpp
X9xUN5xGAPYO7l3tUt+T8deRYDiwb8JUdMA81/G1AHxx11rsdzF9oX702bYwbvR+5xB8ljPAY0+hA+yt/ybwzjzi6K+c97wVvIBfHG1HDUs/JoXxvk8v4A3qx7HE8/7o4ugf5En89snGxGEwkIV8vL0r/WXsryX21wL7VuLvueezf76QGMXYOvYEM25Fh3aeY8IWe1ag0xP465XYPXspVz5CDdOGuHUH+u1M7byOtcIWFh6kBu3J+pMXSpW9i03oupL1PUAOId4o/YQfsKcDxJg/DoFDM8mfN7B+xMi72Wtxdmf/pBe1JvP5yMsef13yEdjo5RXYn5M6gHp3G/mwDT+/56aHWx/Z1PV/0P/sSO9lG323teHEcTD7hhx6RMSVpeCehvjQlr+yVjuY4+2s+U3gqhbkLnqV2+Cfdjk5dBX99CRioxe8Dr81peT+VuQa+h6tsL9viBP3gzsmtMIeid3D6BFtBn+1u4088CG9EfDFp+grcy36XU9dkQBe+ok85sJfiaPtXqTW+QSsRg9mYhU5egL56wH6XrMZL3n8Dmxj43js52PiJ/41A18YQzx+k3z3JPefQBfDHuC6SNa/M3ugbYmHYPYug8lJ2GY2vcc3P2WNqJcf30oejCV+g3v2jQDPDqTPTv8/K56e6G76yEo9V8Fa0X+yo5PcMdSd+fTXWb/6xKGe1Cilt5Hvi8IojsiNR+ibg3f73EwttAq5kchfTjw7SH2+BhvZzvoNAme9wdinsSdwE5jnYuqsb8hx4N/DrOuv8/Hpu4lpxPiB+9HHTmIxvpgE1jv/AuLkKnBxAf1p8kEC+XYOue4E9vjodPwwmv0n+nEPFLLXdAvxfi91YX8wKviohP/XO5c1KqHmTAPXXEv/gvzf+B3msI88CO75rYy6kutW9ec+vr9NXCueCd7JI27fTp/mG3o75L8XLwMzkxv7HcY/qRt/AAMWkqMT6WVtWUbOA+Pd2AesO56+0H7Gcj1xl/VK5b5O9CPO34sP/0Ev+l3WnX7+NV8SJ7ClOtfRo1uLPLBqEXrrv4V604UNfom/r7Lwu2VZPxs2vpr8ug8cu4P4/z347gD4Df+J5rrn/05MHUpPgVrqe/LV53egE2yvyWL8IpH+ipN1QGfXlWAzxNOMduwFRdOTJwcvjiEX/UBOm0duL8Tnr6Tvyxqsqkd+24ptLCUOsacwdA2664gdt2fM8GxXCN5gH6UNveaFyLniBHXrCmoE8PgVR8H0/YkhFxP76H9urYstfAEeo+eQRozoDI/XT4Jd6NGc8yB4/mFqE+R3fAk7nU4sgte6+eCyJ8lx+EnkdvpnHrAR+ah0NviqEmzytSKPM74J+O9o9bn76AlgFWL55APErFdYyy3U7BPwcR/2MY9Youzroqcq4kv4AmIgeNv9ArUF/nVZMbmjKf23buw7PwNGRCcRVeTFHmBvH32NydjrYfTWmB74GjANPtoQjHLNIHoHV9BXo27q2xKcDVZ9Fb0OiAU/toYPPtSC3NRtG3niNvIIc7w8HB8mzx4Gyw6dTP5Df1//TP2yDP+Ywnla5ryjG/jpR/DM89gpWGfnO/QJyDeJVjBXR2SDX9qCt9+5DntJZ04NqQtew5ZeJqeijx7lYCXy6kIwRws3sXQ7dnsD14Mv15dSuxKj7ODKsUr/FuzqrYOOveDTYeAPfN3BYZuLd4O56Tl3OolfYzeRX2NX+PvUcuzjYQtrwfq3YJ9/EGvVCox4JbV0R65jnFdzT8dSvqOD+YCqe8g3zk3UZOT0354Fe6ZR0yawTsShOePA1sSPFY/iv52JmeSO58FG5Tvo9XyJHsnJs8HwB8lnDTZHhRECEEJdg7y5++tY5oU=
*/