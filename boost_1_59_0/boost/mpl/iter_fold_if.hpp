
#ifndef BOOST_MPL_ITER_FOLD_IF_HPP_INCLUDED
#define BOOST_MPL_ITER_FOLD_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright Eric Friedman 2003
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
#include <boost/mpl/logical.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/iter_fold_if_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Predicate, typename LastIterator >
struct iter_fold_if_pred
{
    template< typename State, typename Iterator > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : and_<
              not_< is_same<Iterator,LastIterator> >
            , apply1<Predicate,Iterator>
            >
    {
#else
    {
        typedef and_<
              not_< is_same<Iterator,LastIterator> >
            , apply1<Predicate,Iterator>
            > type;
#endif
    };
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(ForwardOp)
    , typename BOOST_MPL_AUX_NA_PARAM(ForwardPredicate)
    , typename BOOST_MPL_AUX_NA_PARAM(BackwardOp)
    , typename BOOST_MPL_AUX_NA_PARAM(BackwardPredicate)
    >
struct iter_fold_if
{

    typedef typename begin<Sequence>::type first_;
    typedef typename end<Sequence>::type last_;

    typedef typename eval_if<
          is_na<BackwardPredicate>
        , if_< is_na<BackwardOp>, always<false_>, always<true_> >
        , identity<BackwardPredicate>
        >::type backward_pred_;

// cwpro8 doesn't like 'cut-off' type here (use typedef instead)
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003)) && !BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600))
    struct result_ :
#else
    typedef
#endif
        aux::iter_fold_if_impl<
          first_
        , State
        , ForwardOp
        , protect< aux::iter_fold_if_pred< ForwardPredicate,last_ > >
        , BackwardOp
        , backward_pred_
        >
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003)) && !BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600))
    { };
#else
    result_;
#endif

public:

    typedef pair<
          typename result_::state
        , typename result_::iterator
        > type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , iter_fold_if
        , (Sequence,State,ForwardOp,ForwardPredicate,BackwardOp,BackwardPredicate)
        )
};

BOOST_MPL_AUX_NA_SPEC(6, iter_fold_if)

}}

#endif // BOOST_MPL_ITER_FOLD_IF_HPP_INCLUDED

/* iter_fold_if.hpp
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
*/