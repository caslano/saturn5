
#ifndef BOOST_MPL_AUX_PARTITION_OP_HPP_INCLUDED
#define BOOST_MPL_AUX_PARTITION_OP_HPP_INCLUDED

// Copyright Eric Friedman 2003
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>

namespace boost { namespace mpl { 

namespace aux {

template< typename Pred, typename In1Op, typename In2Op >
struct partition_op
{
    template< typename State, typename T >
    struct apply
    {
        typedef typename State::first first_;
        typedef typename State::second second_;
        typedef typename apply1< Pred,T >::type pred_;

        typedef typename eval_if<
              pred_
            , apply2<In1Op,first_,T>
            , apply2<In2Op,second_,T>
            >::type result_;

        typedef typename if_<
              pred_
            , pair< result_,second_ >
            , pair< first_,result_ >
            >::type type;
    };
};

} // namespace aux

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(3, aux::partition_op)

}}

#endif // BOOST_MPL_AUX_PARTITION_OP_HPP_INCLUDED

/* partition_op.hpp
PMItZqKXRZXJxwn3BayI0+mCvQJZVQojMA0oXIqD6TERZ78+QfAfAKLjDMUUFlfMWxcLMT2PpmiAL+QJtVhwGAntYqkCMiRwybiyc3py9PFgzzt82/M67vHepji2FdqkFeEc6BnlUs3R7sfuyd7RW3cXNon+BRgLi/0RRgHpjyLUHyVpoMxnbb7onu+qAIqwr27ATS5GQr9wdiOnIr5ZXMjx6WAA7JHotlT1hXCr3W29EMh13554qqGZGsp4OkBBARCAXAo5Q0amy+3HFzMjqIzIUecTQGy67hDoGWFJOCkOsREOuTyhlpiJvXCfkAxV8pjyiuJcFnMLY5RTX6wvwIcKxzQdEmOWJVAgwGgLXYthTXEXKXC9xWyLlrFN29d6yfQDLcT1fTIE5a/V1yIVHtqDorUduO4H6G3i88Hdjtzz0oHtcdkED4sH4GnkkiU3YwqRdKJ/93zP/nJ6un04tv/WBtb+p3PvoPM1qnXJ4ZvDPu6OO+MdrvL3ftYm3rsd79iNdKPX3Z103h+H5knqmye6b5xNPphnk/5BfOmb725DwPguBKb1EYjOBGlkiRQjqJC3bcrW0Yglm5XSdDFd/uQAr0MjqDesPrZNrGFTq9ftBm5qpNkIDNs3RMldGYb5v1PpYTz4lalk/UQq
*/