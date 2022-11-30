/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUNCTION_ADAPT_CALLABLE_HPP
#define BOOST_PHOENIX_FUNCTION_ADAPT_CALLABLE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define BOOST_PHOENIX_ADAPT_CALLABLE_NULLARY(NAME, FUNC)                        \
    inline                                                                      \
    boost::phoenix::detail::expression::function_eval<FUNC>::type const         \
    NAME()                                                                      \
    {                                                                           \
        return boost::phoenix::detail::expression::                             \
                function_eval<FUNC>::make(FUNC());                              \
    }                                                                           \
/**/


#define BOOST_PHOENIX_ADAPT_CALLABLE(NAME, FUNC, N)                             \
    template <BOOST_PHOENIX_typename_A(N)>                                      \
    inline                                                                      \
    typename                                                                    \
        boost::phoenix::detail::expression::function_eval<                      \
            FUNC                                                                \
          , BOOST_PHOENIX_A(N)>::type const                                     \
    NAME(BOOST_PHOENIX_A_const_ref_a(N))                                        \
    {                                                                           \
        return boost::phoenix::detail::expression::                             \
            function_eval<FUNC, BOOST_PHOENIX_A(N)>::                           \
                make(FUNC(), BOOST_PHOENIX_a(N));                               \
    }                                                                           \
/**/


#define BOOST_PHOENIX_ADAPT_CALLABLE_VARARG(NAME, FUNC)                         \
    BOOST_PHOENIX_ADAPT_CALLABLE_NULLARY(NAME, FUNC)                            \
    BOOST_PP_REPEAT_FROM_TO(                                                    \
        1                                                                       \
      , BOOST_PHOENIX_LIMIT                                                     \
      , BOOST_PHOENIX_ADAPT_CALLABLE_VARARG_R                                   \
      , (NAME, FUNC)                                                            \
    )                                                                           \
/**/

#define BOOST_PHOENIX_ADAPT_CALLABLE_VARARG_R(Z, N, D)                          \
    BOOST_PHOENIX_ADAPT_CALLABLE(                                               \
        BOOST_PP_TUPLE_ELEM(2, 0, D)                                            \
      , BOOST_PP_TUPLE_ELEM(2, 1, D)                                            \
      , N                                                                       \
    )                                                                           \
/**/

#endif

/* adapt_callable.hpp
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
*/