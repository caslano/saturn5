/*
 [auto_generated]
 boost/numeric/odeint/stepper/detail/adams_bashforth_call_algebra.hpp

 [begin_description]
 Algebra caller for the Adams Bashforth stepper.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_BASHFORTH_CALL_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_BASHFORTH_CALL_ALGEBRA_HPP_INCLUDED

#include <boost/assert.hpp>


namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template< size_t Step , class Algebra , class Operations >
struct adams_bashforth_call_algebra;

template< class Algebra , class Operations >
struct adams_bashforth_call_algebra< 1 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each3( out , in , steps[0].m_v , typename Operations::template scale_sum2< value_type , Time >( 1.0 , dt * coef[0] ) );
    }
};


template< class Algebra , class Operations >
struct adams_bashforth_call_algebra< 2 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each4( out , in , steps[0].m_v , steps[1].m_v ,
                typename Operations::template scale_sum3< value_type , Time , Time >( 1.0 , dt * coef[0] , dt * coef[1] ) );
    }
};


template< class Algebra , class Operations >
struct adams_bashforth_call_algebra< 3 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each5( out , in , steps[0].m_v , steps[1].m_v , steps[2].m_v ,
                typename Operations::template scale_sum4< value_type , Time , Time , Time >( 1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] ) );
    }
};


template< class Algebra , class Operations >
struct adams_bashforth_call_algebra< 4 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each6( out , in , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v ,
                typename Operations::template scale_sum5< value_type , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] ) );
    }
};


template< class Algebra , class Operations >
struct adams_bashforth_call_algebra< 5 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each7( out , in , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v , steps[4].m_v ,
                typename Operations::template scale_sum6< value_type , Time , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] ) );
    }
};


template< class Algebra , class Operations >
struct adams_bashforth_call_algebra< 6 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each8( out , in , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v , steps[4].m_v , steps[5].m_v ,
                typename Operations::template scale_sum7< value_type , Time , Time , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] , dt * coef[5] ) );
    }
};


template< class Algebra , class Operations >
struct adams_bashforth_call_algebra< 7 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        //BOOST_ASSERT( false ); // not implemented
        typedef typename Coefficients::value_type value_type;
        algebra.for_each9( out , in , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v , steps[4].m_v , steps[5].m_v , steps[6].m_v ,
                            typename Operations::template scale_sum8< value_type , Time , Time , Time , Time , Time , Time >(
                                1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] , dt * coef[5] , dt * coef[6] ) );
    }
};


template< class Algebra , class Operations >
struct adams_bashforth_call_algebra< 8 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        //BOOST_ASSERT( false ); // not implemented
        typedef typename Coefficients::value_type value_type;
        algebra.for_each10( out , in , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v , steps[4].m_v , steps[5].m_v , steps[6].m_v , steps[7].m_v ,
                             typename Operations::template scale_sum9< value_type , Time , Time , Time , Time , Time , Time , Time >(
                                 1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] , dt * coef[5] , dt * coef[6] , dt * coef[7] ) );
    }
};




} // detail
} // odeint
} // numeric
} // boost



#endif // BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_BASHFORTH_CALL_ALGEBRA_HPP_INCLUDED

/* adams_bashforth_call_algebra.hpp
TFR71CpbG4/j2LgLkTYQr/OrGOF1zCqqOgaovBB4KO2g1tZM14pkbPApjHeAzEzKrzbiVUxB2xJhoktGIZu8S64AZx282d1z0yocXcdpHT0Xb5g89i2z55iole33q7Idm8S8kz53JdlQDEaYSSY1jI/61tUbjbDk/jwcuW+7R5XckO4iTGYsLG4XBLz7vj982+273X5twDSGVPTOM85dFoZWdXR4IAXlqroJ6lsPCTa2lIfbSPxSnRhwPce1i3lHX3bq94mHhh49leqsMaYUebkJAl5Bvz1od3QOXHH6OwrduDNsmfpvCAsm4gKNuj17T7CnUdXeMbmWZgnOVGBWQZKi2ONYntVNitfjt6Y9P7EQ/veyS+erCsDmmG12b1dzeCGppDAgPwBr4zFU67M6Fqv/AFBLAwQKAAAACAAtZ0pSNmQxOe0EAABvDAAAIgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliNTQxLmNVVAUAAbZIJGC1Vm1P20gQ/u5fMVD1miBDWj5dedO5EChtLkFJaIWEZG3scbyVs2vtrgn06H+/mbWTwAGNdNdzVezd7DzzzDOzs9vZ+nVPAFuw9on9/5geenuLC6O/YeKeXx3H91D/I6treq9z0oGVyX3chvUm99Dy
*/