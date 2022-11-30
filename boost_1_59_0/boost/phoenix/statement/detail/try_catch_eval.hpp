
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
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
*/