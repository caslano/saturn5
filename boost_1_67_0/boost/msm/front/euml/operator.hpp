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