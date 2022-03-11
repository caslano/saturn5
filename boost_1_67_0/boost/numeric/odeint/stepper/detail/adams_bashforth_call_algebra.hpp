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