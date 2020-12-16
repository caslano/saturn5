
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
7198zkNf4DCW3UMoqBZsIuvIeHxwOR5bVNpyTHRtf4kfpVfwGjlvPyLXr9lNbetN34fk4Wqe+uZ4un7VInPvw+a5DcDY7jdGri8K6sepD/Bn5s0MsefTbNEG00pNSz5TcnlNpLatmJaGY7r3Mkh9GtuRZJqczxz3b/p2x0Zn6O+rT7Md+yvLdmhVEw1t9CX9mVd19JS62mBs+5Ux1FWJX80SKOMCxrGMykZU7OToGIlrC9NrST4czwzkfECN2eJfZzvmyL3pUkMf9WlSpbblM+T/kg3l3c607aQfK3kOMDzTmazNJ+NH2d6msy7VIbxOM8e2v0LylBCj0pJxzPbnT4524f6yzGuk5fTeUNk+msj9TSPbPW4r+/ah7663fLei9/uaHAwp6P27wJ6/D+v9+7yev6ub9+8I5/W7up6/P+v9u8aev/Ob9+/wev4usPfvL3v+fq737/kGlVTT3/kw8sfn4iudu/FIerfPa77CYP/+2vTMM8OrPzb2+eILShz2Cbz07K68f283r98L9vY95QwtP4VyKlyZPCB29OfF6y6zrnygtPfvCHv+nq/37yPP0+LfODNkTtdGvbPrzPb55b1pR6reve9N5/W70hf1tkD55gDbpYxrKEYYbNJ/h33076Mele8EH8Nh+BGOxE8wDj/FKXgCZ+LnOBdPoi0dv0e9p/OnpGMqoKdTEFU6hVClUxTj1DKo0imOKp2SqNIphSqdcBW3pFNP0ilC6Cbp9JHv4vbDktgf/dRyGIQDsTpGYB0chPJ9YXkPP/Us8Rq/L7xR8r8J22O64bvJ4bJca1nO+J3jfj56fvpL/Q7Aaiof2FSljy1xsI8jH+kSX3EP+egk5QvDotjZkP9MWc7Pw3KtZbk2WBpD1XJS1ixZbpAsV4jQUpaLMenlNst3jS1YA8fjAJxgstWDvFMem3qohy1SD09jOXwGg3Ar1sPnsTFuM9RrmsQXosV359/L3rfauJ7u7HvZ2va+Ro8v2cP2/qpsL7skvt14H+7BPvgmDlfLYTS+hRPxHUzE/YZ00m+SzneSzg+Szo+SzgVJJ1vS+UXSuSjp5Eg6vxnqO2St9/p+XOp7vdT3BqnvjVLf6VLfTxrq27rWe33PkfjmSjxpJr2+52FTrT+rXt8LJL40FYfEt1LiM34PO1XqYTrWxhk+en5mYhucjT1UuthXpYuD8AFMUenibHwQ01S6uAgX4jJ8yLhdrtPz0VDLx51/J32fxMd04ruz76QTn7z7m23XQ3wdJb5OEl+YxNdF6qsbtsDuEl+4ChJfFw/H22VS3odNenzLMUhbR/p+/Qi2w1UYhqsNx51MiTfEw3HHKvFOkXiTJN4U2c5SDce9bImnhBZP7r4LH6Zt1PpyCR7SXyXb02rZntbhAFW1sv88bjher5B41PabXsA5/e/L6Omfwyr4A15U86k0ZblMWc5fqyf916q0nn5rVPG2wbYYih2wLfbCe1Hlqx0Ox/YYhR1Q5bMjWtX6xlmq3PgAdsal2AUfwa74BHbDDOyO+vff5T3Q0rch3eX778GSz+pYGWtgDayJ9VU9YFOsjW2wDvbEutgX6+EQrI8jsQEmqPWGKdgIH8LGuAmb4gsYgnJ8lPc1UwbJn/H4OKegnr+5WF7Ni1XwAayN87ARPogtcT6q+l2InfAhVOlMJ5yWdJZLOiUxXtIZUFq+x4/adQbWxAgMxUHYFQdjJA7BaByKMThMyhuJs3E4LsORUs4sk7xrGYN89PQrqPOEpP+Uj36c2YJV5Lyq0n8OG8j5tbmcX9tiho9evhfkuPgijsCXMBUzcb5a5/g3fBkfw1d89PWwHV/EHbhdznc78TU8jjvxjJz/fpDzXyE=
*/