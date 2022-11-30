/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUNCTION_ADAPT_FUNCTION_HPP
#define BOOST_PHOENIX_FUNCTION_ADAPT_FUNCTION_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define BOOST_PHOENIX_ADAPT_FUNCTION_NULLARY(RESULT, NAME, FUNC)                \
    namespace detail0                                                            \
    {                                                                           \
        struct BOOST_PP_CAT(NAME, _impl_nullary)                                \
        {                                                                       \
            typedef RESULT result_type;                                         \
                                                                                \
            result_type                                                         \
            operator()() const                                                  \
            {                                                                   \
                return FUNC();                                                  \
            }                                                                   \
        };                                                                      \
    }                                                                           \
                                                                                \
    inline                                                                      \
    boost::phoenix::detail::expression::function_eval<                          \
        detail0:: BOOST_PP_CAT(NAME, _impl_nullary)                              \
    >::type const                                                               \
    NAME()                                                                      \
    {                                                                           \
        return boost::phoenix::detail::expression::                             \
                function_eval<detail0:: BOOST_PP_CAT(NAME, _impl_nullary)>       \
                    ::make(detail0:: BOOST_PP_CAT(NAME, _impl_nullary)());       \
    }                                                                           \
/**/

#define BOOST_PHOENIX_ADAPT_FUNCTION(RESULT, NAME, FUNC, N)                     \
    namespace detail1                                                            \
    {                                                                           \
        struct BOOST_PP_CAT(BOOST_PP_CAT(NAME, _impl_), N)                      \
        {                                                                       \
            template <typename Sig>                                             \
            struct result;                                                      \
                                                                                \
            template <typename This, BOOST_PHOENIX_typename_A(N)>               \
            struct result<This(BOOST_PHOENIX_A(N))>                             \
            {typedef RESULT type;};                                             \
                                                                                \
            template <BOOST_PHOENIX_typename_A(N)>                              \
            RESULT                                                              \
            operator()(BOOST_PHOENIX_A_ref_a(N)) const                          \
            {                                                                   \
                return FUNC(BOOST_PHOENIX_a(N));                                \
            }                                                                   \
        };                                                                      \
    }                                                                           \
                                                                                \
    template <BOOST_PHOENIX_typename_A(N)>                                      \
    inline                                                                      \
    typename                                                                    \
        boost::phoenix::detail::expression::function_eval<                      \
        detail1:: BOOST_PP_CAT(BOOST_PP_CAT(NAME, _impl_), N)                    \
          , BOOST_PHOENIX_A(N)>::type const                                     \
    NAME(BOOST_PHOENIX_A_const_ref_a(N))                                        \
    {                                                                           \
        return boost::phoenix::detail::expression::                             \
            function_eval<                                                      \
                detail1:: BOOST_PP_CAT(BOOST_PP_CAT(NAME, _impl_), N)            \
              , BOOST_PHOENIX_A(N)                                              \
            >::make(                                                            \
                detail1:: BOOST_PP_CAT(BOOST_PP_CAT(NAME, _impl_), N)()          \
              , BOOST_PHOENIX_a(N)                                              \
            );                                                                  \
    }                                                                           \
/**/

#define BOOST_PHOENIX_ADAPT_FUNCTION_VARARG(RESULT, NAME, FUNC)                 \
    BOOST_PHOENIX_ADAPT_FUNCTION_NULLARY(NAME, FUNC)                            \
    BOOST_PP_REPEAT_FROM_TO(                                                    \
        1                                                                       \
      , BOOST_PHOENIX_LIMIT                                                     \
      , BOOST_PHOENIX_ADAPT_FUNCTION_VARARG_R                                   \
      , (RESULT, NAME, FUNC)                                                    \
    )                                                                           \
/**/

#define BOOST_PHOENIX_ADAPT_FUNCTION_VARARG_R(Z, N, D)                          \
    BOOST_PHOENIX_ADAPT_FUNCTION(                                               \
        BOOST_PP_TUPLE_ELEM(3, 0, D)                                            \
      , BOOST_PP_TUPLE_ELEM(3, 1, D)                                            \
      , BOOST_PP_TUPLE_ELEM(3, 2, D)                                            \
      , N                                                                       \
    )                                                                           \
/**/

#endif

/* adapt_function.hpp
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
*/