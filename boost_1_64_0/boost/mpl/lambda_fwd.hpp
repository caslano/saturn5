
#ifndef BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED
#define BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/void_fwd.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   include <boost/mpl/int.hpp>
#   include <boost/mpl/aux_/lambda_arity_param.hpp>
#   include <boost/mpl/aux_/template_arity_fwd.hpp>

namespace boost { namespace mpl {

template< 
      typename T = na
    , typename Tag = void_
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(
          typename Arity = int_< aux::template_arity<T>::value >
        )
    >
struct lambda;

}}

#else // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#   include <boost/mpl/bool.hpp>

namespace boost { namespace mpl {

template< 
      typename T = na
    , typename Tag = void_
    , typename Protect = true_
    > 
struct lambda;

}}

#endif

#endif // BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED

/* lambda_fwd.hpp
mNzwtSuK0UM9nMb0SLfBamLm07Wem4UcpGgA3UfrpwLLFC00q62QR+fIaU68b5K187cyt+wCqhjlS5aM2j+nBntuz075f0tfEfTm2olKVk3IMGjoPtN1ba1kEiC1B9/iv1iCbkZDQZySmz1KjzuhXhDgTatkbMgi8X0rVcS6K4AEFsCnfOp6KcBFgkCcrHvaeVUYwzct3YRs8/dedFyAXgUJzc8vtWJTvvniRqORyFAynT36GX3xQs9Tgu2mUodhRKJD01oqtXpygT1mkPj4PFz0moGes/+z+90obeTGeei/IN23obBdtsasPD4JT0o2sKZXF059w9HJeWzhPSvJ1FzoLHnr/gUnQNqtQ2P3kNP7DOe5NOIp2CQYJflSat9pLufptN7JGL5AQHTdZTw+M/k489E6x6FUH2HVJpxt9QubMY+imBZSewIvpwuWRvKmOovcHXRR9tkZ+h2Ial8Z7608+2oo73vECWf6nMK7B3W1yhhNZvsiqEhx+Q+ECinxVChrc7FjTC6DzBk3xqeRM7KqCJ+cSrvuZsEo8qxllDoD/zb4EiOvHyCIHw==
*/