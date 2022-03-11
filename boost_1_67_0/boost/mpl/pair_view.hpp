
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
+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
*/