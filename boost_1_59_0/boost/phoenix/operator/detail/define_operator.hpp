/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_DEFINE_OPERATOR_HPP
#define BOOST_PHOENIX_DEFINE_OPERATOR_HPP

#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#define BOOST_PHOENIX_UNARY_EXPRESSION(__, ___, name)                           \
    template <typename Operand>                                                 \
    struct name                                                                 \
        : expr<proto::tag::name, Operand>                                       \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_UNARY_RULE(__, ___, name)                                 \
    struct name                                                                 \
        : expression::name<meta_grammar>                                        \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_UNARY_FUNCTIONAL(__, ___, name)                           \
    namespace functional                                                        \
    {                                                                           \
        typedef                                                                 \
            proto::functional::make_expr<proto::tag::name>                      \
            BOOST_PP_CAT(make_, name);                                          \
    }                                                                           \
    namespace result_of                                                         \
    {                                                                           \
        template <typename Operand>                                             \
        struct BOOST_PP_CAT(make_, name)                                        \
            : boost::result_of<                                                 \
                functional:: BOOST_PP_CAT(make_, name)(                         \
                    Operand                                                     \
                )                                                               \
            >                                                                   \
        {};                                                                     \
    }                                                                           \
    template <typename Operand>                                                 \
    inline                                                                      \
    typename result_of::BOOST_PP_CAT(make_, name)<Operand>::type                \
    BOOST_PP_CAT(make_, name)(Operand const & operand)                          \
    {                                                                           \
        return functional::BOOST_PP_CAT(make_, name)()(operand);                \
    }                                                                           \
/**/

#define BOOST_PHOENIX_BINARY_EXPRESSION(__, ___, name)                          \
    template <typename Lhs, typename Rhs>                                       \
    struct name                                                                 \
        : expr<proto::tag::name, Lhs, Rhs>                                      \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_BINARY_RULE(__, ___, name)                                \
    struct name                                                                 \
        : expression::name<meta_grammar, meta_grammar>                          \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_BINARY_FUNCTIONAL(__, ___, name)                          \
    namespace functional                                                        \
    {                                                                           \
        typedef                                                                 \
            proto::functional::make_expr<proto::tag::name>                      \
            BOOST_PP_CAT(make_, name);                                          \
    }                                                                           \
    namespace result_of                                                         \
    {                                                                           \
        template <typename Lhs, typename Rhs>                                   \
        struct BOOST_PP_CAT(make_, name)                                        \
            : boost::result_of<                                                 \
                functional:: BOOST_PP_CAT(make_, name)(                         \
                    Lhs, Rhs                                                    \
                )                                                               \
            >                                                                   \
        {};                                                                     \
    }                                                                           \
    template <typename Rhs, typename Lhs>                                       \
    inline                                                                      \
    typename result_of::BOOST_PP_CAT(make_, name)<Rhs, Lhs>::type               \
    BOOST_PP_CAT(make_, name)(Lhs const & lhs, Rhs const & rhs)                 \
    {                                                                           \
        return functional::BOOST_PP_CAT(make_, name)()(lhs, rhs);               \
    }                                                                           \
/**/

#define BOOST_PHOENIX_GRAMMAR(_, __, name)                                      \
    template <typename Dummy>                                                   \
    struct meta_grammar::case_<proto::tag::name, Dummy>                         \
        : enable_rule<rule::name, Dummy>                                        \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_UNARY_OPERATORS(ops)                                      \
    namespace expression {                                                      \
        BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_UNARY_EXPRESSION, _, ops)           \
    }                                                                           \
    namespace rule {                                                            \
        BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_UNARY_RULE, _, ops)                 \
    }                                                                           \
    BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_GRAMMAR, _, ops)                        \
    BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_UNARY_FUNCTIONAL, _, ops)               \
/**/


#define BOOST_PHOENIX_BINARY_OPERATORS(ops)                                     \
    namespace expression {                                                      \
        BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_BINARY_EXPRESSION, _, ops)          \
    }                                                                           \
    namespace rule {                                                            \
        BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_BINARY_RULE, _, ops)                \
    }                                                                           \
    BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_GRAMMAR, _, ops)                        \
    BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_BINARY_FUNCTIONAL, _, ops)              \
/**/

#endif

/* define_operator.hpp
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
*/