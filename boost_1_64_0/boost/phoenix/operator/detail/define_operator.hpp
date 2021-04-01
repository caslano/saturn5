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
ROL4KDwws1lDNrQsRgOCa9ZdG321BWiYL1Ufd/HC4jRC5DteCeaCyKfKcWC5koMEJ/tFmz5FZMiM7Uu98lbBIj/clSqSe+6f0bRRes8JuMbiB5PK4uvjLE1bFUkUF1HgZUtXuIo6t78BSFEgqDMMI5vk2cmBJpT8siJxHhcdLWsGlfYMJPpnsAF3yWT+DsHTHyDTcR2mG4T0dPf33Oy3OfNKLiqYyRqOo+YCHl7OXf0WgbF1hIGqwRbr508cOW7hLSUurxvKvgf0QfEWYFRsem+dcoFiCblaN7eugHoarujCaiKNv97cI1eRcHZemphz07oRzGvlDaIMw357Xcn5A5r52lLYFf/jM/d7w5mRThRHSUrF9IKTYiv2Bcb/yETTWqY9kOduqHa+leb1wBDkQX6cdPSSNz+lWASkiuvoWVZw1zO+Be8aqeUHky25A7eIcZ/tW/rWGztEu/GdNUIRegXXnrTOjoSBf4Cp8pZSoGZMMY2McQkr6EP8PGASrhjnv6U+aeIXFv5++pPmcAMcyjo6So3A8hNCZvBN/ttwJaSQ4KedM+2Rz1BtGg==
*/