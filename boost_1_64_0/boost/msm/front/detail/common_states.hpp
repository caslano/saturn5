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
PFzjEvRIdYDCXw0JN3O/kJIK4/TivdJM8tLq1ag1NjNfl/wi1XyDcJSjMdhKrCTf+DnS2fasbRV8rCJm5LBqAP03kkh8Rt8AfIchFNuriFD84Sl/pQZWn6HHzUQHoDz2g+mRPMr/Vlt98I2MziU96+HrBzuvoDV+I2TiTAmrE7jn0z1A0dNQZeKKf/kYRLqB2ZiiBB2HI6qruWk3Ay+vgWh7wDnbJOM8YJzGhrxHFkpmhxRXK4aMyKVfLk9sn7SpmAm0+F5AExjJHi7b4eaa7XDf9TVD+8RU8H3r8QQOWihXPsZHIKRSkHM1dJHFck6/2eH8CnCebM+gRIgRheseNa3+Nb2YsgAAS5TBEAEv90enD3HhJP7+zLlX4kEDyU8crYvNb7f+rDzSg9TfjofnfPq1fGfIMo+r1saYk3FYs8Zw2QVeoJ3gy+fXHG3HgLKi4iBuiv8mtmjX0X1J1eBP6hQ6il0TXi1f0x5WdoXYN0af+PivsZn1m7Y3U1OJATKmFD2Z3wCDK+KlrODnaphWlSJ3dzLrM7m8WYYISTg4x3VXCXPmiNGk3TAoQQ==
*/