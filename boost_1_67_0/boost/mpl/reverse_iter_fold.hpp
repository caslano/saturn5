
#ifndef BOOST_MPL_ITER_FOLD_BACKWARD_HPP_INCLUDED
#define BOOST_MPL_ITER_FOLD_BACKWARD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright Dave Abrahams 2001-2002
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
#include <boost/mpl/O1_size.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/reverse_iter_fold_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(BackwardOp)
    , typename ForwardOp = arg<1>
    >
struct reverse_iter_fold
{
    typedef typename aux::reverse_iter_fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , typename lambda<BackwardOp>::type
        , typename lambda<ForwardOp>::type
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , reverse_iter_fold
        , (Sequence,State,BackwardOp,ForwardOp)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, reverse_iter_fold)

}}

#endif // BOOST_MPL_ITER_FOLD_BACKWARD_HPP_INCLUDED

/* reverse_iter_fold.hpp
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
*/