
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_STATEMENT_DETAIL_TRY_CATCH_EVAL_HPP
#define BOOST_PHOENIX_STATEMENT_DETAIL_TRY_CATCH_EVAL_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/statement/detail/preprocessed/try_catch_eval.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_STATEMENT_DETAIL_TRY_CATCH_EVAL_HPP
#define BOOST_PHOENIX_STATEMENT_DETAIL_TRY_CATCH_EVAL_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/try_catch_eval_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

    #define BOOST_PHOENIX_TRY_CATCH_EVAL_R(Z, N, DATA)                          \
            catch(                                                              \
                typename proto::result_of::value<                               \
                    typename proto::result_of::child_c<                         \
                        BOOST_PP_CAT(A, N)                                      \
                      , 0                                                       \
                    >::type                                                     \
                >::type::type &e                                                \
            )                                                                   \
            {                                                                   \
                eval_catch_body(BOOST_PP_CAT(a, N), e, ctx);                    \
            }                                                                   \
    /**/


#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
        (3, (1, BOOST_PHOENIX_CATCH_LIMIT,                                      \
        <boost/phoenix/statement/detail/try_catch_eval.hpp>))
#include BOOST_PHOENIX_ITERATE()

    #undef BOOST_PHOENIX_TRY_CATCH_EVAL_R

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

        template <typename Try, BOOST_PHOENIX_typename_A, typename Context>
        typename boost::enable_if<
            proto::matches<
                BOOST_PP_CAT(A, BOOST_PP_DEC(BOOST_PHOENIX_ITERATION))
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, BOOST_PHOENIX_A_const_ref_a, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_TRY_CATCH_EVAL_R, _)
        }

        template <typename Try, BOOST_PHOENIX_typename_A, typename Context>
        typename boost::disable_if<
            proto::matches<
                BOOST_PP_CAT(A, BOOST_PP_DEC(BOOST_PHOENIX_ITERATION))
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, BOOST_PHOENIX_A_const_ref_a, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            BOOST_PP_REPEAT(
                BOOST_PP_DEC(BOOST_PHOENIX_ITERATION)
              , BOOST_PHOENIX_TRY_CATCH_EVAL_R, _
            )
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        BOOST_PP_CAT(a, BOOST_PP_DEC(BOOST_PHOENIX_ITERATION))
                    )
                  , ctx);
            }
        }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* try_catch_eval.hpp
UAX9kaW6PkqDPvr+Ndgctvqh4rME4iy0Idh7sn9gWLKJYc2Xq8eJFY+m9TCUrD+wzqP6X4YOrZr7Gj8ToFmdcw1PcQukl4M+3z/JTr1fHYvbAw30qyz1W4x6Nl38sNTkmkfvnNWxH82CeCERPcBycWhs8FjZcwwXvh8zHTZhKO3/cg5ep1571f4LlpNDo9WGPYYT+h47MCkZ94K/ee7YGue6ZNwLXst54WD1QXxjJO6jFaHQKvsuaCyDPvFjvbtW3beolnsc3yx0UMtb0/j4fH2uBa2hnENf9PervRMddDlcDeg+OyyANeKNo3cwzNBmmdVYnfosun7i2yUmrqL/+VBE1GuMecHG9ReR60/eWiPHzZ7n1+r78uDc7OKU+hcIDbP78LRfRnYO+kcNdIlZqkM5QIN5f0zfOGrCvCOS0LkBSzMB1xwLoUrN+zaQsJUlgWciXFCM0NATKwjyrpExO/t/e71DfnnB2XiMFey12ZfmHTCUxkCqBQjQbATAKWSRfKMAi9TjjEFg3WTNQqOhKlCPOLBI7oznX/u4BUnvpHHGhPnruFHDC2rwiAqXg9jBNEKCq7OEjAI6csbOiNf+g+FnCETQLGKNt5PGeLo2j/g9O1j0r5QyKPlAyz+2OPYc3Gk6/6SZTHcWPpaB
*/