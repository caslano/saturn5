
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
cqcVaBakcasnf2b8d62WoAJJoEfDfKDqKSZA6r5UnrFVN72anNJyLjs9hJWSiXsLqV7k2KVtoZDYC5Ci4VtL2DxJdsUIk4SgUCgXhC07t5fZczpE7uPn5Cjir8DndosZGvA+9rYwWU/ZHGsIs/J1DWjev2kMGPgnNPPduLgfimTxxXIKgZNC2sVaxCgwwRt+fFMPAHvDQuY2G96trl4CGjzTG7Hw4uGEjkeS4g2EAWZC5rPxTbgpAndka+QQiJVa+3UwtVBUTJgFYAFNcMc5y/8xq8V1yYTzuxs1OGMjF+QPjVsVFzeUFZK+vwNC2cgYXZS2i3xgnTbVFe5brg8fUU0pZ0ZI7PocXX2i3zZfmfnzytRW9ivqGS01ccntAH7B7mh2GuUIeF6MR/73q+byWp81qxbVljoS0pZfSFg1yj3f6814w9KUaPEtskMTC+lzv1FAx+DDmT2kVleX6ZiPWsFSCJMMFDP2nvAJRqAxU/ymQ1rKF73ummwNyc9H9GuZSfpKn2o1tMeKV5C/XbKdtestW2pWIsVISDmiBB8zcYuIsuyvsffHnF/4KA==
*/