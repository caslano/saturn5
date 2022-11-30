/*
 [auto_generated]
 boost/numeric/odeint/stepper/detail/adams_moulton_call_algebra.hpp

 [begin_description]
 Algebra caller for the Adams Moulton method.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_MOULTON_CALL_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_MOULTON_CALL_ALGEBRA_HPP_INCLUDED

#include <boost/assert.hpp> 

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template< size_t Step , class Algebra , class Operations >
struct adams_moulton_call_algebra;

template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 1 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage& /* steps */ , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each3( out , in , dxdt , typename Operations::template scale_sum2< value_type , Time >( 1.0 , dt * coef[0] ) );
    }
};


template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 2 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each4( out , in , dxdt , steps[0].m_v ,
                typename Operations::template scale_sum3< value_type , Time , Time >( 1.0 , dt * coef[0] , dt * coef[1] ) );
    }
};


template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 3 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each5( out , in , dxdt , steps[0].m_v , steps[1].m_v ,
                typename Operations::template scale_sum4< value_type , Time , Time >( 1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] ) );
    }
};


template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 4 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each6( out , in , dxdt , steps[0].m_v , steps[1].m_v , steps[2].m_v ,
                typename Operations::template scale_sum5< value_type , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] ) );
    }
};


template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 5 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each7( out , in , dxdt , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v ,
                typename Operations::template scale_sum6< value_type , Time , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] ) );
    }
};


template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 6 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each8( out , in , dxdt , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v , steps[4].m_v ,
                typename Operations::template scale_sum7< value_type , Time , Time , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] , dt * coef[5] ) );
    }
};


template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 7 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each9( out , in , dxdt , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v , steps[4].m_v , steps[5].m_v ,
                typename Operations::template scale_sum8< value_type , Time , Time , Time , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] , dt * coef[5] , dt * coef[6] ) );
    }
};


template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 8 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each10( out , in , dxdt , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v , steps[4].m_v , steps[5].m_v , steps[6].m_v ,
                typename Operations::template scale_sum9< value_type , Time , Time , Time , Time , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] , dt * coef[5] , dt * coef[6] , dt * coef[7] ) );
    }
};




} // detail
} // odeint
} // numeric
} // boost



#endif // BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_MOULTON_CALL_ALGEBRA_HPP_INCLUDED

/* adams_moulton_call_algebra.hpp
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
*/