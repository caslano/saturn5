#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/poly_function_funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_NORMALIZE_ARG(Z, N, DATA)                                                   \
        static_cast<typename normalize_arg<BOOST_PP_CAT(A, N) const &>                              \
            ::reference>(BOOST_PP_CAT(a, N))                                                        \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/poly_function_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // poly_function_funop.hpp
    // Contains overloads of poly_function\<\>::operator()
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/poly_function_funop.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_NORMALIZE_ARG

#else

    #define N BOOST_PP_ITERATION()

    template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct result<This(BOOST_PP_ENUM_PARAMS(N, A))>
      : Derived::template impl<
            BOOST_PP_ENUM_BINARY_PARAMS(
                N
              , typename normalize_arg<A
              , >::type BOOST_PP_INTERCEPT
            )
        >
    {
        typedef typename result::result_type type;
    };

    template<BOOST_PP_ENUM_PARAMS(N, typename A)>
    typename result<
        Derived const(
            BOOST_PP_ENUM_BINARY_PARAMS(N, A, const & BOOST_PP_INTERCEPT)
        )
    >::type
    operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a)) const
    {
        result<
            Derived const(
                BOOST_PP_ENUM_BINARY_PARAMS(N, A, const & BOOST_PP_INTERCEPT)
            )
        > impl;

        return impl(BOOST_PP_ENUM(N, BOOST_PROTO_NORMALIZE_ARG, ~));
    }

    #undef N

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* poly_function_funop.hpp
dpG+izQbESifZqLU17Vx0JToFdo00hs1QlVCLuALe03cjwd1zDECqX4k98KcnQ+tOivpjBKVoOjZd+NJCNpmLBLp5sP6brqfe3HAT8X9X97OmcOwi8tajCI9iqvsl1af+Q4Hr2VOd+K9xHanyCVm2rr53ku65sTNBUUi0m1hwtdT4xTkYbcnVl7mjgFCtQD7GWw2caZNXS7c3W5wcHV/7SYOK5xiDZ7aiP547UaXnO0CLMdjWtmNnOFXru+jyLWqaQU0pqNDHf2Oln3P+g0/KWYZJlJaCnVKJbzoi/7fPC7zNMG7vmfDW1PDm7WMaVkWajV5jiOzin03jRFL846E7INjJT1f79INlrMJKoAq+xYuXEcCshc5s6QhqEctkb+D4EtLPGPcde5J9SIkV73epkF9acLbm7WW+jc5v6ezVYBJ5og/zaMozOsc3+KbR+WV+PZUC4n/bXXCjV7RPTF+h//zDkaENPp1wwGvVxnM3nVOs1gAQDIpF8QMevAtTcng1uGGLpiozr2KmeipPxEMmyNfWqE85plZBW9EwfQpnu53ut7ragn5qv5Spw==
*/