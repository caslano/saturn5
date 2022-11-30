/*=============================================================================
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_CORE_DETAIL_EXPRESSION_HPP
#define BOOST_PHOENIX_CORE_DETAIL_EXPRESSION_HPP

#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/pop_back.hpp>
#include <boost/preprocessor/seq/reverse.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repeat_from_to.hpp>

#define BOOST_PHOENIX_DEFINE_EXPRESSION(NAME_SEQ, SEQ)                          \
    BOOST_PHOENIX_DEFINE_EXPRESSION_BASE(                                       \
        NAME_SEQ                                                                \
      , SEQ                                                                     \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_EXPRESSION_DEFAULT                      \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_RULE_DEFAULT                            \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_RESULT_OF_MAKE_DEFAULT                  \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_MAKE_EXPRESSION_DEFAULT                 \
      , _                                                                       \
    )                                                                           \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(NAME_SEQ, GRAMMAR_SEQ, LIMIT)    \
    BOOST_PHOENIX_DEFINE_EXPRESSION_BASE(                                       \
        NAME_SEQ                                                                \
      , GRAMMAR_SEQ                                                             \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_EXPRESSION_VARARG                       \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_RULE_VARARG                             \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_RESULT_OF_MAKE_VARARG                   \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_MAKE_EXPRESSION_VARARG                  \
      , LIMIT                                                                   \
    )                                                                           \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_EXT(ACTOR, NAME_SEQ, GRAMMAR_SEQ)       \
    BOOST_PHOENIX_DEFINE_EXPRESSION_BASE(                                       \
        NAME_SEQ                                                                \
      , GRAMMAR_SEQ                                                             \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_EXPRESSION_EXT                          \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_RULE_DEFAULT                            \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_RESULT_OF_MAKE_DEFAULT                  \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_MAKE_EXPRESSION_DEFAULT                 \
      , ACTOR                                                                   \
    )                                                                           \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_EXT_VARARG(ACTOR, NAME, GRAMMAR, LIMIT) \
    BOOST_PHOENIX_DEFINE_EXPRESSION_BASE(                                       \
        NAME_SEQ                                                                \
      , GRAMMAR_SEQ                                                             \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_EXPRESSION_VARARG_EXT                   \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_RULE_VARARG                             \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_RESULT_OF_MAKE_VARARG                   \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_MAKE_EXPRESSION_VARARG                  \
      , ACTOR                                                                   \
    )                                                                           \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_NAMESPACE(R, D, E)                      \
namespace E {                                                                   \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_NAMESPACE_END(R, D, E)                  \
}                                                                               \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_NS(R, D, E)                             \
E ::                                                                            \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_BASE(NAME_SEQ, GRAMMAR_SEQ, EXPRESSION, RULE, RESULT_OF_MAKE, MAKE_EXPRESSION, DATA) \
BOOST_PP_SEQ_FOR_EACH(                                                          \
    BOOST_PHOENIX_DEFINE_EXPRESSION_NAMESPACE                                   \
  , _                                                                           \
  , BOOST_PP_SEQ_POP_BACK(NAME_SEQ)                                             \
)                                                                               \
    namespace tag                                                               \
    {                                                                           \
        struct BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ)) {};            \
        template <typename Ostream>                                             \
        inline Ostream &operator<<(                                             \
            Ostream & os                                                        \
          , BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ)))                  \
        {                                                                       \
            os << BOOST_PP_STRINGIZE(                                           \
                BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))               \
            );                                                                  \
            return os;                                                          \
        }                                                                       \
    }                                                                           \
    namespace expression                                                        \
    {                                                                           \
        EXPRESSION(NAME_SEQ, GRAMMAR_SEQ, DATA)                                 \
    }                                                                           \
    namespace rule                                                              \
    {                                                                           \
        RULE(NAME_SEQ, GRAMMAR_SEQ, DATA)                                       \
    }                                                                           \
    namespace functional                                                        \
    {                                                                           \
        typedef                                                                 \
            boost::proto::functional::make_expr<                                \
                    tag:: BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))     \
            >                                                                   \
            BOOST_PP_CAT(                                                       \
                make_                                                           \
              , BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))               \
            );                                                                  \
    }                                                                           \
    namespace result_of                                                         \
    {                                                                           \
        RESULT_OF_MAKE(NAME_SEQ, GRAMMAR_SEQ, DATA)                             \
    }                                                                           \
    MAKE_EXPRESSION(NAME_SEQ, GRAMMAR_SEQ, DATA)                                \
                                                                                \
BOOST_PP_SEQ_FOR_EACH(                                                          \
    BOOST_PHOENIX_DEFINE_EXPRESSION_NAMESPACE_END                               \
  , _                                                                           \
  , BOOST_PP_SEQ_POP_BACK(NAME_SEQ)                                             \
)                                                                               \
namespace boost { namespace phoenix                                             \
{                                                                               \
    template <typename Dummy>                                                   \
    struct meta_grammar::case_<                                                 \
        :: BOOST_PP_SEQ_FOR_EACH(                                               \
            BOOST_PHOENIX_DEFINE_EXPRESSION_NS                                  \
          , _                                                                   \
          , BOOST_PP_SEQ_POP_BACK(NAME_SEQ)                                     \
        ) tag:: BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))               \
      , Dummy                                                                   \
    >                                                                           \
        : enable_rule<                                                          \
            :: BOOST_PP_SEQ_FOR_EACH(                                           \
                BOOST_PHOENIX_DEFINE_EXPRESSION_NS                              \
              , _                                                               \
              , BOOST_PP_SEQ_POP_BACK(NAME_SEQ)                                 \
            ) rule:: BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))          \
         , Dummy                                                                \
        >                                                                       \
    {};                                                                         \
} }                                                                             \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_EXPRESSION_DEFAULT(NAME_SEQ, GRAMMAR_SEQ, D) \
        template <BOOST_PHOENIX_typename_A(BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ))>     \
        struct BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))                \
            : boost::phoenix::expr<                                             \
                :: BOOST_PP_SEQ_FOR_EACH(                                       \
                    BOOST_PHOENIX_DEFINE_EXPRESSION_NS                          \
                  , _                                                           \
                  , BOOST_PP_SEQ_POP_BACK(NAME_SEQ)                             \
                ) tag:: BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))       \
              , BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ), A)>        \
        {};                                                                     \
/**/
        
