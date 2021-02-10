
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
2zAQ/X7g/3BLKWxlruK2tNRzM0q7LWVbE9qs+1A6UOxzI+pIxlISAvvxO1lN066sMNiEsdHp3d3TvYczR9bl0lIPMqVLw587Wi5MU9ge9EejYfvC4eByBJlYH2UioGEDL6mZUxNbVRBkDdXVko8L6WQoIJLtBHe6XRx8RruweWUswal0lOJoRm+xe4jnZs6IpIvJXrp3mDL209cRhLopeoaxbTeilHcEJ0Y70i7+QvrWTVJMugDjSoaHmYXembjnwhRPKuUTAsW83TAg1OzBxLma4astZlpOKZDH6axyqpaNw9I009pYhwvlJpgHDhbLxkxRYqkq4kwRUjHLzXQqdRGKp0Js9nmCZ8N001cdDi5GYkFiIbUTyf4uxh+x4zOPssrcilJRVXC44+POmOoonzUVM3wouoHfCfOGeIroJsq27XFMzNEH+CwgkY+Unps7Kl5B1oLaNp0nbXqwug3424CE9jagaVEpTdq+hyVZrCtinwDerwiunRzfXJ9c3HiSTM9n+bmvBsw0r6hR5RK9IihLR03LziuKE2mZMWns2IlxHcjmLdbr4hpV9+DH65XQo2XNbnmQQngpYl/z3c/40XqzveVlDNlZ3RhnclP1wJsXn8x75csI+qxois/UieAb2yE+vuX2Kfrxi82r
*/