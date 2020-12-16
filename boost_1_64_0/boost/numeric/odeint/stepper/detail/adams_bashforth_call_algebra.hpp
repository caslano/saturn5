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
lU7pq3BSXoTzeSHw9C/D96ssoEzZCd8ICuyi3SC1bjdiyzwIu4qSHPMZwE/fAljSB6BihXN1NcA/f4mIfpkAL18F8MVi0tuBsGjm9s17LG8swG3vAJy8DM7E94H8xxFwbiLlhJcQ9rPfwnmCwh4wCs4XRtZHDHxFgxFxyyVwdr8LsHsWfK9TsFeMBeVPFsC3iQT6sCruZfF3FsD36h1wepNA7WfwmRvh3JyNFPpfAeUjP3yrqQyGRjgnRyJ29MsIW9EA8Hcs21AKdstUhM1hRSWT/BN0chi74Vo4trsR0Y0ZXXkUeLs/Zf2y0MNXIuyp3sj8cQOcgtcQNus4ULb8DuDDowBGbIRzNev3TVLZQKKZdyH2MPP9FcH51JfEXyLZyQsQkXQtnM0XUf9kRFR9Buc7qs9LElJccB/p1VOflwJlQzV8a0V9kMprCQhb7WB9kHL/0XCObqM+90JErxfg+2Uywlwfw4ntAvDVdSAQOgzOR4+QP5Zy8D6AAynT10wIq7wXzlyWbcIXcJ76Fs7bfYByFUX89F1wyucjWeqb8B1PQ7LPvqRasIBfdobv8z8itlsenM5UavulcB7LMYCeASn2UNeiTwIsWAffz6kHo3oCZefvyR8bSWglfBd3gxNDJi/XsT7C4fxhuAR69yDtpcVwXn8HTqddcCIvR7LfxbP9UndDjsD3fArbRy6c0DqEpV0Ax1wPZ8lkhBU9A98BFnD3LSzv23C6MGIPpfH2/QAXLWN52ehCSuDsf8sQ0DAr24zuPDg/0FSFsfLuoVxOMEV0Dzi5CulRbWeSaBylUZAKvCoqZs0hUEkYAfACRtx3Mxzdi2y/rK21K+Er+jVQbvmc9qoGvrdIeQILcx6FOPk+tl8aD8eTcH7zA8A5djhTiVfxJ7bfV5FsGo3qkxeSP+rub59HRMND1Gfqxgc0BU/dDp9xPJAnMu0xLxzXJCCX9IZznGo2WIeqrWXxzTQy31+OiEuq4JvOLFVyNZdUumwDvU5TAU4uByjfD991LyDZT34B3zHq81iWKONi4F38JiL2PQcwczqcj9kWTrDk0dlAvpFi6s88Vq2HM6gWzq93kb9ixIZQ6w6xLo8zo8MrWL9sofvIwee/gO+evnDuakIedlpgN/X5daJ4NgBlpER61MkvyqjPzOj5a2hf0uGLor6U6tlMT7C9sWyXsLO5kmGrHwde2WFE9H8CpNbNAxhBK3DNnxF7E1PcRHufwCI88AXr43E4A6jeX86F42P39NxBOCfupvzWsf3OBZV8tto9lL2TBH7HLP9IRcpj2kNr2T5eoj2l7xG284epjp/vYvvdibTvnw9HfQQEEp3wvf4g2xs1bHMRnF5M9kUinHvvo76EAuX4GtqXHCnA3ywa38EEP6bvhBlO2Q9w5n5P+7eI9uAX7JRYAbeOgbM9iv0l5SKR/NTr2N6oAreRq31UmvunIuJrNvGZtKdZV7Dl0QDMZpbn+WjrNtOestH98iVElDO37F5w+nZCxNWs0HGU+CxRtWQo/QdE3LmM5SWTb5H8MvZ0oylJIzWiFyV0/gL2b8xouRMRYynODDbErmT3Szbi+1ndH29H7B+orPOZzK3Cd9H1iD36McDNBD9kxHU1cC4jV6lF8I1l8deQaFfGPv0t8N4zkN6HiDh5guUdTf4Ye/AnCGtMJ7272F9OYf+bAafHTjhvE1lJgs+6CbE6NqtpM+GzxcLZxdzeT4AzfzAL2ET5sRPZsxxhTraZ2QcAbu+qB70ecJ4/Tn3pBOezL0hvPu3V87SnL8PRk/ywH8jfTvL3Est7A8I8CtvvALaPW2ivJgLc8ku2j/UAf0ZJWo/DdzerIvcbJLvcCnDI1/A=
*/