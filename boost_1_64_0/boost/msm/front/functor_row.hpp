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
773QbR7raHcRfkthGpG1nqtRvLweMbi+0dJnPA9NLc4eXpihf5lbTmRXdIpxoibW8G6Qwxo0iho44xrk7M0JQp3z/ftCrMk4pzEOhkcmkqaxNtHgNHbz2DTiGu7I7cbxnTE+7/jfeCpdw+ONnhvuzlNLa3Qaq8Yf7aDcdvmNvRjFc8JQuaXj71n4QUGGmgAx6MummTE+gX3LEX3V8j5fTysHv9+rdJMI9ufV7905adfTF5emlo5Ztxf+yN4Q485J++FwTFw8dklm4ajNiljPuayvmyhYLyjdBC++6Sjqb36ORsd7OA2J8xzkDMZ3KEeKcRsQxprL+lyaKfS9N/J1t+HAVoKcwcTbjIrRDSZjdxSrGwvaomKDDaUKH1nxXiMhXw/2t1exDTkWl3X5UaXy2BgLncTZuSPztlvmOHp7NUORsL8QCIMiYT/+xlInl5zm/47hUFyopzBrUD4/ohlpPDW+y6s4tV7d02E5BiTTNgyzBkVeo5soxjei1YwtadY3olXchdJsyIjYPjXvG1GD7xNpluq3gn5F687aVOGo0u0UQNxPP99hzJpvagMnabes3uY5wK00Z+uM73NrJnWoNuubdqrK7yQE2JOdTkzSJtrIrTUj+7NhQG+m8WxijnPHMGNtqIW9jDtpjsqS+7NJrSdkj+SEP1DexY4uJzga9g6dWMo2jR6Itr1XM3ZYAVMMhkMpEsykx0xPLU3ZSnkgxpZ9AUa+eREKw0Qjwtj2GH8s7u/1dXeM7N1T6ZvVzupJGUdXx2FScRLj0r2UTsVvmhjNVKn8Yc8n8jizV8T11Pfio+WqbJmjivYVYGTZjUI6pVquM3fnNGMbYRW2dXnJHJ+/28y07O9biG9vmJNrcKVwWE6/UBYMvUh9nGbUR+cPu75PHGS8/a8g4/lZkqEHqck7WrAFzczeAOOtj/dD4djCxphxE8HQivbRGTWp4Dspuazre5Ru6nNqUsH90eVDrOsX9a8aYuyNylp0Fj65ildPPtDHBVn2o26elXOQ075Uxg/+K09DoZh7RDfL4fVw2MniKAV/o/0qrP/tDfLOO4fRFUJM6l+hfEW81dXVejx+zyimrbl6YkjnDdObC5ZWPsbf6d7qtNbWxuQZjLf3Zo7eMWispqZHH14S9+1vHmSareZqneQz8KXCYZlX97cS4rC2dV+PSxfmEowRVV+3i3KReI9QzMVMYskQnf5itOTqNhX0n3aEMI54TKfl3I2ObiF0sw9hs4x6vaqv06Z9o9boUEoRRkkwtGdug4C/FEu9vZHNkxqon2OOnn0YwWSD19/vzAwVA61lcVl27y81vgXt9FPu7+kG4Va9bYIRTKHCTKtZJw8C7Z/3pO/CDF2pS+qVrbbZZ0dfc3XWKYAtOj1nLMQEwv3CNTTDFsm21t+vObZK5ooVxVEGxwZXr1F42H/SnM0n2jPa1rJmZZlEaIPX1Jzxv9JhPWI7CnGUQJI2MW7VNWNbxSZs6VqSSWKbctha19P992+Wrx3Q0XyFTV/H4+y7NhjPQ/q4AhOeQwcZMgQxNvaDTNym+2mrdVo4db6xGGRNKVLq29xmt7nu0HnalVweZ68TYMwolvZGCGvnupqzxcV7Mcc0E+qLJtlXJxtp1qiOzfSDx2mt23mDONc9pRk5d+45eocc2rNIk/+Ge0/kzVwo3qjbEjVJl9+KEu2QWnslOb1Kj/GNo+3AXj6VrsWWZ+YWF4/Snv1ChVLHa0Wx1qlCeM4UvfjiUp+dm8XcG3GUAgwlgr85oHV7lb651lg3z3eZRslj9vLHCpI/ehfrPpG0hvW+jyumRZssbB9hncbjdZ6H+Iz9LA7m075uc44x9xOebp+oP9NMd2I=
*/