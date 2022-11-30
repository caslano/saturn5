// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_ROW2_HPP
#define BOOST_MSM_ROW2_HPP

#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/msm/back/common_types.hpp>
#include <boost/msm/row_tags.hpp>
#include <boost/msm/front/detail/row2_helper.hpp>

namespace boost { namespace msm { namespace front
{
    template<
        typename T1
        , class Event
        , typename T2
    >
    struct _row2
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
        , typename CalledForAction
        , void (CalledForAction::*action)(Event const&)
    >
    struct a_row2
    {
        typedef a_row_tag row_type_tag;
        typedef T1 Source;
        typedef T2 Target;
        typedef Event Evt;
        template <class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt, 
                                AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            ::boost::msm::front::detail::row2_action_helper<CalledForAction,Event,action>::template call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForAction,FSM>::type::value>());
            return ::boost::msm::back::HANDLED_TRUE;
        }
    };

    template<
        typename T1
        , class Event
        , typename T2
        , typename CalledForAction
        , void (CalledForAction::*action)(Event const&)
        , typename CalledForGuard
        , bool (CalledForGuard::*guard)(Event const&)
    >
    struct row2
    {
        typedef row_tag row_type_tag;
        typedef T1 Source;
        typedef T2 Target;
        typedef Event Evt;
        template <class FSM,class SourceState,class TargetState, class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt, 
                                AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            ::boost::msm::front::detail::row2_action_helper<CalledForAction,Event,action>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForAction,FSM>::type::value>());
            return ::boost::msm::back::HANDLED_TRUE;
        }
        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt,
                               AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            return ::boost::msm::front::detail::row2_guard_helper<CalledForGuard,Event,guard>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForGuard,FSM>::type::value>());
        }
    };
    template<
        typename T1
        , class Event
        , typename T2
        , typename CalledForGuard
        , bool (CalledForGuard::*guard)(Event const&)
    >
    struct g_row2
    {
        typedef g_row_tag row_type_tag;
        typedef T1 Source;
        typedef T2 Target;
        typedef Event Evt;
        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt,
                               AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            return ::boost::msm::front::detail::row2_guard_helper<CalledForGuard,Event,guard>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForGuard,FSM>::type::value>());
        }
    };
    // internal transitions
    template<
        typename T1
        , class Event
        , typename CalledForAction
        , void (CalledForAction::*action)(Event const&)
    >
    struct a_irow2
    {
        typedef a_irow_tag row_type_tag;
        typedef T1 Source;
        typedef T1 Target;
        typedef Event Evt;
        template <class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt, 
                                AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            ::boost::msm::front::detail::row2_action_helper<CalledForAction,Event,action>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForAction,FSM>::type::value>());
            return ::boost::msm::back::HANDLED_TRUE;
        }
    };

    template<
        typename T1
        , class Event
        , typename CalledForAction
        , void (CalledForAction::*action)(Event const&)
        , typename CalledForGuard
        , bool (CalledForGuard::*guard)(Event const&)
    >
    struct irow2
    {
        typedef irow_tag row_type_tag;
        typedef T1 Source;
        typedef T1 Target;
        typedef Event Evt;
        template <class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt, 
                                AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            ::boost::msm::front::detail::row2_action_helper<CalledForAction,Event,action>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForAction,FSM>::type::value>());
            return ::boost::msm::back::HANDLED_TRUE;
        }
        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt,
                               AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            return ::boost::msm::front::detail::row2_guard_helper<CalledForGuard,Event,guard>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForGuard,FSM>::type::value>());
        }
    };
    template<
        typename T1
        , class Event
        , typename CalledForGuard
        , bool (CalledForGuard::*guard)(Event const&)
    >
    struct g_irow2
    {
        typedef g_irow_tag row_type_tag;
        typedef T1 Source;
        typedef T1 Target;
        typedef Event Evt;
        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt,
                               AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            return ::boost::msm::front::detail::row2_guard_helper<CalledForGuard,Event,guard>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForGuard,FSM>::type::value>());
        }
    };

}}}

#endif //BOOST_MSM_ROW2_HPP


/* row2.hpp
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
*/