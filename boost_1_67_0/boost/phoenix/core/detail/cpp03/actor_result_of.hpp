
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