#define BOOST_PHOENIX_DEFINE_EXPRESSION_RULE_DEFAULT(NAME_SEQ, GRAMMAR_SEQ, D)  \
    struct BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))                    \
        : expression:: BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))        \
            <BOOST_PP_SEQ_ENUM(GRAMMAR_SEQ)>                                    \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_RESULT_OF_MAKE_DEFAULT(NAME_SEQ, GRAMMAR_SEQ, D) \
    template <BOOST_PHOENIX_typename_A(BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ))>         \
    struct BOOST_PP_CAT(make_, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))) \
        : boost::result_of<                                                     \
            functional::                                                        \
                BOOST_PP_CAT(                                                   \
                    make_                                                       \
                  , BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))           \
                )(BOOST_PHOENIX_A(BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ)))              \
        >                                                                       \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_MAKE_EXPRESSION_DEFAULT(NAME_SEQ, GRAMMAR_SEQ, D) \
    template <BOOST_PHOENIX_typename_A(BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ))>         \
    inline                                                                      \
    typename                                                                    \
        result_of::BOOST_PP_CAT(                                                \
            make_                                                               \
          , BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))                   \
        )<                                                                      \
            BOOST_PHOENIX_A(BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ))                     \
        >::type const                                                           \
    BOOST_PP_CAT(                                                               \
        make_                                                                   \
      , BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))                       \
    )(                                                                          \
        BOOST_PHOENIX_A_const_ref_a(BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ))             \
    )                                                                           \
    {                                                                           \
        return                                                                  \
            functional::BOOST_PP_CAT(                                           \
                make_                                                           \
              , BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))               \
            )()(                                                                \
              BOOST_PHOENIX_a(BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ))                   \
            );                                                                  \
    }                                                                           \
/**/

#ifndef BOOST_PHOENIX_NO_VARIADIC_EXPRESSION

#define BOOST_PHOENIX_DEFINE_EXPRESSION_EXPRESSION_VARARG(NAME_SEQ, _G, _L)     \
    template <typename A0, typename... A>                                       \
    struct BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))                    \
        : boost::phoenix::expr<                                                 \
            tag:: BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))             \
          , A0, A...                                                            \
        >                                                                       \
    {};                                                                         \
/**/

#else // BOOST_PHOENIX_NO_VARIADIC_EXPRESSION

