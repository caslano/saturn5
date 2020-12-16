
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/set_error.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_const_binds.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_binds.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/list/append.hpp>
#include <boost/preprocessor/list/size.hpp>

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT( \
        decl_traits) \
    BOOST_PP_IIF(BOOST_PP_GREATER(BOOST_PP_LIST_SIZE(BOOST_PP_LIST_APPEND( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                    decl_traits), \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES( \
                    decl_traits))), \
            1), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SET_ERROR \
    , /* do nothing (keeping previous error, if any) */ \
        decl_traits BOOST_PP_TUPLE_EAT(2) \
    )(decl_traits, /* trailing `EMPTY` because error might not be present */ \
            ERROR_cannot_bind_object_this_multiple_times BOOST_PP_EMPTY)

#endif // #include guard


/* this_count.hpp
Be70fBH0vHiOBYff1ZrfyTNia35rePuu1v0eCt858/ahMyO529z97vL2vcU91ip3f13w9v9PnH03fP181IsayAWQhyHvQX6HZNeiXkOqIAsg90CWQ9ohvjrw+CEFkEbIYsh7EMOPawKSB6mBNEFaIK2QNZD0o2Ic/3W1JUDq1wv/v76ivqy2QkwAMIxuzQEI8vy/VHj+/fncDAhtXG/Cb+Ff19SVVTATJRiSNyLzZcz+n6We6PsNRhR6ED54+wuemn/lTm3fLkh7ZNh+q86Ivj9E34/k3P+g7w+Jvt9A33/i1O8U/RxofT+Pc3+avp8q+v6u1YaYb8q6YQjJgcQp38Kp4XvFDGB2nBHx2cL5ucL6TLEcwmcJ9RmCzwza5wXtM8JKoPls0ApphwSfBRZovvtxAUS97+/Cez3u8/IeXzEp8v18BER3D/8ZksB7Ne7Rlvsy78mWe/Fyy/1Xf+9V77m836r3Wvs9Vr2/8n7qfP9cyHum5n4Zdq9U75NGoeWeyPshdGP3ptgW22JbbIttsS22xbbY9h/a1t/8/+ACj8G3/+6/+68aYMi1gad4wtfYfi/IP5nQ07DO8Rfv//766lnIR8m0mbXlgeq62ojrbPsmuJuLoVlnW+bxd4c8ZjvkcebhahYjrwWe3Y08TmAer40Lz+P7yGNOWB5R7pj2U10ZnP0D4mwU+czpRj7Nvp5mTthYwnf3xyC50Btryacs6zJQCOFM6zqvWZxrMV7EedAYhL9FkLkQ7RwA5jtNrmOOJEuqK7Scbpv+3sIfM6vFqqZ1FTpet9TPkHPUy0E/P7ysfDrmHwXKtPOVEUdypAqFZ/zIVMccmXfE8UFyTsefYj/OGAKeFMpWroF+BQS/iZAo5lSZ8zAy1LXQFd8gXNgKHyC8wwdZ6lqbNlvF+poir/iOMOKpZb8oSV/2ORPDyh7XUE11uSh6fdnvMNFd2edMjK7scyZGV/Y5E6Mve8TptOyfx3G17L+Z+N8p+6UTZdlb1ngu5Rrw97Ls74FcCJ3sPHvZ2xsoffkPE/HuEOV/KORMbfkzfXKnR4g0GrTlDj1ZJk3poXIsqajVlrmqe67Q9YuM6spa1T0vpCsKW7f+AHRl3Ts/pFsXwMftHdYegH7ndbW/oo/f0I9cV7OVONlKnIGoe0naute1emdyzEeI/QY5fwW+x77wvZwXf24wjD5GmPDbecEw+jKDc+LPF2HSZyK8v0Mdzu6kDr8kbAYPIt36HYOClPA14x9OB9rXCtI/q0RcVx3pyPLZV5RnMJ1gMiXTDCf+bJTr35j+z6L/cR7sq+ex2jw2VW9zjs1m/bNP5LXkkQ7rsGozkkFWtO1zF+3NsNnLc3COGdeb0nwT4FHo59tt1bZT7ss5X7H5ImkzknOwOb+bNuMc2Jfn6BYvOlr+s9M4UYUYX3suKe/Y+e1//NnvT//QLTc6Ljd6XvT/dU3laPnS0Y5vrmte9LpeO5m8PLzfOa/nC2wM4jBgD+CmQDNedifxNme8LRhvSxkP0km8bRgvh/G2ZbxWyFjGW8J4fSBPKbxisT4DeYpjyH/cDzgYeAB5wpOAw4C7k/83FrgTeYTjgHsCi6lfQv1S4HhgJfmFdeQXzmb686g/n/pnkl94OfmFV1HvYeo9Rj3ahWdZZ7sOoV2FtKuIdk2nXTNol592HUa7SmhXKe0qAxZTv4T6pcAK2gURdk2jXdNp1wza5add1bTrSNo1nXbNoF1+2tVsPvcA76VdvSAX0K5ZtGs27TqG9hxHexbQnhNoz4m05yTa00g7TgEeTv1y4BxgFXAueb2nAZt4/FzgfOA93Oe6x7j/O6977BOnwjHya9OAPmBvJX5OJ/EzGL8=
*/