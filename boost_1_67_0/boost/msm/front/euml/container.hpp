// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_CONTAINER_H
#define BOOST_MSM_FRONT_EUML_CONTAINER_H

#include <utility>
#include <boost/msm/front/euml/common.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/not.hpp>
#include <boost/msm/front/euml/operator.hpp>
#include <boost/type_traits.hpp>

BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator_category)

namespace boost { namespace msm { namespace front { namespace euml
{

template <class T>
struct Front_ : euml_action<Front_<T> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_reference< 
            typename ::boost::remove_reference<
                typename get_result_type2<T,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_reference< 
            typename ::boost::remove_reference<
                typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T()(evt,fsm,src,tgt)).front();
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T()(evt,fsm,state)).front();
    }
};

struct front_tag {};
struct Front_Helper: proto::extends< proto::terminal<front_tag>::type, Front_Helper, boost::msm::sm_domain>
{
    Front_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Front_<Arg1> type;
    };
};
Front_Helper const front_;

template <class T>
struct Back_ : euml_action<Back_<T> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_reference< 
            typename ::boost::remove_reference<
                typename get_result_type2<T,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_reference< 
            typename ::boost::remove_reference<
                typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T()(evt,fsm,src,tgt)).back();
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T()(evt,fsm,state)).back();
    }
};

struct back_tag {};
struct Back_Helper: proto::extends< proto::terminal<back_tag>::type, Back_Helper, boost::msm::sm_domain>
{
    Back_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Back_<Arg1> type;
    };
};
Back_Helper const back_;

template <class T>
struct Begin_ : euml_action<Begin_<T> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type2<T,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T()(evt,fsm,src,tgt)).begin();
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T()(evt,fsm,state)).begin();
    }
};

struct begin_tag {};
struct Begin_Helper: proto::extends< proto::terminal<begin_tag>::type, Begin_Helper, boost::msm::sm_domain>
{
    Begin_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Begin_<Arg1> type;
    };
};
Begin_Helper const begin_;

template <class T>
struct End_ : euml_action<End_<T> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type2<T,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T()(evt,fsm,src,tgt)).end();
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T()(evt,fsm,state)).end();
    }
};
struct end_tag {};
struct End_Helper: proto::extends< proto::terminal<end_tag>::type, End_Helper, boost::msm::sm_domain>
{
    End_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef End_<Arg1> type;
    };
};
End_Helper const end_;

template <class T>
struct RBegin_ : euml_action<RBegin_<T> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_reverse_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type2<T,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_reverse_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T()(evt,fsm,src,tgt)).rbegin();
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T()(evt,fsm,state)).rbegin();
    }
};

struct rbegin_tag {};
struct RBegin_Helper: proto::extends< proto::terminal<rbegin_tag>::type, RBegin_Helper, boost::msm::sm_domain>
{
    RBegin_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef RBegin_<Arg1> type;
    };
};
RBegin_Helper const rbegin_;

template <class T>
struct REnd_ : euml_action<REnd_<T> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_reverse_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type2<T,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_reverse_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T()(evt,fsm,src,tgt)).rend();
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T()(evt,fsm,state)).rend();
    }
};
struct rend_tag {};
struct REnd_Helper: proto::extends< proto::terminal<rend_tag>::type, REnd_Helper, boost::msm::sm_domain>
{
    REnd_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef REnd_<Arg1> type;
    };
};
REnd_Helper const rend_;

template <class Container,class Element>
struct Push_Back_ : euml_action<Push_Back_<Container,Element> >
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
        (Container()(evt,fsm,src,tgt)).push_back(Element()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).push_back(Element()(evt,fsm,state));        
    }
};
struct push_back_tag {};
struct Push_Back_Helper: proto::extends< proto::terminal<push_back_tag>::type, Push_Back_Helper, boost::msm::sm_domain>
{
    Push_Back_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Push_Back_<Arg1,Arg2> type;
    };
};
Push_Back_Helper const push_back_;

template <class Container>
struct Pop_Back_ : euml_action<Pop_Back_<Container> >
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
        (Container()(evt,fsm,src,tgt)).pop_back();
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).pop_back();        
    }
};
struct pop_back_tag {};
struct Pop_Back_Helper: proto::extends< proto::terminal<pop_back_tag>::type, Pop_Back_Helper, boost::msm::sm_domain>
{
    Pop_Back_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Pop_Back_<Arg1> type;
    };
};
Pop_Back_Helper const pop_back_;

template <class Container,class Element>
struct Push_Front_ : euml_action<Push_Front_<Container,Element> >
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
        (Container()(evt,fsm,src,tgt)).push_front(Element()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).push_front(Element()(evt,fsm,state));        
    }
};
struct push_front_tag {};
struct Push_Front_Helper: proto::extends< proto::terminal<push_front_tag>::type, Push_Front_Helper, boost::msm::sm_domain>
{
    Push_Front_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Push_Front_<Arg1,Arg2> type;
    };
};
Push_Front_Helper const push_front_;

template <class Container>
struct Pop_Front_ : euml_action<Pop_Front_<Container> >
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
        (Container()(evt,fsm,src,tgt)).pop_front();
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).pop_front();        
    }
};
struct pop_front_tag {};
struct Pop_Front_Helper: proto::extends< proto::terminal<pop_front_tag>::type, Pop_Front_Helper, boost::msm::sm_domain>
{
    Pop_Front_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Pop_Front_<Arg1> type;
    };
};
Pop_Front_Helper const pop_front_;

template <class Container>
struct Clear_ : euml_action<Clear_<Container> >
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
        (Container()(evt,fsm,src,tgt)).clear();
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).clear();        
    }
};
struct clear_tag {};
struct Clear_Helper: proto::extends< proto::terminal<clear_tag>::type, Clear_Helper, boost::msm::sm_domain>
{
    Clear_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Clear_<Arg1> type;
    };
};
Clear_Helper const clear_;

template <class Container>
struct ListReverse_ : euml_action<ListReverse_<Container> >
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
        (Container()(evt,fsm,src,tgt)).reverse();
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).reverse();        
    }
};
struct list_reverse_tag {};
struct ListReverse_Helper: proto::extends< proto::terminal<list_reverse_tag>::type, ListReverse_Helper, boost::msm::sm_domain>
{
    ListReverse_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef ListReverse_<Arg1> type;
    };
};
ListReverse_Helper const list_reverse_;

