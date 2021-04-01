
#ifndef BOOST_MPL_ITER_FOLD_HPP_INCLUDED
#define BOOST_MPL_ITER_FOLD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
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
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/iter_fold_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(ForwardOp)
    >
struct iter_fold
{
    typedef typename aux::iter_fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , typename lambda<ForwardOp>::type
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,iter_fold,(Sequence,State,ForwardOp))
};

BOOST_MPL_AUX_NA_SPEC(3, iter_fold)

}}

#endif // BOOST_MPL_ITER_FOLD_HPP_INCLUDED

/* iter_fold.hpp
rd5WTouPNcvAREusCrtoDfA98BKUR/Ci7c/NRumZTCDXAswWCtVemfFc3ThD81qCWCVlHnjziV4ckW7FO6yPbYOpRfwGXYh5TsdLAIxHzZFXc+ZFE/L0GrFLpOdJfAWrAlhXQoQaTLG1zyOXA/QyCBGEJG/U+QZD1DRD045sjcQiUSW81rJBzlvamFMTC/Rmp5WruB9m/Sjrhe5wskHMq4u6x+pi6s/QUlJXdfSykbTH1ScEDTZAAfS3oHtCDI9BTIRH5p2XOW+F9QBPQ/tWhaRCIjb2rW1M2nBEg4bhbfjmSgu3EmP4OKCTiYRhHxoXMiGVqS65ec4eL0ziMNjhPJt+U4lZrmFe2X5D/rgkBAFr6Gz4ZpnJm2UPhLhhW7/9a1o+ldrtu7WqUtIqlgAL4YZ8F7tRElkzjY6HWJF4NjaCz8nQx1keCJb6XpijIEqky+XTtN9nN54bKTaihA7IZiNd/39o4kOfIz5tx+nodxN9YeHFveKWj1HoSLJYz/tYT+FDxOw+MyOP4yI37Axv5mr6e8ADr6iToA1fnmUqzxDT7bNGPnhH7NuVww==
*/