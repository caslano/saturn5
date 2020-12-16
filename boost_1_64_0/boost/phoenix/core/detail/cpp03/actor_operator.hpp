
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
h9+vPn8njW93wH/Bnr8baDOK2PgL78Punx6E8Y2Ed8FfIdf/8uEvya7+fgT4c2T/dw22GZ+Q52vz4QeFi/jF+to58DdJ/KV4OPV2Mr6UwX9M1o8XwTdLrp6fu4by40Mh/NUEEV54ZvT4Bn8GniT5rnRrfjIL/ivh4v5Y0b8vhj8huXp/7Bz4DsnV+2ObcPG8Nzn+tMCHtrN+0D06fsCzEmE2y1/1W+uLiSNsRmfFM5ZJ+/8ozD/Y/NeJ+R0Zf2zwb5DxpxTen90/Bj+XjO8/gI9lv38CPof9fg14kezq+c9ZfP8rhaeT+vHDu5DwdfDBJH9r4QPZ9YUY6TfCNyZIrqzvvwmfDM9KsnxvlbW+/x48X/HO1XiZn/4GH6b4Qni0fx+BD1X8Bbi4fwe/AHIkuT/9GDwXDhOO44tY3zgO7y1cHF/E+sa/4TnCxfFF5O9LeLbk6vHFX2AzbmHrN/AfSq7e/3sHfLHk6v2/d8PLFL8FHu3NW+Alin8OF/d3jbUZhax/wYex+TF8Prn//iX4hfAkyeXnA16GXyC5+nzAK/DzJVfHv1fh58muPh8wju8fy+Bs/6iHF5Pwd8MXkPsfHoSfT+5/cIy30fULl3DN+nUML4rhpfBcUr4yeG92/QBO12eEa55fi1H+Rjhdn4nhzTG8hTq+JvD82+Es/w44bV84bV84bV/hmuNLjPB+4Zr9H+5K0M+v1sKdkqvzq2vgZ0quzq+egH9Mni8+Am+QXF1/KcTi/SOG/vnsC+E/N9T5l/V89iz4VuFi/BHPD3wLvkW4GH/EJ8e5tuj1F+Hy+cMF8B5wdf1N3B8F7y5crL+J+rkQ3k24WH8Tn2bBu0qurr8VTrGJ52/k/HWO5g++isx/WuAjZVf771ScP7Hf/wevJuefE+Fu9vsj4Q8kkt/PA78TniK5fH9u8jdxfFR8Wo0V/3XwtxPa+i3waGlvgf9W8aNwcf8DDk7HSfnL4F+Q8tfPsBn1hvSlHl/gd0qmhvdfgPZjxzf4CnJ/4Bq4V3L1/pnvwsskV++f2QqfILl6/4x9Js5/yf093eC/kFy9vzQb/jNyf89E+Bpyf8858NXk/p4W+EWkfydg8jKJ/f4XeC8Svg5eKJ2fqPfPfQ8+mJzfNME9pH1/By9n5x+zbMZZ5Pr1JupIHz7MHH9zhUvP98AHyq6mPxsztQT99duL4amSq+0/D54gudr+AfgBZf7/mc9qjdvguxS/tEq6/lhkM0aw9ZOLUT/ES+H0+Aqnx1d4DzZ/gs9N1h9fPoH/LgFhJZfHv0/hvxUuzm9Ean+HvyJcnN+IT/+G75FcPb8pwuQ/i5Uf7mLX5+C5bP4GH83mV5fx+EvhKcT9cJo/eCbxJviZxI0FNiOD5R9+qU2/fw+AXyK5en7xDfgoxe1e69Ml8FeU+i2Fi+e7L+f10wzPIf3fKLbR5+/t8CziLrideBG8l00/f7kY3lO4GD/E+tQcuF24mH+K5ycvg6eQ+WfDFYiftT/8RnL8/h38BsnU9kteKM4PxVd5pbT+C+9C6n8TvIL8/kF7iY1eP+4LH0GOb/4Y4a+OEb4J3pf1n1I+PtpjuEO4+Grbv+D0/CqGF8Hp+RWcjv9wOv5TR/vC+e//4t4Ap+fXcHp+De9GvAU+TXL1+P4JfKrk6vH9c/hEydXnhxLLbMZw8vu7kuBnkt/fVQS/OsHc76X85UR/PyK8Gm6XHOdn4vcXVMAXCRfnZ2J9ajG8VLg4PxPrU5XwhZKr52d+N65vRdeF2qnfu+ALJVfXB7fBZ0uurg/+Aj5LcnV98CH4ebKr64Mem3Eb8o85qpinvo0FyeHR+zcrMT9m/Qt+e4JSPun66EvwjfA0yf8=
*/