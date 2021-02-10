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
M1VUBQABtkgkYH1T0W7aMBR9t5R/uGrVxzTaApWKvGiBUcEESwZpx/ZmYiO8OrFrO9Dw9XMSClSb9hI795577rnHNrbM2JwYFiHMy410yzOr91JTE6HlPEvRMl7O2g/Ej9kE0lk8/YYWD6Pe3Ye7dr3v9xAOzlU46IjQNbqGJdM7pn3DKUNYMyVqBzBtMC9ohC45x+nsZ9ckDHtdEEyllNSW0WOarr4efv3YxyR8qmk87JHV8GUeDs16Nf4EH8M+xJXdstLynDRFOLjohYOjgFbZSHCHOyrL25+TtAiZwqpTdYQAl6RgnSOgBOElkHMjLkvYc7sFIizTpQvsWJuXmh+6tOvisLZ2TEFHhY2lvIxQQbiAtaS11/TrYoBzWRSkpJ2QQRDcTJJlNk0HN42CNFlkwX0/BN9vqn2dKwua5Vw1U3xmr6RQgt06jjfERru9YSVl+n26gudK28ErV79DJYoXV2CIEX6j/sApVNowAX4GvlN3EuW2R8NaK5+Y5psaKLEEyMZZAM4aaG4WbImBNWMlXJmttFcI71qso1BaWplLEaHxZJaAG8e7uA0e+t9Je2geT2fwsEjmA/z3WJGHFqM0gywZ4H/a4gBf4iz20PfHadb4fhaDKyUkoe/O5baBvMVxcBohOD+eP1BL
*/