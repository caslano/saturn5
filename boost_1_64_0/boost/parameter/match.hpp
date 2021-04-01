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
FnDRW4awzTwETA4Sawu4FgFxY19AGFaD37WFEw8O8YClKN/bfwm8rIeQigD8bb+b01XkqEoLBw7ySb+JlURQIMNfPWcjb7A/XE0qquGTKfppUL8JkEVMwLxqujROilLnWcBaOjw4E0WEcd4dF2IYhI0KvbP5a+Q5wuMICpAmT2Tp9kfblie5aVmA/qoh+tx5iiNbOZpsVlKT32QlljWZ+2IvsXSeyqq1Ie52FVzc9mrtjshNEcD2vXSKc1H5LeJPqfkwxF/2YmxALItzdlR7KBsvO8IKUb2v+wMAFgIDtJbzJ+Tft0KxN+lE37QMPTaOzu9qO36vfu1nvbdwB/X/sGrbluUJaE8Cd4mJDxRywzR2IBvRMcdyRAd5WTpOFiSZcj8L1UUTF/2HOhWONG3HcRDhWUNhcf7ll6yNqWcZCwojXvIhYCX7c3VJSIFfXeKck06z+zLiR93skKqWVOwzyKVhNL1eWvFOHHg73NApqty48TQC3Wyj8l43dP1EviXSq+fW5Kol/7wJMfG0eaeOPRglYYbt/DulY5mFwYGkC4s7Coi5do+rKFRFjQ==
*/