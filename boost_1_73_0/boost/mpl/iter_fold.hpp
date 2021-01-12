
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
dLD2wbiYNXkdG/BmNuMtbMPbOJa3cy7v5PVcxht5N+/j7/k47+EW3ss3uYJv8z5+wvsZOe+t4uFcy+P4GDtxHXtxPQfwCSbxSU7kRp7PTZzPp3kln+ENfJYP8zk+yT/yj3yRW7iZW/kyP+IWFpMnr7IEt7IKt7EO/8QW3M72fJtd+S77cCcH8wOm8888jx/yKn7M67mbD/Ev3MnP+RG/4OGRfr9Zi1/xVH7DAfyWF/BHzmMh
*/