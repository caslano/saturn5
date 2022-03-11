
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