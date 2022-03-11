
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