//==============================================================================
//         Copyright 2003 - 2011  LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011  LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011         Eric Niebler
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_PROTO_PREPROCESSOR_REMOVE_TYPENAME_HPP_INCLUDED
#define BOOST_PROTO_PREPROCESSOR_REMOVE_TYPENAME_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the BOOST_PROTO_REMOVE_TYPENAME macro
 */
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/expand.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>

//==============================================================================
// Boost.Preprocessor author P. Mensodines confirmed on an Boost email thread
// (subject ``check if a token is a keyword (was "BOOST_PP_IS_UNARY()")'')
// that it is OK to used `PP_IS_UNARY()` to check if tokens match predefined
// "keyword" as it is done by the macros below (even if `PP_IS_UNARY()` is
// technically only part of Boost.Preprocessor private API).
//==============================================================================

//==============================================================================
// `checking_prefix ## tokens` expand to unary (e.g., `(1)`) iff `tokens` start
// with keyword to check.
//==============================================================================
#define BOOST_PROTO_DETAILS_KEYWORD_FACILITY_IS_FRONT(T, CHECKING_PREFIX)                           \
    BOOST_PP_IS_UNARY(BOOST_PP_CAT(CHECKING_PREFIX, T))                                             \
    /**/

//==============================================================================
// `is_front_macro(tokens)` is 1 iff `tokens` start with keyword to remove.
// `removing_prefix ## <keyword-to-remove>` must expand to nothing.
//==============================================================================
#define BOOST_PROTO_DETAILS_KEYWORD_FACILITY_REMOVE_FRONT(TOKENS, IS_FRONT_MACRO, REMOVING_PREFIX)  \
    BOOST_PP_EXPAND( /* without EXPAND doesn't expand on MSVC */                                    \
        BOOST_PP_IIF(                                                                               \
            IS_FRONT_MACRO(TOKENS)                                                                  \
          , BOOST_PP_CAT                                                                            \
          , TOKENS BOOST_PP_TUPLE_EAT(2)                                                            \
        )(REMOVING_PREFIX, TOKENS)                                                                  \
    )                                                                                               \
    /**/

#define BOOST_PROTO_DETAILS_KEYWORD_TYPENAME_IS_typename (1) /* unary */
#define typename_BOOST_PROTO_DETAILS_KEYWORD_TYPENAME_IS (1) /* unary */
#define BOOST_PROTO_DETAILS_KEYWORD_TYPENAME_REMOVE_typename /* nothing */
#define typename_BOOST_PROTO_DETAILS_KEYWORD_TYPENAME_REMOVE /* nothing */

#define BOOST_PROTO_DETAILS_KEYWORD_IS_TYPENAME_FRONT(TOKENS)                                       \
    BOOST_PROTO_DETAILS_KEYWORD_FACILITY_IS_FRONT(TOKENS, BOOST_PROTO_DETAILS_KEYWORD_TYPENAME_IS_) \
    /**/

//==============================================================================
/*!
 * \ingroup preprocessor
 * For any symbol \c X, this macro returns the same symbol from which a potential
 * leading \c typename keyword has been removed. If no typename keyword is present,
 * this macros evaluates to \c X itself without error.
 *
 * The original implementation of this macro is from Lorenzo Caminiti.
 *
 * \param X Symbol to remove \c typename from
 */
//==============================================================================
#define BOOST_PROTO_REMOVE_TYPENAME(X)                                                              \
    BOOST_PROTO_DETAILS_KEYWORD_FACILITY_REMOVE_FRONT(                                              \
        X                                                                                           \
      , BOOST_PROTO_DETAILS_KEYWORD_IS_TYPENAME_FRONT                                               \
      , BOOST_PROTO_DETAILS_KEYWORD_TYPENAME_REMOVE_                                                \
    )                                                                                               \
    /**/

#endif

