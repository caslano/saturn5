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