#define BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG_R(_, N, NAME)                    \
    template <                                                                  \
        BOOST_PHOENIX_typename_A(                                               \
            BOOST_PP_ADD(                                                       \
                N                                                               \
              , BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(2, 1, NAME))              \
            )                                                                   \
        )                                                                       \
    >                                                                           \
    struct BOOST_PP_TUPLE_ELEM(2, 0, NAME)<                                     \
        BOOST_PHOENIX_A(                                                        \
            BOOST_PP_ADD(N, BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(2, 1, NAME))) \
        )                                                                       \
    >                                                                           \
        : boost::phoenix::expr<                                                 \
            tag:: BOOST_PP_TUPLE_ELEM(2, 0, NAME)                               \
          , BOOST_PHOENIX_A(                                                    \
                BOOST_PP_ADD(                                                   \
                    N                                                           \
                  , BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(2, 1, NAME))          \
                )                                                               \
            )                                                                   \
        >                                                                       \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_EXPRESSION_VARARG(NAME_SEQ, GRAMMAR_SEQ, LIMIT) \
        template <                                                              \
            BOOST_PHOENIX_typename_A_void(                                      \
                BOOST_PP_ADD(                                                   \
                    LIMIT, BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ)))        \
            )                                                                   \
          , typename Dummy = void                                               \
        >                                                                       \
        struct BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ));               \
                                                                                \
        BOOST_PP_REPEAT_FROM_TO(                                                \
            1                                                                   \
          , BOOST_PP_ADD(LIMIT, BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ)))   \
          , BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG_R                            \
          , (                                                                   \
                BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))               \
              , BOOST_PP_SEQ_POP_BACK(GRAMMAR_SEQ)                              \
            )                                                                   \
        )                                                                       \
/**/
#endif // BOOST_PHOENIX_NO_VARIADIC_EXPRESSION

#define BOOST_PHOENIX_DEFINE_EXPRESSION_RULE_VARARG(NAME_SEQ, GRAMMAR_SEQ, LIMIT) \
        struct BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))                \
            : expression:: BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ)) <  \
                BOOST_PP_IF(                                                    \
                    BOOST_PP_EQUAL(1, BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ))           \
                  , BOOST_PP_EMPTY                                              \
                  , BOOST_PP_IDENTITY(                                          \
                      BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_POP_BACK(GRAMMAR_SEQ))     \
                    )                                                           \
                )()                                                             \
                BOOST_PP_COMMA_IF(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ))) \
                boost::proto::vararg<                                           \
                    BOOST_PP_SEQ_ELEM(                                          \
                        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ))            \
                      , GRAMMAR_SEQ                                             \
                    )                                                           \
                >                                                               \
            >                                                                   \
        {};                                                                     \
/**/

#ifndef BOOST_PHOENIX_NO_VARIADIC_EXPRESSION

#define BOOST_PHOENIX_DEFINE_EXPRESSION_RESULT_OF_MAKE_VARARG(NAME_SEQ, _G, _L) \
    template <typename A0, typename... A>                                       \
    struct BOOST_PP_CAT(make_, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))) \
        : boost::result_of<                                                     \
            functional:: BOOST_PP_CAT(make_, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ)))( \
                A0, A...                                                        \
            )                                                                   \
        >                                                                       \
    {};                                                                         \
/**/

#else // BOOST_PHOENIX_NO_VARIADIC_EXPRESSION

#define BOOST_PHOENIX_DEFINE_EXPRESSION_RESULT_OF_MAKE_VARARG_R(Z, N, NAME)     \
    template <BOOST_PHOENIX_typename_A(N)>                                      \
    struct BOOST_PP_CAT(make_, NAME) <BOOST_PHOENIX_A(N)>                       \
        : boost::result_of<                                                     \
            functional:: BOOST_PP_CAT(make_, NAME)(                             \
                BOOST_PHOENIX_A(N)                                              \
            )                                                                   \
        >                                                                       \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_RESULT_OF_MAKE_VARARG(NAME_SEQ, GRAMMAR_SEQ, LIMIT) \
    template <BOOST_PHOENIX_typename_A_void(LIMIT), typename Dummy = void>      \
    struct BOOST_PP_CAT(                                                        \
        make_                                                                   \
      , BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))                       \
    );                                                                          \
    BOOST_PP_REPEAT_FROM_TO(                                                    \
        1                                                                       \
      , LIMIT                                                                   \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_RESULT_OF_MAKE_VARARG_R                 \
      , BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))                       \
    )                                                                           \
/**/
#endif // BOOST_PHOENIX_NO_VARIADIC_EXPRESSION

#ifndef BOOST_PHOENIX_NO_VARIADIC_EXPRESSION

#define BOOST_PHOENIX_DEFINE_EXPRESSION_MAKE_EXPRESSION_VARARG(NAME_SEQ, GRAMMAR_SEQ, LIMIT) \
    template <typename A0, typename... A>                                       \
    inline                                                                      \
    typename                                                                    \
        result_of:: BOOST_PP_CAT(make_, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ)))< \
            A0, A...                                                            \
        >::type                                                                 \
    BOOST_PP_CAT(make_, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ)))(A0 const& a0, A const&... a) \
    {                                                                           \
        return functional::BOOST_PP_CAT(make_, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ)))()(a0, a...); \
    }                                                                           \
/**/

