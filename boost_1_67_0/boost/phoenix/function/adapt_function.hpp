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