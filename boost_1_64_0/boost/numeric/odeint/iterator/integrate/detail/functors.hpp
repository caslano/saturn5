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
SGe0PSjUOijSxQ5PTbrGt9ezdr9zSoCQ8eqM5JyT0CuJwS6gcoF2ECTTVtqC5sRCdu64GQCsQrPRkTAxLop3ahgDs+UYzykKofICTkN4Z8yfCFUZTD6UEGv8/V51ujPIjC4vQOFhMqfnvhzTSVVIPPFJnYlRiX506VSzs5dKenEbR8ODirfqu8uf8pkk+07v6rUkm7d2zoYEVTop1wY87dKP/cFPzRZO4V2ULRkxLyWJZfNXZraRyL9QDtyHi+qCbGjwRm4bA0ZOUmy7GlN3+qduRxKsYSWpAORk7FcWuxDxqZCQ6hvLtyCd7Klg16BC452EH1a3RMI/4fxrdvcRu1WTT4eka9o436mRzzAbM2VFxsS8wYH1pGcTnF4iVFzjTYOnSfueNyTZtoq6HH002t/Qkp9bThDQDXr8/QlBppwdxHV9hnxkrzRwav+hCHQ3oTSR3G4Tlqvf4TgwcWZMPnkMrTFcJCIJVYtokJUVkO4V9RxbCXtMGkTOWmGOPMLXse3laE/jTXZBRSOegDNJvEyIff5xJAmKJKdySpCYdeLrMXI3f/0/n4sGtw==
*/