// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_OPERATOR_H
#define BOOST_MSM_FRONT_EUML_OPERATOR_H

#include <iterator>
#include <boost/msm/front/euml/common.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/set.hpp>
#include <boost/type_traits.hpp>

BOOST_MPL_HAS_XXX_TRAIT_DEF(reference)
BOOST_MPL_HAS_XXX_TRAIT_DEF(key_type)

namespace boost { namespace msm { namespace front { namespace euml
{

template <class T1,class T2>
struct Or_ : euml_action<Or_<T1,T2> >
{
    template <class EVT,class FSM,class SourceState,class TargetState>
    bool operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)
    {
        return (T1()(evt,fsm,src,tgt) || T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    bool operator()(Event const& evt,FSM& fsm,STATE& state)
    {
        return (T1()(evt,fsm,state) || T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct And_ : euml_action<And_<T1,T2> >
{
    template <class EVT,class FSM,class SourceState,class TargetState>
    bool operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)
    {
        return (T1()(evt,fsm,src,tgt) && T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    bool operator()(Event const& evt,FSM& fsm,STATE& state)
    {
        return (T1()(evt,fsm,state) && T2()(evt,fsm,state));
    }
};
template <class T1>
struct Not_ : euml_action<Not_<T1> >
{
    template <class EVT,class FSM,class SourceState,class TargetState>
    bool operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)
    {
        return !(T1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    bool operator()(Event const& evt,FSM& fsm,STATE& state)
    {
        return !(T1()(evt,fsm,state));
    }
};

template <class Condition,class Action1,class Action2, class Enable=void >                                             
struct If_Else_ : euml_action<If_Else_<Condition,Action1,Action2,Enable> > {};        

template <class Condition,class Action1,class Action2>
struct If_Else_<Condition,Action1,Action2
    , typename ::boost::enable_if<typename has_tag_type<Action1>::type >::type>
    : euml_action<If_Else_<Condition,Action1,Action2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Action1,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Action1,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Action1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        if (Condition()(evt,fsm,src,tgt))
        {
            return Action1()(evt,fsm,src,tgt);
        }
        return Action2()(evt,fsm,src,tgt);
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Action1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        if (Condition()(evt,fsm,state))
        {
            return Action1()(evt,fsm,state);
        }
        return Action2()(evt,fsm,state);
    }
};

template <class Condition,class Action1,class Action2>
struct If_Else_<Condition,Action1,Action2
    , typename ::boost::disable_if<typename has_tag_type<Action1>::type >::type>
    : euml_action<If_Else_<Condition,Action1,Action2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef bool type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef bool type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    bool operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        if (Condition()(evt,fsm,src,tgt))
        {
            return Action1()(evt,fsm,src,tgt);
        }
        return Action2()(evt,fsm,src,tgt);
    }
    template <class Event,class FSM,class STATE>
    bool operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        if (Condition()(evt,fsm,state))
        {
            return Action1()(evt,fsm,state);
        }
        return Action2()(evt,fsm,state);
    }
};

struct if_tag 
{
};
struct If : proto::extends<proto::terminal<if_tag>::type, If, boost::msm::sm_domain>
{
    If(){}
    using proto::extends< proto::terminal<if_tag>::type, If, boost::msm::sm_domain>::operator=;
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef If_Else_<Arg1,Arg2,Arg3> type;
    };
};
If const if_then_else_;

template <class Condition,class Action1, class Enable=void >                                             
struct If_Then_ : euml_action<If_Then_<Condition,Action1,Enable> > {};        

template <class Condition,class Action1>
struct If_Then_<Condition,Action1
    , typename ::boost::enable_if<typename has_tag_type<Action1>::type >::type>
    : euml_action<If_Then_<Condition,Action1> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Action1,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Action1,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Action1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        if (Condition()(evt,fsm,src,tgt))
        {
            return Action1()(evt,fsm,src,tgt);
        }
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Action1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        if (Condition()(evt,fsm,state))
        {
            return Action1()(evt,fsm,state);
        }
    }
};

template <class Condition,class Action1>
struct If_Then_<Condition,Action1
    , typename ::boost::disable_if<typename has_tag_type<Action1>::type >::type>
    : euml_action<If_Then_<Condition,Action1> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef bool type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef bool type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    bool operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        if (Condition()(evt,fsm,src,tgt))
        {
            return Action1()(evt,fsm,src,tgt);
        }
    }
    template <class Event,class FSM,class STATE>
    bool operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        if (Condition()(evt,fsm,state))
        {
            return Action1()(evt,fsm,state);
        }
    }
};
struct if_then_tag 
{
};
struct If_Then : proto::extends< proto::terminal<if_then_tag>::type, If_Then, boost::msm::sm_domain>
{
    If_Then(){}
    using proto::extends< proto::terminal<if_then_tag>::type, If_Then, boost::msm::sm_domain>::operator=;
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef If_Then_<Arg1,Arg2> type;
    };
};
If_Then const if_then_;

