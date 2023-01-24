
#ifndef BOOST_MPL_AUX_SORT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_SORT_IMPL_HPP_INCLUDED

// Copyright Eric Friedman 2002-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/partition.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename Seq, typename Pred >
struct quick_sort;

// agurt, 10/nov/04: for the sake of deficeint compilers 
template< typename Pred, typename Pivot >
struct quick_sort_pred
{
    template< typename T > struct apply
    {
        typedef typename apply2<Pred,T,Pivot>::type type;
    };
};

template< 
      typename Seq
    , typename Pred
    >
struct quick_sort_impl
{
    typedef typename begin<Seq>::type pivot;
    typedef typename partition<
          iterator_range< 
              typename next<pivot>::type
            , typename end<Seq>::type
            >
        , protect< aux::quick_sort_pred< Pred, typename deref<pivot>::type > >
        , back_inserter< vector<> >
        , back_inserter< vector<> >
        >::type partitioned;

    typedef typename quick_sort< typename partitioned::first, Pred >::type part1;
    typedef typename quick_sort< typename partitioned::second, Pred >::type part2;

    typedef joint_view< 
              joint_view< part1, single_view< typename deref<pivot>::type > >
            , part2
            > type;
};

template< 
      typename Seq
    , typename Pred
    >
struct quick_sort
    : eval_if<
          empty<Seq>
        , identity<Seq>
        , quick_sort_impl<Seq,Pred>
        >
{
};


template <
      typename Sequence
    , typename Pred
    , typename In
    >
struct sort_impl
{
    typedef typename quick_sort< 
          Sequence
        , typename if_na<Pred,less<> >::type
        >::type result_;
        
    typedef typename copy<result_,In>::type type;
};

template <
      typename Sequence
    , typename Pred
    , typename In
    >
struct reverse_sort_impl
{
    typedef typename quick_sort< 
          Sequence
        , typename if_na<Pred,less<> >::type
        >::type result_;
        
    typedef typename reverse_copy<result_,In>::type type;
};

}}}

#endif // BOOST_MPL_AUX_SORT_IMPL_HPP_INCLUDED

/* sort_impl.hpp
k05pXDy5gtZfOQTkD3C5tnlMzUByoevlxwfT/Ab1PzIbMQncdr8nYqSUfmpq08/IzCxVGNEqd0lMGuO+2QfnuLmD/rIKnKwdKcuqSQs6hfsj0lv38pRdhlO909HfRbyXKyE37hqjW1M5EbbB0/MHR4rMLsysz8+vTC2Y2Z5yNAV3QmxZBXfnM3Yt9GhppQUFB0pL6bKxIF/+cs0kJYMaY/e+glI0RaZ76ecpk5orYjcVUX40+CaJUViOnSj4yex85SSKm3SEEtxfTf75IZd5/oZ/3o2XvxkCadZlUcbHdxsYuLGwAGJiWqGhZa+p/WXf+zbW4QeJnDTz52PVffxsIPNTmXDw1V9qLEFZpL9w90k7pbE73wpI6I5R0rWKMjCLMrIAsPGUa+I7Z5jfOVg1vxV/t3O7q+CIbWI19rr2MG6Jqw+ol6AUKFAo5t22Bv1yW3XVXN05y8w9PrdG0L5MQF2xYD3OROsNCP7wDa91ZoUagkeKJiqKAxwTcRiL/asxwHMOH1VhpQXoyOhbYbd1Hj63uMtKecVy7fLplT/7N2tYC/qMX+t0cZ2la+DwCe8DFmNDZwklrd05ydOcUVemnhshkMgotXTWQlddg9bnVqDd4i9jzq7j7TOHyqWIxs1Ps3gl9bceWgro+UBQE7qz5Jdkn8+yWcbs6V4YxLfSmjxFL27Dx8eTDg/VYe5/1hD7TinNjjQarunlIUX7
*/