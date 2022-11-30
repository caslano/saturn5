
#ifndef BOOST_MPL_AUX_SINGLE_ELEMENT_ITER_HPP_INCLUDED
#define BOOST_MPL_AUX_SINGLE_ELEMENT_ITER_HPP_INCLUDED

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

#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/distance_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl { 

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

namespace aux {

template< typename T, BOOST_MPL_AUX_NTTP_DECL(int, is_last_) >
struct sel_iter;

template< typename T >
struct sel_iter<T,0>
{
    typedef random_access_iterator_tag category;
    typedef sel_iter<T,1> next;
    typedef T type;
};

template< typename T >
struct sel_iter<T,1>
{
    typedef random_access_iterator_tag category;
    typedef sel_iter<T,0> prior;
};

} // namespace aux

template< typename T, BOOST_MPL_AUX_NTTP_DECL(int, is_last_), typename Distance >
struct advance< aux::sel_iter<T,is_last_>,Distance>
{
    typedef aux::sel_iter<
          T
        , ( is_last_ + BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Distance) )
        > type;
};

template< 
      typename T
    , BOOST_MPL_AUX_NTTP_DECL(int, l1)
    , BOOST_MPL_AUX_NTTP_DECL(int, l2) 
    >
struct distance< aux::sel_iter<T,l1>, aux::sel_iter<T,l2> >
    : int_<( l2 - l1 )>
{
};

#else

namespace aux {

struct sel_iter_tag;

template< typename T, BOOST_MPL_AUX_NTTP_DECL(int, is_last_) >
struct sel_iter
{
    enum { pos_ = is_last_ };
    typedef aux::sel_iter_tag tag;
    typedef random_access_iterator_tag category;

    typedef sel_iter<T,(is_last_ + 1)> next;
    typedef sel_iter<T,(is_last_ - 1)> prior;
    typedef T type;
};

} // namespace aux

template<> struct advance_impl<aux::sel_iter_tag>
{
    template< typename Iterator, typename N > struct apply
    {
        enum { pos_ = Iterator::pos_, n_ = N::value };
        typedef aux::sel_iter<
              typename Iterator::type
            , (pos_ + n_)
            > type;
    };
};

template<> struct distance_impl<aux::sel_iter_tag>
{
    template< typename Iter1, typename Iter2 > struct apply
    {
        enum { pos1_ = Iter1::pos_, pos2_ = Iter2::pos_ };
        typedef int_<( pos2_ - pos1_ )> type;
        BOOST_STATIC_CONSTANT(int, value = ( pos2_ - pos1_ ));
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}

#endif // BOOST_MPL_AUX_SINGLE_ELEMENT_ITER_HPP_INCLUDED

/* single_element_iter.hpp
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
*/