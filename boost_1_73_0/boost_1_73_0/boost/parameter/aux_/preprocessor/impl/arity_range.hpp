// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_ARITY_RANGE_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_ARITY_RANGE_HPP

// Helper macros for BOOST_PARAMETER_ARITY_RANGE.
#define BOOST_PARAMETER_ARITY_RANGE_M_optional(state) state
#define BOOST_PARAMETER_ARITY_RANGE_M_deduced_optional(state) state

#include <boost/preprocessor/arithmetic/inc.hpp>

#define BOOST_PARAMETER_ARITY_RANGE_M_required(state) BOOST_PP_INC(state)
#define BOOST_PARAMETER_ARITY_RANGE_M_deduced_required(state)                \
    BOOST_PP_INC(state)
/**/

#include <boost/parameter/aux_/preprocessor/impl/argument_specs.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_ARITY_RANGE_M(s, state, x)                           \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_ARITY_RANGE_M_                                       \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(x)                                  \
    )(state)
/**/

#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/size.hpp>

// Calculates [begin, end) arity range.
#define BOOST_PARAMETER_ARITY_RANGE(args)                                    \
    (                                                                        \
        BOOST_PP_SEQ_FOLD_LEFT(BOOST_PARAMETER_ARITY_RANGE_M, 0, args)       \
      , BOOST_PP_INC(BOOST_PP_SEQ_SIZE(args))                                \
    )
/**/

#endif  // include guard


/* arity_range.hpp
l6lHRxDYWOr/hX5CMuZS14wSRTZMFuFOn3vYSM6jctgnC1O97g/mh+xPcdhxWg5K0ogveOiPRsPaO06FhYo1U6PKOA6kXCKc5qnQEFsM8pE/iRiQihVN9YjuoG1BgcLDzwip0eHi0O48a6K3MZRhr3RDwv5ztnNIUQeRZJE0ImMxWhyeHlE4VpDHGql6j3Lxju0xSjq1tV0cpTjbbysqK9yO56mxhoGh6Qk0bMtUigx1cA6kNg1OAWgU6NT77xUix29HTr8eengcu6ZRzh1S2uP/Dild/97xAysNaXk4OQxD46xA5NEKj/HBpcQlvctkymvuzizkr88sxMHMggbA5+9PTujrgzQIfsfphIHJLqfW2kTgsVoNLkFOa4jV9CbPiPblEnmf5q3otjX38zSTooaiRFJomQS535tBoQ2yBBc81PykBhTRNDymbxiomSUeqqid4twGQ/gd4NHQ2lhk0t2MK2f0BdKOjnIq0gipzMfylzyOf4Gx0T7Q/c/E6s60iesxcvEwv8KV0L6AKXW94S9jNH37QuUVe82QwYVXG2ZHmjg08ask8msMOxw/l7AEQSlPTlpKG2vu5mXZ015B+IdjXSxBGt2GVFP42LnuhxCpYfchzv3Y2xZrNPmJEsVBpwNoyEUbBzV923ua
*/