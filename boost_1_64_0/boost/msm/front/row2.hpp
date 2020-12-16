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
Wb5bnMPY4LjNeen3BnJucyGO+wy+O/QIj9MD/jzKLsiivjmNOZwf99Dn9IDP6XxkkA36JctBlvuSiSydPpc/4LMdhn5j+xTsEXQvm8PAOBbh930oHB71QQneSQ0yuh/K8tX7H/isL8p+Mwr/RvdHsr09Sv/Gt4X+F0OMHiPiLwU4Ti6nc3eu0mlXaw1zIVCcB13206kdlxr8Fp/VjksNbSzI6rF08quay/pA9Mtf04zsB8E9WnPoC2UbCHLcHyK/YU72iTXU9wVTuyar2D9B6Vq6y+LUkfRU5QzGU8nQzYQ7L7rrR6M9vu6uH5XV792zbrGjm9cK+EQm/MQ9IcY9V7cTDMddq4ovJpnyofTGG+8lbyudzkk2Tq/LddSeE48pL+SZ+7bJAGM3+en8wEFaiAG7szt7ajU5CDaaymft+RSwpV1Y+s+G7CuWd2HTJOCBBl6jCZWD3c+AzR4KMPZrHp1OG2kdXHhXLpFn3LfzwrQFK9leHmsLVrLDfDaprtHGlVwLOpzLmuUvbtt5nHe+bWcXjmqK6386h6NzIetmABBpjHNZ4sTa5nBPiCNzlkyoru05MfSdTh1Su6rQiYw5GhXM9rD83vIlPC4tik3Y7UU8nWyqQac1Ns41bWDCFnZnaeuB2cHurLOP0bukz55yxoniRX19o0WLrwRR0cozgpfyOWNK0alMH5wX0hPuOy8tdNse5Xg9+c99rOMVlMQktob7+xcSYaTtM8Y89qZSo27OvLgfcfpiTyf7JoD1nWlPT5v1Kcw5LxrSTURcln3FyHqJtrC3cmXJmW1svi9bdPJIitgjHFzO1eqbKChzHHgL6bi84ujoM/o9cDGVucfFtOY+rjlqhVw3V5HhUZWYbKdtoY7x96ohhsxWMP1rBRkyVxHOzSRDVURL8XU6gNURd05LThmZtiv2WW/laXE1SeS3Tf4l8pxmt7rVOWn7RTEmaC6+dXoxOMF6zr8DDJVyivFeX/faIk3pac6I3+t2tBUa0EwlQV+W5WFPmlG5c/u+uadvxYbg/vgCQqf68HOMdeA9Psc5xhioGZljDmu/4OzJSpvsKvawXnU5MJW73/nI/ojXtXvfuUymnc+uTbSKuvF1dm2q8MV+wIzd8Usf4ZLv3/wkzFQW7zK1X+630r4hOKqicTmL9yZGIb3SOE3SFGzlFiEmSStbxDW6rssZTOZ9+3paL5kL7eKcW/mmDnOqtpamGOObzPdp3zuMwG0f2CM5m1pGMabOo75vXZlaWloY39AYd16nUUaKOT6zMHvkBFFsN2XBTM/eGfcCpb3Pa0beeSzqMNw356ROs+eFE2VEgvqe14xM53IoDIrEKTuPMQ/i0FOFiAv1OZ/DUXyw03BYiBPtwuWO022csj14cAZzi/kQY6qKmWEwHIqMGOwJPPBKzJgXpGg3dWpuurJItTp1FN+tOAd/7x6X3YVPEwl2fjfWm5/sGq77NtikYGkKSXvAFXnPqglf+4lhbt02NVnmy/NhlhJZAhOO17HLQU6c1G7ZVmQ4ponNTKv2Ec9rRraPrg7DuefYV/qCLKR1zM2frDi3kMTYUp4Ps9LGhznxWhvfyLiRjhcFJbnevfM4OhUhuGjB49yGw23Qz4PXeOBP54dHORF3z48Ljsa3dHrYWBmnzzxPa85Yyr2ee7r8fsvblsbhelyG0aHRDnlR6aROtMvivcJ8sknxr1ZjQvhO+v2C7JbzRtlTmcGUqLFGl76IoiDQxz7N59obzjxtx9PbdXpHukFZEHPyp+cx6fkQnNF9hsfxVYYG7Pl+AaYus8htqPDMEMtrAKVnC93kn0yptWmpNGko0x3J2kqyNg9/t/gcyXSooMR9gIrQjBs=
*/