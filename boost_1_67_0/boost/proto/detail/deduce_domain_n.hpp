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