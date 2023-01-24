
#ifndef BOOST_MPL_MULTIPLIES_HPP_INCLUDED
#define BOOST_MPL_MULTIPLIES_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/times.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/preprocessor/default_params.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

// backward compatibility header, deprecated

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#   define AUX778076_OP_ARITY BOOST_MPL_LIMIT_METAFUNCTION_ARITY
#else
#   define AUX778076_OP_ARITY 2
#endif

template<
      BOOST_MPL_PP_DEFAULT_PARAMS(AUX778076_OP_ARITY, typename N, na)
    >
struct multiplies
    : times< BOOST_MPL_PP_PARAMS(AUX778076_OP_ARITY, N) >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          AUX778076_OP_ARITY
        , multiplies
        , ( BOOST_MPL_PP_PARAMS(AUX778076_OP_ARITY, N) )
        )
};

BOOST_MPL_AUX_NA_SPEC(AUX778076_OP_ARITY, multiplies)

#undef AUX778076_OP_ARITY

}}

#endif // BOOST_MPL_MULTIPLIES_HPP_INCLUDED

/* multiplies.hpp
1x12PEiQN/E+Ern9abMccUh2t0msFgNDjjltKfPBvIS64tbb22k2ex8Wk+i9z6+FO0wQNAX3wf4IupOWiccThr8xOGi7scsS9QnAcreJNRBUy1it+eGBbzMP4woUNyes97ToCzpFhiLvMBCXzJllPTmLhTaoT15J8OqoneoDZH5Xs1/ODfDe9E5i3944+A17Tw5UtxYFIaJ4Xgl7WoQYXV9ebKzXT1G0mBPeBmGW3obOQv9+Q/4WktlO8n8l/D9n7ff/tYQNCaAaSsuRj6rr4o5yYI9PER6Rc7EUiXJ0UTR0JTUkAoVHg1iLOFZraXxkqwpV32qacHGyO3Fpm7OoUs27/IWQu2pqg0HDMLxtv0Jxd3e3AsWtaNHiDgWKW3EnuLu7u7sUd3cLkOJuwSUhZG1mj3Zn/8B7fs3zzl2nXC+N1Cr+B1pI532VLhmgEP3+CREEc2ZE76BwRtzG6Gxbs/3eYpUd5udo4d5ZRKuH6y3214mwr3tvj5fj0Uw2Ebsl/MF4FXA9o4/xylCNjKjzAVoCGswyMKcckBSSRE+Elxiwb44c9oWpaD7jDAbftanOFhOYZd25RVhIoRThLYRdU119BcV2yHb8TT8eSLnp/sO3XhHO6ys4yJUm3ZQxWMQa3DhhUd0elGWCcydom/e6K98Vnw7X0BgDdVN0P2rC653hCLEpXnIpXrpBh+u4SaNuGCYcs2bxikamXB+W
*/