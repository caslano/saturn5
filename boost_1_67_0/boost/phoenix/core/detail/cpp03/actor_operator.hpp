
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_CORE_DETAIL_ACTOR_OPERATOR_HPP
#define BOOST_PHOENIX_CORE_DETAIL_ACTOR_OPERATOR_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/core/detail/cpp03/preprocessed/actor_operator.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_CORE_DETAIL_ACTOR_OPERATOR_HPP
#define BOOST_PHOENIX_CORE_DETAIL_ACTOR_OPERATOR_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/actor_operator_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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

#define M0(Z, N, D)                                                             \
    typename detail::result_type_deduction_helper<BOOST_PP_CAT(A, N)>::type     \
/**/

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
        (3, (1, BOOST_PHOENIX_ACTOR_LIMIT,                                      \
        <boost/phoenix/core/detail/cpp03/actor_operator.hpp>))
#include BOOST_PHOENIX_ITERATE()

#undef M0

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

#if BOOST_PHOENIX_ITERATION >= BOOST_PHOENIX_PERFECT_FORWARD_LIMIT

        template <typename This, BOOST_PHOENIX_typename_A>
        struct result<This(BOOST_PHOENIX_A)>
            : result<This(BOOST_PHOENIX_A_const_ref)>
        {};

        template <typename This, BOOST_PHOENIX_typename_A>
        struct result<This(BOOST_PHOENIX_A_ref)>
            : result_of::actor<proto_base_expr, BOOST_PHOENIX_A_ref>
        {};

        template <BOOST_PHOENIX_typename_A>
        typename result_of::actor<proto_base_expr, BOOST_PHOENIX_A_ref>::type
        operator()(BOOST_PHOENIX_A_ref_a)
        {
            typedef
                BOOST_PP_CAT(vector, BOOST_PP_INC(BOOST_PHOENIX_ITERATION))<
                    const actor<Expr> *, BOOST_PHOENIX_A_ref
                >
                env_type;
            env_type env = {this, BOOST_PHOENIX_a};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }

        template <BOOST_PHOENIX_typename_A>
        typename result_of::actor<proto_base_expr, BOOST_PHOENIX_A_ref>::type
        operator()(BOOST_PHOENIX_A_ref_a) const
        {
            typedef
                BOOST_PP_CAT(vector, BOOST_PP_INC(BOOST_PHOENIX_ITERATION))<
                    const actor<Expr> *, BOOST_PHOENIX_A_ref
                >
                env_type;
            env_type env = {this, BOOST_PHOENIX_a};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }

        template <BOOST_PHOENIX_typename_A>
        typename result_of::actor<proto_base_expr, BOOST_PHOENIX_A_const_ref>::type
        operator()(BOOST_PHOENIX_A_const_ref_a)
        {
            typedef
                BOOST_PP_CAT(vector, BOOST_PP_INC(BOOST_PHOENIX_ITERATION))<
                    const actor<Expr> *, BOOST_PHOENIX_A_const_ref
                >
                env_type;
            env_type env = {this, BOOST_PHOENIX_a};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }

        template <BOOST_PHOENIX_typename_A>
        typename result_of::actor<proto_base_expr, BOOST_PHOENIX_A_const_ref>::type
        operator()(BOOST_PHOENIX_A_const_ref_a) const
        {
            typedef
                BOOST_PP_CAT(vector, BOOST_PP_INC(BOOST_PHOENIX_ITERATION))<
                    const actor<Expr> *, BOOST_PHOENIX_A_const_ref
                >
                env_type;
            env_type env = {this, BOOST_PHOENIX_a};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }

#else

// We need to define operator() for all permutations of reference types.
// For BOOST_PHOENIX_ITERATION <= BOOST_PHOENIX_LIMIT_PREFECT_FORWARD
// 2^BOOST_PHOENIX_ITERATION overloads are created
// For compile time reasons,
// if BOOST_PHOENIX_ITERATION > BOOST_PHOENIX_LIMIT_PERFECT_FORWARD
// only operator()(A const &...a) and operator()(A &...a) are generated
// this is all handled by the PP mumbo jumbo above
#define BOOST_PHOENIX_ACTOR_OPERATOR(_, I, __)                                  \
        template <typename This, BOOST_PHOENIX_typename_A>                      \
        struct result<This(BOOST_PHOENIX_PERM_A(I))>                            \
            : result_of::actor<proto_base_expr, BOOST_PHOENIX_PERM_A(I)>        \
        {};                                                                     \
                                                                                \
        template <BOOST_PHOENIX_typename_A>                                     \
        typename result_of::actor<proto_base_expr, BOOST_PHOENIX_PERM_A(I)>::type\
        operator()(BOOST_PHOENIX_PERM_A_a(I)) const                             \
        {                                                                       \
            typedef                                                             \
                BOOST_PP_CAT(vector, BOOST_PP_INC(BOOST_PHOENIX_ITERATION))<    \
                    const actor<Expr> *, BOOST_PHOENIX_PERM_A(I)                \
                >                                                               \
                env_type;                                                       \
            env_type env = {this, BOOST_PHOENIX_a};                             \
                                                                                \
            return phoenix::eval(*this, phoenix::context(env, default_actions()));\
        }                                                                       \
                                                                                \
        template <BOOST_PHOENIX_typename_A>                                     \
        typename result_of::actor<proto_base_expr, BOOST_PHOENIX_PERM_A(I)>::type\
        operator()(BOOST_PHOENIX_PERM_A_a(I))                                   \
        {                                                                       \
            typedef                                                             \
                BOOST_PP_CAT(vector, BOOST_PP_INC(BOOST_PHOENIX_ITERATION))<    \
                    const actor<Expr> *, BOOST_PHOENIX_PERM_A(I)                \
                >                                                               \
                env_type;                                                       \
            env_type env = {this, BOOST_PHOENIX_a};                             \
                                                                                \
            return phoenix::eval(*this, phoenix::context(env, default_actions()));\
        }                                                                       \
        /**/

        template <typename This, BOOST_PHOENIX_typename_A>
        struct result<This(BOOST_PHOENIX_A)>
            : result<This(BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, M0, _))>
        {};

        BOOST_PP_REPEAT(BOOST_PHOENIX_PERM_SIZE, BOOST_PHOENIX_ACTOR_OPERATOR, _)

#undef BOOST_PHOENIX_ACTOR_OPERATOR

#endif

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* actor_operator.hpp
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
*/