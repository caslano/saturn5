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