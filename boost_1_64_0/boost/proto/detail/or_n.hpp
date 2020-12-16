#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/or_n.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/or_n.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file or_n.hpp
    /// Definitions of or_N
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (2, BOOST_PROTO_MAX_LOGICAL_ARITY, <boost/proto/detail/or_n.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    template<bool B, typename Expr, typename BasicExpr, BOOST_PP_ENUM_PARAMS(N, typename G)>
    struct BOOST_PP_CAT(or_, N)
    #if 2 == N
      : mpl::bool_<matches_<Expr, BasicExpr, typename G1::proto_grammar>::value>
    {
        typedef G1 which;
    };
    #else
      : BOOST_PP_CAT(or_, BOOST_PP_DEC(N))<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, BOOST_PP_ENUM_SHIFTED_PARAMS(N, G)
        >
    {};
    #endif

    template<typename Expr, typename BasicExpr BOOST_PP_ENUM_TRAILING_PARAMS(N, typename G)>
    struct BOOST_PP_CAT(or_, N)<true, Expr, BasicExpr, BOOST_PP_ENUM_PARAMS(N, G)>
      : mpl::true_
    {
        typedef G0 which;
    };

    #undef N

#endif

/* or_n.hpp
85Li1FEGa/jmHMtg6qapmrJJmXu7eF5kZRF8OMEGGds0yNJKrjL5P75hwP/PbhNZ4irld4FLbhqptbPEQ3GrNFiGvfA2GJVBslwbmTZ5yebbbmustReU/GF/h/cMt0ZfGYL/nuCLmPKpWVpmWQbulCC+q3sU2j3qHNFNgn8CmqZheZmWshCCWfTC4e7AxBHX8RNQBkPT8YzlRjS5FQW7REu33bcynIXYWTT9xUJVteRcsuFlH9WLeLlz/hZRJkrTrNvKFEmZibZ6aDV0LvgLp9izdSZkVebgJex5CO30xb8Ztb8Cfw+6rAwPb0lHbcggl3Z8NDkALXpwIX009kYqnazkD1H5uG1yqYV/pcZMhyEmbdR+isksU2CUEcd8jkM992NI3PYePR82Kq1TVfR5cG3nPl2mM/fWGfgEm61HIB+Mw+Kqr7nt9KV9hGAX4oPELFjudu96WLYq4slZWdikScSiTwVkjQZxUNpznR+zwx4fqaskMYnt/MdhZWHJQHtE0nC0jK58WOe3RXwrJqVSIstkx1edbCDVZdO+SQbdiIinZFlWZalRla8zJpqHwgpz299YIWZyeDejfGqWi7JR2oKuDrqEjt9h/9zrv1wmpRB1yebuHIivEseDqArF44pt4Li6Z2xbIkWa15o3yI9GyEbV3aDXT3hS2/9VylMI1qgsTasmxbYJJfS3NN+B1BUR0d/d6vGqrSoNGKw0biz5Zc4V0R1fLzvlO1yAIlYdrxdQXrJkqq4bWUCAhOE2euFEFpBaP/9oQoct8HoCrk9Ru6WskrmyipcMNjpvB0MjF57rx0b8Hk1/Jk8aW+S8Zpnaiu0b/kBxjn2apLnSpu63pa8tTizSMaQtb3iv3t6TmlrIkl1eEi8+eMEnjUnX0YdQXq7gqSwLKfJ00Z6PmoCGdkiRj4zKVDJZpGnW2PR/KtS4s6d9RVSejNmKp5ng3icMRvQiDNCHUrDHjdKnrBamVk1atemd6t34YElyoj/52V57WCu5VI0hznigQrSXkO25/h71w6hNCibztCpNUv9PbXJd1yb/iMokHR9VW6Pskj5abtN/b7qvypLrStYSImtMF3Q0HkKxQrOqSnglkoqs3d7DHDQGOg8boVssVLtj3Vk4ylvYJFO6TltPqpj3BLHPptjzylS6ElK1WJdRHEtyF7EhbqAU8FwZ/EqAavF4G7T/QrCc3SGuJoN5PPK0AvNleNt6FJ6RKN9zPM2q2hQcPJ2dX33B6mpor/BWRfFrprYV17lo8Yhlazg2KfZCmSSZzStDo1SG4JbTx+A7VJRG5k2pS20cf19LSJAb0EDsjgjb2EZfpml5wXSVJblROVvaJtAa2CwGvknTcq+Qb2ijX1C+60IWddEoQcvk9Zaw3r+Jx5+2hS6bAvALZRfYrve8TxTTj1dlXYPLwmvusW68HY/vB0RYlSludCPZph00yVYeYx9BsWfB4qrQMmeVTeTC++3ZCJsnjax4mrLh8WyC2C72EsVyy7IKgj/WCRvBHPXeGyDdupeKhD2lb7/4zIhPylKZgIdaNHPBxWbpUY76yJ1FfCTLTd0UhazYpnJmEc44ZKDNltpIE6GCn2uOPp+itDmzvCmlkJZt+2Mb3GbQsrq39iUhhlDEQzDRJCXPhWTLyw+OxqjJbKfbTPmImpVlWTWZbdgonM/chg/nGlTfw1XZPeaxFVxD3SIYn90bUJDWWcb+szu9YHd3R5p+3Zg0F1mTMjQdhB9hPQs2rTSNKJjNUm0Krvplpz4vYYh42zqis4d8UJexyLMmKWKfkEduoAWbJ/hEN4N4zdql/M4JlSdWGc4wwlEUM+6QYs/XaSHTpCix3qCe09P7iXhXjWw=
*/