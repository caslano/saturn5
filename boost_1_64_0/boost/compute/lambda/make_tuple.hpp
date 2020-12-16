//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_HPP
#define BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_HPP

#include <boost/preprocessor/repetition.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/types/tuple.hpp>

namespace boost {
namespace compute {
namespace lambda {
namespace detail {

// function wrapper for make_tuple() in lambda expressions
struct make_tuple_func
{
    template<class Expr, class Args, int N>
    struct make_tuple_result_type;

    #define BOOST_COMPUTE_MAKE_TUPLE_RESULT_GET_ARG(z, n, unused) \
        typedef typename proto::result_of::child_c<Expr, BOOST_PP_INC(n)>::type BOOST_PP_CAT(Arg, n);

    #define BOOST_COMPUTE_MAKE_TUPLE_RESULT_GET_ARG_TYPE(z, n, unused) \
        typedef typename lambda::result_of<BOOST_PP_CAT(Arg, n), Args>::type BOOST_PP_CAT(T, n);

    #define BOOST_COMPUTE_MAKE_TUPLE_RESULT_TYPE(z, n, unused) \
        template<class Expr, class Args> \
        struct make_tuple_result_type<Expr, Args, n> \
        { \
            BOOST_PP_REPEAT(n, BOOST_COMPUTE_MAKE_TUPLE_RESULT_GET_ARG, ~) \
            BOOST_PP_REPEAT(n, BOOST_COMPUTE_MAKE_TUPLE_RESULT_GET_ARG_TYPE, ~) \
            typedef boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> type; \
        };

    BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_MAKE_TUPLE_RESULT_TYPE, ~)

    #undef BOOST_COMPUTE_MAKE_TUPLE_RESULT_GET_ARG
    #undef BOOST_COMPUTE_MAKE_TUPLE_RESULT_GET_ARG_TYPE
    #undef BOOST_COMPUTE_MAKE_TUPLE_RESULT_TYPE

    template<class Expr, class Args>
    struct lambda_result
    {
        typedef typename make_tuple_result_type<
            Expr, Args, proto::arity_of<Expr>::value - 1
        >::type type;
    };

    #define BOOST_COMPUTE_MAKE_TUPLE_GET_ARG_TYPE(z, n, unused) \
        typedef typename lambda::result_of< \
            BOOST_PP_CAT(Arg, n), typename Context::args_tuple \
        >::type BOOST_PP_CAT(T, n);

    #define BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_APPLY_ARG(z, n, unused) \
        BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(const Arg, n) BOOST_PP_CAT(&arg, n)

    #define BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_APPLY_EVAL_ARG(z, n, unused) \
        BOOST_PP_EXPR_IF(n, ctx.stream << ", ";) proto::eval(BOOST_PP_CAT(arg, n), ctx);

    #define BOOST_COMPUTE_MAKE_TUPLE_APPLY(z, n, unused) \
    template<class Context, BOOST_PP_ENUM_PARAMS(n, class Arg)> \
    static void apply(Context &ctx, BOOST_PP_REPEAT(n, BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_APPLY_ARG, ~)) \
    { \
        BOOST_PP_REPEAT(n, BOOST_COMPUTE_MAKE_TUPLE_GET_ARG_TYPE, ~) \
        typedef typename boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> tuple_type; \
        ctx.stream.template inject_type<tuple_type>(); \
        ctx.stream << "((" << type_name<tuple_type>() << "){"; \
        BOOST_PP_REPEAT(n, BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_APPLY_EVAL_ARG, ~) \
        ctx.stream << "})"; \
    }

    BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_MAKE_TUPLE_APPLY, ~)

    #undef BOOST_COMPUTE_MAKE_TUPLE_GET_ARG_TYPE
    #undef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_APPLY_ARG
    #undef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_APPLY_EVAL_ARG
    #undef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_APPLY
};

} // end detail namespace

#define BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_ARG(z, n, unused) \
    BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(const Arg, n) BOOST_PP_CAT(&arg, n)

#define BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_ARG_TYPE(z, n, unused) \
    BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(const Arg, n) &

#define BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_REF_ARG(z, n, unused) \
    BOOST_PP_COMMA_IF(n) ::boost::ref(BOOST_PP_CAT(arg, n))

#define BOOST_COMPUTE_LAMBDA_MAKE_TUPLE(z, n, unused) \
template<BOOST_PP_ENUM_PARAMS(n, class Arg)> \
inline typename proto::result_of::make_expr< \
    proto::tag::function, \
    detail::make_tuple_func, \
    BOOST_PP_REPEAT(n, BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_ARG_TYPE, ~) \
>::type \
make_tuple(BOOST_PP_REPEAT(n, BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_ARG, ~)) \
{ \
    return proto::make_expr<proto::tag::function>( \
        detail::make_tuple_func(), \
        BOOST_PP_REPEAT(n, BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_REF_ARG, ~) \
    ); \
}

BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_LAMBDA_MAKE_TUPLE, ~)

