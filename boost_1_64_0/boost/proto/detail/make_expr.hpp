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
p1crHqGbdHt5p6NiHNq3XFXGa3PXVCmvovK6dGy/YDm0vXpLeOUd4q6jTymkRyC8vvUsPxkme+7m8aHLt1ycIR+lm7EQQP9OEyW+gPUABVAI6GIG3vx1OMkQ7ocbH3nQMZSe/XrA83Vhly4DSYpaX1KpDNjOh+Br2Kkkfj7KN35dDwg1K44F1jN/Ci5E34AJgnFqCAyJm/D8fY+jYDiokjLZI7f5k+VHOckSMSjib7E9tOQ2JRLR2JJcG/rQzfuPMfP1Frk7y0hi6Xl2OubTCD5R8I1hNnR1T8Wj7og+IfoFiP/Now9+dZdg1UaBOta1cJwxaO/gpYqlnVODFlUPb8EK/5s9Wi9FrG/XYoOdPJxAalXOE4A+iTaaHdbbF/wOSQ2MBK/lI0bHy4PmfqsqNeCydzIFMjPLWUoddFEUBg63yr+GK0irK3neN6Q2C41UqnwdY1HLMqTu0mIldqRKTLLlzsmg7ILzIjzy+BQyJ2jtz9FM0iC2cv0zWe6gpyZp72c2BjA2F8dOsflTV1Me7cxnawU1vc70H7jyMfJb4njggLHuisbha4z1pg==
*/