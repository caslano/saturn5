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
MQ4orkG1Tl2quKc5+qTPUAmKNlbsK71VS605ke12ZxfOzqn5bc0PBdmtpLqehVyFL/hfWRM612Hh04rf2hw/TMX9UNlnyPRod7t+WpTxUDGJLGPuFz+iOEoUxxWHdaedR5/RTPtkNTkp+t/h9GUlU01WJ7aajShBP/BiJwzq2s42OvKN1C877Y0+fDNBz+tRPCKO8lUcxmw/kr1we+u5cdjtSdaX3yzbm21m4kx28S2OXmsIn2j4TSfu9c1Og5omjy+T3wroNPo/gDQw3w4wFM3aGjPlrzgMlQHdV2lP0DyXmf5XfYbKaYKKTN6B+6Jk3LdxopcUfK0yPgnX4jiW3bJoJNQwTzeMby2Yy1zRZzpb6+54OXL7OPmRd3upO+G9iK87aabVrrG/t4Ex/C5XkHpyivq/euy+FRvd1WO4j+RxJIepxGRuwp8v3k1xZE5RHfpRT0+dlzrqO6jTfEycRVnWDPWlHEbP17mPbKNc5hST+N9kKSuG+lERxiik23sUaMPzPkN9lyivktLjVkw6+pqQbscO9Pea2aKOBuVVLPs6GR3lA3s4Id3MG8afLeW09jV3srEmzhncQ+lUoML2lb7VTEPgOLZ9xh6gRhqU/qB6uyXK+xtOe6BGvrFKDia3l4BOTQF66Zu+3iSPivOw8yrZD/AH6ajSkIfBjNOvU58+QX276HOPKH2rs3aQ9w/v4uqkTRDE9U1nzY2+RJ/1wIF9eV/3o65uzUW84+vp8h0K77d2PYLL/99p3xTXm5Q2M3VJGi1RPqXoEgHdGL3oI264hxjzTvBEeWph6u42fU2c0/N0mb6yr1H65H5l97qZLoPmsPueTkHXM23gaRQ0l2kWL31EVKSay03p7p5wV+nuPu3gmfvG+szd00/kGrOS40b3A1q3Phi3nWe5zJk2+UhiDXfy2QHdBCLD+DIY+Q5JA2sUX3F09xyrq2VnVRsYgx+b6emnPs3isM3oFuauj9MMZ5a5wdM0xxni/rP3QnAr5nuDIqwV2PSLwdTqdGmefPuV6uopbi8vEfqpdNkFdtFlrWU3ruS4WXw5dHLo6Y4SvsdjUszlXng1OJoYr2Zv4sxcIUsj6yYHSNvwdxeTfzffKGaf55POb+g5I7zLNIfyPu0xi1Pl9FEm811GUY6aq5SPHaKrTzzuDjVjIxTnos64zMzh8t3KeLaJ63dSc5wska4dxWXJis5hr91jwgdCeW97JPns27tUF6jzD2r9IOm47xTSK+WF2eMVSlha8egLz7qsTfwCxv9PeTqXwt1wttMLY8Gtw9mM6wa48cNaBiMO61g+x3V9Dv3ZV1zGNEL6892wPvNVrVemjt0ronqxDP0rwNAhE8mUQgxtgsozcvFrwKB1o139/mK+ZtoIt89Pq9/KdjKLcyDnFOe3FfaVNeu0F8xHNee0GZyVeJDi/HYTZexkmJXJ5DUHzTrtZyJrP5rLa0P8Xr/+DdoR7OyDikFbsm2XIldMsD1h7/rBikebQp/3Gc1wWXK7KnxOc7L9YT9Hx6naIPoGzap2iDFOs05bRDl+RXFoj7DJr2pGtsmMix6iOW6XzJU0F2yb/beDs+6IeA+K2qbUTMOkP98G8wWKQ+qiYd4DfpFmzlroHmhnipGVw+VYfKjPcWEjTYrhBot+1mP8xop0eZzfUJGuhykOfQnOAvlMuIGyP+rxtnGWMQ/qa50aZhnnU4O6TD634d5/Yc1pYufcqeZ1g5fraF5e/DorftHTOWoeBx7uMl4DrqDv0JxsvBXYpc9xw+X58lddxjbaQ/CnlM4NFowfDzdWzv+2z3BDRb7yGDKke4o2G78DHHvbwveJPnoBpaezjaRDHcUmEfPwEbz2j8E=
*/