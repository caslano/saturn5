// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_FUNCTOR_ROW_H
#define BOOST_MSM_FRONT_FUNCTOR_ROW_H

#include <boost/mpl/set.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/count_if.hpp>

#include <boost/typeof/typeof.hpp>

#include <boost/msm/back/common_types.hpp>
#include <boost/msm/row_tags.hpp>
#include <boost/msm/common.hpp>
#include <boost/msm/front/completion_event.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_MPL_HAS_XXX_TRAIT_DEF(deferring_action)
BOOST_MPL_HAS_XXX_TRAIT_DEF(some_deferring_actions)
    
namespace boost { namespace msm { namespace front
{
    template <class Func,class Enable=void>
    struct get_functor_return_value 
    {
        static const ::boost::msm::back::HandledEnum value = ::boost::msm::back::HANDLED_TRUE;
    };
    template <class Func>
    struct get_functor_return_value<Func, 
        typename ::boost::enable_if<
            typename has_deferring_action<Func>::type 
        >::type
    > 
    {
        static const ::boost::msm::back::HandledEnum value = ::boost::msm::back::HANDLED_DEFERRED;
    };
    // for sequences
    template <class Func>
    struct get_functor_return_value<Func, 
        typename ::boost::enable_if<
                typename has_some_deferring_actions<Func>::type
        >::type
    > 
    {
        static const ::boost::msm::back::HandledEnum value = 
            (Func::some_deferring_actions::value ? ::boost::msm::back::HANDLED_DEFERRED : ::boost::msm::back::HANDLED_TRUE );
    };
    template <class SOURCE,class EVENT,class TARGET,class ACTION=none,class GUARD=none>
    struct Row
    {
        typedef SOURCE  Source;
        typedef EVENT   Evt;
        typedef TARGET  Target;
        typedef ACTION  Action;
        typedef GUARD   Guard;
        // action plus guard
        typedef row_tag row_type_tag;
        template <class EVT,class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,EVT const& evt,SourceState& src,TargetState& tgt, AllStates&)
        {
            // create functor, call it
            Action()(evt,fsm,src,tgt);
            return get_functor_return_value<Action>::value;
        }
        template <class EVT,class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,EVT const& evt,SourceState& src,TargetState& tgt,AllStates&)
        {
            // create functor, call it
            return Guard()(evt,fsm,src,tgt);
        }
    };