template <class Condition,class Body>
struct While_Do_ : euml_action<While_Do_<Condition,Body> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef void type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef void type;
    };

    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    void operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        Body body_;
        Condition cond_;
        while (cond_(evt,fsm,src,tgt))
        {
            body_(evt,fsm,src,tgt);
        }
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        Body body_;
        Condition cond_;
        while (cond_(evt,fsm,state))
        {
            body_(evt,fsm,state);
        }
    }
};
struct while_do_tag 
{
};
struct While_Do_Helper : proto::extends< proto::terminal<while_do_tag>::type, While_Do_Helper, boost::msm::sm_domain>
{
    While_Do_Helper(){}
    using proto::extends< proto::terminal<while_do_tag>::type, While_Do_Helper, boost::msm::sm_domain>::operator=;
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef While_Do_<Arg1,Arg2> type;
    };
};
While_Do_Helper const while_;

template <class Condition,class Body>
struct Do_While_ : euml_action<Do_While_<Condition,Body> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef void type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef void type;
    };

    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    void operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        Condition cond_;
        Body body_;
        do
        {
            body_(evt,fsm,src,tgt);
        } while (cond_(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        Condition cond_;
        Body body_;
        do
        {
            body_(evt,fsm,state);
        } while (cond_(evt,fsm,state));
    }
};
struct do_while_tag 
{
};
struct Do_While_Helper : proto::extends< proto::terminal<do_while_tag>::type, Do_While_Helper, boost::msm::sm_domain>
{
    Do_While_Helper(){}
    using proto::extends< proto::terminal<do_while_tag>::type, Do_While_Helper, boost::msm::sm_domain>::operator=;
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Do_While_<Arg1,Arg2> type;
    };
};
Do_While_Helper const do_while_;

template <class Begin,class End,class EndLoop,class Body>
struct For_Loop_ : euml_action<For_Loop_<Begin,End,EndLoop,Body> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef void type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef void type;
    };

    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    void operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        End end_;
        EndLoop end_loop_;
        Body body_;
        for(Begin()(evt,fsm,src,tgt);end_(evt,fsm,src,tgt);end_loop_(evt,fsm,src,tgt))
        {
            body_(evt,fsm,src,tgt);
        }
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        End end_;
        EndLoop end_loop_;
        Body body_;
        for(Begin()(evt,fsm,state);end_(evt,fsm,state);end_loop_(evt,fsm,state))
        {
            body_(evt,fsm,state);
        }
    }
};
struct for_loop_tag 
{
};
struct For_Loop_Helper : proto::extends< proto::terminal<for_loop_tag>::type, For_Loop_Helper, boost::msm::sm_domain>
{
    For_Loop_Helper(){}
    using proto::extends< proto::terminal<for_loop_tag>::type, For_Loop_Helper, boost::msm::sm_domain>::operator=;
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef For_Loop_<Arg1,Arg2,Arg3,Arg4> type;
    };
};
For_Loop_Helper const for_;




template <class T>
struct Deref_ : euml_action<Deref_<T> >
{
    Deref_(){}
    using euml_action<Deref_<T> >::operator=;
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::add_reference<
                    typename std::iterator_traits <
                        typename ::boost::remove_reference<
                            typename get_result_type2<T,Event,FSM,STATE>::type>::type>::value_type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::add_reference<
                    typename std::iterator_traits< 
                        typename ::boost::remove_reference<
                            typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type
                    >::value_type
        >::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return *(T()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return *(T()(evt,fsm,state));
    }
};

