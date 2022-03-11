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