template <class Container, class Predicate, class Enable=void>
struct ListUnique_ : euml_action<ListUnique_<Container,Predicate,Enable> >
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
        (Container()(evt,fsm,src,tgt)).unique();
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).unique();        
    }
};
template <class Container, class Predicate >
struct ListUnique_<Container,Predicate,
               typename ::boost::disable_if<typename ::boost::is_same<Predicate,void>::type >::type> 
                    : euml_action<ListUnique_<Container,Predicate> >
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
        (Container()(evt,fsm,src,tgt)).unique(Predicate()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).unique(Predicate()(evt,fsm,state));        
    }
};
struct list_unique_tag {};
struct ListUnique_Helper: proto::extends< proto::terminal<list_unique_tag>::type, ListUnique_Helper, boost::msm::sm_domain>
{
    ListUnique_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef ListUnique_<Arg1,Arg2> type;
    };
};
ListUnique_Helper const list_unique_;

template <class Container, class Predicate, class Enable=void>
struct ListSort_ : euml_action<ListSort_<Container,Predicate,Enable> >
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
        (Container()(evt,fsm,src,tgt)).sort();
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).sort();        
    }
};
template <class Container, class Predicate >
struct ListSort_<Container,Predicate,
               typename ::boost::disable_if<typename ::boost::is_same<Predicate,void>::type >::type> 
                    : euml_action<ListSort_<Container,Predicate> >
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
        (Container()(evt,fsm,src,tgt)).sort(Predicate()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).sort(Predicate()(evt,fsm,state));        
    }
};
struct list_sort_tag {};
struct ListSort_Helper: proto::extends< proto::terminal<list_sort_tag>::type, ListSort_Helper, boost::msm::sm_domain>
{
    ListSort_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef ListSort_<Arg1,Arg2> type;
    };
};
ListSort_Helper const list_sort_;

template <class Container>
struct Capacity_ : euml_action<Capacity_<Container> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_size_type< 
            typename ::boost::remove_reference<
                typename get_result_type2<Container,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_size_type< 
            typename ::boost::remove_reference<
                typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).capacity();
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).capacity();        
    }
};
struct capacity_tag {};
struct Capacity_Helper: proto::extends< proto::terminal<capacity_tag>::type, Capacity_Helper, boost::msm::sm_domain>
{
    Capacity_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Capacity_<Arg1> type;
    };
};
Capacity_Helper const capacity_;

template <class Container>
struct Size_ : euml_action<Size_<Container> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_size_type< 
            typename ::boost::remove_reference<
                typename get_result_type2<Container,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_size_type< 
            typename ::boost::remove_reference<
                typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).size();
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).size();        
    }
};
struct size_tag {};
struct Size_Helper: proto::extends< proto::terminal<size_tag>::type, Size_Helper, boost::msm::sm_domain>
{
    Size_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Size_<Arg1> type;
    };
};
Size_Helper const size_;

template <class Container>
struct Max_Size_ : euml_action<Max_Size_<Container> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_size_type< 
            typename ::boost::remove_reference<
                typename get_result_type2<Container,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_size_type< 
            typename ::boost::remove_reference<
                typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).max_size();
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).max_size();        
    }
};
struct max_size_tag {};
struct Max_Size_Helper: proto::extends< proto::terminal<max_size_tag>::type, Max_Size_Helper, boost::msm::sm_domain>
{
    Max_Size_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Max_Size_<Arg1> type;
    };
};
Max_Size_Helper const max_size_;

template <class Container, class Value>
struct Reserve_ : euml_action<Reserve_<Container,Value> >
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
        (Container()(evt,fsm,src,tgt)).reserve(Value()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).reserve(Value()(evt,fsm,state));        
    }
};
struct reserve_tag {};
struct Reserve_Helper: proto::extends< proto::terminal<reserve_tag>::type, Reserve_Helper, boost::msm::sm_domain>
{
    Reserve_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Reserve_<Arg1,Arg2> type;
    };
};
Reserve_Helper const reserve_;

template <class Container, class Num, class Value ,class Enable=void >
struct Resize_ : euml_action<Resize_<Container,Num,Value> >
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
        (Container()(evt,fsm,src,tgt)).resize(Num()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).resize(Num()(evt,fsm,state));        
    }
};
template <class Container, class Num , class Value >
struct Resize_<Container,Num,Value,typename ::boost::disable_if<typename ::boost::is_same<Value,void>::type >::type> 
                    : euml_action<Resize_<Container,Num,Value> >
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
        (Container()(evt,fsm,src,tgt)).resize(Num()(evt,fsm,src,tgt),Value()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).resize(Num()(evt,fsm,state),Value()(evt,fsm,state));
    }
};
struct resize_tag {};
struct Resize_Helper: proto::extends< proto::terminal<resize_tag>::type, Resize_Helper, boost::msm::sm_domain>
{
    Resize_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Resize_<Arg1,Arg2,Arg3> type;
    };
};
Resize_Helper const resize_;

// version for 3 parameters (sequence containers)
template <class Container, class Param1, class Param2, class Param3 >
struct Insert_ : euml_action<Insert_<Container,Param1,Param2,Param3> >
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
        (Container()(evt,fsm,src,tgt)).insert(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),
                                              Param3()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).insert(Param1()(evt,fsm,state),Param2()(evt,fsm,state),
                                            Param3()(evt,fsm,state));
    }
};
// version for 2 parameters
template <class Container, class Param1, class Param2>
struct Insert_ < Container,Param1,Param2,void>
    : euml_action<Insert_<Container,Param1,Param2,void> >
{
    // return value will actually not be correct for set::insert(it1,it2), should be void
    // but it's ok as nobody should call an inexistent return type
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type2<Container,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    // version for transition + second param not an iterator (meaning that, Container is not an associative container)
    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::and_<
            typename ::boost::mpl::has_key<
                typename Container::tag_type,action_tag>::type,
                typename ::boost::mpl::not_<
                    typename has_iterator_category<
                        typename Param2::template transition_action_result<EVT,FSM,SourceState,TargetState>::type
                    >::type
                   >::type
                >::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type 
        >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).insert(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }

    // version for transition + second param is an iterator (meaning that, Container is an associative container)
    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::and_<
            typename ::boost::mpl::has_key<
                typename Container::tag_type,action_tag>::type,
                    typename has_iterator_category<
                        typename Param2::template transition_action_result<EVT,FSM,SourceState,TargetState>::type
                    >::type
                >::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type 
        >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        (Container()(evt,fsm,src,tgt)).insert(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }

    // version for state action + second param not an iterator (meaning that, Container is not an associative container)
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::and_<
            typename ::boost::mpl::has_key<
                typename Container::tag_type,state_action_tag>::type,
                typename ::boost::mpl::not_<
                    typename has_iterator_category<
                        typename Param2::template state_action_result<Event,FSM,STATE>::type
                    >::type
                   >::type
                >::type,
            typename state_action_result<Event,FSM,STATE>::type 
        >::type  
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).insert(Param1()(evt,fsm,state),Param2()(evt,fsm,state));        
    }

    // version for state action + second param is an iterator (meaning that, Container is an associative container)
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::and_<
            typename ::boost::mpl::has_key<
                typename Container::tag_type,state_action_tag>::type,
                    typename has_iterator_category<
                        typename Param2::template state_action_result<Event,FSM,STATE>::type
                    >::type
                >::type,
            typename state_action_result<Event,FSM,STATE>::type 
        >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).insert(Param1()(evt,fsm,state),Param2()(evt,fsm,state));        
    }
};

