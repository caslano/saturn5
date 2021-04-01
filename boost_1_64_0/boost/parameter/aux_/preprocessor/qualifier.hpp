// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_QUALIFIER_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_QUALIFIER_HPP

#define BOOST_PARAMETER_QUALIFIER_EAT_in(x)
#define BOOST_PARAMETER_QUALIFIER_EAT_out(x)
#define BOOST_PARAMETER_QUALIFIER_EAT_in_out(x)
#define BOOST_PARAMETER_QUALIFIER_EAT_consume(x)
#define BOOST_PARAMETER_QUALIFIER_EAT_move_from(x)
#define BOOST_PARAMETER_QUALIFIER_EAT_forward(x)

#define BOOST_PARAMETER_GET_QUALIFIER_in(x) in_reference
#define BOOST_PARAMETER_GET_QUALIFIER_out(x) out_reference
#define BOOST_PARAMETER_GET_QUALIFIER_in_out(x) in_out_reference
#define BOOST_PARAMETER_GET_QUALIFIER_consume(x) consume_reference
#define BOOST_PARAMETER_GET_QUALIFIER_move_from(x) move_from_reference
#define BOOST_PARAMETER_GET_QUALIFIER_forward(x) forward_reference

#define BOOST_PARAMETER_STRIP_QUALIFIER_in(x) x
#define BOOST_PARAMETER_STRIP_QUALIFIER_out(x) x
#define BOOST_PARAMETER_STRIP_QUALIFIER_in_out(x) x
#define BOOST_PARAMETER_STRIP_QUALIFIER_consume(x) x
#define BOOST_PARAMETER_STRIP_QUALIFIER_move_from(x) x
#define BOOST_PARAMETER_STRIP_QUALIFIER_forward(x) x

#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_GET_QUALIFIER_GET(x) \
    BOOST_PP_CAT(BOOST_PARAMETER_GET_QUALIFIER_, x)
/**/

#define BOOST_PARAMETER_GET_UNQUALIFIED(x) \
    BOOST_PP_CAT(BOOST_PARAMETER_STRIP_QUALIFIER_, x)
/**/

#include <boost/preprocessor/facilities/is_empty.hpp>

// Expands to 1 if x is either "in(k)", "out(k)", "in_out(k)", "consume(k)",
// "move_from(k)", or "forward(k)"; expands to 0 otherwise.
#define BOOST_PARAMETER_IS_QUALIFIER(x) \
    BOOST_PP_IS_EMPTY(BOOST_PP_CAT(BOOST_PARAMETER_QUALIFIER_EAT_, x))
/**/

#include <boost/preprocessor/control/iif.hpp>

// Expands to the qualifier of x,
// where x is either a keyword qualifier or a keyword.
//
//   k => forward_reference
//   in(k) => in_reference
//   out(k) => out_reference
//   in_out(k) => in_out_reference
//   forward(k) => forward_reference
//   consume(k) => consume_reference
//   move_from(k) => move_from_reference
#define BOOST_PARAMETER_GET_QUALIFIER(x) \
    BOOST_PP_IIF( \
        BOOST_PARAMETER_IS_QUALIFIER(x) \
      , BOOST_PARAMETER_GET_QUALIFIER_GET(x) \
      , forward_reference \
    )
/**/

// Expands to the unqualified version of x,
// where x is either a keyword qualifier or a keyword.
//
//   k => k
//   in(k) => k
//   out(k) => k
//   in_out(k) => k
//   forward(k) => k
//   consume(k) => k
//   move_from(k) => k
#define BOOST_PARAMETER_UNQUALIFIED(x) \
    BOOST_PP_IIF( \
        BOOST_PARAMETER_IS_QUALIFIER(x) \
      , BOOST_PARAMETER_GET_UNQUALIFIED(x) \
      , x \
    )
/**/

#endif  // include guard


/* qualifier.hpp
TBqUiDA+xAsRKcpR2OihCE/fXHugPfkPGb0bV2Nc8D4xQinj+TAzogF1k56HLg4hYZgEHwgdiEKVNOpEp9kwoWdsFUqK85b5D9npW1exu4iy+WtPMTiiWnGJRxEGuyddiCMa3mcWBKAhyqfSug6RXa9TpFyZxFU60IByQFzCNd2zXP2I9HYQGOwQMLKVAKTGOE9YIDoJ+532dc+PPw/JoyLTtxHwnGkCSFwv+AAOT7FbuLxDtywmujhUNgvDGVCAIMsPjLHFCWgQBeH+kDsy/WH49SUPMGqaJ+lty45LqurEBMToRJ0GJLY+rfJ0hm+UkunXF47hOuCTySG+BOLPfgGqy2x7tlS6WMpR6KP+g3c/Z4Gwf8/hBHveO0f2HWcxo4FHwzu15K0X/uRq6hiCis+jgbZv4fILy76fROX0DczKXEXHUbB3kOgCt+Q8BfPrAU1XLwDE8aSIRZRgJP1vbU6BzeFJy9q4AJ3nKsvGKHhegLE5cQEX8rdCh94SZJDiEB773wZs6v4bWG7pd74X7E4IxQpaZAxyJ80Ov13OkVEQ3mo+T9jdMowv4w==
*/