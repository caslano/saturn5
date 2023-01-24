// Copyright David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_MATCH_DWA2005714_HPP
#define BOOST_PARAMETER_MATCH_DWA2005714_HPP

#include <boost/parameter/config.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
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
XD+7kx0VXDA8F9CI/lZ+tJRcWx1hxH2SWroKIFuaOTJVrel73YoBkazxHH7RtiHeyLBHPMQ7ISGNjVueRfNfH4euKp5ZuDd2tmmqab0oX7sTgOMcKqRjtJT6yRjRVWUznjpPNNsepDdb1fTpX9e1Ok7VOX241Jkqd224wUlX5rxb06WeDfEYB3fIdIsFvc4h4bWJJPfiLgtA/XlnwO+ZbjdcMXq4OSfev5FiFOfgrlY2INzIMvt/yi2dqaFPOq9UNw/YYXN0s2Dt+bwn1NXPG4XtzJnsOgkulz3FdkLAUXtySDy72wMqQj6HLesHP6SHVrrv8KT6/HugzfvU6+gjCtaUgEsRnxdw24Od1zKbGVRn7gl9JijM7PwJWBdN6MU5/nGNcy963E/2AXfFu3Ou9Il6G2U/YkCURyLSExAFAAdztWMyr/+gXmtUBDWnWAidgCPKKT6vkM/r0R4vMSgMhnqmaiwVSW9nnzFwkCeYP6j5eapxYpA/9a6Z79wVSWf6bfuxO9WIX4VGic74meglvG6r+TrebEvCtoSVy6jtQsLtrldD2t8NUdwmVkNsBtOavdIytfTvHvInc7oCvJ+jtF+ndlcsBUSFqY3AqX+ePJ6ah7AtNxzeXY7I3i53mvK2kt6hRSf6XG4mQd/5jJBJTkDVw+zdGX+aix46poXQ21uL/Jshes+dI7kWrfdrUi5mfyqrW5QKv97JvHPR
*/