#else // BOOST_PHOENIX_NO_VARIADIC_EXPRESSION

#define BOOST_PHOENIX_DEFINE_EXPRESSION_MAKE_EXPRESSION_VARARG_R(Z, N, NAME)    \
    template <BOOST_PHOENIX_typename_A(N)>                                      \
    inline                                                                      \
    typename                                                                    \
        result_of:: BOOST_PP_CAT(make_, NAME)<                                  \
            BOOST_PHOENIX_A(N)                                                  \
        >::type                                                                 \
    BOOST_PP_CAT(make_, NAME)(BOOST_PHOENIX_A_const_ref_a(N))                   \
    {                                                                           \
        return functional::BOOST_PP_CAT(make_, NAME)()(BOOST_PHOENIX_a(N));     \
    }                                                                           \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_MAKE_EXPRESSION_VARARG(NAME_SEQ, GRAMMAR_SEQ, LIMIT) \
    BOOST_PP_REPEAT_FROM_TO(                                                    \
        1                                                                       \
      , LIMIT                                                                   \
      , BOOST_PHOENIX_DEFINE_EXPRESSION_MAKE_EXPRESSION_VARARG_R                \
      , BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))                       \
    )                                                                           \
/**/
#endif // BOOST_PHOENIX_NO_VARIADIC_EXPRESSION

#define BOOST_PHOENIX_DEFINE_EXPRESSION_EXPRESSION_EXT(NAME_SEQ, GRAMMAR_SEQ, ACTOR) \
        template <BOOST_PHOENIX_typename_A(BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ))>     \
        struct BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))                \
            : ::boost::phoenix::expr_ext<                                       \
                ACTOR                                                           \
              , tag:: BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(NAME_SEQ))         \
              , BOOST_PHOENIX_A(BOOST_PP_SEQ_SIZE(GRAMMAR_SEQ))>                \
        {};                                                                     \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_EXT_VARARG_R(_, N, NAME)                \
    template <                                                                  \
        BOOST_PHOENIX_typename_A(                                               \
            BOOST_PP_ADD(                                                       \
                N                                                               \
              , BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 1, NAME))              \
            )                                                                   \
        )                                                                       \
    >                                                                           \
    struct BOOST_PP_TUPLE_ELEM(3, 0, NAME)<                                     \
        BOOST_PHOENIX_A(                                                        \
            BOOST_PP_ADD(N, BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 1, NAME))) \
        )                                                                       \
    >                                                                           \
        : expr_ext<                                                             \
            BOOST_PP_TUPLE_ELEM(3, 2, NAME)                                     \
          , tag:: BOOST_PP_TUPLE_ELEM(3, 0, NAME)                               \
          , BOOST_PHOENIX_A(                                                    \
                BOOST_PP_ADD(                                                   \
                    N                                                           \
                  , BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 1, NAME))          \
                )                                                               \
            )                                                                   \
        >                                                                       \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_EXRPESSION_VARARG_EXT(N, G, D)          \
        template <                                                              \
            BOOST_PHOENIX_typename_A_void(                                      \
                BOOST_PP_ADD(LIMIT, BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(G)))         \
            )                                                                   \
          , typename Dummy = void                                               \
        >                                                                       \
        struct BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(N));                      \
                                                                                \
        BOOST_PP_REPEAT_FROM_TO(                                                \
            1                                                                   \
          , BOOST_PP_ADD(LIMIT, BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(G)))             \
          , BOOST_PHOENIX_DEFINE_EXPRESSION_EXT_VARARG_R                        \
          , (                                                                   \
              BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(N))                        \
            , BOOST_PP_SEQ_POP_BACK(G)                                          \
            , ACTOR                                                             \
          )                                                                     \
        )                                                                       \
/**/

#define BOOST_PHOENIX_DEFINE_EXPRESSION_RULE_VARARG_EXT(N, GRAMMAR, D)          \
        struct BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(N))                       \
            : expression:: BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(N)) <         \
                BOOST_PP_IF(                                                    \
                    BOOST_PP_EQUAL(1, BOOST_PP_SEQ_SIZE(GRAMMAR))               \
                  , BOOST_PP_EMPTY                                              \
                  , BOOST_PP_IDENTITY(                                          \
                      BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_POP_BACK(GRAMMAR))         \
                    )                                                           \
                )()                                                             \
                BOOST_PP_COMMA_IF(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(GRAMMAR)))     \
                proto::vararg<                                                  \
                    BOOST_PP_SEQ_ELEM(                                          \
                        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(GRAMMAR))                \
                      , GRAMMAR                                                 \
                    )                                                           \
                >                                                               \
            >                                                                   \
        {};                                                                     \


#endif

/* expression.hpp
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
*/