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
yaHfpPEuVh/d11EVTjyS8aCbjn+Vz6H9cYN3JFPD7h3r9kvmCWR6I3TCTDdduGVxo28TO9qQedMyNgYih7HLKYraNdPeEwxuACpes36C9o5kuzJYt+8ZNt/e8XyLMiC/Py54RRWPf1Eo6nBUJncZv3ntHDO7jas52hDRwDUC7xWZ8QccLpbdkbQriV5q2bWzV47HtR/6b73l4XoCMxZiU01Bdg+3js0vT7zr0NfM87d9x2ajVP8ul4NsounOa7hxWm/FJLlIV8H5LyasEDbat9kd64C3O8rZCA52koxYvxAFU+1I44qyie8pQyWpfbPe3aTZ8n7OaX97SosLm3mXlxZu23/WPZbjGL+qnLQqFbsZ6W3BOPhHn3QnPjKTZE1WwjeSqBMbWXJ4p2ctvFp4hBS50g1EvMxvd8v9rGNgzNaK72WUHVfKlRcYdikTaY2okHTSDYGhF96m7BUeMqcKkZDZOu3PoVYLVXe4KSoL1Himq5Z5M2l2uSkibancOFcFTUiFgDAvEFW9RTE9ahPPfkcXMJNwv7HRwvh2Mxo/EFwJgsPB0o/mmBWMnpccZa+QlySVYRdzjuIV7rDYaKzHaWuE9Z6A7wA1uBfWtSmKHx06WHudevhIjhScl2S0rs31/ZWG+6YwyqRVOjvRWgtQxgqMcvU18ApL9g22wy+1IHJsJZTTZUfxCOP1u9g7HbA5AErjg7IpXQPGRS4f
*/