    template<class SOURCE,class EVENT,class TARGET>
    struct Row<SOURCE,EVENT,TARGET,none,none>
    {
        typedef SOURCE  Source;
        typedef EVENT   Evt;
        typedef TARGET  Target;
        typedef none    Action;
        typedef none    Guard;
        // no action, no guard
        typedef _row_tag row_type_tag;
    };
    template<class SOURCE,class EVENT,class TARGET,class ACTION>
    struct Row<SOURCE,EVENT,TARGET,ACTION,none>
    {
        typedef SOURCE  Source;
        typedef EVENT   Evt;
        typedef TARGET  Target;
        typedef ACTION  Action;
        typedef none    Guard;
        // no guard
        typedef a_row_tag row_type_tag;
        template <class EVT,class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,EVT const& evt,SourceState& src,TargetState& tgt, AllStates&)
        {
            // create functor, call it
            Action()(evt,fsm,src,tgt);
            return get_functor_return_value<Action>::value;
        }
    };
    template<class SOURCE,class EVENT,class TARGET,class GUARD>
    struct Row<SOURCE,EVENT,TARGET,none,GUARD>
    {
        typedef SOURCE  Source;
        typedef EVENT   Evt;
        typedef TARGET  Target;
        typedef none    Action;
        typedef GUARD   Guard;
        // no action
        typedef g_row_tag row_type_tag;
        template <class EVT,class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,EVT const& evt,SourceState& src,TargetState& tgt, AllStates&)
        {
            // create functor, call it
            return Guard()(evt,fsm,src,tgt);
        }
    };
    // internal transitions
    template<class SOURCE,class EVENT,class ACTION>
    struct Row<SOURCE,EVENT,none,ACTION,none>
    {
        typedef SOURCE  Source;
        typedef EVENT   Evt;
        typedef Source  Target;
        typedef ACTION  Action;
        typedef none    Guard;
        // no guard
        typedef a_irow_tag row_type_tag;
        template <class EVT,class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,EVT const& evt,SourceState& src,TargetState& tgt, AllStates&)
        {
            // create functor, call it
            Action()(evt,fsm,src,tgt);
            return get_functor_return_value<Action>::value;
        }
    };
    template<class SOURCE,class EVENT,class GUARD>
    struct Row<SOURCE,EVENT,none,none,GUARD>
    {
        typedef SOURCE  Source;
        typedef EVENT   Evt;
        typedef Source  Target;
        typedef none    Action;
        typedef GUARD   Guard;
        // no action
        typedef g_irow_tag row_type_tag;
        template <class EVT,class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,EVT const& evt,SourceState& src,TargetState& tgt, AllStates&)
        {
            // create functor, call it
            return Guard()(evt,fsm,src,tgt);
        }
    };
    template<class SOURCE,class EVENT,class ACTION,class GUARD>
    struct Row<SOURCE,EVENT,none,ACTION,GUARD>
    {
        typedef SOURCE  Source;
        typedef EVENT   Evt;
        typedef Source  Target;
        typedef ACTION  Action;
        typedef GUARD   Guard;
        // action + guard
        typedef irow_tag row_type_tag;
        template <class EVT,class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,EVT const& evt,SourceState& src,TargetState& tgt, AllStates&)
        {
            // create functor, call it
            Action()(evt,fsm,src,tgt);
            return get_functor_return_value<Action>::value;
        }
        template <class EVT,class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,EVT const& evt,SourceState& src,TargetState& tgt, AllStates&)
        {
            // create functor, call it
            return Guard()(evt,fsm,src,tgt);
        }
    };
    template<class SOURCE,class EVENT>
    struct Row<SOURCE,EVENT,none,none,none>
    {
        typedef SOURCE  Source;
        typedef EVENT   Evt;
        typedef Source  Target;
        typedef none    Action;
        typedef none    Guard;
        // no action, no guard
        typedef _irow_tag row_type_tag;
    };
    template<class TGT>
    struct get_row_target
    {
        typedef typename TGT::Target type;
    };

    template <class EVENT,class ACTION=none,class GUARD=none>
    struct Internal
    {
        typedef EVENT   Evt;
        typedef ACTION  Action;
        typedef GUARD   Guard;
        // action plus guard
        typedef sm_i_row_tag row_type_tag;
        template <class EVT,class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,EVT const& evt,SourceState& src,TargetState& tgt, AllStates&)
        {
            // create functor, call it
            Action()(evt,fsm,src,tgt);
            return get_functor_return_value<Action>::value;
        }
        template <class EVT,class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,EVT const& evt,SourceState& src,TargetState& tgt, AllStates&)
        {
            // create functor, call it
            return Guard()(evt,fsm,src,tgt);
        }
    };

    template<class EVENT,class ACTION>
    struct Internal<EVENT,ACTION,none>
    {
        typedef EVENT   Evt;
        typedef ACTION  Action;
        typedef none    Guard;
        // no guard
        typedef sm_a_i_row_tag row_type_tag;
        template <class EVT,class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,EVT const& evt,SourceState& src,TargetState& tgt, AllStates&)
        {
            // create functor, call it
            Action()(evt,fsm,src,tgt);
            return get_functor_return_value<Action>::value;
        }
    };
    template<class EVENT,class GUARD>
    struct Internal<EVENT,none,GUARD>
    {
        typedef EVENT   Evt;
        typedef none    Action;
        typedef GUARD   Guard;
        // no action
        typedef sm_g_i_row_tag row_type_tag;
        template <class EVT,class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,EVT const& evt,SourceState& src,TargetState& tgt, AllStates&)
        {
            // create functor, call it
            return Guard()(evt,fsm,src,tgt);
        }
    };
    template<class EVENT>
    struct Internal<EVENT,none,none>
    {
        typedef EVENT   Evt;
        typedef none    Action;
        typedef none    Guard;
        // no action, no guard
        typedef sm__i_row_tag row_type_tag;
    };
    struct event_tag{};
    struct action_tag{};
    struct state_action_tag{};
    struct flag_tag{};
    struct config_tag{};
    struct not_euml_tag{};

    template <class Sequence>
    struct ActionSequence_
    {
        typedef Sequence sequence;
        // if one functor of the sequence defers events, the complete sequence does
        typedef ::boost::mpl::bool_< 
            ::boost::mpl::count_if<sequence, 
                                   has_deferring_action< ::boost::mpl::placeholders::_1 > 
            >::value != 0> some_deferring_actions;

        template <class Event,class FSM,class STATE >
        struct state_action_result 
        {
            typedef void type;
        };
        template <class EVT,class FSM,class STATE>
        struct Call
        {
            Call(EVT const& evt,FSM& fsm,STATE& state):
        evt_(evt),fsm_(fsm),state_(state){}
        template <class FCT>
        void operator()(::boost::msm::wrap<FCT> const& )
        {
            FCT()(evt_,fsm_,state_);
        }
        private:
            EVT const&  evt_;
            FSM&        fsm_;
            STATE&      state_;
        };
        template <class EVT,class FSM,class SourceState,class TargetState>
        struct transition_action_result 
        {
            typedef void type;
        };
        template <class EVT,class FSM,class SourceState,class TargetState>
        struct Call2
        {
            Call2(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt):
        evt_(evt),fsm_(fsm),src_(src),tgt_(tgt){}
        template <class FCT>
        void operator()(::boost::msm::wrap<FCT> const& )
        {
            FCT()(evt_,fsm_,src_,tgt_);
        }
        private:
            EVT const & evt_;
            FSM& fsm_;
            SourceState& src_;
            TargetState& tgt_;
        };

        typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

        template <class EVT,class FSM,class STATE>
        void operator()(EVT const& evt,FSM& fsm,STATE& state)
        {
            mpl::for_each<Sequence,boost::msm::wrap< ::boost::mpl::placeholders::_1> >
                (Call<EVT,FSM,STATE>(evt,fsm,state));
        }
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt)
        {
            mpl::for_each<Sequence,boost::msm::wrap< ::boost::mpl::placeholders::_1> >
                (Call2<EVT,FSM,SourceState,TargetState>(evt,fsm,src,tgt));
        }
    };

    // functor pre-defined for basic functionality
    struct Defer 
    {
        // mark as deferring to avoid stack overflows in certain conditions
        typedef int deferring_action;
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const& evt,FSM& fsm,SourceState& ,TargetState& ) const
        {
            fsm.defer_event(evt);
        }
    };
}}}
#endif //BOOST_MSM_FRONT_FUNCTOR_ROW_H

