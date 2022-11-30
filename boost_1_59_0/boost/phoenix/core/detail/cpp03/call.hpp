
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_CORE_DETAIL_CALL_HPP
#define BOOST_PHOENIX_CORE_DETAIL_CALL_HPP

#include <boost/phoenix/core/detail/cpp03/preprocessed/call.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_CORE_DETAIL_CALL_HPP
#define BOOST_PHOENIX_CORE_DETAIL_CALL_HPP

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/call_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define M0(Z, N ,D) \
            typedef \
                typename proto::result_of::child_c<Expr, N>::type \
                BOOST_PP_CAT(A, N); \
/**/
#define M1(Z, N ,D) \
    BOOST_PP_COMMA_IF(N) proto::child_c<N>(e)
/**/
    

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_LIMIT,                                                \
    <boost/phoenix/core/detail/cpp03/call.hpp>))
#include BOOST_PHOENIX_ITERATE()

#undef M0
#undef M1

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, BOOST_PHOENIX_ITERATION>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;

            BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M0, _)

            typedef
                typename boost::result_of<
                    Fun(BOOST_PHOENIX_A, context_type)
                >::type
                result_type;

            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M1, _)
                      , boost::phoenix::context(s, d)
                    );
            }
        };

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* call.hpp
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
*/