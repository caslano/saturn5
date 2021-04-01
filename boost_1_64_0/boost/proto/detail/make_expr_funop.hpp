#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/make_expr_funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_expr_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr_funop.hpp
    /// Contains definition of make_expr\<\>::operator() member functions.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                     \
        (3, (2, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/make_expr_funop.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct result<This(BOOST_PP_ENUM_PARAMS(N, A))>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
            >::type
        type;
    };

    /// \overload
    ///
    template<BOOST_PP_ENUM_PARAMS(N, typename A)>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
    >::type const
    operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, const A, &a)) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
        >()(BOOST_PP_ENUM_PARAMS(N, a));
    }

    #undef N

#endif

/* make_expr_funop.hpp
qsm3fH32wdKMJyL7OXNCXuQsFzEjkCLDVJIRL1hLKAu8huoXNm/yZCmaQ7LrYIW9GPUIoxCGItCnQFOLz4knSDq2C4UtY49WGGw70tZn+F4fUAPWhS8u2p/9RbP2v/NY/QsS9W3V8wNcn8nmyTCF1mVkG+eHu9tTNBE4jTbWBMvH0sqKnBvDfOAR0XokTdD7hStz9rNOcqYmsYCPAufYLzp8YVh0fE0m+2pzouZnMSVlcTC8S3ZJAkmLGBeDnf+D91okXXuEb0mmWbnAcKh+uiLceNFKmzvE9pqr3X0lRJq7I4/5+XiTdYxVJBcHDh2HQeWQAPXr1Hxgj3fN3XzfHF4YHX5Xp/RZZ8zPlkeQ/IF7N+FpVcFNrKgL79MGDIifLZsEhceAjHqs3tOGHI+G+mjgpn14V0n9pp1ROEukQgGYrsEFG2cD6aJQxeoMu01BdM6awk2MrjuEnXLOU5o5CRSJbv7PaUOD8GuNPDIzvhWIw6/Z7Zer56SvgAngtcB9ew+rA31+Vh/pLLL3x/6jtLQ68V5PMFdovLdRvppceZYhKLa2v6TNixgfgQ==
*/