// version for 1 parameter (associative containers)
template <class Container, class Param1>
struct Insert_ < Container,Param1,void,void>
    : euml_action<Insert_<Container,Param1,void,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename std::pair<
            typename get_iterator< 
                typename ::boost::remove_reference<
                    typename get_result_type2<Container,Event,FSM,STATE>::type>::type>::type,bool> type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename std::pair<
            typename get_iterator< 
                typename ::boost::remove_reference<
                    typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type>::type,bool> type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).insert(Param1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).insert(Param1()(evt,fsm,state));        
    }
};
struct insert_tag {};
struct Insert_Helper: proto::extends< proto::terminal<insert_tag>::type, Insert_Helper, boost::msm::sm_domain>
{
    Insert_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Insert_<Arg1,Arg2,Arg3,Arg4> type;
    };
};
Insert_Helper const insert_;

template <class Container1,class Container2>
struct Swap_ : euml_action<Swap_<Container1,Container2> >
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
        (Container1()(evt,fsm,src,tgt)).swap(Container2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container1()(evt,fsm,state)).swap(Container2()(evt,fsm,state));        
    }
};
struct swap_tag {};
struct Swap_Helper: proto::extends< proto::terminal<swap_tag>::type, Swap_Helper, boost::msm::sm_domain>
{
    Swap_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Swap_<Arg1,Arg2> type;
    };
};
Swap_Helper const swap_;

template <class Container, class Iterator1, class Iterator2 ,class Enable=void >
struct Erase_ : euml_action<Erase_<Container,Iterator1,Iterator2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Iterator1,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Iterator1,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Iterator1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
    operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).erase(Iterator1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Iterator1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
    operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).erase(Iterator1()(evt,fsm,state));        
    }
};
template <class Container, class Iterator1 , class Iterator2 >
struct Erase_<Container,Iterator1,Iterator2,
              typename ::boost::disable_if<typename ::boost::is_same<Iterator2,void>::type >::type> 
                    : euml_action<Erase_<Container,Iterator1,Iterator2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Iterator1,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Iterator1,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Iterator1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
    operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).erase(Iterator1()(evt,fsm,src,tgt),Iterator2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Iterator1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
    operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).erase(Iterator1()(evt,fsm,state),Iterator2()(evt,fsm,state));        
    }
};
struct erase_tag {};
struct Erase_Helper: proto::extends< proto::terminal<erase_tag>::type, Erase_Helper, boost::msm::sm_domain>
{
    Erase_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Erase_<Arg1,Arg2,Arg3> type;
    };
};
Erase_Helper const erase_;

template <class Container>
struct Empty_ : euml_action<Empty_<Container> >
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
        return (Container()(evt,fsm,src,tgt)).empty();
    }
    template <class Event,class FSM,class STATE>
    bool operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).empty();        
    }
};
struct empty_tag {};
struct Empty_Helper: proto::extends< proto::terminal<empty_tag>::type, Empty_Helper, boost::msm::sm_domain>
{
    Empty_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Empty_<Arg1> type;
    };
};
Empty_Helper const empty_;

template <class Container,class Element>
struct ListRemove_ : euml_action<ListRemove_<Container,Element> >
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
        (Container()(evt,fsm,src,tgt)).remove(Element()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).remove(Element()(evt,fsm,state));        
    }
};
struct list_remove_tag {};
struct ListRemove_Helper: proto::extends< proto::terminal<list_remove_tag>::type, ListRemove_Helper, boost::msm::sm_domain>
{
    ListRemove_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef ListRemove_<Arg1,Arg2> type;
    };
};
ListRemove_Helper const list_remove_;

template <class Container,class Element>
struct ListRemove_If_ : euml_action<ListRemove_If_<Container,Element> >
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
        (Container()(evt,fsm,src,tgt)).remove_if(Element()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).remove_if(Element()(evt,fsm,state));        
    }
};
struct list_remove_if_tag {};
struct ListRemove_If_Helper: proto::extends< proto::terminal<list_remove_if_tag>::type, ListRemove_If_Helper, boost::msm::sm_domain>
{
    ListRemove_If_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef ListRemove_If_<Arg1,Arg2> type;
    };
};
ListRemove_If_Helper const list_remove_if_;

template <class Container, class ToMerge, class Predicate, class Enable=void>
struct ListMerge_ : euml_action<ListMerge_<Container,ToMerge,Predicate,Enable> >
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
        (Container()(evt,fsm,src,tgt)).merge(ToMerge()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).merge(ToMerge()(evt,fsm,state));        
    }
};
template <class Container, class ToMerge, class Predicate >
struct ListMerge_<Container,ToMerge,Predicate,
               typename ::boost::disable_if<typename ::boost::is_same<Predicate,void>::type >::type> 
                    : euml_action<ListMerge_<Container,ToMerge,Predicate> >
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
        (Container()(evt,fsm,src,tgt)).merge(ToMerge()(evt,fsm,src,tgt),Predicate()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).merge(ToMerge()(evt,fsm,state),Predicate()(evt,fsm,state));
    }
};
struct list_merge_tag {};
struct ListMerge_Helper: proto::extends< proto::terminal<list_merge_tag>::type, ListMerge_Helper, boost::msm::sm_domain>
{
    ListMerge_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef ListMerge_<Arg1,Arg2,Arg3> type;
    };
};
ListMerge_Helper const list_merge_;

