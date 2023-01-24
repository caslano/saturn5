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
T+v1g1pt0u2ONxU4gEYrOIBvWTehKhgM0CW1FTeBZQmCFozrwC6XsHa5mCxmrfkkN+sFJk3LoGkctk3jlrHfMPbqxm7L0uvYey1bp+vsdZydlrPddDYbzkbdWa87qjV7pWKrlKylgiWfsaVjzjgUj8CajoSJSEQbi8lTCX42e1LInWYzklhU63GbLFaGNlpIiiHA2gZarwNr60il2igFa0usPBEUaSiSA+7XZ64XGPevZziSn7HfqQKvGqVMs53Z/ZatO9Y3G9bvHmcNLQy85wAF8qwOoGjUewf7L1691qrVEI2BnVqhNGi1AqEAUqdCLtNrNSoF2kjrDQqp9Olvz/k8PncEtVKJOGq0sOXo8Eiv0WiUKqjJ1ViwUSAQcBvRFjhz1GqgD70V7EPo9HjMGr0G2GFv/+3JyYnNZNZrdbCzQiajdDros6Akg1quX6mMP25qjnW/0znl8e0M08PTrrjuC18zX664vhuwQ3U2WE7Ks15k3HWPe7ZJ2zxqGYctU79p6lWoVtva77tHPdeg4+q1XZ22u91ytZouwA2sazVHpWqvlG2lgrWQsWVizgSwtgXDxgiyNmRtVSIuSafO8tnTXFYUj6t9Ptpmg6yEWUNBDrj1KGsTai36uTaJjMFFmu0YcPMhkiNrPz9zPzv1/HLqeUKEzurldLdf4r6Y5StY28zmUa3eyGSyoXAzl6+lUmenJ+CpZhHq4WoO
*/