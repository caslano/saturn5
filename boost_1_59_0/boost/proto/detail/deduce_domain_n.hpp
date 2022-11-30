#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/deduce_domain_n.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_COMMON_DOMAIN2(Z, N, DATA)                                                  \
        typedef                                                                                     \
            typename common_domain2<common ## N, A ## N>::type                                      \
        BOOST_PP_CAT(common, BOOST_PP_INC(N));                                                      \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/deduce_domain_n.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // deduce_domain_n.hpp
    // Definitions of common_domain[n] and deduce_domain[n] class templates.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (3, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/deduce_domain_n.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_COMMON_DOMAIN2

#else

    #define N BOOST_PP_ITERATION()

    template<BOOST_PP_ENUM_PARAMS(N, typename A)>
    struct BOOST_PP_CAT(common_domain, N)
    {
        typedef A0 common1;
        BOOST_PP_REPEAT_FROM_TO(1, N, BOOST_PROTO_COMMON_DOMAIN2, ~)
        typedef BOOST_PP_CAT(common, N) type;
        BOOST_PROTO_ASSERT_VALID_DOMAIN(type);
    };

    template<BOOST_PP_ENUM_PARAMS(N, typename E)>
    struct BOOST_PP_CAT(deduce_domain, N)
      : BOOST_PP_CAT(common_domain, N)<
            BOOST_PP_ENUM_BINARY_PARAMS(
                N
              , typename domain_of<E, >::type BOOST_PP_INTERCEPT
            )
        >
    {};

    #undef N

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* deduce_domain_n.hpp
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
*/