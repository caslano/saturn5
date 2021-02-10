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
y3MSN2qiBgTH1cZuc/eliyMsbj8E4SUIF0zyAwkF1ssw8nkdUoe7YM6FQy8e5o2jpMFre5R7QJKUVo4VAm/3Es5kHEWTSbRwxC9LOQ+k6JTzQkjnb+MiJeYcZpiYGmR+2xlJvPwq0aX0bpalMa1RWfq/bzKBKG2FAxRFwLoqp0Z88IL0TRT/AqwagCtwdo1ptEn7MzTIyQ60Zu1RVuInIliC+ShReDeN5txS6E0B6iyY8SsWOKBmfFypBUtO90QneU6TYdicBoM4wqzHJng8O364PU92JsF17MV3OwsON+7AyHxKoxlUOPjHj7v7/2h6yezzV0L68fneDz/ua0gYzcQVeqFyf5H0cY2iT0l/hSglLY+w/jQUjWhRg4ZhOKcUCQbF6wpSnT0GXl0JgS644uzf4tpFGrnpITpjwqnuXcNwHary6vTSrKxw3pNTezpP/c9cm75SKmLM9flfGCzgVuM18oKGKCYOxwKHtc47eSpxY7XT81/POidqMjuHYZ+CXRCL6q0m7VMtEWwcdVZPQ+mAI/9NPu6TduOFhYv2MWJEnIX2STzEd6eti7ftPvhM7bftCxIuDUw7yALKyPoodcObdNxALUzqa4djZJR9IY2xCWbobDI4mKaEPZoCS/pWt0khVgTJrXwMGR9u
*/