template <class Container, class Param1, class Param2, class Param3, class Param4 ,class Enable=void >
struct Splice_ : euml_action<Splice_<Container,Param1,Param2,Param3,Param4,Enable> >
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
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).splice(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).splice(Param1()(evt,fsm,state),Param2()(evt,fsm,state));        
    }
};
template <class Container, class Param1, class Param2, class Param3, class Param4 >
struct Splice_<Container,Param1,Param2,Param3,Param4,
               typename ::boost::disable_if<  
                    typename ::boost::mpl::or_<typename ::boost::is_same<Param3,void>::type,
                                               typename ::boost::mpl::not_<
                                                    typename ::boost::is_same<Param4,void>::type>::type>::type >::type> 
                    : euml_action<Splice_<Container,Param1,Param2,Param3,Param4> >
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
        (Container()(evt,fsm,src,tgt)).splice(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),
                                              Param3()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).splice(Param1()(evt,fsm,state),Param2()(evt,fsm,state),
                                            Param3()(evt,fsm,state));
    }
};
template <class Container, class Param1, class Param2, class Param3, class Param4 >
struct Splice_<Container,Param1,Param2,Param3,Param4,
               typename ::boost::disable_if<typename ::boost::is_same<Param4,void>::type >::type> 
                    : euml_action<Splice_<Container,Param1,Param2,Param3,Param4> >
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
        (Container()(evt,fsm,src,tgt)).splice(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),
                                              Param3()(evt,fsm,src,tgt),Param4()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    void operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).splice(Param1()(evt,fsm,state),Param2()(evt,fsm,state),
                                            Param3()(evt,fsm,state),Param4()(evt,fsm,state));
    }
};
struct splice_tag {};
struct Splice_Helper: proto::extends< proto::terminal<splice_tag>::type, Splice_Helper, boost::msm::sm_domain>
{
    Splice_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Splice_<Arg1,Arg2,Arg3,Arg4,Arg5> type;
    };
};
Splice_Helper const splice_;

//template <class Container, class Param1, class Param2, class Param3, class Enable=void >
//struct StringFind_ : euml_action<StringFind_<Container,Param1,Param2,Param3,Enable> >
//{
//};
template <class Container,class Param1, class Param2, class Param3>
struct StringFind_ : euml_action<StringFind_<Container,Param1,Param2,Param3> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).
            find(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),Param3()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).
            find(Param1()(evt,fsm,state),Param2()(evt,fsm,state),Param3()(evt,fsm,state));
    }
};

template <class Container,class Param1>
struct StringFind_ < Container,Param1,void,void>
                : euml_action<StringFind_<Container,Param1,void,void> >

{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).find(Param1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).find(Param1()(evt,fsm,state));
    }
};

template <class Container,class Param1, class Param2>
struct StringFind_ <Container,Param1,Param2,void>
                : euml_action<StringFind_<Container,Param1,Param2,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).find(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).find(Param1()(evt,fsm,state),Param2()(evt,fsm,state));
    }
};

struct string_find_tag {};
struct StringFind_Helper: proto::extends< proto::terminal<string_find_tag>::type, StringFind_Helper, boost::msm::sm_domain>
{
    StringFind_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef StringFind_<Arg1,Arg2,Arg3,Arg4> type;
    };
};
StringFind_Helper const string_find_;

template <class Container, class Param1, class Param2, class Param3, class Enable=void >
struct StringRFind_ : euml_action<StringRFind_<Container,Param1,Param2,Param3,Enable> >
{
};

template <class Container,class Param1, class Param2, class Param3>
struct StringRFind_ < 
        Container,Param1,Param2,Param3,
        typename ::boost::enable_if< 
                    typename ::boost::is_same<Param2,void>::type
                    >::type
                >
                : euml_action<StringRFind_<Container,Param1,Param2,Param3> >

{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).rfind(Param1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).rfind(Param1()(evt,fsm,state));
    }
};

template <class Container,class Param1, class Param2, class Param3>
struct StringRFind_ < 
                Container,Param1,Param2,Param3,
                    typename ::boost::enable_if<
                        typename ::boost::mpl::and_<
                            typename ::boost::is_same<Param3,void>::type,
                            typename ::boost::mpl::not_<
                                typename ::boost::is_same<Param2,void>::type
                                                >::type
                                             >::type
                                       >::type
                    >
                : euml_action<StringRFind_<Container,Param1,Param2,Param3> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).rfind(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).rfind(Param1()(evt,fsm,state),Param2()(evt,fsm,state));
    }
};

template <class Container,class Param1, class Param2, class Param3>
struct StringRFind_< 
    Container,Param1,Param2,Param3,
            typename ::boost::disable_if< 
                                typename ::boost::is_same<Param3,void>::type
                                >::type
                >
                : euml_action<StringRFind_<Container,Param1,Param2,Param3> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).
            rfind(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),Param3()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).
            rfind(Param1()(evt,fsm,state),Param2()(evt,fsm,state),Param3()(evt,fsm,state));
    }
};

struct string_rfind_tag {};
struct StringRFind_Helper: proto::extends< proto::terminal<string_rfind_tag>::type, StringRFind_Helper, boost::msm::sm_domain>
{
    StringRFind_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef StringRFind_<Arg1,Arg2,Arg3,Arg4> type;
    };
};
StringRFind_Helper const string_rfind_;

template <class Container,class Param1, class Param2, class Param3>
struct StringFindFirstOf_ : euml_action<StringFindFirstOf_<Container,Param1,Param2,Param3> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).
            find_first_of(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),Param3()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).
            find_first_of(Param1()(evt,fsm,state),Param2()(evt,fsm,state),Param3()(evt,fsm,state));
    }
};
template <class Container,class Param1>
struct StringFindFirstOf_ <Container,Param1,void,void>
                : euml_action<StringFindFirstOf_<Container,Param1,void,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).find_first_of(Param1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).find_first_of(Param1()(evt,fsm,state));
    }
};

template <class Container,class Param1, class Param2>
struct StringFindFirstOf_ <Container,Param1,Param2,void>
                : euml_action<StringFindFirstOf_<Container,Param1,Param2,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).find_first_of(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).find_first_of(Param1()(evt,fsm,state),Param2()(evt,fsm,state));
    }
};

struct string_find_first_of_tag {};
struct StringFindFirstOf_Helper: 
    proto::extends< proto::terminal<string_find_first_of_tag>::type, StringFindFirstOf_Helper, boost::msm::sm_domain>
{
    StringFindFirstOf_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef StringFindFirstOf_<Arg1,Arg2,Arg3,Arg4> type;
    };
};
StringFindFirstOf_Helper const string_find_first_of_;

template <class Container, class Param1, class Param2, class Param3, class Enable=void >
struct StringFindFirstNotOf_ : euml_action<StringFindFirstNotOf_<Container,Param1,Param2,Param3,Enable> >
{
};

template <class Container,class Param1, class Param2, class Param3>
struct StringFindFirstNotOf_ < 
        Container,Param1,Param2,Param3,
        typename ::boost::enable_if< 
                    typename ::boost::is_same<Param2,void>::type
                    >::type
                >
                : euml_action<StringFindFirstNotOf_<Container,Param1,Param2,Param3> >

