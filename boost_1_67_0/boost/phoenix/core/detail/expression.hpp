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