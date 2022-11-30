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
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
*/