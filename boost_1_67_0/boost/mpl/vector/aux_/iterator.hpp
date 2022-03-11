
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