{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).find_first_not_of(Param1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).find_first_not_of(Param1()(evt,fsm,state));
    }
};

template <class Container,class Param1, class Param2, class Param3>
struct StringFindFirstNotOf_ < 
                Container,Param1,Param2,Param3,
                    typename ::boost::enable_if<
                        typename ::boost::mpl::and_<
                            typename ::boost::is_same<Param3,void>::type,
                            typename ::boost::mpl::not_<
                                typename ::boost::is_same<Param2,void>::type
                                                >::type
                                             >::type
                                       >::type
                    >
                : euml_action<StringFindFirstNotOf_<Container,Param1,Param2,Param3> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).find_first_not_of(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).find_first_not_of(Param1()(evt,fsm,state),Param2()(evt,fsm,state));
    }
};

template <class Container,class Param1, class Param2, class Param3>
struct StringFindFirstNotOf_< 
    Container,Param1,Param2,Param3,
            typename ::boost::disable_if< 
                                typename ::boost::is_same<Param3,void>::type
                                >::type
                >
                : euml_action<StringFindFirstNotOf_<Container,Param1,Param2,Param3> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).
            find_first_not_of(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),Param3()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).
            find_first_not_of(Param1()(evt,fsm,state),Param2()(evt,fsm,state),Param3()(evt,fsm,state));
    }
};

struct string_find_first_not_of_tag {};
struct StringFindFirstNotOf_Helper: 
    proto::extends< proto::terminal<string_find_first_not_of_tag>::type, StringFindFirstNotOf_Helper, boost::msm::sm_domain>
{
    StringFindFirstNotOf_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef StringFindFirstNotOf_<Arg1,Arg2,Arg3,Arg4> type;
    };
};
StringFindFirstNotOf_Helper const string_find_first_not_of_;

template <class Container, class Param1, class Param2, class Param3, class Enable=void >
struct StringFindLastOf_ : euml_action<StringFindLastOf_<Container,Param1,Param2,Param3,Enable> >
{
};

template <class Container,class Param1, class Param2, class Param3>
struct StringFindLastOf_ < 
        Container,Param1,Param2,Param3,
        typename ::boost::enable_if< 
                    typename ::boost::is_same<Param2,void>::type
                    >::type
                >
                : euml_action<StringFindLastOf_<Container,Param1,Param2,Param3> >

{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).find_last_of(Param1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).find_last_of(Param1()(evt,fsm,state));
    }
};

template <class Container,class Param1, class Param2, class Param3>
struct StringFindLastOf_ < 
                Container,Param1,Param2,Param3,
                    typename ::boost::enable_if<
                        typename ::boost::mpl::and_<
                            typename ::boost::is_same<Param3,void>::type,
                            typename ::boost::mpl::not_<
                                typename ::boost::is_same<Param2,void>::type
                                                >::type
                                             >::type
                                       >::type
                    >
                : euml_action<StringFindLastOf_<Container,Param1,Param2,Param3> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).find_last_of(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).find_last_of(Param1()(evt,fsm,state),Param2()(evt,fsm,state));
    }
};

template <class Container,class Param1, class Param2, class Param3>
struct StringFindLastOf_< 
    Container,Param1,Param2,Param3,
            typename ::boost::disable_if< 
                                typename ::boost::is_same<Param3,void>::type
                                >::type
                >
                : euml_action<StringFindLastOf_<Container,Param1,Param2,Param3> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).
            find_last_of(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),Param3()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).
            find_last_of(Param1()(evt,fsm,state),Param2()(evt,fsm,state),Param3()(evt,fsm,state));
    }
};

struct string_find_last_of_tag {};
struct StringFindLastOf_Helper: 
    proto::extends< proto::terminal<string_find_last_of_tag>::type, StringFindLastOf_Helper, boost::msm::sm_domain>
{
    StringFindLastOf_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef StringFindLastOf_<Arg1,Arg2,Arg3,Arg4> type;
    };
};
StringFindLastOf_Helper const string_find_last_of_;

template <class Container, class Param1, class Param2, class Param3, class Enable=void >
struct StringFindLastNotOf_ : euml_action<StringFindLastNotOf_<Container,Param1,Param2,Param3,Enable> >
{
};

template <class Container,class Param1, class Param2, class Param3>
struct StringFindLastNotOf_ < 
        Container,Param1,Param2,Param3,
        typename ::boost::enable_if< 
                    typename ::boost::is_same<Param2,void>::type
                    >::type
                >
                : euml_action<StringFindLastNotOf_<Container,Param1,Param2,Param3> >

{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).find_last_not_of(Param1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).find_last_not_of(Param1()(evt,fsm,state));
    }
};

template <class Container,class Param1, class Param2, class Param3>
struct StringFindLastNotOf_ < 
                Container,Param1,Param2,Param3,
                    typename ::boost::enable_if<
                        typename ::boost::mpl::and_<
                            typename ::boost::is_same<Param3,void>::type,
                            typename ::boost::mpl::not_<
                                typename ::boost::is_same<Param2,void>::type
                                                >::type
                                             >::type
                                       >::type
                    >
                : euml_action<StringFindLastNotOf_<Container,Param1,Param2,Param3> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).find_last_not_of(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).find_last_not_of(Param1()(evt,fsm,state),Param2()(evt,fsm,state));
    }
};

template <class Container,class Param1, class Param2, class Param3>
struct StringFindLastNotOf_< 
    Container,Param1,Param2,Param3,
            typename ::boost::disable_if< 
                                typename ::boost::is_same<Param3,void>::type
                                >::type
                >
                : euml_action<StringFindLastNotOf_<Container,Param1,Param2,Param3> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).
            find_last_not_of(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),Param3()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).
            find_last_not_of(Param1()(evt,fsm,state),Param2()(evt,fsm,state),Param3()(evt,fsm,state));
    }
};

struct string_find_last_not_of_tag {};
struct StringFindLastNotOf_Helper: 
    proto::extends< proto::terminal<string_find_last_of_tag>::type, StringFindLastNotOf_Helper, boost::msm::sm_domain>
{
    StringFindLastNotOf_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef StringFindLastNotOf_<Arg1,Arg2,Arg3,Arg4> type;
    };
};
StringFindLastNotOf_Helper const string_find_last_not_of_;

template <class Container>
struct Npos_ : euml_action<Npos_<Container> >
{
    Npos_(){}
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename Container::size_type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename Container::size_type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return Container::npos;
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return Container::npos;
    }
};

