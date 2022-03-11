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