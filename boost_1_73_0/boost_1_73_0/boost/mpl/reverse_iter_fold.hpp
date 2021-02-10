
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
kHUmgkjpIhozeid3BKtDjbA1oFrCHus5/AXo7WU5Zru/HfoPKtD5kLzrnW/qtCzaU6Gpmd84SBATs5yo8ksU5kTy8xuQWu0xfjdRcCoo9+Wp0VZGOwMgecCBq/5+r/Q6kArOW9f3w/FgJPotySJZpvyE/KQ0ccoV8UptkbcAiCqIggLoPyar9Gkh+otl8vNXe8j3q6OWG1TkWuNG9yz4GnG4zp93/oJ1sWmgrQyoDWENlKPvBeTKwm9EDTc2N3TD5NFjHYVnjdnZ8Ace4DwJbiaMJfERpsd+uDpGk61TIyA71CXvv8yWq6dk3mOLNkU0DSNYGC3gGbGKJmVxxDCenYhWDJnMlDFz3zb8qXj/qmeSZVi58B2/u6Tv0kp+KQy//oTeAFBLAwQKAAAACAAtZ0pSj3CEoTkCAADVAwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE5MDVVVAUAAbZIJGCFU8Fu2kAQPbMS/zB1lEtUWKjSQxyDFFEIUWhAwem1Wtbj2MV4rN0l1H/fWdtJGvVQyZI9OzvvzXszjhxap5XFqYjyMiV+7bE+kUnsVCzjeCM00T5HKxarp+1SRPI9Hcm2QpzBFs0LmoHNExSRwaqoOZ0op6AknaHeT4IabdBCyvFw
*/