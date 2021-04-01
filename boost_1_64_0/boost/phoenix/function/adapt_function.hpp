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
NPwRP2wV5Y706rinf5zrE0TyMN50ub2ceNPBeRY7p7gekqQ7jLUgOClK6hOQRdfVKd4ENQpuBL4JdBANrUwjaPvgsvsDs6HqfEslwG3373nbprgxYHw0X7Rq7Tf71YaC5E74/K+WmDoTVKdorK3xa8i6svXiqFfw33kvNrVLcKzjyvaNuBWyrsUrC2jX7xhnmW+XLggiC3FaPRTsg5emZiHr6HuZaRQzeO4V/5+TK4FbIjzECOLOGIlJXBtkeRaCLp2PRw2whZqKGz3S9FGiINvyOSff6GUgvXXHxQFzDW57Qokq8Dgo5reM6UD+jdK80IRkEN8KoU+093B6W+9XFFZ0I/SKNsdY+B0tmRwnyyMJSoHc5qXcbr4zvZ5U4vKD/w0Ck2Lx1GYaDaEfxK1asBpCCdcegRq/eNAWsBp8P+3aLIkSwg3ObVWa/zSoa4EolDMuLZ015+mOgkmFZ6nd90i5UT09jrxZH+PII/Y09y9xyhXkR9myTd9/pfJ7XBFOL9ZHTI1U+UtbZI9LHAdLL8r3Hg+5+qoc1NW7/GZ04ilRz0sLkYRhx2CGUw==
*/