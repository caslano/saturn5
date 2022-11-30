
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
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
*/