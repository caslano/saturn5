
#ifndef BOOST_MPL_COUNT_IF_HPP_INCLUDED
#define BOOST_MPL_COUNT_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Predicate >
struct next_if
{
    template<
          typename N
        , typename T
        >
    struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : eval_if<
              typename apply1<Predicate,T>::type
            , next<N>
            , identity<N>
            >
    {
#else
    {
        typedef typename eval_if<
              typename apply1<Predicate,T>::type
            , next<N>
            , identity<N>
            >::type type;
#endif
    };
};

} // namespace aux


template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    >
struct count_if
    : aux::msvc_eti_base< typename fold<
          Sequence
        , integral_c<unsigned long,0>
        , protect< aux::next_if<Predicate> >
        >::type >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,count_if,(Sequence,Predicate))
};

BOOST_MPL_AUX_NA_SPEC(2, count_if)

}}

#endif // BOOST_MPL_COUNT_IF_HPP_INCLUDED

/* count_if.hpp
fJEJBSSpGLaHkNbYrEMAeK/BkBqxggO2ShRUTz4BdRmq9HG9gSRwXa8f2r5pXj0hi5qoBl5RAnA7fXPLqRgJx+teL9bTEIA9fLwJ3UKubqUmxXlz7AS3ad4GPjqvv1G/IVBJEe5qnXqyjE0EUrTcHt5yJ7SA4GMpLG+JlW8DxwMirlkn034cbXn6DK0hvdXwbPsUqe+BsCbOpSjtHkBokMHovEJH47bgKFjf2r7WIrRkUHgXJ+e6APRzXWxBYKg6hIuQ08qxHDVd8O+yqAvGC0RITwPaG91yVWeElNw5P7io4mMwkAfmf3FFNEa9IJQGrwQtzIxz3Mf98yOAum5oP3JAHNfsQhuWowSEde9x6DsL7TcexrqyhxLeCL2XWnQTNQaCSySEjojpzoU5zZQdrxWCHh/BdSKA29AHFUMpqOrHseWJl19zZC1QTSvs+70jPj0PFNiuYru8yioPleaz6P0TINwdlQ9KfDzvNEHtupzqZWWZ0yuTqwAEvdk1QON/vf7UDEusbG0pP/4JNZ8FBGD2Wv6gMWZ9CXq+XRr0tvYrRzMRLm81yJf2JzEZUPO/YHXJfLOFdWQypDIIpeSnioNZJr6nQmTUgZNRl2fIY4XRodoOnRBRAPqGfrHopDTjX2Oto24JLA80LX28
*/