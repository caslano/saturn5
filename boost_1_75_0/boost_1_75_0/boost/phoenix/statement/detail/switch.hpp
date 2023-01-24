
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_STATEMENT_DETAIL_SWITCH_HPP
#define BOOST_PHOENIX_STATEMENT_DETAIL_SWITCH_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/statement/detail/preprocessed/switch.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_STATEMENT_DETAIL_SWITCH_HPP
#define BOOST_PHOENIX_STATEMENT_DETAIL_SWITCH_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/switch_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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

        #define BOOST_PHOENIX_SWITCH_EVAL_TYPEDEF_R(Z, N, DATA)                 \
            typedef                                                             \
                typename fusion::result_of::deref<                              \
                    typename fusion::result_of::advance_c<                      \
                        flat_view_begin                                         \
                      , N                                                       \
                    >::type                                                     \
                >::type                                                         \
                BOOST_PP_CAT(case, N);                                          \
            typedef                                                             \
                typename proto::detail::uncvref<                                \
                    typename proto::result_of::value<                           \
                      typename proto::result_of::child_c<                       \
                            BOOST_PP_CAT(case, N)                               \
                          , 0                                                   \
                        >::type                                                 \
                    >::type                                                     \
                >::type                                                         \
                BOOST_PP_CAT(case_label, N);                                    \
    /**/

    #define BOOST_PHOENIX_SWITCH_EVAL_R(Z, N, DATA)                             \
        case BOOST_PP_CAT(case_label, N)::value :                               \
            boost::phoenix::eval(                                               \
                proto::child_c<1>(                                              \
                    fusion::deref(                                              \
                        fusion::advance_c<N>(fusion::begin(flat_view))          \
                    )                                                           \
                )                                                               \
              , ctx                                                             \
            );                                                                  \
            break;                                                              \
    /**/

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
        (3, (2, BOOST_PHOENIX_LIMIT,                                            \
        <boost/phoenix/statement/detail/switch.hpp>))
#include BOOST_PHOENIX_ITERATE()

        #undef BOOST_PHOENIX_SWITCH_EVAL_R
        #undef BOOST_PHOENIX_SWITCH_EVAL_TYPEDEF

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<BOOST_PHOENIX_ITERATION>
              , mpl::false_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;

                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;

                flat_view_type flat_view(proto::flatten(cases));

                BOOST_PP_REPEAT(
                    BOOST_PHOENIX_ITERATION
                  , BOOST_PHOENIX_SWITCH_EVAL_TYPEDEF_R
                  , BOOST_PHOENIX_ITERATION
                )

                switch(boost::phoenix::eval(cond, ctx))
                {
                    BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_SWITCH_EVAL_R, _)
                }
            }

            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<BOOST_PHOENIX_ITERATION>
              , mpl::true_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;

                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;

                flat_view_type flat_view(proto::flatten(cases));

                BOOST_PP_REPEAT(
                    BOOST_PP_DEC(BOOST_PHOENIX_ITERATION)
                  , BOOST_PHOENIX_SWITCH_EVAL_TYPEDEF_R
                  , BOOST_PHOENIX_ITERATION
                )

                switch(boost::phoenix::eval(cond, ctx))
                {
                    BOOST_PP_REPEAT(
                        BOOST_PP_DEC(BOOST_PHOENIX_ITERATION)
                      , BOOST_PHOENIX_SWITCH_EVAL_R, _
                    )
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        BOOST_PP_DEC(BOOST_PHOENIX_ITERATION)
                                    >(fusion::begin(flat_view))
                                )
                            )
                            , ctx
                        );
                }
            }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* switch.hpp
5lfEMw02/k+qssPfY2090Cs9P3rQk0JhvJgpxsqFAUZ59x+5Yr9hUWR08uPnPZsMBSxjO2d8lkhEUfiP1td7tQrs4b8XPvghUeglFs+rLM2AYDIsLf65h8VU/ny9oQ6h1T+oDOot1xf8RE2nAjlrKNIpxdNQvcM62hkuVEXtPmk9cqoWwLeXnCGOatJm3b8qsF+gTzo5Be/ArMBI3bSTca1wYIF08z7Zwts436WkzpSLhna85cn2dHIo6nijEdTuHhWM6qML4vExM3rVW0AuXpAXZPWB0n1p2XJwyD3kwjFXx2zBVtLqIDjMxYF5qacntC/F3UxqPaqBSc/vHEc4UDAufNiedHPBxuyDf8HTv38C5xHrSA/lY8tJSwWYEy5oOW0s0dZyu0P4BDxl4RygRI696ybnX0IYu0FXLlEigj/tG4rCoSxYFwTFvhJY40jczdP9jDdallAFXYEsS3M9Fi4J08KLhsEbl+1XKcNq4VffO/+FRi/T9jZRGROOpr01oXS7hS2b2bnb8ENeOp8fCHtVV3QjUD3oNCLxaZuD+WyiFlxtFOacLcnXSI+5sGcOg7CMTVK4Y5fx3/Dvvf/CIeSTOpMf2vPq3yBMF75FH15UtcmPVjdjGr4/nX07UlgoPxUpGeaBnoOU0ndpBV81fVfVS5S4ulqpH11dZK+m3wyvTAjpUxX1t1oSZ3LbPUpic79hI2w38ZN1lFH+
*/