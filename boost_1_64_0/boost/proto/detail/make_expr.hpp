#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/make_expr.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_expr.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr.hpp
    /// Contains overloads of make_expr() free function.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (2, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/make_expr.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    /// \overload
    ///
    template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    BOOST_FORCEINLINE
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
            BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
        >
    >::type const
    make_expr(BOOST_PP_ENUM_BINARY_PARAMS(N, const A, &a))
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
            BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
        >()(BOOST_PP_ENUM_PARAMS(N, a));
    }

    /// \overload
    ///
    template<typename Tag, typename Domain BOOST_PP_ENUM_TRAILING_PARAMS(N, typename C)>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        BOOST_PP_ENUM_TRAILING_PARAMS(N, const C)
    >::type const
    make_expr(BOOST_PP_ENUM_BINARY_PARAMS(N, const C, &c))
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            BOOST_PP_ENUM_TRAILING_PARAMS(N, const C)
        >()(BOOST_PP_ENUM_PARAMS(N, c));
    }

    #undef N

#endif

/* make_expr.hpp
FoiJxy3k6iPNubJhvo85EevtChDHABePxdPggAEsLPBOCLgUcaR/IizJe6PDPvnMwJnHI+fBwba7RYQ58oHHrQAOuhm4wMtsZ2tzO6C13wbhBD1d2UH6bc+39KPJrBOPu8+B3twF6POeg5ngt6AdzPtlj2zph6A3Nbg2mh5MVvaxL069qqXBQyoZf7C+rWxj+k+9OmBw6oY9/NTp6PzDdWnzMm0Yrmfbw9iW92WnorNwbjOpswzsr8fukj5AQ+LonPAimseFhluhbFUx6NvLw+loIbbEa07H9yKVW5MVKujY+TU0ejBA13a87z/iw5RXzbioGtuIipHZF3ROw3n7dFxHnqec13CyiSXVeEfHet51jdZTVxBnPrNBdIj5XEP8AyK8TcGpZSYZjAB4sQp4g3qja737YlIlXFMlbu/sGl2PnznBtSfmX0X510UjuTF5exql+a8bvANQvJCMpwkXBdWHJwfZ5cWI4pq+KKpP0vpTq6xSjMwkIqSdBHn9Ws8nuSmT0grSDuQeC7ywLFgUtsJwfHx2rXdH0aLmjWBuD5x7RgPZeGyP+22aRlWsznmhyoSBJ6ZWUDbamYYAF/5NDq7uQ2/53MlW7ngmfpep8srq4LGR+JOnUTfQeJoE5Q3jg/KTGcuSKmtsqVi7Nnc6oJ4XimrWr41aKdtlkOLvMmJHu0v5WcZFUuZCl8wLlijTUJaRQRloVDe4NKc8tTrrlwXjnHgRB1Bg61704fouyk8UTGYmz6wQC/wuD3dwWQiOvNbBVLN7H/9mxMsyq2VaizRZygtcMjoOq/BxAi9l8Mu2+9E2whRiXQT/YGf6OsYiyxues5ahb7HxaIpuwbyHSPShD4shicV7z7P9mCGqztO8YVdJDKF2x8C26vwlrkZpOcsaXtlSKJAr+ZQ4sHxQgb4usYzSJ0zmpS2qOmN1GzXWP88u0fneoulAjVnZMm+sZmZCKn9lcnwwf4/YHx5dF2RbRHYS8VGMl1nNy7R9VBmBeCZuT8+nnWHTOTcSB+5sPw5CnqtCCrZ5vA139ivHe3vXsEfIwgEFZU70E/zGRW0iWVHZPKlSeM0iXgljD8TBPy5NWzNuikQkUrL2icdt+4OdgyA74WirgGlQB0Q2MhWNZfsgaLhKoy5Me/YOV7DMt12P568RQsi0Yv6td0lKIqt45no8/qpc6rQxBg8GoM91NIO5GsucDmk6lYETGHgo1qzF+9kdBzhadb+CfHUXwv9Gsv2v3Z/KqOtMJY2wFZtN3PMNrjdY3i+sx2PWaqFMmWehvM6xXlfa7g3k2zQdHDGEyHWeNszh/2tp3QrBiF7ELc9FsqsssTxTtmuy8OpE5JT3PNd7e+Z1XqhEM/QHvjeZXHd8CCLL58NAP7gWqRFEehF5xEuypkgMb0SGPkWfvwuCcHR3Gq+SVB6+R/nwkqnKplmiLIO7VX9x9c2zurokRvxrenxS29hG5eXJfJbb0n044tOwQslSGqv/R3uZITGXmRrcA8717OGapJamKiI/XFfcAgtLPsrCL3hpPPXJzdH+IipjBYoKygqlWe2EdEfe/gtl3P3106De13m6f9esTLlt364BKFJvE+L1PeDf8XkLn8lIPzLKT0gmRC3rhBcM1KF1qkWypa0BNQojVKUkbHneTz8MmO6Ne4fy4ZpVYKViVHMSn76d2otoejim2UQlpSnZU0AUN68V3gb8Qw3W0L8ou8HJcSyc7/uUy0Vd1jLETYUUyz35rge7m6g8CQPTPZnohi2YyeGJejaZ+Jh6yCvslX+kvMAlsGjKpsLSLKyvo+BnMqqHBEcw4FXPstbh+DpvW8LLMfB01a0zF6L7SVUXosoTCc8B9NQcx6c=
*/