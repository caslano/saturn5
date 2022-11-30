// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_ROW2_HELPER_HPP
#define BOOST_MSM_ROW2_HELPER_HPP

#include <boost/mpl/bool.hpp>
#include <boost/fusion/include/at_key.hpp>

namespace boost { namespace msm { namespace front
{
    namespace detail
    {
        template<
            typename CalledForAction
            , typename Event
            , void (CalledForAction::*action)(Event const&)
        >
        struct row2_action_helper
        {
            template <class FSM,class Evt,class SourceState,class TargetState, class AllStates>
            static void call_helper(FSM&,Evt const& evt,SourceState&,TargetState&,
                                    AllStates& all_states,::boost::mpl::false_ const &)
            {
                // in this front-end, we don't need to know source and target states
                ( ::boost::fusion::at_key<CalledForAction>(all_states).*action)(evt);
            }
            template <class FSM,class Evt,class SourceState,class TargetState, class AllStates>
            static void call_helper(FSM& fsm,Evt const& evt,SourceState&,TargetState&,AllStates&,
                                    ::boost::mpl::true_ const &)
            {
                // in this front-end, we don't need to know source and target states
                (fsm.*action)(evt);
            }
        };

        template<
            typename CalledForGuard
            , typename Event
            , bool (CalledForGuard::*guard)(Event const&)
        >
        struct row2_guard_helper
        {
            template <class FSM,class Evt,class SourceState,class TargetState,class AllStates>
            static bool call_helper(FSM&,Evt const& evt,SourceState&,TargetState&,
                                    AllStates& all_states, ::boost::mpl::false_ const &)
            {
                // in this front-end, we don't need to know source and target states
                return ( ::boost::fusion::at_key<CalledForGuard>(all_states).*guard)(evt);
            }
            template <class FSM,class Evt,class SourceState,class TargetState,class AllStates>
            static bool call_helper(FSM& fsm,Evt const& evt,SourceState&,TargetState&,
                                    AllStates&,::boost::mpl::true_ const &)
            {
                // in this front-end, we don't need to know source and target states
                return (fsm.*guard)(evt);
            }
        };
    }

}}}

#endif //BOOST_MSM_ROW2_HELPER_HPP


/* row2_helper.hpp
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
*/