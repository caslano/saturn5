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
tEi8clL96GZCmYlVCOUjLQsqcQd2prSjVDoUWqByB9Tt8oQD5F1CBSLOsRKQpJADAyhi2ZBYnuCVeXyfKoZLKHWyGIfgN5xZktKoXXaYcXwnooCziJJ+NaecBWmKSSVlQBVlGKVsxuW6ztIKevJJBKGaah4sdJA2jhC5cRxkw5mfeuFZmWnIl3FnFfk0WeD7NJK05MgBYAjQQ01TIiPvLmU17NID6RFVdolUY1XZtwGZKoj4V+45FJDf9n/Twa1ChlkKpKk6Aau8e56TGkW8rlkIamxJbKk9TQzGUoTmMhrlI/RbDBYbwy9+wH0imS5kaFdR+AAMZRZB5f17JlD9AszBYlj2IIugOE1ZBW9xE3jfJv1geWK+h8Hwwae9B/rVtcpCdO1wO4UWpliotKrQkgXkiddtNPq1+ry1NjfV5QpNXkvVqaAOshOarAjqtwzrtw7st0pMKbg/XpaCYsBaMVZEwQ1D/I2RsB4LvyHQNyhEy/ZVoX7DYP/PCKlD/hohbwr617jla8FbGq4OqNRywSAM4QTDIHhkltJTdELfm2GXkLlZaGN/0fK9dCEJL+eVCFNqs9QiDMZlqkwlJfXgAm5ho29upRjToWaCYL4AI7YEgASGbqDBsElNyxVRbd2aKbKHYkhKlFB1U3Uw
*/