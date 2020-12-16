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
imQubNX4w4kHwxHFsdNWlYUq+a4X2Ux8Koker+IaEiI5imtLcaTteBBpPS+eI/TyMtRaML7hJoTJtaesutYfrs3YMYvxLHzE9VZX1MSTHRHIs7LcE2m7OPIWfe/2+UrwqirzVsfVc9oJh/qrXRRXYNHNW//tWBhQJKVgx4K1/oudKrg0VNPaDF9+/OXH4cd9RuN/MSM6uWNG/IP56RptT8t1Mr97kXEGKu1No/Vrq/nvOLzClVmFV7J4tir8lWq+y8C/xv+//v/1/69T9rXJZRgh88nfNPNn13YxjATzucwfwIsUPwK3QcNfN8NnK353bwNfKZH3W+DnKt4Cj376GfwcxS/uY+DLHnnvH20Yt5H8LYMvI/kLwGtI/q6BLyT5uxZezPJXYBjDxbOnVv7OMPO3Aj5A8QY4tPU9/GW8NWMU4XuaW+yCv5GI95LvSkdezPC74a8p/i94FzO1p+BNil+QYRipZmlegD+n+P0ZVm4aJhrGfPEsr5U/m/n5Yfg8xd/tbn06AB+seG6WVRuOc1BHJP4B8FrJ1fpzwhcr7ku34m+E48ii9h+xvX1S+EgjfSnugM9i+YPPJPkbDx9N8lcHL5P6hxr/WngJ6T8/gs+QXI3fONcw1pH82+DXkPbLgS9R/M3Lrfh7wSsVf7Lcqu0G+CK1fNL++zC8VC2ftP/ugBeT8rnwfPa3SPny4ReS9tkE7yS52v718Ant9J9Opt8NF/1Lij/ZjO3n8HzJ1fy3wLuS9O3fMIzfpojyC3eY7oLfDSi0WT7uBiu2VfBvK74CHv30PvyC5Lb+Ijya22sKDWN7Ult3bbTGBwc6/0CyfxXBXaT+LoY7Sf3Ngw8l9bcJfgZrP3h/qf+o3gQfRBydR05feLLpyXCH5Gr/csEnSPGr5c+Hj5NcLf/Z8LNI/6+DzyTHn7XwGYofgXcy418PL1Q8DwWxmZ++B5+s+FVpVmmb4WPJ+LUfPkZ2tX4wuE4j4fPhUyVXx6fJcJfk6vFlE3wyab9b4ONJ+zXD+5H+Yf8WnPT/QvgQ4n64k5R/Gbw/mz/AzyXhH4afQ+pvD3w4qT9jNpyVD55C9r8i+HfJ+HwxfB4Zn42LDOMDdvyC/5WEd8CvV7zb9Vb5zoSvVrwMHi2tEx5S/Nfw6PjnKkJ8rPzwGZKrx7+L4dMlV49/c+DTyPyhgcaP9o8R/w4aP0p5MfZBmzQ/VfafHvBthuTq8XUOn1/VwyeS+muBX0Ha/xP45aT9/ZegJNhY3T/6RH8/Ejzcf3Ilf36kNf7eAN+v+KENVmw74Y8oPuE6q/88AX9Y8Tvg0dpqnItt2ilfF/PzS/D7zLCi/3aX9v9LUX/CrfCp0c/zeP3b4UNI/RfC/0zqfwr8HTJ/XAJ/RPEffs+qv9JvYx+06eMvgw+RXI0/AM8j5xdN89GWpHzN8APteK75+XP4M0b0s+gf4vh5DL5L8YIN1vHzOPwJxb8LF6PpApx/svENXkz6dx18veTq+eOtcI+SfulSa///Ebxc8b9I7ePCzpVBjn9F8MPtpG83P18Of+fE/iv2r1L4HxV/eIg0v0Hhb5THF/X8CH4DGX9cV/D5aSmczQ83wQcRb4Sz+c8zcDb/sS/k85MecDY/KYX3Y/mHs/nFD+BsftEEZ8d/ewk//jvgPUn+CuFd2PETPpz4Jho/ygIvl/Kvjq874QsUPwJMNFN7Aj5fuLV+lGCm9iR8nuItcJv5aRe8SHJ1/chVGmP/gicTLy3l45tfuPhq43XCNfUbI/36GN4APyLtn+r5z2Pwg5Kr85PH4QckV+cnl5eJ82vhj9il8xP4ZtnV/C9CXmz69Ym74UmSq+uLW+AJij/bx/r0e3iTUj8=
*/