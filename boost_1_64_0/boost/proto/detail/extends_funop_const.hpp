#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        BOOST_PROTO_EXTENDS_FUNCTION_()
        BOOST_PROTO_DEFINE_FUN_OP_VARIADIC_IMPL_(BOOST_PROTO_CONST)
    #else
        #include <boost/proto/detail/preprocessed/extends_funop_const.hpp>
    #endif

#else

    #define BOOST_PP_LOCAL_MACRO(N)                                                                 \
        BOOST_PROTO_DEFINE_FUN_OP_CONST(1, N, ~)                                                    \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/extends_funop_const.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file extends_funop_const.hpp
    /// Definitions for extends\<\>::operator()
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    BOOST_PROTO_EXTENDS_FUNCTION_()

    #define BOOST_PP_LOCAL_LIMITS                                                                   \
        (0, BOOST_PP_DEC(BOOST_PROTO_MAX_FUNCTION_CALL_ARITY))
    #include BOOST_PP_LOCAL_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#endif

/* extends_funop_const.hpp
EK3K5aebKY2cQvB+WuKZXhpe6TY/Z8VJAhvOhbP4dxTvUb0HO/naMXeElhVzmSfngTge2YUYYetgDNGRT9Bhfawn//aTRjyBqTwXsoU3jMGtYWZnGv0Rp/tXovAK1PaiJW80dyh0079PfvrZNX9z++wYjiAsf+G1eIYMMFCO58fLlsQTGB5PZgZkO0jr79fimVXQmmD5ykuKtqCKcYLnytcL/NGBRuzmbrrk/CE17mR/jeMy9m9fK9XH6U62EKguSLsTg3LF6bzy3BhzldqBPed4FHtA9X1l+6V0YjOQxGC3hXT2Sv9OW3MhTNMsxjAYRpiGMqD5gV91PIoTZdtGd5ViG8mkJUVUPo3xFsGc/vk7KaL5EIs4x9IdjRG8OErXY1yQa4Y1iuwjDfg9rNk/75VnT9N7p7qK/8c4D2h7QvbaV2mbLvfBOWutZ7WDV7pJdgyY5P1yPLIbNN4KKxyLNQ2qlRh8IStVUJHW9mO7tp9TWo+QnQ2VD5ZF5OOsc8i6lQJWCSdF6B3AvmAB9g8l3SCt7poOYK8u6DL+djx6c5dS+14OMnHuV0RH0UqkCHDQu0F2Gfy/UOa87QtKuaVuRed1vagbiKT/O4kzBlomMiej9EXHmtap1gie6QPdR0Wa/nipUBiLUfl1DfCGSPdlI7pd1VmtG7FI9wXn0X3BMrpfHNE1oQtaG7dI9+p5dK9Sus/FOaR0m8A62Xd11bqlsmw5Jq2d/btalLxgoWSwL907KfW2UjXCdDL8d/c+jPjs0tjOeQsLehXYkFlv3RJ+5NzNfALy3ccij/DNWwEfAHWUAh7c+5fvjnGbIcVf7W092Kr88DpRDgG8UWyfg+vNvxNBK+vBn1/aMIo+bpteOKYPqakKnGlyLRmprIYndws2BI8o6PQM7LXiJumASfhvCOXYDiM60rZWcqOpQAYDiPIRjd9J+fxPXVvETEs5+8BNncg+nxnBXCUwKJN8brjLMY3XBcT/SnH3FgLHfs6Pd058IGT8cz7bwzIuuvS2Na2bM/4RoWSEtxDvtkeln7DmsmuqhoX56HTUmDDiIa91j6OSd29c3WkbJPLetM6xv8xnjkbvaVYr2/X/5ftcXIfEPu/Oc53Gp285X/M0NhbGAooD+RAoS0s3n0N7u6O4glUVLNdLQ8/Mva2VSz/BQGL/NH1YiAP0poKuYSHoVjShXdwTNJhkaSv9yd2R71ovG611DfvhPxKJ66dG36SCjmauFUK2WqbYI7gfWnqeIA1m8H6mNHjLQuVN3fQD4z9O7z8iC7bbSOuGV0c8i651y9sGPUSQs4cYsec07N4XUWeCtFDWFVzXBs3SSrHivsifUpwLSqimN23NLo5jXTIKJwRTVSuDbfTymJOr89fNi3MpaKjvtKivtnXLQ9+w1XGMmBeP6jOey6qy1b+vbxXrG2yxKB0emJWch8aJuU8VCU24s4TvZSs59u383GqT3QHD7w/N38FVYYWhzPII/H6uyLJyFWk8GmGTDifrbxiRi9okWOQyRc5KLEMZp6d4L84y0POxfC3jLi9/KraHikixHOt+NpYP4dsOEXeblqGDEMF9TT7/QQqMcPHYwbP9PUvP9hYb+OKcQ3Y5HPbkxQp542INVazWCgKLskFTD9FE5+Z9V5JRYIy+Prf9IjmU90p/xlr61gRdlTJTe67IdEp8BL5DaXHBvGyU8p2Zy0zw79WjZNt5hLLTZG4PDeITPTtuu1/aLCqlnHd2mZ5KtMs4JELrEQWtwFTTtk4IQfNSHSNzgO5U+Dw9ig+2QWnxhskmSBXa/0BqAl4mu7Cvqa3JywpaNashNK7jnhJ7wTJi2DQ20PpY0UfHnHJG8tCfTwudHhY=
*/