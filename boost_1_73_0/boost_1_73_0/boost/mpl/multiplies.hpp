
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
Ubt3i1tQP+gChM1tDUHGfDTLkzR0Drcap4OHlpcmMy3fK8JE6pXmr5UtSq7t29mFfHDekmShhb3uGZcVdWkuWgcU9/AUQwNPMeb6pwiEXvn8Ermufe9s6U+1Wd1B/VSjP7gdTXYXXLBIGFT0pK4nuhfsjzOVLmFhhcDEXLerOkm5rol7Xf0VlDsbVzRe7GxDeyB973AByLYRBvjeM5HMN+Y9hchcaYV2roqJhB4Hfa0ADzBVcPwnc9cI44pTnl454DX0T3HapRckGqhYR9/D4LjIvuyqR1U20PUp4N0u/vqAynUHwlwcAR51A5d3et8ejbu3N/D+pJStYPu193onD1I+Y9QK+52xlYtT6DE67X9wJEyXucZ4Cp1Bj6nuDw97IIK16UIYd3HHbHR1c2Iv4Ip5N8Ct4af+Y7vc/9R9/iqmrcdqLKt59bG0iN5/bIpe/9eLWrAk/KbTmnffP3ZGKa2OyrRyv5lW7zez6/iJVoc/hSde+GDbrHTe6mxsFCwJNKtv9q83KBdJo6B1MtflimcSji/Pwhr0p/Ll2zNSqtLarHZJZ5fnFUIuZmGVnRf+PRh1ydilue/tc987/Nf6J1BLAwQKAAAACAAtZ0pSKTP7ucYBAAATAwAAHQAJAGN1cmwtbWFzdGVyL3Rl
*/