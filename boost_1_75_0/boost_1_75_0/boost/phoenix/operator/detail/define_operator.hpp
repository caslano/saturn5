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
/UUylqwa8WSQ6Ge7HajLZ7Y621PucKGLz+hpYbw67DwTVGTdnqP/wfpLzy+VJaqyw9x7cfuMgJQNXb9y1PSwbt0pvS80PX8BMoBmcuxBtWQA/LnB9DFf7sK8JGF3YjrYXwPdFsSTxWkO4ywCU+pPm+txiw/4M/inQM+kO8XnwXNKYJfSITIrpBKwgnh2FvIU+pPz6cHwVLX8xpmoKDlP7AWG32GB0AUSKb6jgHcNWdKNWnXRURSV9r7GOlVjpr5MK+6nLIWMMZlNpiPOh9iLPUHMaLa91DE0tovBslPxi47rUvlXVz9smqwmMB6YU0wBhLMIQcAdi/VATZqum4+sn8srTFxwnh898a7PhlIEovkvUy6WNdAGRrzHveOKzIDqiwKQ/IeD5+zXcN5T3mONypwz4sJ933ezZd9vbBnuUd7zQNiiiT5hFhSuIRYX75L4eMEKw8M7NFmy1Zov/U5p2DIa4pz5d7EHLIlyFaL7hRMCeRovI6MavbeiKQf3Olmj9hJyvmECtU8rHbnC+gogkvCcwm9px7iEbeU5UhKva7EtdaKjVpPqlc2aG/Ebwo4trZLA6hpraxvaqpF1+znCpEjRr8B5/qHfLVvN6tlUEvoJBOoi+Q82iXaGevhK5W8t/i3ACp2D652iBztChV52TRHp6+X3MlDiGyx0I29STBmlzu3APj0cAitM7IYF+wiC7Z6zkKBPYRl/b5Vg
*/