/* remove_typename.hpp
fDRqsSaov/WWTMqjZG6P2cyJ2fw0IPrb/ls/k1tKnyyCvHR2bhFiAMt6432eOC8HKt7ZwhnrIp/bjoRY7Yvohi8Pk1NGuxT2mAx5ysnnFrP5VFQibj3AvW45lS9Emjuz2+JSs7IKS/wdcznbD98i+2nysCdysMysdkHnzX6hbC6ZT7QA6+j1S+Qw/n64w8OZGdRtcdNui+T8Zj/dE8Q84jJ9JDrB50f2uJ1dyMvWJ1lHdgrOfP2iTbIOmvlfsT0Yst7P4kLj4skWR94O5bn7I2a+SpivxWOvTc0W5Lf5yHaTs+djSvMTgjM9rEYpPhPdazLW/KrPQ2xZck6U3LjJGXOeyNsFL/c6ow9dsdKUc5ndxyv7XVao/2p8Hm/JDLXXNYvzzWM/GzMZ3zx2x2HC8xiPByuOmJuKxKzvMBnf3JTbYzLW3FTkurM5c25i7vRukzPnJr13qThceG76kcWG5qbbIyYn5yaery2G5hHJfNVl+ohmnvdYk6F5JBLMhByr5gs7Xf42yDZyvaDqdjK4cJ88ZXG+OeSgzHtJMdJzrhin09tNzp5D+M677Isw5llDVG33D6fJzlnLHhRH1OE/dvo5FcTzcHKbzXTbaqtIh1tdtrPb5XBNnssEd327zYGZr9qJvjW2ye3yfUQ7XbpyHe+UwCJlvaheEdR+Iobz3I6be20W7rPEG9USrS3rJM9gojKVY2KXEy6NWdbZVsnLybzp9dMH9vpYNKHOxrfudRsnvXLZtH+F72l6OXSqh8lrmTNOmdtVlU1q7A1eL9sy8dAOGrBK9XfJz7DO9rLoB1vyeq7uRU6R7OFxORrfg3XK1ix3WrUKZkvn+2l2vmEDKGxkDjtjC07aK7HqUNo7TNjpUZ2b3bfM7TSU13ZMH5DlN72/c3m/6jBrGzTSpC3CHcH5vavr89DfStb1sq73AS5n9/kmvz+4z2XF/bJioybG+C6HDY6Pe491WO/4+Jmb1+D4eCBZ23u7sJ04vC3ElZu9Rlf7PRTyfJ7m5ZrkXohV+1jqc4/scRh5kAEfjJJaiGs7Sl8+5cZd6FYv+9ppMh5EXD9PI3kGg07aVXCK/bj6uAlxqVCcl94Z9bHYkPB17na6ho3F/C4vTw1fY99G+7wc93v5DZzxy+R+T3PHLaeNQP8o7B/tNLFqkBJtve7UT6W2Vo3PUqpsy7XdYWKHxNglhA7XlgXX5eJvrv4mH7IZUjr32i24cEJ1dsGuB49ymr+Pcq3keuQv8rwsONvzv1xXvdDPYQ0K7pAzPyuXTaUOzc/M5bb5OWhZ4Kj+7st6lq85qCJSvWRIlmQmcaFETzbw2Y2fxQ8twUKn9xNnTOPd+2IusZRYgGJhY05RHxzOU7NynJvD45BrdI7z/eFxKsqmaB3Yo7TXGB4H7OXUEe25qmrTDuuihsabpH5VpTi3txAH+5iOc2cLcfr9rcq+dYfH4fHzcNdAFhYa3O6/HywX7/xHws70wEB+rUofH1HeC0PjTNAnkMt7aXgcLm/02EEsTntT9B0eWF4YJPQ4j15j3Zf1ab78I8/Ra8RXjLEcfimIdXwHvLwcEGXK/+a2MEtfYPXi2HpH1OU//PmXx9BF1pv78w6dRp/b7PMzcIwrzm/XWdfpl0nfozLXg5+DRqGO2OR94L4gC5XLeW3568s8CRS27N3BPG5tFU9zTf3AQH4CZ+cq3KiF8+kOpzMsHvQQsR+4/dgwD23Db4eFObqnUT9KYz/M0itAaoVIC+qoQ/E2DwyOB5eWe41+wSMd76Jo3628csW6iX2D4pF2Aj8DfGdq1xbiqDHCZQrnTZrFU/vrsTA2MN4kWvFqe6ULIp2hL4OJ72DrwLB4JchfrFw=
*/