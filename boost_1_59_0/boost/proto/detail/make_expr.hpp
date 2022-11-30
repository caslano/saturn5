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
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
*/