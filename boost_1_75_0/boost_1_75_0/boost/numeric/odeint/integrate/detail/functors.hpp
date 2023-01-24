/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/functors.hpp

 [begin_description]
 some functors for the iterator based integrate routines
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2009-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_FUNCTORS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_FUNCTORS_HPP_INCLUDED

#include <utility>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {


template< class Observer >
struct obs_caller {

    size_t &m_n;
    Observer m_obs;

    obs_caller( size_t &m , Observer &obs ) : m_n(m) , m_obs( obs ) {}

    template< class State , class Time >
    void operator()( std::pair< const State & , const Time & > x )
    {
        typedef typename odeint::unwrap_reference< Observer >::type observer_type;
        observer_type &obs = m_obs;
        obs( x.first , x.second );
        m_n++;
    }
};

template< class Observer , class Time >
struct obs_caller_time {

    Time &m_t;
    Observer m_obs;

    obs_caller_time( Time &t , Observer &obs ) : m_t(t) , m_obs( obs ) {}

    template< class State >
    void operator()( std::pair< const State & , const Time & > x )
    {
        typedef typename odeint::unwrap_reference< Observer >::type observer_type;
        observer_type &obs = m_obs;
        obs( x.first , x.second );
        m_t = x.second;
    }
};

} // namespace detail
} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_FUNCTORS_HPP_INCLUDED

/* functors.hpp
wtvqCGwnbYLFMb1Xgi2o/IjeGLo+cT2niFpBKImbF3aslbsK8CspdDgixC2R7fFiwtVGCsmRhrXb1VhO8TYgsYiLW2UMQDcjCgOfC/qmTrKZ7W7/Bq4U1bvgyjCki75LSWNCRL2S9wW92KkgMwM3bgG8N80GbB6+3l+aKivpSIRpW+DEjCGMPEwveuUHFJh5e4grkWAxhDWwANvuvcR+xFJASsR5pdKwLFg3UjPRJpJRQUlZa0LNJ2YMGKnPnPw8sUXdIF5Nsn69wD9s4p53RflG3fw2YOfhOS/YHI2TTvNLinbYkwxL1IDZVw5unFQyrk0Me3Ly7xL+O2sHw/t5TxaiFweHWS9eyZeQC+whChClD2xNk6wfhm+u0tTTb9wOSBrXLz58zzpv1tU3laMhy3tkB8X6Z70bGyzpcoz4dABxr2LpsOPX/u1nu3+ojt15FdrnPE17VF07sAaZV8+9MPEr50UX9107IeB2Unr8BQa6sg70IdT6uFgOaffaMPjTx7q4ho5dJItScH/3hHuTvWw8M13J8Vx08of6vDOxes3Dv3prDQ2DB2t7rkNjW7juZ/3hYu5g4x8Slf4rLdyshqSMAzuSSE8uqw8tCrO9eaGFrMFaCxrn50a5Zbz5sVjmSyrQInrUx+UT1Qdc9yEYjy5jZx1rCkiuvBtu2pIrOHMh9lLWr5ZVt0WvxttPVQmx/jHe9/8pEHRKg2v7
*/