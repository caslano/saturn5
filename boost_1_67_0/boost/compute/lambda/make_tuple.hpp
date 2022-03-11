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
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
*/