template <class T>
struct Pre_inc_ : euml_action<Pre_inc_<T> >
{
    using euml_action<Pre_inc_<T> >::operator=;

    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<T,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return ++T()(evt,fsm,src,tgt);
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return ++T()(evt,fsm,state);
    }
};
template <class T>
struct Pre_dec_ : euml_action<Pre_dec_<T> >
{
    using euml_action<Pre_dec_<T> >::operator=;

    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<T,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return --T()(evt,fsm,src,tgt);
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return --T()(evt,fsm,state);
    }
};
template <class T>
struct Post_inc_ : euml_action<Post_inc_<T> >
{
    using euml_action<Post_inc_<T> >::operator=;

    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type2<T,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return T()(evt,fsm,src,tgt)++;
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return T()(evt,fsm,state)++;
    }
};
template <class T>
struct Post_dec_ : euml_action<Post_dec_<T> >
{
    using euml_action<Post_dec_<T> >::operator=;

    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type2<T,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return T()(evt,fsm,src,tgt)--;
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return T()(evt,fsm,state)--;
    }
};

template <class T1,class T2>
struct Plus_ : euml_action<Plus_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type2<T1,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return T1()(evt,fsm,src,tgt)+T2()(evt,fsm,src,tgt);
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return T1()(evt,fsm,state)+T2()(evt,fsm,state);
    }
};
template <class T1,class T2>
struct Minus_ : euml_action<Minus_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type2<T1,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return T1()(evt,fsm,src,tgt)-T2()(evt,fsm,src,tgt);
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return T1()(evt,fsm,state)-T2()(evt,fsm,state);
    }
};
template <class T1,class T2>
struct Multiplies_ : euml_action<Multiplies_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type2<T1,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return T1()(evt,fsm,src,tgt)*T2()(evt,fsm,src,tgt);
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return T1()(evt,fsm,state)*T2()(evt,fsm,state);
    }
};
template <class T1,class T2>
struct Divides_ : euml_action<Divides_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type2<T1,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return T1()(evt,fsm,src,tgt)/T2()(evt,fsm,src,tgt);
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return T1()(evt,fsm,state)/T2()(evt,fsm,state);
    }
};
template <class T1,class T2>
struct Modulus_ : euml_action<Modulus_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type2<T1,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return T1()(evt,fsm,src,tgt)%T2()(evt,fsm,src,tgt);
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return T1()(evt,fsm,state)%T2()(evt,fsm,state);
    }
};
template <class T1,class T2>
struct Bitwise_And_ : euml_action<Bitwise_And_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type2<T1,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return T1()(evt,fsm,src,tgt)&T2()(evt,fsm,src,tgt);
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return T1()(evt,fsm,state)&T2()(evt,fsm,state);
    }
};
template <class T1,class T2>
struct Bitwise_Or_ : euml_action<Bitwise_Or_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type2<T1,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return T1()(evt,fsm,src,tgt)|T2()(evt,fsm,src,tgt);
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return T1()(evt,fsm,state)|T2()(evt,fsm,state);
    }
};
template <class T1,class T2>
struct Bitwise_Xor_ : euml_action<Bitwise_Xor_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type2<T1,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return T1()(evt,fsm,src,tgt)^T2()(evt,fsm,src,tgt);
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return T1()(evt,fsm,state)^T2()(evt,fsm,state);
    }
};
template <class T1,class T2>
struct Subscript_ : euml_action<Subscript_<T1,T2> >
{
    template <class T>
    struct get_reference 
    {
        typedef typename T::reference type;
    };
    template <class T>
    struct get_mapped_type 
    {
        typedef typename T::value_type::second_type& type;
    };
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type2<T1,Event,FSM,STATE>::type>::type container_type;
        typedef typename ::boost::mpl::eval_if<
            typename has_key_type<container_type>::type,
            get_mapped_type<container_type>,
            ::boost::mpl::eval_if<
                typename ::boost::is_pointer<container_type>::type,
                ::boost::add_reference<typename ::boost::remove_pointer<container_type>::type >,
                get_reference<container_type> 
             >
        >::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type>::type container_type;
        typedef typename ::boost::mpl::eval_if<
            typename has_key_type<container_type>::type,
            get_mapped_type<container_type>,
            ::boost::mpl::eval_if<
                typename ::boost::is_pointer<container_type>::type,
                ::boost::add_reference<typename ::boost::remove_pointer<container_type>::type >,
                get_reference<container_type> 
             >
        >::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return T1()(evt,fsm,src,tgt)[T2()(evt,fsm,src,tgt)];
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return T1()(evt,fsm,state)[T2()(evt,fsm,state)];
    }
};
template <class T1,class T2>
struct Plus_Assign_ : euml_action<Plus_Assign_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<T1,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt)+=T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T1()(evt,fsm,state)+=T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct Minus_Assign_ : euml_action<Minus_Assign_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<T1,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt)-=T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T1()(evt,fsm,state)-=T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct Multiplies_Assign_ : euml_action<Multiplies_Assign_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<T1,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt)*=T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T1()(evt,fsm,state)*=T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct Divides_Assign_ : euml_action<Divides_Assign_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<T1,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt)/=T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T1()(evt,fsm,state)/=T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct Modulus_Assign_ : euml_action<Modulus_Assign_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<T1,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt)%=T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T1()(evt,fsm,state)%=T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct ShiftLeft_Assign_ : euml_action<ShiftLeft_Assign_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<T1,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt)<<=T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T1()(evt,fsm,state)<<=T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct ShiftRight_Assign_ : euml_action<ShiftRight_Assign_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<T1,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt)>>=T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T1()(evt,fsm,state)>>=T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct ShiftLeft_ : euml_action<ShiftLeft_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<T1,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt)<<T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T1()(evt,fsm,state)<<T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct ShiftRight_ : euml_action<ShiftRight_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<T1,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt)>>T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T1()(evt,fsm,state)>>T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct Assign_ : euml_action<Assign_<T1,T2> >
{
    using euml_action< Assign_<T1,T2> >::operator=;
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<T1,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt)=T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T1()(evt,fsm,state)=T2()(evt,fsm,state));
    }
};
template <class T1>
struct Unary_Plus_ : euml_action<Unary_Plus_<T1> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type2<T1,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return +T1()(evt,fsm,src,tgt);
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return +T1()(evt,fsm,state);
    }
};
template <class T1>
struct Unary_Minus_ : euml_action<Unary_Minus_<T1> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type2<T1,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::remove_reference<
            typename get_result_type<T1,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return -(T1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return -(T1()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct Less_ : euml_action<Less_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef bool type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef bool type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    bool operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt) < T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    bool operator()(Event const& evt,FSM& fsm,STATE& state)const
    {
        return (T1()(evt,fsm,state) < T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct LessEqual_ : euml_action<LessEqual_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef bool type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef bool type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    bool operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt) <= T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    bool operator()(Event const& evt,FSM& fsm,STATE& state)const
    {
        return (T1()(evt,fsm,state) <= T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct Greater_ : euml_action<Greater_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef bool type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef bool type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    bool operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt) > T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    bool operator()(Event const& evt,FSM& fsm,STATE& state)const
    {
        return (T1()(evt,fsm,state) > T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct GreaterEqual_ : euml_action<GreaterEqual_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef bool type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef bool type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    bool operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt) >= T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    bool operator()(Event const& evt,FSM& fsm,STATE& state)const
    {
        return (T1()(evt,fsm,state) >= T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct EqualTo_ : euml_action<EqualTo_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef bool type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef bool type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    bool operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt) == T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    bool operator()(Event const& evt,FSM& fsm,STATE& state)const
    {
        return (T1()(evt,fsm,state) == T2()(evt,fsm,state));
    }
};
template <class T1,class T2>
struct NotEqualTo_ : euml_action<NotEqualTo_<T1,T2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef bool type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef bool type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    bool operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T1()(evt,fsm,src,tgt) != T2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    bool operator()(Event const& evt,FSM& fsm,STATE& state)const
    {
        return (T1()(evt,fsm,state) != T2()(evt,fsm,state));
    }
};

}}}}

#endif // BOOST_MSM_FRONT_EUML_OPERATOR_H

/* operator.hpp
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
*/