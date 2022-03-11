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