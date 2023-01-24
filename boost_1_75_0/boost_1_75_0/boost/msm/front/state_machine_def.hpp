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
5rZQvoZ1tcAd+xHrPFMGRUcYa5YzlQi5bOAlgfY8OTBpDns9PWkjvOuIbbuCa0d37Eh6t/i/GK7XNxOAzXEmMGigJSyj5OiZBZ0RMDeqZ0PVy+WGWrGGcDPyOH5hdAs+WjB0kW2Z9iGQ9t8UgYpoMmsR3cAqxzCmG0UEMF3U4llKRQEoYuqIze3Gw9wue+1yt1tT4BQaRGiYyTO2IR5GNQS3cZrYhI3wLZr6bJA2msWotJTGtjixe0SKKcIWI3aPSjFF2aLE7g1TTA2tTU3uNebCsihT4TntuJ24urw2qWytR54X7hH//Hw9lUf8JJPA5sLhTg0zNpy4/hHv4xIXHxAA2njn+22BLiCkFQIkpTioNqH4xltMl3aJMSmZSw5yrzw0vH+Ng/fv2TZ++pdJ/dP769/gkPo3qSBI/6LQZuP9G3suaP9+bs3714BZPJAnKmmfS4edEXtl2fXwSHnrUHpUNY16lElBl9QjP/05fDZof/oH6c9Q6s89IfVncOD+eODvvuD9+baVH/zlEP56tvGDv1dbhdK7lVNDxd/nZ4LTf6vA45VL4xUZUo9unupnvFTymqdcKiOZ3eKMLLOXhIF7+rxFktm5IMZy4cPPtSQplKvI7Fz27u7eIKelzFuUGsv5SHuU1r2+BGmd0QKl9b1fkrTmjxjaRzBZ1JPNOsrEzLPy5bM3gZiOPrcU3mxKbx5d6vHmDzeRJM/z
*/