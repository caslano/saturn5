
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