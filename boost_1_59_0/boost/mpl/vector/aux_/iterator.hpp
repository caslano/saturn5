
#ifndef BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/vector/aux_/at.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/distance_fwd.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct v_iter
{
    typedef aux::v_iter_tag tag;
    typedef random_access_iterator_tag category;
    typedef typename v_at<Vector,n_>::type type;

    typedef Vector vector_;
    typedef mpl::long_<n_> pos;

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    enum { 
          next_ = n_ + 1
        , prior_ = n_ - 1
        , pos_ = n_
    };
    
    typedef v_iter<Vector,next_> next;
    typedef v_iter<Vector,prior_> prior;
#endif

};


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct next< v_iter<Vector,n_> >
{
    typedef v_iter<Vector,(n_ + 1)> type;
};

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct prior< v_iter<Vector,n_> >
{
    typedef v_iter<Vector,(n_ - 1)> type;
};

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    , typename Distance
    >
struct advance< v_iter<Vector,n_>,Distance>
{
    typedef v_iter<
          Vector
        , (n_ + BOOST_MPL_AUX_NESTED_VALUE_WKND(long, Distance))
        > type;
};

template< 
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    , BOOST_MPL_AUX_NTTP_DECL(long, m_)
    > 
struct distance< v_iter<Vector,n_>, v_iter<Vector,m_> >
    : mpl::long_<(m_ - n_)>
{
};

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template<> struct advance_impl<aux::v_iter_tag>
{
    template< typename Iterator, typename N > struct apply
    {
        enum { pos_ = Iterator::pos_, n_ = N::value };
        typedef v_iter<
              typename Iterator::vector_
            , (pos_ + n_)
            > type;
    };
};

template<> struct distance_impl<aux::v_iter_tag>
{
    template< typename Iter1, typename Iter2 > struct apply
    {
        enum { pos1_ = Iter1::pos_, pos2_ = Iter2::pos_ };
        typedef long_<( pos2_ - pos1_ )> type;
        BOOST_STATIC_CONSTANT(long, value = ( pos2_ - pos1_ ));
    };
};

#endif

}}

#endif // BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED

/* iterator.hpp
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
*/