// version for 2 parameters
template <class Container, class Param1, class Param2>
struct Associative_Erase_ : euml_action<Associative_Erase_<Container,Param1,Param2> >
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
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        (Container()(evt,fsm,src,tgt)).erase(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).erase(Param1()(evt,fsm,state),Param2()(evt,fsm,state));        
    }
};
// version for 1 parameter
template <class Container, class Param1>
struct Associative_Erase_ < Container,Param1,void>
    : euml_action<Associative_Erase_<Container,Param1,void> >
{
    // return value will actually not be correct for set::erase(it), should be void
    // but it's ok as nobody should call an inexistent return type
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_size_type< 
            typename ::boost::remove_reference<
                typename get_result_type2<Container,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_size_type< 
            typename ::boost::remove_reference<
                typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    // version for transition + param is an iterator
    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::and_<
            typename ::boost::mpl::has_key<
                typename Container::tag_type,action_tag>::type,
                    typename has_iterator_category<
                        typename Param1::template transition_action_result<EVT,FSM,SourceState,TargetState>::type
                    >::type
                >::type,
            void 
        >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        (Container()(evt,fsm,src,tgt)).erase(Param1()(evt,fsm,src,tgt));
    }

    // version for state action + param is an iterator
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::and_<
            typename ::boost::mpl::has_key<
                typename Container::tag_type,state_action_tag>::type,
                    typename has_iterator_category<
                        typename Param1::template state_action_result<Event,FSM,STATE>::type
                    >::type
                >::type,
            void 
        >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        (Container()(evt,fsm,state)).erase(Param1()(evt,fsm,state));        
    }

    // version for transition + param not an iterator
    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::and_<
            typename ::boost::mpl::has_key<
                typename Container::tag_type,action_tag>::type,
                typename ::boost::mpl::not_<
                    typename has_iterator_category<
                        typename Param1::template transition_action_result<EVT,FSM,SourceState,TargetState>::type
                    >::type
                   >::type
                >::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type 
        >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).erase(Param1()(evt,fsm,src,tgt));
    }

    // version for state action + param not an iterator
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::and_<
            typename ::boost::mpl::has_key<
                typename Container::tag_type,state_action_tag>::type,
                typename ::boost::mpl::not_<
                    typename has_iterator_category<
                        typename Param1::template state_action_result<Event,FSM,STATE>::type
                    >::type
                   >::type
                >::type,
            typename state_action_result<Event,FSM,STATE>::type 
        >::type  
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).erase(Param1()(evt,fsm,state));        
    }
};

struct associative_erase_tag {};
struct Associative_Erase_Helper: proto::extends< proto::terminal<associative_erase_tag>::type, Associative_Erase_Helper, boost::msm::sm_domain>
{
    Associative_Erase_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Associative_Erase_<Arg1,Arg2,Arg3> type;
    };
};
Associative_Erase_Helper const associative_erase_;


template <class T, class Param>
struct Associative_Find_ : euml_action<Associative_Find_<T,Param> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type2<T,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T()(evt,fsm,src,tgt)).find(Param()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T()(evt,fsm,state)).find(Param()(evt,fsm,state));
    }
};

struct associative_find_tag {};
struct Associative_Find_Helper: proto::extends< proto::terminal<associative_find_tag>::type, Associative_Find_Helper, boost::msm::sm_domain>
{
    Associative_Find_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Associative_Find_<Arg1,Arg2> type;
    };
};
Associative_Find_Helper const associative_find_;

template <class Container,class Param>
struct AssociativeCount_ : euml_action<AssociativeCount_<Container,Param> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_size_type< 
            typename ::boost::remove_reference<
                typename get_result_type2<Container,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_size_type< 
            typename ::boost::remove_reference<
                typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).count(Param()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).count(Param()(evt,fsm,state));        
    }
};
struct associative_count_tag {};
struct AssociativeCount_Helper: proto::extends< proto::terminal<associative_count_tag>::type, AssociativeCount_Helper, boost::msm::sm_domain>
{
    AssociativeCount_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef AssociativeCount_<Arg1,Arg2> type;
    };
};
AssociativeCount_Helper const associative_count_;

template <class T, class Param>
struct Associative_Lower_Bound_ : euml_action<Associative_Lower_Bound_<T,Param> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type2<T,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T()(evt,fsm,src,tgt)).lower_bound(Param()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T()(evt,fsm,state)).lower_bound(Param()(evt,fsm,state));
    }
};

struct associative_lower_bound_tag {};
struct Associative_Lower_Bound_Helper: proto::extends< proto::terminal<associative_lower_bound_tag>::type, 
                                                       Associative_Lower_Bound_Helper, boost::msm::sm_domain>
{
    Associative_Lower_Bound_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Associative_Lower_Bound_<Arg1,Arg2> type;
    };
};
Associative_Lower_Bound_Helper const associative_lower_bound_;

template <class T, class Param>
struct Associative_Upper_Bound_ : euml_action<Associative_Upper_Bound_<T,Param> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type2<T,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T()(evt,fsm,src,tgt)).upper_bound(Param()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T()(evt,fsm,state)).upper_bound(Param()(evt,fsm,state));
    }
};

struct associative_upper_bound_tag {};
struct Associative_Upper_Bound_Helper: proto::extends< proto::terminal<associative_upper_bound_tag>::type, 
                                                       Associative_Upper_Bound_Helper, boost::msm::sm_domain>
{
    Associative_Upper_Bound_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Associative_Upper_Bound_<Arg1,Arg2> type;
    };
};
Associative_Upper_Bound_Helper const associative_upper_bound_;

template <class T>
struct First_ : euml_action<First_<T> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_first_type< 
            typename ::boost::remove_reference<
                typename get_result_type2<T,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_first_type< 
            typename ::boost::remove_reference<
                typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T()(evt,fsm,src,tgt)).first;
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T()(evt,fsm,state)).first;
    }
};

struct first_tag {};
struct First_Helper: proto::extends< proto::terminal<first_tag>::type, First_Helper, boost::msm::sm_domain>
{
    First_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef First_<Arg1> type;
    };
};
First_Helper const first_;

template <class T>
struct Second_ : euml_action<Second_<T> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_second_type< 
            typename ::boost::remove_reference<
                typename get_result_type2<T,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_second_type< 
            typename ::boost::remove_reference<
                typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T()(evt,fsm,src,tgt)).second;
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T()(evt,fsm,state)).second;
    }
};

struct second_tag {};
struct Second_Helper: proto::extends< proto::terminal<second_tag>::type, Second_Helper, boost::msm::sm_domain>
{
    Second_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Second_<Arg1> type;
    };
};
Second_Helper const second_;