/* functor_row.hpp
FxdqQkrSSmDSiFnu0jSjPfJP2YZe3jy8G5f57XqBTtWcKND4DAHagGxgzHkxLLxIzV4ZTfTHddQf61eKEY8H5FbwUCCzpw3nPAEUEjJZNI6kpShd+HuxG6LNaHc620Wzow3riDoyoaJ+ekFT/asDJpBqBCPRcXhPGkRA0OrwQrsQakCco2jfLNuteUdPl1iLAuP9BVA3t0etPatNCQLpVeibIwrRkmwpfBRLCYysidUYPOr953QvOUeRNzMdK/NpEeOuGb5CkpqBiXpb+Xv/RIz9Zg6f73Og4XJjyJP/Epkp8RzewHwcyQDBbJ9j310/ZWNh3qtJUTHS4fLn/pkEaRPBsVVrgPIOsz09tRVi5Iy4dReObebe7iFsD4x1tRWs10HkExv/hxzeTJujySu5LUQRDspxV2bwqGxjiyqYJz9cPDSWGCcBeHvPC/jrJRy4xK2eCjTpIV4MjGNNeILBoy0tiY3/DnJ8SJWVN1NeR4gaLbS5zqjLiULqarWWkCW0QeO/bLYZtSqXBzUemsxNASgoLCVEj7rJRdQ0RCu192x8WnQWDUmaEBWHKs9dlZ1AlnMEYstR5RzBNqNjFfbGNOLspBL/AYBCzxC709iCm5OgDiBjej2gUy6x52gRG4qo82Go8mqWssdYzfNVavt1wO8aMy1chi4sPerUXp2b0qC5qqJu3Le0aRUr03WVJG5x/pm45fHLNQWJchE4ToCeM/qO6aeDtRgx6xBlFw1wOrd+qiMhb807zFv+/9Kuq7V23dCvn23gVH2OxOwOUKd21ErcFredxAv+4Wj3Jboy0gsUI0dYEza5mwqgBhiLCmyc6NihssuJ8ptLybbNS22VhUSsBJURenxBEoLyjaDcedB2c1/g4qdIsIxlm0lgEB9An/mfGXweqcuibF4XLBNo/cAZTZwELJUawTkPsz3wnlRhYuWETElu71u09i44/T3tvWyQ9m7h7b1tanJ7a/1y0D5JRXFe6O7ReaG9f7vCpDcLNx/dzkQ3UP8e96XxEHqq7Kc+pdRnDdbH6FH936bWh2sFWCnJ0XuXXVN6WLrX6W+FmlA+l/rJT0kRqKYsg7KkU6eT/D6ndYgEfn9ic7mBKgAKjgHcxRYVJdEn77CbHQECfC1uPcRrzBbNYiW5eYfDxZYYxvNojecPEcvj0Rtg+Q2c5Q9pLN8BKYDlB3Avl1YomD24cBEXIQ9rJFfOGessjkdRhaxPZ/QNFNOYOstdDjzLhZ4ThR6+c8auDAjLqwcwdskPMnbnlamMPYEzNjDUK7qDi0DG8upkno4ur/4Olk5u/016+3/9o9v/M2z/Tbz9L0lqf1wdcSNx3GXqZXG3G+mISFVUw00fn62YMJOGVFobwIKmet3lTo+6ktZa8IyApbqqksY+3NvC1eeamAvSlHnU9TSht0HqXFIRJEiZMNIjLRIt3TLQoNypns+m4ZAvISh1dqtBvtrDvhW3fg3j4Rho9L09Xzv2BGAqsJunDGWw60BLFnEG4EF7Wgq2VlXznR6uT5AVPUB/VIPO7egrYM5wVM7G+mR61buytYE4lC4P87qd6h+ztS27ZJNCpIXVw0CR1/334nZtR6AHKTNtd3iNUS9rRnJZUM5FXlXsX8TPBhSRiu8Xk74b392T+gH7atJg+KbWfxB4V+Amgjc8y8AOHOpy7AsM86q38mShdMpHwB8YDPgA+D8bBP4MDX6Qwg60dZl4IaaBhVw5sJBU+P+c+OPh/2niAPgHJv4A/Prvgb9Hh2/m8K8fCP/2gfA9SqvgZWdY6Xl2Cg16RJ/DM7M2jaafwY5yNrVWCJ6Q1+a1BjtqR4XnG3xK3VyDafVtaKTVdtdXvtDmdaQDNZL1s1uMvC+PdqrvXszxpGDirxPyleFZE1j7IdURDYhe9QmeIkQp2AuU/TRgWe5ROyjKurxSN0SqrE6seoDgjCxeVpvjC3aEbblsb+2kdQUG2erYvWo8oAS/A980tNFicasR0qz+eNreKBpkgTbMDk47xFdhy5wsw+kvxsnJOvhwqb7JJHvyWqPojBflTsO5UaCb43Z6nd0evj27HYhM88jmpWmoHOfBZ1gxoTPFXq/Y3JFG20s7a2l7aRZ8gZzJwaX5qeTsB1fEmSV0E/czRdqhKTTX1vWEgTTaHDFi9IXm5uDiuNi4ERX82eiOYhPuRc3ONASs7c04Inz0N4PUvco3OzsekvskhPzcN7vIIKf7Zq8zBMp5+B0YPv/0XMM6LEyMzJAzxcjcXMdeOZ9trKDtWhy3lFutH3q86rvz+WoVrqzbxMZQGu5gBXLZEeCvAqQAkGSq26v+8xIcyEqtbV1pbm9Y3pit7seQF0qtiQ0AkKBDxiqLrbjmYUNZSmZJgISPmaCOM7qfxQr72EhfqDy/+69EmVylzwTDfZ9RDEaNVPY13fcRBa8Ke2LK2YzVQyCsoAsNoQAN7yVk46svxDs9/k1/pdWuiaQBZ3XdhMohAUbXQXdwkDO7rsFghDoePXm4QYaHKmcBjQQxOAGjyqVQZXaoPKtruJbfxyy+0E1FXRdw2hCvwvVdJ/o4oGPGY5WlXR9qscdMxyqdXYf6eN5jhs7Km7ui8ZSdlRVdz2sp2QyoK1bYJAYPGwi7X3RtScp4S9f6pIz+rrp4xnBJDFeNm/+TZ1vR9fO+OK7QlwHd23xMAtqu7JrXP6aOx9R3XQEx62/KgVbNYWbNUlGJCuGb7vCAGuCH+RIbDe+esvBc2anejO/DPC5lz5pydQFNpuxdeAQSgYcXAne8oz53jptPvYXBst0OrfSPKf1ayeXf/jfocgfJKv9r6uXZ3OBEZxF20emoKP9EucdiEIPP4l62tm/i9j/3V9J5Z5HOC+2UhftaMO/v+vkFjTTJeVen5P2A5zXoebP1vJdcSCFrmthcTPZVfWlA2unbsXMFJvqUtTnZgcmF1K8C43n/ehx6Yte/zlPidDH4Af1am1MkBg/Bz4ZX9D4oBtvgPUR5ul6An2jsAKNqIAeJJ0Z4y4QfQTkg4ZS9rGHP47QLeD3fZuxqwI0zffvIb9Ep6FL/kcVXCqtANtGZPtSFeHcTIw+uo3nT3Jl5R6ftRg+hj0XDFROMwPdNueepiXKUvefDL6NmhpxQIujdd6+ARlC38Omf0i4o3cbAsa6ec1rXMbI7BaVNUFchU/TmdTgOTDjaczQYC1WA5GhC/63e8IO4S+kpUw/0cHffL+MqWte2c6nsGH6C9jeBIx/Ec9ld6Cy24dyngPjqKnlCwzn0ThJYFe+GYdSlu1ZpQPIOF0rig7vFyG5fsNUXClJ1G8shtsZIp0ca9uCYUg60yaV5z+84Ll0zEED0is/WYfpHQL4qqlFsDOo/8s24lgbc+xaMleh8zBo8HZLtmWLjftwZV+qtc6BJcdv3wVY6qRc8XH8x+wN6hWKvw/hYeJX8CzzM1GZ1BDFB3RcsjJHh640hCqBtHNzEUdvGakI3sEC38yjzr9Db16keuug72zdsKwrn/46ObYarLHK+U71lLF8An8LCrXyEyQxb54fllm9CQSw/NBYStpfQGUbtCB/uL5VaXOqZrIT500wcACjGKbEiS5mTD1zcdt/l35Lov3kXxffnNBEPivW6u0WDPBFU5hxlj+BT7k6/ELCwuefRCnMmKz8f8gjdM8TIHBipYjH5Yt/sCzF5nG92XywwBFkVk4niKwcxWQbgSgfAEdbdFlNgFJtrcLrVrG+5ncKt0DvYIkHcesCl3jxG1zTNYuMbXFJmrvuNCHKgj3rBjek+5UxMbES7X/h1gXsPgF993AEGAFLOGMWNB/F3mWbPLDY/ym2ZbasN0vpyAxYFnDXO5WxZYp+kThnDDw38sxePisWjs1zO0BK7XRW06Fd6cVzpH/svG4/9I8Qem4uxnTCFcfGdQXWfFqvEY49RLOVX/0uL/SUWDGBrDE61yaYpdgNZhXkEdhPAeA99Uq3U8l7Wi10N1aSXp0KTrk57OX9IhgRcfwGkMja9Jm/Kyp3+3ITEuS5Tk9mDFEMSOHg0cA1u14MAefbi1HOD7jL/2wne/nZcP+kfqrR3PdSjyRhQmzK7Qj36GK70mcXmv0ODx+zPl0JjbBdo7Js7veuXkIbWUOnN26OdyKO3+fhm1t8c8PbUbQYpAs8eeN6CZ/qv4R2eV+E5BE83PJevNEhz4KmB5zfw/BWe5+DZDc+H8JyA5xw8Y283SJfeaZBuhO9ceN6HZ+wdBqkNnjoID8N7GfxeD2m3wHPLXQbJMMloMguTJqWlT5qUMYn/WSZNGjJ00jDr8BHiJGmkFjhp1Gj4sE0a8Ddm7LhM/mv8pEkX4feErIsnrpYN0oiAQXoQvp+D5zA8q7UnOQyfk9q7ACrqKHiy4ZlemzjDUGPwetT3xmtnDgJ5DTG6Zeskccn2q4FL+PTd68RraHqxRaUnUYWeMlZXoRtiaIMkX4mrAvJl69aMMASmIE8l9iGyIYd/IWU7PkbbFohyt3+0nkBLBeqd5PBPHoN6JNuwU19aJT6P6lMCd3l8zp/ZEEOd/SWupv8bGnw1XmtGa6q4mv46twI7X09qugxfrKSUzvKNrK4KmSpZdHmUleQOCMnvF+JjJQv1IF8izDlIWNkgYUsGCfMMEnbzIGHL+oexkoqB2K0YJOcv+ocdK/FrQccuqtJC7sCTM8xSfWw8D8Glks6SNcxU3ZnJQzpL6rRcnVouH9t8LxcGmBPDfKGRkJDP7XhoZzK8JjT+SgLpY03r+EQotWb0DpHoKRR0DgiHovC2GjYkUQylMkLEI3oqCV83oPRGWJYkWKxpE08UMuHLA/GXzVsSUAko3/RK1IgHPjdIoF7840nFsw1PUOl64WjtuGgW1Dg1pKhfiI8tWoRBqUgDAXbGCcA2t/bDlMpnm/drdQElsulxGvU8y6YddLwlbkCVBlMc1FMgfm8PwG/DB7xRqvoX/moy9ff2o35DjBQ2rzypIUYK268g0b5BuMFX+CiiFZjAmkjvK8wMSHqDs2glQNeLxK4dZ4EDDV1cVcsC4NNeFxtN2rdKm54grC4fowkrsfF+nOgpa1BFa6JtBrInPZrXETwsbrgClbYX0KKUTS9ca5BHKm1GZa/V8Vrdl9WcDQtuFuV5kF+4gMgHLga9x4N+HUMj8WQ9kItEi04ei4/H+gaPLrUoZ0xi4/+jpigSUOMRGztpZn8Bfh2gX33wC9dtKGdhlSBuRAco4TkgrUD/OE/6R3DJPSCmPBZO0PWjCNkWbPkS3JnMWm9AErZo9AJMsDGhqYYk8ZGe28dGJXUcnp8ZkkWdnh+zp+buNCV3Yx52zNRPVGB+Uyol+AjyUsWTOIK8dA2MINBoD47heoY+Jrid/ltwUHiABoX3RE07yDuaBLl4QP8pSAoRI4sWKW0x5Yx5dUnMHm5BolFNgAztBpMhiaeBBL7QRfSexKTtRrNBA2zytVP34HlizjUG6RfwyPA0wfN7eJ6BZzc878Jz628M0ufw3QfPqLth/Id3O3wXwHMHPPfC8wA8f4enFZ534DkOz8jfQhpIOwqe5+Fph+cEPOUQfj98d8KzENJVwTO8DvSHyag/TJ6clj55csZk+rMMmTx5KGkP0sjJo0ZP1v5sY+Bj7OQBf+Myx19kseKvCZMnZ+H3xRMnZfcA7ONrDdIkeBbAswqeYfBg+NXwXa2F4dOspcmBsfNn8CyCZ0V9Qn9IjN/UOcMj9YON13A+WD0eesNA0+2mbH2cbx18nI+vx9N6aI2Qd0LZm13uUe8j/6Z3cAMEq1OtGMLXFVfewUpkHjRfD5JZyRoedI0etIavXEKo6FSztdBnaNwiKcojMvSIxyliZzziC4sWsTNu/MIj3tEjuMHLtnjETj1iW9wShkf8WY/gdjSb4hHr9Qju9uKBeMSdegQGoY3JMzg01Od582LdFu26oU1cfLPiDAtkGuJUZ/FM6O+j3ep4lKaoR6t5KseeEIFYjtBH69BfJe9eehugLcQfC6ATh4bjZ9SF5hcWvldlFRvbaaPHEZ5ncjS1QEvW/kS3n3T5n8AO/hFNHk8P042cyNKvkSxPzO14zgW6/74MYhrQH9eRUaSlTH1+NJ/inUCzSAvMocPFzSbZHJprCJcKjg1aUZrhSZl/n16UU2UpRW2gogTzPpdb/XlSMUPc6i94EXzRGdOOTjUc1Uw20cL/WcMgNp2WZJvO+/m2OsdfKFO/HZXkamMwo87gCadLzogdhhp1mxImlwgd3ZkLbh24IE9O1FN6Kl7PPw/VbKAAdb1KG3mp8RrFm+J4oil+lZQvYX+DlrPAR7QgbJV/6u7O0BiqxhCusNvUNN2mTx6qtBsV6O6GwGfLff2tdeP6uQYRtXRfMEarzJEvay9lMchqM8gXE9hM9ZkLOtgZDXvI0U/wxOoP8LzctAvKl0ZPaJHNF9p1nvz0lGQZDOp/L9COcFcO7l6D7JHRZMkZKrX52oswz908TzQRXyQl7scE/s5rLZxjEx8gB+QYr6gGebaiGuUx8BHIbU+bNYS7tudTFjYc33GHpN4Gw4el0BYsyMiQ5GLaI6k7CXMbnkQ5U7/2FKagtGPo/kw98TgtccgWxnfQTUKUhxfRfz+LDATYh+qiUzRFGsunR+Fie6bTrYtOJMgg9EDzLWBJSGt1usrUhdxyKZrUXgQc4m3O8OpslVlIMc90wZx+MYzLflTu8k6A6B0paIqLNgMvWeELcd0u1IQLeiQmfKGqa+DJgScfngJ4ZraXzKI7nVZmhVZmh6rsoUe3UK6q6aGqTF/o0SfJ9izLsYcvtW76m0EKbUVCtDdjNVfA1L29GccJaQ3GvIqzzXR+/MxN51a4P62GW6093ORKG8mT7MfzThSutAQmaUbG+diNeqkbVXChoJkto8eFDci5bmV3zCtGzvocF9AVRnuxXcJFiNrLC2/DtUHcyidba+DiLFXV7Y3kuoZ24mLHhdXvllPc/njcCvJ7kCQLyrVTA9R7h7GoUz0wgls/9veNk6XZ3KE0KNVsQur0OrjULekphtJ4ljVL7/kr9GRl6p3pXDLqNtqbK8iO4LDmagmtYCdxowEYOsY4VaNJGxHI9OIZNAdo8Fm3fhmLeVRcjPKor3AbO9yeXx5aKYVW2kJk6hdq4hZVaI5QpUujJH3BowbJvSL6fSqxcTtDgEH7g4mcpAk4YXiw03WCHEBX9IqUC9m6/np16vuH16S+X1eQ8o79XTmeGxbsAHklQM47DDOJR3YrnxunoCq4G89WJKVPvgsF/6IDzz/QYWmql39Ti0Hyr8MPJ34U4UcufmTjhwQfuN+yZTkSdirdQHKHkCpAaT/fb10uSG5VonQWpTcWELBnU0+V/C8AbYYb1qHapC69zqivWq+d4PU/gq2NmWsM6r2CtpyMWd2gm7lwk6sX08bwYMal19KtGHThcAKFrqFzUum3od/79n7vL1lT36dlptIb6ANsq4shj/cuG5vhuCowSlFxW0HZjd5ZVh0HWlSJL8wQXyic1hOYC2IXJ2u7jRA8Lx48PTk4Nx48Ljl4PAUbp52UxeBp4rx7LNx6BA/0Rrl85xeunAdaqd8WAxFai5yq5wYyCPYL/wWhH+qhRRBKairoKehhyKW+qkftu55nkDDDM3qoeEMSr+rjDS8vExMG9YT/4tl19gHINXrUSg1yNmZYooc+f30/yNr5GITgz1yOsuyjm5P5ZWmU81KCXdzqyYVGrp7DiCysvcjtfxoZJpMzjMuk+0VbGi1nV/TipSfevNMe+KuJuT2e2DvosbB+tlf918/iF7UEJvh36jCc6ghT0qnypdEamrFDZrpC9x22tztt+0lITdOyClD9AKWXzoMkYb3qpXSAGy+2AkVmfX6cNyuXL40Odv7BKwMP7+K7IKyJi7KDHrrPiZVkcvsh1H+5hqHs2ofMIF/G6AcTQxvo2wu65nhI4lVHc1mmJQy8p58RkEfpwhGgfcG9f2k6sJzNSOnlWqZ2EANUeTJAJoENCj+3uaoAfR2+5m5iG+g47KyHfco91jmBy5hXqhHK/FOxrcfepLVOYBSbB9Rcdx4R+w2/g5YswhFa3U4Ow0X3LwE2yz2q57zuzwv5zcO2PYGjIttOGKn7YHD0xt5FSV01QH6hfm+H0kPD8TNK70Wk7+NnlOKCrUR2GWfYVtLZy8j+zEopkUZJEdDS6H5QKykpv5Xyax4fUvOPiUdA+dYyjysOAuvTbkD1YvtUYLEofy/E92y/9o4qFrMwExvpYbmOd+WheD63DxQsIEeRZdqcZBeNZN9tYS6JMlrYfGm9caYpML4RKrF+jnHm9cbAcKXNpOw2NbYGPgPpD7COxKL9z4/wZiXNqb1pu2YoV59pbqe9PpgAEuEP0OBv6ZbC1pfpIh/1D7o6EKIkgXH++XgwoWI7mkXCh1o7jvNAjG1+jpSAbTRr2FQ/mg77vBfCvVSlzQbjVeBr4y6ehj6JKfzZGwzAUCBO3NTVpQH6OdmL0UCCNjHboEy3uhT6c95pKLYwgqDqa8rj+r92fFv4B3r62LF9O57g2dEKX7jO/+I+en/xIHwxv1ReJkacVhcrtZSJrzjTXeIrpUIZQ57wH6FyvpoNOO01Kq/mOKiguj9W9jfgIv27d/jqS8UX1uVvomV7O3xxtZgUzyhtB0W3W7Rbg1gsAxIMh2c0POM3oVE4nmqkD/gfOD+gg+JWKmILL6Ll+4sAvb0GUtwBTy08dVSGEVcm4SO1COw/YmTOwiczxEirbGlTzcCH3Wb4FiPz9QWr+TF7eOr9BimvA4/vPdimtA1jbVGl17g6fTuaekXpSnrHQbw1Vmm1aDGE34sUs4/HmKPb0S4R8UsDcN2A1zF4Jt2fWJ/B/qQct5HbQzsZN7FmhJR31BGVxxRODYx0vM71WUephbvadLwu/xt7KM5NqP+yjc/pBw9teP42F0895zt9eI4fPy7Fj5yWCvt0eK5E3wCh2+zZ6jLiQRuUNIQZqnHj0Bat5juAtqiHEQ/kdTi+rh/Py0N/l6bCqbKNxnPB8SZOpqq0jFUhQlx7S/i74HajoOY/S/U64fgWq5krz6EtykW8f1+U1L9HJPfv7jTq4I49QIgLYiMukzvqgRCv448L8s9xf9LvBDJg1YEAv3uO+4TMZQpiXAbUycFljAIX+nPwwcdU/LgcP3L3FttnGOAjzxCqs+eosQWcHHvkClw+5hU=
*/