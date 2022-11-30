// Copyright David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_MATCH_DWA2005714_HPP
#define BOOST_PARAMETER_MATCH_DWA2005714_HPP

#include <boost/parameter/config.hpp>

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
#include <boost/parameter/aux_/void.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/seq/size.hpp>

#define BOOST_PARAMETER_MATCH_DEFAULTS(ArgTypes)                             \
    BOOST_PP_ENUM_TRAILING_PARAMS(                                           \
        BOOST_PP_SUB(                                                        \
            BOOST_PARAMETER_MAX_ARITY                                        \
          , BOOST_PP_SEQ_SIZE(ArgTypes)                                      \
        )                                                                    \
      , ::boost::parameter::void_ BOOST_PP_INTERCEPT                         \
    )
/**/
#else
#define BOOST_PARAMETER_MATCH_DEFAULTS(ArgTypes)
#endif 

#include <boost/parameter/aux_/preprocessor/seq_enum.hpp>

//
// Generates, e.g.
//
//    typename dfs_params::match<A1,A2>::type name = dfs_params()
//
// with workarounds for Borland compatibility.
//
#define BOOST_PARAMETER_MATCH(ParameterSpec, ArgTypes, name)                 \
    typename ParameterSpec::match<                                           \
        BOOST_PARAMETER_SEQ_ENUM(ArgTypes)                                   \
        BOOST_PARAMETER_MATCH_DEFAULTS(ArgTypes)                             \
    >::type name = ParameterSpec()
/**/

#endif  // include guard


/* match.hpp
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
*/