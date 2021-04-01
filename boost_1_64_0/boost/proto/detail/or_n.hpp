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
oLWBUTn9aAnqMqWO+2SBS29wJuSnTEEOC7O+IDcfZAzWnnfpWFNhVQVrG9BA1ueEpAXDAPtV6Xc3yPC8diJBp6ZiVZp2zu8wlAxqkWmgE35AVyCdiy0gBSeDAwvRDTvyZMznzLK11FefaulAnqJ6WbwhRPxKVvoeY5Qnep4lWhtR35DsW5GzC1dZGrz+rekTIFY0uY3RRORNjYRCMDqWjv1RI4Gd1YPWAbe6ZPqEg+yoBPi2HQJYo9WszwjzVKmQLScfXTQmGw3jis5cFmGxQ7JB9VUCkp/UlWDDdC4GHNJ5XHMB/09nTsprum2/A+TIAcz8urjm49iSaYPrxufwywhTpLEbq6zN24g15bHsEF4dkVom2enjegzf0h6tquSRcCdLIMU/ayOBRyp61VO2WvlBfOFuoSfrJY9vcuc5GHCdelOqSWvCBdWuKhuWxi+8McpLttojPOaKjw5udXPe7jYAeVZrrvCn2+ywcsmUTcAa0M5MqPdL4v0GTBk6KMSRgfg7LodF8izdrwiY/vnreZsmrIBZUpKGdlKhPmdB8Q6EGzlFE7or3CX1bA==
*/