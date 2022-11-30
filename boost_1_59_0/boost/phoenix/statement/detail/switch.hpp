
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
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
*/