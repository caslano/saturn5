
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
bZdXboc7mexi+A1gtxj/rRD9A/FfDk+j+EA9n47mUYEwxhr096DNB0sjv9+ER/3HT1tfL4gZYb2YtMWxVtSibUTAGP82Q+ShtNaqi68PDdMyFXb0L4eiVxITpFE9xfruQ3f3QBuoxbis4g7Ty2SqbN6jrxKqf0lczAjQ/6S1shqOpJloWsG4FX1zzlf6Mr+YDu5nG+Ifx2qS/qkve+dlpgp/F77ik7elZVV+16cWoR/b+uPAC5xr8FOnF3eQbRBJeXwTZahIDnWfGGk+t00Y3hZN5uo84/6jIkGkzTOhRvTDF9XupOCFrqo9KW/W5tX4xTmZi166QSIEyNYKUvGDlRqn6Gyl12wyraPH1Unh3h2V6VX8G8+5r6tT9AGJQ3WP8AONad+AxtBT4dHY9ECvT7ACQQf2h7oBIVJuWNGOfdaKwDBGJOdCtK8zr18S6IP20QcNOtSO8tIHLJZGdNtyJUG03mY8fAnSQg9MO6XAwO3q2WZTEZbytTnE/oDg1kinjlz6ZfB6HdxmeyG2qrHUwOyN+MKwYlvF6+tCQRVlBBqmrKyZtZ4AXRcf3g==
*/