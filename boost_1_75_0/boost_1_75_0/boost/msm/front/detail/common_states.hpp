// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_DETAILS_COMMON_STATES_H
#define BOOST_MSM_FRONT_DETAILS_COMMON_STATES_H

#include <boost/mpl/int.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace msm { namespace front {namespace detail
{
template <class Attributes= ::boost::fusion::map<> >
struct inherit_attributes
{
    inherit_attributes():m_attributes(){}
    inherit_attributes(Attributes const& the_attributes):m_attributes(the_attributes){}
    // on the fly attribute creation capability
    typedef Attributes      attributes_type;
    template <class Index>
    typename ::boost::fusion::result_of::at_key<attributes_type, 
                                                Index>::type
    get_attribute(Index const&) 
    {
        return ::boost::fusion::at_key<Index>(m_attributes);
    }
    
    template <class Index>
    typename ::boost::add_const<
        typename ::boost::fusion::result_of::at_key<attributes_type,
                                                    Index>::type>::type
    get_attribute(Index const&)const 
    {
        return const_cast< 
            typename ::boost::add_const< 
                typename ::boost::fusion::result_of::at_key< attributes_type,
                                                             Index >::type>::type>
                                (::boost::fusion::at_key<Index>(m_attributes));
    }

private:
    // attributes
    Attributes m_attributes;
};

// the interface for all states. Defines entry and exit functions. Overwrite to implement for any state needing it.
template<class USERBASE,class Attributes= ::boost::fusion::map<> >
struct state_base : public inherit_attributes<Attributes>, USERBASE
{
    typedef USERBASE        user_state_base;
    typedef Attributes      attributes_type;

    // empty implementation for the states not wishing to define an entry condition
    // will not be called polymorphic way
    template <class Event,class FSM>
    void on_entry(Event const& ,FSM&){}
    template <class Event,class FSM>
    void on_exit(Event const&,FSM& ){}
    // default (empty) transition table;
    typedef ::boost::mpl::vector0<>  internal_transition_table;
    typedef ::boost::mpl::vector0<>  transition_table;
};

}}}}

#endif //BOOST_MSM_FRONT_DETAILS_COMMON_STATES_H


/* common_states.hpp
luRzqROSMP+phoR5a8jzZn+DkvewIyVgUjIGxFsc0R/eqdc4l8yqdYMEPwuJzE5BfusILTmRk+G/RO4VHgpvWNrlS/ncIHzG0i7PHTuUfxBSMDKr7S60JFF5MEQUQ2gOiu2UCA0qile11J8SHgmQiQ5+Ebd/RqqKc3bBlZhK2CRrKH6a3d6Q1i5LK33dLA4ScA9r73BsdSh+fC7PNMf0h3NMS6Ym4ENSrUdKWc1amMWLTc6Qq3wa3ZnJ0EprLT0qZbU2KO/zCBw+8Wngjp1ynR4HyaiuhWlQIMMX3BuqPq6FACP58xliedIOWDs/Cx/8kncASe2G60DHqdJHGWS88c9LtLC3jaQC8+X8VR4qcAlXgXGTSAWWkQpks7HxyfKMjNSgKYK1xRTg4zo6PgzH5WC/O2+KQNXYT4cHgT/waBQdh0ZRoJXsOxjyX/D/lPr4DmL8+A5yFd+Bb46M55k4U3JkzGK/pBwZWezceUMTzD/xKAi9q5Mj4wSTDFVLG4aUI+Mn9qxHjoyl7IJzWmOqXw4iBnNkfHWmXig5Mto86JPD4ehgdQ6H7sPY7Ox0T2kLdD6fnU2b6DM784jlWzA4aCxfbqBYvjMn6gWJ5Xu8md9Yvr4ar1g+c7NQpPcT+d6xfD+EedSq8lnHGaz0LsA6Tvm1Qddxzviui8GIOssmXcp6rgBrurhyY8/mSzYPZElLNh2z5CWb54aEvGSz
*/