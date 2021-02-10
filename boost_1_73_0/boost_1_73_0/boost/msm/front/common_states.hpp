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
NxWjOmqAa3fgwwsjH4FdpYUs4EkgShRCC5ZBxVUpC8WRyWmoqNKpKHySM5HBTqanltFrYkATmeesSBsjI8dpL8JtvNyM2sbBJoxiZ+gNwLLMaatKSo0KiShNFV/4P5aXGbeR4xmxr3CteJHy6nX6CEesEWHSuHetHWcV7vP5n6E96e0tz+5+e1hjXjGVWQKRMVho9OIPl+fe1V39wSuxP0HKNAO210iFPQHzEcGBKdhxXsCNOkh9Q+hjjUWKspJaJjLzyWyxCgEra725Z2jv+t6v4o6NjeG7dqd7kEqPu+7A7uDTxUApKz2+NAgDpqTx5N2KMIvvb+Rst8g6WK5gHoXrEX3bI79Foukmhjgc0Xd7jICvQRy0yPf7ZWwu8VoOPZaZZOmrS7YN5DlOnUsTnOuf9h9QSwMECgAAAAgALWdKUqnzZLcUAwAAMQUAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q5NDhVVAUAAbZIJGC1VF1v4jgUfY/U/3DVCmlXmhBIAgyjgLZlgFKlwAQoLTurynHMkmliZ20Hyvz6vQbastp9XSWyY9+Pc33OdQLNlKZEsa4VpHwtcHph+52Qiepas/v51Jpdz8LDANeL+S1MzOha0aDntxu+mZstv23mVtP9
*/