
#ifndef BOOST_MPL_PAIR_VIEW_HPP_INCLUDED
#define BOOST_MPL_PAIR_VIEW_HPP_INCLUDED

// Copyright David Abrahams 2003-2004
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/iterator_category.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/min_max.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

namespace aux {
struct pair_iter_tag;

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Iter1, typename Iter2, typename Category >
struct pair_iter;

template< typename Category > struct prior_pair_iter
{
    template< typename Iter1, typename Iter2 > struct apply
    {
        typedef typename mpl::prior<Iter1>::type i1_;
        typedef typename mpl::prior<Iter2>::type i2_;
        typedef pair_iter<i1_,i2_,Category> type;
    };
};

template<> struct prior_pair_iter<forward_iterator_tag>
{
    template< typename Iter1, typename Iter2 > struct apply
    {
        typedef pair_iter<Iter1,Iter2,forward_iterator_tag> type;
    };
};

#endif
}

template< 
      typename Iter1
    , typename Iter2
    , typename Category
    >
struct pair_iter
{
    typedef aux::pair_iter_tag tag;
    typedef Category category;
    typedef Iter1 first;
    typedef Iter2 second;
    
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    typedef pair< 
          typename deref<Iter1>::type
        , typename deref<Iter2>::type
        > type;

    typedef typename mpl::next<Iter1>::type i1_;
    typedef typename mpl::next<Iter2>::type i2_;
    typedef pair_iter<i1_,i2_,Category> next;
    
    typedef apply_wrap2< aux::prior_pair_iter<Category>,Iter1,Iter2 >::type prior;
#endif
};


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Iter1, typename Iter2, typename C >
struct deref< pair_iter<Iter1,Iter2,C> >
{
    typedef pair< 
          typename deref<Iter1>::type
        , typename deref<Iter2>::type
        > type;
};

template< typename Iter1, typename Iter2, typename C >
struct next< pair_iter<Iter1,Iter2,C> >
{
    typedef typename mpl::next<Iter1>::type i1_;
    typedef typename mpl::next<Iter2>::type i2_;
    typedef pair_iter<i1_,i2_,C> type;
};

template< typename Iter1, typename Iter2, typename C >
struct prior< pair_iter<Iter1,Iter2,C> >
{
    typedef typename mpl::prior<Iter1>::type i1_;
    typedef typename mpl::prior<Iter2>::type i2_;
    typedef pair_iter<i1_,i2_,C> type;
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION


template<> struct advance_impl<aux::pair_iter_tag>
{
    template< typename Iter, typename D > struct apply
    {
        typedef typename mpl::advance< typename Iter::first,D >::type i1_;
        typedef typename mpl::advance< typename Iter::second,D >::type i2_;
        typedef pair_iter<i1_,i2_,typename Iter::category> type;
    };
};

template<> struct distance_impl<aux::pair_iter_tag>
{
    template< typename Iter1, typename Iter2 > struct apply
    {
        // agurt, 10/nov/04: MSVC 6.5 ICE-s on forwarding
        typedef typename mpl::distance<
              typename first<Iter1>::type
            , typename first<Iter2>::type
            >::type type;
    };
};


template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence1)
    , typename BOOST_MPL_AUX_NA_PARAM(Sequence2)
    >
struct pair_view
{
    typedef nested_begin_end_tag tag;

    typedef typename begin<Sequence1>::type iter1_;
    typedef typename begin<Sequence2>::type iter2_;
    typedef typename min<
          typename iterator_category<iter1_>::type
        , typename iterator_category<iter2_>::type
        >::type category_;
    
    typedef pair_iter<iter1_,iter2_,category_> begin;
    
    typedef pair_iter<
          typename end<Sequence1>::type
        , typename end<Sequence2>::type
        , category_
        > end;
};

BOOST_MPL_AUX_NA_SPEC(2, pair_view)

}}

#endif // BOOST_MPL_PAIR_VIEW_HPP_INCLUDED

/* pair_view.hpp
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
*/