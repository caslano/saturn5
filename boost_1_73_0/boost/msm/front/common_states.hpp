// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_COMMON_STATES_H
#define BOOST_MSM_FRONT_COMMON_STATES_H

#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/msm/front/detail/common_states.hpp>

namespace boost { namespace msm { namespace front
{
// default base: non-polymorphic, not visitable
struct default_base_state 
{
    ~default_base_state(){}
};
// default polymorphic base state. Derive all states from it to get polymorphic behavior
struct polymorphic_state
{
    virtual ~polymorphic_state() {}
};

}}}

#endif //BOOST_MSM_FRONT_COMMON_STATES_H


/* common_states.hpp
rTTDubrfcUwthzYxafz0do7jWi3YT9QyfPn2DoNWqW+uQ9VDddhxVLxyB4ejZjzOiz3z1j/FYYoFFXuor0/voQ44efpJQsV2fvE87G9kdP7uKLiL2HMM3nsnwaH+lsc/r3ja+CQIvnTntF6RW+Y8ndb9HDW+yzHcenJ6MvM2hViBGPcaIi9S7uauMN99b4fqoE1ggfrgU9X0VTjPDDjHxNOHnhn8tTXOscv77C208NmL7RFx
*/