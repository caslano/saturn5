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
I4uKgY5g/NnkfsioRxPjg/cd/VMH9sUrITcH0B3Aa8zpqyFPW8vZ8ET/c+O7sQSEf237v7HNtVMrh3nOVfxTPm9GdUJO4ZzCf2Ft0Bz2aDeft8t9h3lt84v/jT3C+wkufNkYS1bOmSM3peLiu96jnLEduH9AvXrMepcGOeTjdSHjxnlRA0fG5fn6/8q6YmKfTuHL+b/hkkoOj/niV/87f4R4tLuLXDbOuxLDus8l4pwtsQRc8oqc+E2pyXcN/gjOXR8r5g2BrLmSsp37WJZZgxzzp3WsSWqmvR4whccxkxnmCIaZUsggGBHX88H020tDmi2eswamYAovYCawpdZhZ3qMtpUWX8jy0FYqvEjK8m2lCY/TtlIdcjkcsDz15bClMIY9TsqHKSxm4y/A3Bh6ZLpRXkP/12Xkd3u0pDY5X5lv0ooWrR+JN58mnijYB7Ldm7AtR6sNyMA8fF4sp8T12ivUf41lxfMiXa7r5nXaiSSQ6dSxvfDXywQsukDOaz6D9g/79ocXNmxjcr45XeW9K03U2XeknO9iRh/m/97egGgmwaI86z8C4807R/ju7Puz5Bnpm/k/x1/4sc+sdk+ZaVcX9mEgZzcpn72qe0wWBC1o9c453wj6qkWfQ1DubMdhtKWA6w57S/KNkD1fbrzitARk7trgcxHJTyQzLjbKe+S+vYLH4u4M6PwOy83YfwY2ynvld+vCPNnqt29xM7HW813HoGq5bos/hawf1M8AcxiP0fWT/MyXo1ClP9NjDkfjmfi5x6h4Cr/w5TIe2HaS0XrQh778UnBaD/roD34lOa0HG0Ie6gHmsJLhuk3RL/8acjQt+Hf2IFP6497o4nWAh142YyuVqeibk9ssd28BA+ljHnI5MBjN4Hfk30ffo1y8HeQq7tLDWNbNiXviJBgsBGJN0f3e7IAEv4FveFAPa4qPgswt+4m9A4+GjJf85J0BLB8v9/XG7bDwnrGM3i6Wb+rI7y41WB+QMpcarH+8V8pcbJQWtHvIzXvIrDP194nvQXy7O0IWxLf9ISlD7iHflXJOT4L8/3ssz95gTpFH8T3M/56QIf/w311OyHR8i5DTu84ivsIB8T2Ib3RBIQviq19YynT+Uynn9EC+Yc+wNmaq5m6l3uqKeyUX+fkEy+3pdzPOszz544V8uTvUivi3Lu3LrcubdemzIvxBds/3nVB3n2eZczqYyNkfg7ghN5HzGjHihtxGnnAbLVzZls8c3VXTWl1qlqlIkbZAdpRkmN9e1ZctrdJ+KNvE+/DLTPiMuSKv3bMM4r+GzwxpLy/sr0B2lmR8NxRkdzlaxp36p3GGIZC7u2DPNYeUCnHWYeIGmgNGHPQg4NyiR5PvjJZy3M/f5HtnWe7sxWy9Y1bcMbetmKNgroN92WDc2vG6udPy1KydPfC6/mFw9hCMNSs77Z7YU3OLPKZ5dFaecb0OOLnueoqYo8jfbcGYomumD3DPexGDfvjwoYy522wF7yyhv72JJzNlC9km/069r7QtZNlMvLNsHiGuHK/McR94U83QqRIuq5tp+XC1a+Yo3OcJxmUMdZvcnGWmhGJp2AwYpAHnSZQcacB6kSgjua9qR/7W6R36t9tmsvnpRvNYhR9F4PFKyf3zn4t3N/VqtvCUJycX5sqTd7feMISv5MEendeHcrsc3Fnqdftyj04et7rakVw9ztE8u7u+TCDypdNl8tXHvEGH04+lK3mD5mLp2opzSBf2LAzBUVc+VhO3pmHvV0CYuyfHLF5xHfRbeO21C91ZAocXWd3RVr6PLYfpE4M5S1sz0ke048nt7rolWt9oLTGzd0oxLho+O7t5X82sds0ZH7Ox1tjSZjedXTBBuXU=
*/