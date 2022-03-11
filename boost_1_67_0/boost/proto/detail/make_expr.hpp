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