template <class T, class Param>
struct Associative_Equal_Range_ : euml_action<Associative_Equal_Range_<T,Param> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef std::pair<
            typename get_iterator< 
                typename ::boost::remove_reference<
                    typename get_result_type2<T,Event,FSM,STATE>::type>::type>::type,
            typename get_iterator< 
                typename ::boost::remove_reference<
                    typename get_result_type2<T,Event,FSM,STATE>::type>::type>::type > type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef std::pair<
            typename get_iterator< 
                typename ::boost::remove_reference<
                    typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type>::type,
            typename get_iterator< 
                typename ::boost::remove_reference<
                    typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type>::type > type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (T()(evt,fsm,src,tgt)).equal_range(Param()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (T()(evt,fsm,state)).equal_range(Param()(evt,fsm,state));
    }
};

struct associative_equal_range_tag {};
struct Associative_Equal_Range_Helper: proto::extends< proto::terminal<associative_equal_range_tag>::type, 
                                                       Associative_Equal_Range_Helper, boost::msm::sm_domain>
{
    Associative_Equal_Range_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Associative_Equal_Range_<Arg1,Arg2> type;
    };
};
Associative_Equal_Range_Helper const associative_equal_range_;

template <class Container,class Param1, class Param2>
struct Substr_ : euml_action<Substr_<Container,Param1,Param2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).
            substr(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).
            substr(Param1()(evt,fsm,state),Param2()(evt,fsm,state));
    }
};
template <class Container>
struct Substr_ <Container,void,void>
                : euml_action<Substr_<Container,void,void> >

{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).substr();
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).substr();
    }
};

template <class Container,class Param1>
struct Substr_ < Container,Param1,void>
                : euml_action<Substr_<Container,Param1,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type2<Container,Event,FSM,STATE>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename remove_reference<
            typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).substr(Param1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).substr(Param1()(evt,fsm,state));
    }
};
struct substr_tag {};
struct Substr_Helper: proto::extends< proto::terminal<substr_tag>::type, Substr_Helper, boost::msm::sm_domain>
{
    Substr_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Substr_<Arg1,Arg2,Arg3> type;
    };
};
Substr_Helper const substr_;

template <class Container, class Param1, class Param2, class Param3, class Param4 >
struct StringCompare_ : euml_action<StringCompare_<Container,Param1,Param2,Param3,Param4> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef int type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef int type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).compare(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),
                                                      Param3()(evt,fsm,src,tgt),Param4()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).compare(Param1()(evt,fsm,state),Param2()(evt,fsm,state),
                                                    Param3()(evt,fsm,state),Param4()(evt,fsm,state));
    }
};
template <class Container, class Param1 >
struct StringCompare_<Container,Param1,void,void,void>  
    : euml_action<StringCompare_<Container,Param1,void,void,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef int type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef int type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).compare(Param1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).compare(Param1()(evt,fsm,state));        
    }
};

template <class Container, class Param1, class Param2>
struct StringCompare_<Container,Param1,Param2,void,void> 
                    : euml_action<StringCompare_<Container,Param1,Param2,void,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef int type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef int type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).compare(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).compare(Param1()(evt,fsm,state),Param2()(evt,fsm,state));
    }
};

template <class Container, class Param1, class Param2, class Param3 >
struct StringCompare_<Container,Param1,Param2,Param3,void> 
                    : euml_action<StringCompare_<Container,Param1,Param2,Param3,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef int type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef int type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).compare(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),
                                              Param3()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).compare(Param1()(evt,fsm,state),Param2()(evt,fsm,state),
                                            Param3()(evt,fsm,state));
    }
};

struct string_compare_tag {};
struct StringCompare_Helper: proto::extends< proto::terminal<string_compare_tag>::type, StringCompare_Helper, boost::msm::sm_domain>
{
    StringCompare_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef StringCompare_<Arg1,Arg2,Arg3,Arg4,Arg5> type;
    };
};
StringCompare_Helper const string_compare_;

template <class Container, class Param1, class Param2, class Param3 >
struct Append_ : euml_action<Append_<Container,Param1,Param2,Param3> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Container,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).append (Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),
                                                      Param3()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).append (Param1()(evt,fsm,state),Param2()(evt,fsm,state),
                                                    Param3()(evt,fsm,state));
    }
};
template <class Container, class Param1>
struct Append_<Container,Param1,void,void> 
                    : euml_action<Append_<Container,Param1,void,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Container,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).append(Param1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).append(Param1()(evt,fsm,state));        
    }
};

template <class Container, class Param1, class Param2 >
struct Append_<Container,Param1,Param2,void> 
                    : euml_action<Append_<Container,Param1,Param2,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Container,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).append(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).append(Param1()(evt,fsm,state),Param2()(evt,fsm,state));
    }
};

struct append_tag {};
struct Append_Helper: proto::extends< proto::terminal<append_tag>::type, Append_Helper, boost::msm::sm_domain>
{
    Append_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Append_<Arg1,Arg2,Arg3,Arg4> type;
    };
};
Append_Helper const append_;

template <class Container, class Param1, class Param2, class Param3, class Param4 >
struct StringInsert_ : euml_action<StringInsert_<Container,Param1,Param2,Param3,Param4> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Container,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).insert(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),
                                                     Param3()(evt,fsm,src,tgt),Param4()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).insert(Param1()(evt,fsm,state),Param2()(evt,fsm,state),
                                                   Param3()(evt,fsm,state),Param4()(evt,fsm,state));
    }
};
template <class Container, class Param1, class Param2>
struct StringInsert_ <Container,Param1,Param2,void,void>
                : euml_action<StringInsert_<Container,Param1,Param2,void,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Container,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).insert(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).insert(Param1()(evt,fsm,state),Param2()(evt,fsm,state));        
    }
};
template <class Container, class Param1, class Param2, class Param3>
struct StringInsert_<Container,Param1,Param2,Param3,void> 
                    : euml_action<StringInsert_<Container,Param1,Param2,Param3,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Container,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).insert(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),
                                                     Param3()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).insert(Param1()(evt,fsm,state),Param2()(evt,fsm,state),
                                                   Param3()(evt,fsm,state));
    }
};

struct string_insert_tag {};
struct StringInsert_Helper: proto::extends< proto::terminal<string_insert_tag>::type, StringInsert_Helper, boost::msm::sm_domain>
{
    StringInsert_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef StringInsert_<Arg1,Arg2,Arg3,Arg4,Arg5> type;
    };
};
StringInsert_Helper const string_insert_;

template <class Container,class Param1, class Param2>
struct StringErase_ : euml_action<StringErase_<Container,Param1,Param2> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Container,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).
            erase(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).
            erase(Param1()(evt,fsm,state),Param2()(evt,fsm,state));
    }
};
template <class Container>
struct StringErase_ <Container,void,void>
                : euml_action<StringErase_<Container,void,void> >

