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
AAABAAAAAABPszsAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzE0VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUiXkph/+BwAAKgsAAB4ACQAAAAAAAQAAAAAAbsA7AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDMxNVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIV4SC/VQQAAF9GAAAeAAkAAAAAAAEAAAAAALHIOwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzMTZVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSTzdxDm0CAAABBwAAHgAJAAAAAAABAAAAAABLzTsAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzE3VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUke6lOlzAgAAIAcAAB4ACQAAAAAAAQAAAAAA/c87AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDMxOFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIIWxi66wIAADEEAAAeAAkAAAAAAAEAAAAAALXSOwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzMTlVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS
*/