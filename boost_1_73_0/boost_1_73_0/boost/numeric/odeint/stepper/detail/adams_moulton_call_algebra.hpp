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
vNeFrTyNrUl4zIB5yl+UnCpxsXVUt5zHWKpM7we8JmttFHLCfmNhprttYJcAWWnIPGtZR0VhQti8tGKKe3BANI5IEALZdnq7DvHoWm22972dQUelBePuaBx3h8P4chSddfmnH+yt5ka0M12iaj10TC7MpEYhTv3LXg8ODxuDF0l5GMhoV2IjLc1rswevU3htiVUYPGxd9KOiQic1/LKWH7cb5k/Au7wG2INUUy/bXgMKjxR7FPj27j50tiiEuqvkoiR7ywM1tb6TzMQ3gp2jNCmnvVGGbKbU/ZadzMrvuNiBhU5EUU97gzxlBTmZLZ5UutXIFMJvy+wulOTFh7D9bqEhOUqEeuOglo6Wh7RHZQG6cjX8czp7Z+3/TenhcDDcY15KPyD2E7WzpNAWF3E/X3p/Rp8Gw/hDdLIsPy72pUA7hMgqv1hcDauGCaXSwnc02qdm45cT4/0dTws9EQXRk67FOzs+6w0+RL046vXasLHa7S9yfoKyyNlqh/47hk19CmAPpIVKF9XoJw79K0Zh7xq/Tflt8PzP6T4wekL2YTxJgUJVZeu/xoHKH+F16+Kt7cPwibTo6Iz2uQi92IOLcXx50RtEdEK967X3H0PcoJkQh3UAX7rDD4NR9xGCLTGhkx8c1Q66tRSGvRD4
*/