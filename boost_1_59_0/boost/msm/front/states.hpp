// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_STATES_H
#define BOOST_MSM_FRONT_STATES_H

#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/msm/front/common_states.hpp>
#include <boost/msm/row_tags.hpp>
#include <boost/msm/back/metafunctions.hpp>

namespace boost { namespace msm { namespace front
{

struct no_sm_ptr 
{
    // tags
    typedef ::boost::mpl::bool_<false>   needs_sm;
};
struct sm_ptr 
{
    // tags
    typedef ::boost::mpl::bool_<true>    needs_sm;
};
// kept for backward compatibility
struct NoSMPtr 
{
    // tags
    typedef ::boost::mpl::bool_<false>   needs_sm;
};
struct SMPtr 
{
    // tags
    typedef ::boost::mpl::bool_<true>    needs_sm;
};

// provides the typedefs and interface. Concrete states derive from it.
// template argument: pointer-to-fsm policy
template<class BASE = default_base_state,class SMPtrPolicy = no_sm_ptr>
struct state :  public boost::msm::front::detail::state_base<BASE>, SMPtrPolicy
{
    // tags
    // default: no flag
    typedef ::boost::mpl::vector0<>       flag_list;
    typedef ::boost::mpl::vector0<>       internal_flag_list;
    //default: no deferred events
    typedef ::boost::mpl::vector0<>       deferred_events;
};

// terminate state simply defines the TerminateFlag flag
// template argument: pointer-to-fsm policy
template<class BASE = default_base_state,class SMPtrPolicy = no_sm_ptr>
struct terminate_state : public boost::msm::front::detail::state_base<BASE>, SMPtrPolicy
{
    // tags
    typedef ::boost::mpl::vector0<>                               flag_list;
    typedef ::boost::mpl::vector< boost::msm::TerminateFlag>      internal_flag_list;
    //default: no deferred events
    typedef ::boost::mpl::vector0<>                               deferred_events;
};

// terminate state simply defines the InterruptedFlag and EndInterruptFlag<EndInterruptEvent> flags
// template argument: event which ends the interrupt
// template argument: pointer-to-fsm policy
template <class EndInterruptEvent,class BASE = default_base_state,class SMPtrPolicy = no_sm_ptr>
struct interrupt_state : public boost::msm::front::detail::state_base<BASE>, SMPtrPolicy
{
    // tags
    typedef ::boost::mpl::vector0<>                           flag_list;
    typedef typename boost::msm::back::build_interrupt_state_flag_list<
        typename boost::msm::back::get_interrupt_events<EndInterruptEvent>::type
    >::type internal_flag_list; 

    //default: no deferred events
    typedef ::boost::mpl::vector0<>                           deferred_events;
};

// not a state but a bunch of extra typedefs to handle direct entry into a composite state. To be derived from
// template argument: zone index of this state
template <int ZoneIndex=-1>
struct explicit_entry 
{
    typedef int explicit_entry_state;
    enum {zone_index=ZoneIndex};
};

// to be derived from. Makes a type an entry (pseudo) state. Actually an almost full-fledged state
// template argument: containing composite
// template argument: zone index of this state
// template argument: pointer-to-fsm policy
template<int ZoneIndex=-1,class BASE = default_base_state,class SMPtrPolicy = no_sm_ptr>
struct entry_pseudo_state
    :  public boost::msm::front::detail::state_base<BASE>,SMPtrPolicy
{
    // tags
    typedef int                          pseudo_entry;
    enum {zone_index=ZoneIndex};
    typedef int explicit_entry_state;
    // default: no flag
    typedef ::boost::mpl::vector0<>       flag_list;
    typedef ::boost::mpl::vector0<>       internal_flag_list;
    //default: no deferred events
    typedef ::boost::mpl::vector0<>       deferred_events;
};

// to be derived from. Makes a state an exit (pseudo) state. Actually an almost full-fledged state
// template argument: event to forward
// template argument: pointer-to-fsm policy
template<class Event,class BASE = default_base_state,class SMPtrPolicy = no_sm_ptr>
struct exit_pseudo_state : public boost::msm::front::detail::state_base<BASE> , SMPtrPolicy
{
    typedef Event       event;
    typedef BASE        Base;
    typedef SMPtrPolicy PtrPolicy;
    typedef int         pseudo_exit;

    // default: no flag
    typedef ::boost::mpl::vector0<>  flag_list;
    typedef ::boost::mpl::vector0<>  internal_flag_list;
    //default: no deferred events
    typedef ::boost::mpl::vector0<>  deferred_events;
};

}}}

#endif //BOOST_MSM_FRONT_STATES_H


/* states.hpp
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
*/