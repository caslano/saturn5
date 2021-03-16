/*
 [auto_generated]
 boost/numeric/odeint/util/state_wrapper.hpp

 [begin_description]
 State wrapper for the state type in all stepper. The state wrappers are responsible for construction,
 destruction, copying construction, assignment and resizing.
 [end_description]

 Copyright 2011-2012 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED


#include <boost/type_traits/integral_constant.hpp>

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>


namespace boost {
namespace numeric {
namespace odeint {


template< class V , class Enabler = void >
struct state_wrapper
{
    typedef state_wrapper< V > state_wrapper_type;

    V m_v;
};


}
}
}



#endif // BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED

/* state_wrapper.hpp
bgb4TC2WvBzkm+eGxllV9Rzbh/dvkoeKr/UNTe46cJ2Phzues4JQWdn+3TJ9x0fFQ0zUY2lJ6P3m1/LdAr9viet3ak3u/bIb2sj71u6X3Rjxv+O7KVzG2/S+yM9j0XxRk4iSbcZV7iJO9DYvEksn6TttN/vaLBlTWq5RdIOBssJC1x764klKCjbdwvbtVtYd7Z8LXMFjYQ/9dTrQWq5ze8Rvb2VuPPKvhXcy7rqI56eM3N3zg1Tsyw70dA+Ftz4=
*/