{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Container,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).erase();
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).erase();
    }
};

template <class Container,class Param1>
struct StringErase_ <Container,Param1,void>
                : euml_action<StringErase_<Container,Param1,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Container,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).erase(Param1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).erase(Param1()(evt,fsm,state));
    }
};

struct string_erase_tag {};
struct StringErase_Helper: proto::extends< proto::terminal<string_erase_tag>::type, StringErase_Helper, boost::msm::sm_domain>
{
    StringErase_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef StringErase_<Arg1,Arg2,Arg3> type;
    };
};
StringErase_Helper const string_erase_;

template <class Container, class Param1, class Param2, class Param3 >
struct StringAssign_ : euml_action<StringAssign_<Container,Param1,Param2,Param3> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Container,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).assign (Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),
                                                      Param3()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).assign (Param1()(evt,fsm,state),Param2()(evt,fsm,state),
                                                    Param3()(evt,fsm,state));
    }
};
template <class Container,class Param1>
struct StringAssign_ < 
        Container,Param1,void,void>
                : euml_action<StringAssign_<Container,Param1,void,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Container,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).assign(Param1()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).assign(Param1()(evt,fsm,state));        
    }
};

template <class Container, class Param1, class Param2 >
struct StringAssign_<Container,Param1,Param2,void> 
                    : euml_action<StringAssign_<Container,Param1,Param2,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Container,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).assign(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).assign(Param1()(evt,fsm,state),Param2()(evt,fsm,state));
    }
};
struct assign_tag {};
struct StringAssign_Helper: proto::extends< proto::terminal<assign_tag>::type, StringAssign_Helper, boost::msm::sm_domain>
{
    StringAssign_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef StringAssign_<Arg1,Arg2,Arg3,Arg4> type;
    };
};
StringAssign_Helper const string_assign_;

template <class Container,class Param1, class Param2, class Param3, class Param4>
struct StringReplace_ : euml_action<StringReplace_<Container,Param1,Param2,Param3,Param4> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Container,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).replace (Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),
                                                       Param3()(evt,fsm,src,tgt),Param4()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).replace (Param1()(evt,fsm,state),Param2()(evt,fsm,state),
                                                     Param3()(evt,fsm,state),Param4()(evt,fsm,state));
    }
};

template <class Container,class Param1, class Param2, class Param3>
struct StringReplace_<Container,Param1,Param2,Param3,void> 
                    : euml_action<StringReplace_<Container,Param1,Param2,Param3,void> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Container,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).replace(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),
                                                      Param3()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).replace(Param1()(evt,fsm,state),Param2()(evt,fsm,state),
                                                    Param3()(evt,fsm,state));        
    }
};

struct string_replace_tag {};
struct StringReplace_Helper: proto::extends< proto::terminal<string_replace_tag>::type, StringReplace_Helper, boost::msm::sm_domain>
{
    StringReplace_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef StringReplace_<Arg1,Arg2,Arg3,Arg4,Arg5> type;
    };
};
StringReplace_Helper const string_replace_;

template <class Container>
struct CStr_ : euml_action<CStr_<Container> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::add_const<
            typename get_value_type< 
                typename ::boost::remove_reference<
                    typename get_result_type2<Container,Event,FSM,STATE>::type>::type>::type>::type* type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::add_const<
            typename get_value_type< 
                typename ::boost::remove_reference<
                    typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type>::type>::type* type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).c_str();
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).c_str();        
    }
};
struct c_str_tag {};
struct CStr_Helper: proto::extends< proto::terminal<c_str_tag>::type, CStr_Helper, boost::msm::sm_domain>
{
    CStr_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef CStr_<Arg1> type;
    };
};
CStr_Helper const c_str_;

template <class Container>
struct StringData_ : euml_action<StringData_<Container> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename ::boost::add_const<
            typename get_value_type< 
                typename ::boost::remove_reference<
                    typename get_result_type2<Container,Event,FSM,STATE>::type>::type>::type>::type* type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename ::boost::add_const<
            typename get_value_type< 
                typename ::boost::remove_reference<
                    typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type>::type>::type* type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).data();
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Container::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).data();        
    }
};
struct string_data_tag {};
struct StringData_Helper: proto::extends< proto::terminal<string_data_tag>::type, StringData_Helper, boost::msm::sm_domain>
{
    StringData_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef StringData_<Arg1> type;
    };
};
StringData_Helper const string_data_;

template <class Container, class Param1, class Param2, class Param3, class Enable=void >
struct StringCopy_ : euml_action<StringCopy_<Container,Param1,Param2,Param3,Enable> >
{
};

template <class Container,class Param1, class Param2, class Param3>
struct StringCopy_< 
    Container,Param1,Param2,Param3,
            typename ::boost::enable_if< 
                                typename ::boost::is_same<Param3,void>::type
                                >::type
                >
                : euml_action<StringCopy_<Container,Param1,Param2,Param3> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_size_type< 
            typename ::boost::remove_reference<
                typename get_result_type2<Container,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_size_type< 
            typename ::boost::remove_reference<
                typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).copy(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).copy(Param1()(evt,fsm,state),Param2()(evt,fsm,state));
    }
};

template <class Container,class Param1, class Param2, class Param3>
struct StringCopy_< 
    Container,Param1,Param2,Param3,
            typename ::boost::disable_if< 
                                typename ::boost::is_same<Param3,void>::type
                                >::type
                >
                : euml_action<StringCopy_<Container,Param1,Param2,Param3> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_size_type< 
            typename ::boost::remove_reference<
                typename get_result_type2<Container,Event,FSM,STATE>::type>::type>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_size_type< 
            typename ::boost::remove_reference<
                typename get_result_type<Container,EVT,FSM,SourceState,TargetState>::type>::type>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState> 
    typename transition_action_result<EVT,FSM,SourceState,TargetState>::type
       operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return (Container()(evt,fsm,src,tgt)).
            copy(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),Param3()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename state_action_result<Event,FSM,STATE>::type
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return (Container()(evt,fsm,state)).
            copy(Param1()(evt,fsm,state),Param2()(evt,fsm,state),Param3()(evt,fsm,state));
    }
};

struct string_copy_tag {};
struct StringCopy_Helper: proto::extends< proto::terminal<string_copy_tag>::type, StringCopy_Helper, boost::msm::sm_domain>
{
    StringCopy_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef StringCopy_<Arg1,Arg2,Arg3,Arg4> type;
    };
};
StringCopy_Helper const string_copy_;

}}}}

#endif //BOOST_MSM_FRONT_EUML_CONTAINER_H

/* container.hpp
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
*/