#undef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_ARG
#undef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_ARG_TYPE
#undef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_REF_ARG
#undef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE

} // end lambda namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_HPP

/* make_tuple.hpp
eZrzOE0UM+O2ZIcwTGAVwbfP521ZWiZNLfIMOfg2p+61v+NTnT3kRBCTQ2RNHuXSxRowWY50pWfhBnZmE0Dnu+rXEt59f0k5JZOZzLJYlGyCiwnKv2S2JfRN93VSRsFkndWpaHJShrVGD4o4gLsjdYCeXdKURyYv7ewL4+7rtnQOJqovN08EOXRVoWrznnzzsu6C6eZ0FlTC/04hb9fhk7TtbRtnGS8405U0VQTb0vB1PnSOlBGzipuoJm2MMvyLRveuH/Yzn7dleVzVtf7WsUs6HqrtNH0ktxMljJPj89WsyDNhbhmZjpnR8cAjGHPe52kYz41pPS9nPEE0W9hRKU9cJkWZ5u2MxxznaR4s6PTbKZ8oeCkibmSZ26U13RF2sQAfcqCdpHoUJ7lJpceZlqXzl13SU+E1LoQGZnO4Ln77ZBi7SMVC8pxpHxJE28CIBOcaWu8mMn6puTCsPhNyhnXfuRs+33JaRbq5ZczsMoM556+lZPxs+sNKJhkzpQe6ypCf7llUz9K6LGJlc6PZWaYHD/qCPkGc4YOkT6Txqih5PpZXLdyrHCVyU1bpL3+VyJTy9gkwHT/GdJnwl1qJyqwVeeHzu1XBBFDYvuxFM+7yqh3bsrEYZEWyps3oBzX9XZdBJ8Ec8A5L//m0Fz9BAxE8Afl4n0b9mKtIFblM3NXJi3mZxeQuA7G/nx6c96JGiLRhQxYvhje9N+FNFIk2k+66ZWDDhqyW2s2LpBJ5bnwG4iHbI7W1963ah6qWZ1bjqJXnzF34uVVzB17H0nunrv98yrOLr0aB7xl8c0PcOd1E3ToPUx4MMc447udxOkQwMm4L31SNsj5z5xCHagHzgLsGGFSpt+uywwQz3h3+m667Ae9lBtN0+A0SOgTCb/IehH56Xn8u3ivEwV8LmI17hxjI69/M3cfHIBMR6N8/MqRrSwhsjn++L+g49AR1RtvO3n8MS/oAb7FDHHTBz9n2wBA30AeU+ZcHjWFRTeBeeXQEhyr2Pg7veEiIm6sbGI9fPHTAA/3AWvOwEAPhaPexRwwwp+f1+bseOYaFrgD3s0eN4SC7r9+xAQ46g1iijwkx0BtgzjzWYHDIwomTrBmPCzH7AGFcQ0zQEfAPfsIAh8ZhzXjiADOQt/ckggkVDjjx5BA3Zx4/NcShWliDDjyNYOYpGubs7ykeSoY16OmU7gSi7hefQemhcmE+Hw9wUCy00Z2rBjjIhF5RDJSKxDU9STFQKq9O73jWOOactgX7uFcuEhy5rfFxT1sa4qCHfjzqMdycfrv5nFHsYByuLY/iBrLftRLghgshsBvPHcWOr9fPH8OimlgLn/SCEDd/MUQOzBeGPFgMgbk+xEA4YnufCjHDxRD9FA2x0Nmg7Rt8DDsco8V4gPN1F7hDYgwH/UUdfzsfBx3GG29psDuzyAB71D/+uiK0yXrgw/SvhNCt7zxyMD+V5vPICq5Snlu/TP2nmOoXkC/e3YLHgWYB72Hqt1yVccUbIQlvfeXSKO9Rn7dmGc+bSoqS8J7R+Z58ZuRL9XnjkjVlxHkS33JO423tkeSfec7TdmRpk9V1rvq6ZDbniF+VRdhXfN7FWsm8sC8+ng1my2Lj/vxdr8VNvNqaKM8vyWJZNrF947bwDPe79UER9rf7d781tdTqYH+7F3Cny0zo8dW//aMr87R8SVNI4UzqVt5fIS+rk1IXs9ra3+/qy1s9E5158aot/yHd7waZCaNf2Pd/0vrRmZ47d3n78jqJ5fG4O2m68UWjdOjf4YMz+u457SWij58+79sPgWZ419av7G2/+tU9/QF3IXStFZsbPv+Nu4I+k23tgz1d3A10UrfHILYRoWsfl9frB7w=
*/