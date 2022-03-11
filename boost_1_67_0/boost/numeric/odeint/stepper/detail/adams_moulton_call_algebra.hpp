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