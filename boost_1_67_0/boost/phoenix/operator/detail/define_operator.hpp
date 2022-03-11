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