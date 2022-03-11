
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