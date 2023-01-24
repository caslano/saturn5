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
zW5Arp6Y/uJN5hka33voYCRFYXyH/G3kzWth/reGVRTvS9B8cWWmidtBud6xp1shPvuZPRdxWMkIZr5cnfyxZU3fKCBL7f3Q62pEYc90Tu/PO7NbrUqZnAJwIbg38kaykgFE9OnOxFNSXymWH9L3lQzpIdfjl2PyAckRguTD9ZbY6YnC8vKR2QmaYtC50Q1Bs9Nwt83pc1IOgcQyebvr7IhI7/TIY7EDyy536Qn0OkeLr4buQtGwHbQMMp/LqixsK48M++g+khw+jmCEYPoMUXjZrrTkmNzsjGPZxLgmNetpV9jMN1uQLmutDpTXPpzcftwexjh2LcSpf2NDeT4/ODJlKxKZ52Klu1rwM0wjgPwE5TzZFeP7kDuiozHc1WFyvc3Q7BiwinRFjvj5XdofnffSB5r1LfUpBr/QegfVvilpIlkgekHuh8xb0DyBhPEuHvASxnYAul7UXu1n031FUVB2OQRiBzdxi07m6TRI+C9+3C8/I7Z89sVxziB7gVNTIaNbvOLdjX5aS03VJYFFY6DxB3YftUf4SH9eap8i+8kaJQXhDXzG1545gxY8gWtzytT08OeBPbqmZD07ZBRCLWBe/BLXeI7T3RhuV/v4oPjy/NuEdhhK3bYp/xR17kHMtPBg9/cGpE+j4xpPWkqMcsuPtbHidHR3kLIif7YbefKKkl13vjNv/urBj7za7EkY9R+iLxNtovf9x3mb
*/