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
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
*/