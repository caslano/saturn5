// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_INTERNAL_ROW_HPP
#define BOOST_MSM_INTERNAL_ROW_HPP

#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/msm/back/common_types.hpp>
#include <boost/msm/row_tags.hpp>
#include <boost/msm/front/detail/row2_helper.hpp>

namespace boost { namespace msm { namespace front
{
    template<
        class Event
        , typename CalledForAction
        , void (CalledForAction::*action)(Event const&)
    >
    struct a_internal
    {
        typedef sm_a_i_row_tag row_type_tag;
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
        class Event
        , typename CalledForAction
        , void (CalledForAction::*action)(Event const&)
        , typename CalledForGuard
        , bool (CalledForGuard::*guard)(Event const&)
    >
    struct internal
    {
        typedef sm_i_row_tag row_type_tag;
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
        class Event
        , typename CalledForGuard
        , bool (CalledForGuard::*guard)(Event const&)
    >
    struct g_internal
    {
        typedef sm_g_i_row_tag row_type_tag;
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
    template<
        class Event
    >
    struct _internal
    {
        typedef sm__i_row_tag row_type_tag;
        typedef Event Evt;
    };
}}}

#endif //BOOST_MSM_INTERNAL_ROW_HPP


/* internal_row.hpp
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
*/