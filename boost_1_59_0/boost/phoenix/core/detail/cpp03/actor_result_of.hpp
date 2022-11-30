
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP
#define BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/core/detail/cpp03/preprocessed/actor_result_of.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP
#define BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/actor_result_of_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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

        template <typename Expr
            , BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_ACTOR_LIMIT)
            , typename Dummy = void>
        struct actor;

        template <typename Expr>
        struct nullary_actor_result
        {
            typedef
                typename boost::phoenix::evaluator::impl<
                    Expr const&
                  , vector2<
                        vector1<const ::boost::phoenix::actor<Expr> *> &
                      , default_actions
                    > const &
                  , proto::empty_env
                >::result_type
                type;
        };

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_ACTOR_LIMIT,                                          \
    <boost/phoenix/core/detail/cpp03/actor_result_of.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

        template <typename Expr, BOOST_PHOENIX_typename_A>
        struct actor<Expr, BOOST_PHOENIX_A>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            BOOST_PP_CAT(
                                vector
                              , BOOST_PP_INC(BOOST_PHOENIX_ITERATION)
                            )<const ::boost::phoenix::actor<Expr> *, BOOST_PHOENIX_A> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* actor_result_of.hpp
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
*/