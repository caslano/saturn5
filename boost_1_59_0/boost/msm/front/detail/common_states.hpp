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
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
*/