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
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
*/