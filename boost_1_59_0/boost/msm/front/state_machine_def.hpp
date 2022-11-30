// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_STATEMACHINE_DEF_H
#define BOOST_MSM_FRONT_STATEMACHINE_DEF_H

#include <exception>
#include <boost/assert.hpp>

#include <boost/mpl/vector.hpp>

#include <boost/msm/row_tags.hpp>
#include <boost/msm/back/common_types.hpp>
#include <boost/msm/front/states.hpp>
#include <boost/msm/front/completion_event.hpp>
#include <boost/msm/front/common_states.hpp>

namespace boost { namespace msm { namespace front
{

template<class Derived,class BaseState = default_base_state>
struct state_machine_def :  public boost::msm::front::detail::state_base<BaseState>
{
    // tags
    // default: no flag
    typedef ::boost::mpl::vector0<>               flag_list;
    typedef ::boost::mpl::vector0<>               internal_flag_list;
    //default: no deferred events
    typedef ::boost::mpl::vector0<>               deferred_events;
    // customization (message queue, exceptions)
    typedef ::boost::mpl::vector0<>               configuration;

    typedef BaseState                             BaseAllStates;
    template<
        typename T1
        , class Event
        , typename T2
        , void (Derived::*action)(Event const&)
    >
    struct a_row
    {
        typedef a_row_tag row_type_tag;
        typedef T1 Source;
        typedef T2 Target;
        typedef Event Evt;
        template <class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState&,TargetState&, AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            (fsm.*action)(evt);
            return ::boost::msm::back::HANDLED_TRUE;
        }
    };

    template<
        typename T1
        , class Event
        , typename T2
    >
    struct _row
    {
        typedef _row_tag row_type_tag;
        typedef T1 Source;
        typedef T2 Target;
        typedef Event Evt;
    };

    template<
        typename T1
        , class Event
        , typename T2
        , void (Derived::*action)(Event const&)
        , bool (Derived::*guard)(Event const&) 
    >
    struct row
    {
        typedef row_tag row_type_tag;
        typedef T1 Source;
        typedef T2 Target;
        typedef Event Evt;
        template <class FSM,class SourceState,class TargetState, class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState&,TargetState&,AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            (fsm.*action)(evt);
            return ::boost::msm::back::HANDLED_TRUE;
        }
        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState&,TargetState&,AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            return (fsm.*guard)(evt);
        }
    };
    template<
        typename T1
        , class Event
        , typename T2
        , bool (Derived::*guard)(Event const&) 
    >
    struct g_row
    {
        typedef g_row_tag row_type_tag;
        typedef T1 Source;
        typedef T2 Target;
        typedef Event Evt;
        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState&,TargetState&,AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            return (fsm.*guard)(evt);
        }
    };
    // internal transitions
    template<
        typename T1
        , class Event
        , void (Derived::*action)(Event const&)
    >
    struct a_irow
    {
        typedef a_irow_tag row_type_tag;
        typedef T1 Source;
        typedef T1 Target;
        typedef Event Evt;
        template <class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState&,TargetState&,AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            (fsm.*action)(evt);
            return ::boost::msm::back::HANDLED_TRUE;
        }
    };

    template<
        typename T1
        , class Event
        , void (Derived::*action)(Event const&)
        , bool (Derived::*guard)(Event const&) 
    >
    struct irow
    {
        typedef irow_tag row_type_tag;
        typedef T1 Source;
        typedef T1 Target;
        typedef Event Evt;
        template <class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState&,TargetState&,AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            (fsm.*action)(evt);
            return ::boost::msm::back::HANDLED_TRUE;
        }
        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState&,TargetState&,AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            return (fsm.*guard)(evt);
        }
    };
    template<
        typename T1
        , class Event
        , bool (Derived::*guard)(Event const&) 
    >
    struct g_irow
    {
        typedef g_irow_tag row_type_tag;
        typedef T1 Source;
        typedef T1 Target;
        typedef Event Evt;
        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState&,TargetState&,AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            return (fsm.*guard)(evt);
        }
    };
    // internal row withou action or guard. Does nothing except forcing the event to be ignored.
    template<
        typename T1
        , class Event
    >
    struct _irow
    {
        typedef _irow_tag row_type_tag;
        typedef T1 Source;
        typedef T1 Target;
        typedef Event Evt;
    };
protected:
    // Default no-transition handler. Can be replaced in the Derived SM class.
    template <class FSM,class Event>
    void no_transition(Event const& ,FSM&, int )
    {
        BOOST_ASSERT(false);
    }
    // default exception handler. Can be replaced in the Derived SM class.
    template <class FSM,class Event>
    void exception_caught (Event const&,FSM&,std::exception& )
    {
        BOOST_ASSERT(false);
    }
};


} } }// boost::msm::front
#endif //BOOST_MSM_FRONT_STATEMACHINE_DEF_H


/* state_machine_def.hpp
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
*/