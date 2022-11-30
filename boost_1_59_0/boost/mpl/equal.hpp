
#ifndef BOOST_MPL_EQUAL_HPP_INCLUDED
#define BOOST_MPL_EQUAL_HPP_INCLUDED

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

#include <boost/mpl/aux_/iter_fold_if_impl.hpp>
#include <boost/mpl/aux_/iter_apply.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Predicate
    , typename LastIterator1
    , typename LastIterator2
    >
struct equal_pred
{
    template<
          typename Iterator2
        , typename Iterator1
        >
    struct apply
    {
        typedef typename and_< 
              not_< is_same<Iterator1,LastIterator1> >
            , not_< is_same<Iterator2,LastIterator2> >
            , aux::iter_apply2<Predicate,Iterator1,Iterator2>
            >::type type;
    };
};

template<
      typename Sequence1
    , typename Sequence2
    , typename Predicate
    >
struct equal_impl
{
    typedef typename begin<Sequence1>::type first1_;
    typedef typename begin<Sequence2>::type first2_;
    typedef typename end<Sequence1>::type last1_;
    typedef typename end<Sequence2>::type last2_;

    typedef aux::iter_fold_if_impl<
          first1_
        , first2_
        , next<>
        , protect< aux::equal_pred<Predicate,last1_,last2_> >
        , void_
        , always<false_>
        > fold_;

    typedef typename fold_::iterator iter1_;
    typedef typename fold_::state iter2_;
    typedef and_<
          is_same<iter1_,last1_>
        , is_same<iter2_,last2_>
        > result_;

    typedef typename result_::type type;
};


} // namespace aux


template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence1)
    , typename BOOST_MPL_AUX_NA_PARAM(Sequence2)
    , typename Predicate = is_same<_,_>
    >
struct equal
    : aux::msvc_eti_base< 
          typename aux::equal_impl<Sequence1,Sequence2,Predicate>::type
        >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,equal,(Sequence1,Sequence2))
};

BOOST_MPL_AUX_NA_SPEC(2, equal)

}}

#endif // BOOST_MPL_EQUAL_HPP_INCLUDED

/* equal.hpp
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
*/