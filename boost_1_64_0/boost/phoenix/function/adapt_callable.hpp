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
GX3ghLnCxWq7768h3m+I8ySOwjNZs+J8iko0HzaZkWNSl3t88T2swackItbcpsOkOFpjDzhDq3o4EtkLUl4yxbYlGSwxciBoNLcV6VKyXdNVCqC9QaHSDUHXkNaCUqtX75AyNFHbZ5TK4SSKvGV65LbJdNPn27rRh6GfqWSPuf2Ie5WKOFqwyFngDL4DcGqmULmWLs+y2dC+7km37BD5kXUXkiM5BpMCI4W0taQAYe2+CMjUaavbafAS9IYva9ARruJIa7LGXbEquk4VP5oVQgUtSy1+LY6oyqzmoWUayxRElt014t1HxpJlBH3LkcZdAGK6Jn+KdOJLtI/3IENUGXtfm8kURQf4YRNj/DdDaMFmgKtgsQpX2WsdrTHWk/z21ZRhoEmXro8bl83a+5C7g71JlG0BShiqpH1Jh6vXo26bWkCzJJJ75E+DMq0taYJqpxhCEEFj2Vd3f0Glg/qasn9X6ZWs59Jz8k3gbA0IeRZpg97tGp56HWk2zvCiPN8P8L+mcwRb7Yl6gn309xDdxqooMyd+QltK+PpK24xxg9J8YJ3ekdW7o73C2g==
*/