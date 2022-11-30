// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_TRANSFORMATION_H
#define BOOST_MSM_FRONT_EUML_TRANSFORMATION_H

#include <algorithm>
#include <boost/msm/front/euml/common.hpp>

namespace boost { namespace msm { namespace front { namespace euml
{
#ifdef __STL_CONFIG_H
BOOST_MSM_EUML_FUNCTION(FillN_ , std::fill_n , fill_n_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(Rotate_ , std::rotate , rotate_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(GenerateN_ , std::generate_n , generate_n_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )

#else
BOOST_MSM_EUML_FUNCTION(FillN_ , std::fill_n , fill_n_ , void , void )
BOOST_MSM_EUML_FUNCTION(Rotate_ , std::rotate , rotate_ , void , void )
BOOST_MSM_EUML_FUNCTION(GenerateN_ , std::generate_n , generate_n_ , void , void )
#endif

BOOST_MSM_EUML_FUNCTION(Copy_ , std::copy , copy_ , RESULT_TYPE_PARAM3 , RESULT_TYPE2_PARAM3 )
BOOST_MSM_EUML_FUNCTION(CopyBackward_ , std::copy_backward , copy_backward_ , RESULT_TYPE_PARAM3 , RESULT_TYPE2_PARAM3 )
BOOST_MSM_EUML_FUNCTION(Reverse_ , std::reverse , reverse_ , void , void )
BOOST_MSM_EUML_FUNCTION(ReverseCopy_ , std::reverse_copy , reverse_copy_ , RESULT_TYPE_PARAM3 , RESULT_TYPE2_PARAM3 )
BOOST_MSM_EUML_FUNCTION(Remove_ , std::remove , remove_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(RemoveIf_ , std::remove_if , remove_if_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(RemoveCopy_ , std::remove_copy , remove_copy_ , RESULT_TYPE_PARAM3 , RESULT_TYPE2_PARAM3 )
BOOST_MSM_EUML_FUNCTION(RemoveCopyIf_ , std::remove_copy_if , remove_copy_if_ , RESULT_TYPE_PARAM3 , RESULT_TYPE2_PARAM3 )
BOOST_MSM_EUML_FUNCTION(Fill_ , std::fill , fill_ , void , void )
BOOST_MSM_EUML_FUNCTION(Generate_ , std::generate , generate_ , void , void )
BOOST_MSM_EUML_FUNCTION(Unique_ , std::unique , unique_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(UniqueCopy_ , std::unique_copy , unique_copy_ , RESULT_TYPE_PARAM3 , RESULT_TYPE2_PARAM3 )
#if __cplusplus < 201703L
BOOST_MSM_EUML_FUNCTION(RandomShuffle_ , std::random_shuffle , random_shuffle_ , void , void )
#endif
#if __cplusplus >= 201103L
BOOST_MSM_EUML_FUNCTION(Shuffle_ , std::shuffle , shuffle_ , void , void )
#endif
BOOST_MSM_EUML_FUNCTION(RotateCopy_ , std::rotate_copy , rotate_copy_ , RESULT_TYPE_PARAM4 , RESULT_TYPE2_PARAM4 )
BOOST_MSM_EUML_FUNCTION(Partition_ , std::partition , partition_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(StablePartition_ , std::stable_partition , stable_partition_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(Sort_ , std::sort , sort_ , void , void )
BOOST_MSM_EUML_FUNCTION(StableSort_ , std::stable_sort , stable_sort_ , void , void )
BOOST_MSM_EUML_FUNCTION(PartialSort_ , std::partial_sort , partial_sort_ , void , void )
BOOST_MSM_EUML_FUNCTION(PartialSortCopy_ , std::partial_sort_copy , partial_sort_copy_ , RESULT_TYPE_PARAM3 , RESULT_TYPE2_PARAM3 )
BOOST_MSM_EUML_FUNCTION(NthElement_ , std::nth_element , nth_element_ , void , void )
BOOST_MSM_EUML_FUNCTION(Merge_ , std::merge , merge_ , RESULT_TYPE_PARAM5 , RESULT_TYPE2_PARAM5 )
BOOST_MSM_EUML_FUNCTION(InplaceMerge_ , std::inplace_merge , inplace_merge_ , void , void )
BOOST_MSM_EUML_FUNCTION(SetUnion_ , std::set_union , set_union_ , RESULT_TYPE_PARAM5 , RESULT_TYPE2_PARAM5 )
BOOST_MSM_EUML_FUNCTION(PushHeap_ , std::push_heap , push_heap_ , void , void )
BOOST_MSM_EUML_FUNCTION(PopHeap_ , std::pop_heap , pop_heap_ , void , void )
BOOST_MSM_EUML_FUNCTION(MakeHeap_ , std::make_heap , make_heap_ , void , void )
BOOST_MSM_EUML_FUNCTION(SortHeap_ , std::sort_heap , sort_heap_ , void , void )
BOOST_MSM_EUML_FUNCTION(NextPermutation_ , std::next_permutation , next_permutation_ , bool , bool )
BOOST_MSM_EUML_FUNCTION(PrevPermutation_ , std::prev_permutation , prev_permutation_ , bool , bool )
BOOST_MSM_EUML_FUNCTION(InnerProduct_ , std::inner_product , inner_product_ , RESULT_TYPE_PARAM4 , RESULT_TYPE2_PARAM4 )
BOOST_MSM_EUML_FUNCTION(PartialSum_ , std::partial_sum , partial_sum_ , RESULT_TYPE_PARAM3 , RESULT_TYPE2_PARAM3 )
BOOST_MSM_EUML_FUNCTION(AdjacentDifference_ , std::adjacent_difference , adjacent_difference_ , RESULT_TYPE_PARAM3 , RESULT_TYPE2_PARAM3 )
BOOST_MSM_EUML_FUNCTION(Replace_ , std::replace , replace_ , void , void )
BOOST_MSM_EUML_FUNCTION(ReplaceIf_ , std::replace_if , replace_if_ , void , void )
BOOST_MSM_EUML_FUNCTION(ReplaceCopy_ , std::replace_copy , replace_copy_ , RESULT_TYPE_PARAM3 , RESULT_TYPE2_PARAM3 )
BOOST_MSM_EUML_FUNCTION(ReplaceCopyIf_ , std::replace_copy_if , replace_copy_if_ , RESULT_TYPE_PARAM3 , RESULT_TYPE2_PARAM3 )



template <class T>
struct BackInserter_ : euml_action<BackInserter_<T> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef std::back_insert_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type2<T,Event,FSM,STATE>::type>::type> type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef std::back_insert_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type> type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return std::back_inserter(T()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return std::back_inserter(T()(evt,fsm,state));
    }
};

struct back_inserter_tag {};
struct BackInserter_Helper: proto::extends< proto::terminal<back_inserter_tag>::type, BackInserter_Helper, boost::msm::sm_domain>
{
    BackInserter_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef BackInserter_<Arg1> type;
    };
};
BackInserter_Helper const back_inserter_;

template <class T>
struct FrontInserter_ : euml_action<FrontInserter_<T> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef std::front_insert_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type2<T,Event,FSM,STATE>::type>::type> type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef std::front_insert_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type> type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return std::front_inserter(T()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return std::front_inserter(T()(evt,fsm,state));
    }
};

struct front_inserter_tag {};
struct FrontInserter_Helper: proto::extends< proto::terminal<front_inserter_tag>::type, FrontInserter_Helper, boost::msm::sm_domain>
{
    FrontInserter_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef FrontInserter_<Arg1> type;
    };
};
FrontInserter_Helper const front_inserter_;

template <class T,class Pos>
struct Inserter_ : euml_action<Inserter_<T,Pos> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef std::insert_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type2<T,Event,FSM,STATE>::type>::type> type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef std::insert_iterator< 
            typename ::boost::remove_reference<
                typename get_result_type<T,EVT,FSM,SourceState,TargetState>::type>::type> type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
        operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return std::inserter(T()(evt,fsm,src,tgt),Pos()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename T::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
        operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return std::inserter(T()(evt,fsm,state),Pos()(evt,fsm,state));
    }
};

struct inserter_tag {};
struct Inserter_Helper: proto::extends< proto::terminal<inserter_tag>::type, Inserter_Helper, boost::msm::sm_domain>
{
    Inserter_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Inserter_<Arg1,Arg2> type;
    };
};
Inserter_Helper const inserter_;

template <class Param1, class Param2, class Param3, class Param4, class Param5, class Enable=void >
struct Transform_ : euml_action<Transform_<Param1,Param2,Param3,Param4,Param5,Enable> >
{
};

template <class Param1, class Param2, class Param3, class Param4, class Param5>
struct Transform_<Param1,Param2,Param3,Param4,Param5,
                  typename ::boost::enable_if<typename ::boost::is_same<Param5,void>::type >::type> 
                    : euml_action<Transform_<Param1,Param2,Param3,Param4,Param5> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Param3,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Param3,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Param1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return std::transform(Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),Param3()(evt,fsm,src,tgt),
                              Param4()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Param1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return std::transform(Param1()(evt,fsm,state),Param2()(evt,fsm,state),Param3()(evt,fsm,state),
                              Param4()(evt,fsm,state));        
    }
};

template <class Param1, class Param2, class Param3, class Param4, class Param5>
struct Transform_<Param1,Param2,Param3,Param4,Param5,
               typename ::boost::disable_if<typename ::boost::is_same<Param5,void>::type >::type> 
                    : euml_action<Transform_<Param1,Param2,Param3,Param4,Param5> >
{
    template <class Event,class FSM,class STATE >
    struct state_action_result 
    {
        typedef typename get_result_type2<Param4,Event,FSM,STATE>::type type;
    };
    template <class EVT,class FSM,class SourceState,class TargetState>
    struct transition_action_result 
    {
        typedef typename get_result_type<Param4,EVT,FSM,SourceState,TargetState>::type type;
    };
    typedef ::boost::mpl::set<state_action_tag,action_tag> tag_type;

    template <class EVT,class FSM,class SourceState,class TargetState>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Param1::tag_type,action_tag>::type,
            typename transition_action_result<EVT,FSM,SourceState,TargetState>::type >::type 
     operator()(EVT const& evt, FSM& fsm,SourceState& src,TargetState& tgt)const
    {
        return std::transform (Param1()(evt,fsm,src,tgt),Param2()(evt,fsm,src,tgt),Param3()(evt,fsm,src,tgt),
                               Param4()(evt,fsm,src,tgt),Param5()(evt,fsm,src,tgt));
    }
    template <class Event,class FSM,class STATE>
    typename ::boost::enable_if<
        typename ::boost::mpl::has_key<
            typename Param1::tag_type,state_action_tag>::type,
            typename state_action_result<Event,FSM,STATE>::type >::type 
     operator()(Event const& evt,FSM& fsm,STATE& state )const
    {
        return std::transform (Param1()(evt,fsm,state),Param2()(evt,fsm,state),Param3()(evt,fsm,state),
                               Param4()(evt,fsm,state),Param5()(evt,fsm,state));
    }
};
struct transform_tag {};
struct Transform_Helper: proto::extends< proto::terminal<transform_tag>::type, Transform_Helper, boost::msm::sm_domain>
{
    Transform_Helper(){}
    template <class Arg1,class Arg2,class Arg3,class Arg4,class Arg5 
#ifdef BOOST_MSVC 
 ,class Arg6 
#endif
>
    struct In
    {
        typedef Transform_<Arg1,Arg2,Arg3,Arg4,Arg5> type;
    };
};
Transform_Helper const transform_;

}}}}

#endif //BOOST_MSM_FRONT_EUML_TRANSFORMATION_H

/* transformation.hpp
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
*/