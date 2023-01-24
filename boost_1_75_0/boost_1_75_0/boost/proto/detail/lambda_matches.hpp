#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/lambda_matches.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_DEFINE_LAMBDA_MATCHES(Z, N, DATA)                                           \
        lambda_matches<                                                                             \
            BOOST_PP_CAT(Expr, N)                                                                   \
          , BOOST_PP_CAT(Grammar, N)                                                                \
        >

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/lambda_matches.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file lambda_matches.hpp
    /// Specializations of the lambda_matches template
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (2, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/lambda_matches.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_DEFINE_LAMBDA_MATCHES

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    template<
        template<BOOST_PP_ENUM_PARAMS(N, typename BOOST_PP_INTERCEPT)> class T
        BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Expr)
        BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Grammar)
    >
    struct lambda_matches<
        T<BOOST_PP_ENUM_PARAMS(N, Expr)>
      , T<BOOST_PP_ENUM_PARAMS(N, Grammar)>
        BOOST_PROTO_TEMPLATE_ARITY_PARAM(N)
    >
      : BOOST_PP_CAT(and_, N)<
            BOOST_PROTO_DEFINE_LAMBDA_MATCHES(~, 0, ~)::value,
            BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_DEFINE_LAMBDA_MATCHES, ~)
        >
    {};

    #undef N

#endif

/* lambda_matches.hpp
fAkaQIJ3vCwdKK6h6BSyw6DKA1lN3CcdW4O/N6jkXlSb+11UlzzXOtzgvVeRG/XDyLhvyS9QFyoToOQ1iIjRr+kOMKRIDoU8bSmvs2oFw3ESX3ilR1NvkJz3GJXsWnF8bAJ6o/J4FdN+CLx3WzdETMJiZXBehJ+j78yMqZXToSCaBks+kpL2CTp95/g0Ct68mGIGm21iLAsuf532m/VTwnx2a0+pMjjVYqqJaKr1kx9zQVsbvZCLaKlnrcw4l9tr7dmBsPpe75Y0LvD1LuwGmw4Ss46MTSYUCUh04h83WWT+tC8X/qzG0K2jC4cfrxbM9D9m2FNuFh90OOAoiD0XjFGPUSPlupZefiB2hFeRYF1i049BC9a5OO7YbUkptaaD0VDzP2eupoYx/Dal4fCAyFjQ3DdhZ0qlB+F/YDhoOZu7DffVq1dc/yeGOf/K9/UfWcnRzszRxMnp3xj28tbW9EFmWTFeMccmtVok8kRclyY1Nhkxxu7NRxiNJRYn8zmcb/8KmWyrszvTNtZ1ckkZYGW8/lxru7DujBPEmj76y9p6voDRuVa0w7o2JsamVtrg7fLqh3vUwdVrYpPkSKjH0U+eZkuPZ6Mnbz7wlOLD+g0MMHnqFXtBBATvPuHpaT2gTmCdq0nVQJjMZUVJVFnEWPOCvf0AqWMHSU7CmEvqj1Q/xMFVKvCjP0kPTyr2/K2oOpjVqJpBqQFWaisr
*/