
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

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/preprocessor.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
#   define AUX778076_INCLUDE_DIR typeof_based
#elif defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#   define AUX778076_INCLUDE_DIR no_ctps
#else
#   define AUX778076_INCLUDE_DIR plain
#endif

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_HEADER \
    AUX778076_INCLUDE_DIR/BOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX778076_HEADER \
    BOOST_PP_CAT(AUX778076_INCLUDE_DIR,/)##BOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/map/aux_/preprocessed/AUX778076_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/map/aux_/preprocessed/AUX778076_HEADER)
#endif

#   undef AUX778076_HEADER
#   undef AUX778076_INCLUDE_DIR

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
2ZE+kEM5TVBLEK34tSRz6n1JGfLkfCzaq7Phe0M3oBMrEClYW5KvZNl9H1soz3cwT+aQUVKPoM7e73ahS6SvMzOx/Il5TOtyWLDP34QKGB4MpFxFNpxXBcPBlFvfepx7vIIfCTPFjsU+LwCDXZ9mv6SRdqSj0aP7PTv2ypk71KrPmZ7mg4iv6/MqrKrEEBM5/jWvp8SbH9B/+1N07A+0VbQXH3uebD3ZepnjQtn3e3RMT/I3wvf+hESBtWaAgOBPAMVt+Nutp1tMW2RbAvq4F7hb6HRv3BQ3vbT2xjfgbFvqPYI9buo6ePk/XCj0Xmbo5Olg/jQm5KSTkyTRe2UfLFv6YHLOZSUNLJLPv85JNuTIC8Jjj08WEgSWBHEXrcgJlZq8yOeyIE++tv1eni0nZPb5TT4kaXoa22tkZOQonw+8d2xG/4sETgbmSxT1bNNJI+rut7neixSTfKwmRxfbxsr8EddfJmQs9jxNNRRbfxvRoplXFpx5x5P68acZq6ilwq7x2+7k9KPJ3Fi8X9iu5N7zhFWKAvPVpwUYhkdyeya2q4mAgaE57uaqCel2yyeXNE3+dPev44Y1ksm5htXemLyZ4NiLs8Zumvyt+nwySrgpNjB+ysqNPjC57vi9GqRwV1mBKzc7W3kKd0yyers5WcroQ+31F4XUqSgydZwTwpnqZrLec6kZ+rm8lY9xH7ovRePHkk4xqORN2Nnj
*/