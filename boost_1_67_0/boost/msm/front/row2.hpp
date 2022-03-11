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