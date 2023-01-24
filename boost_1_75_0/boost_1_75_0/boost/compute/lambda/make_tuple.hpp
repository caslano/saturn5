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
ihTdQKNFFm2IlB/1Wi+66qWuushq11L1AkUXrfWDrHptt3XBta71tt3oVtf2p23saq+1bhetWnW1vc95v88z55whdu/+Pp/74/N5D+85mfOc9+/z/3le8UntYeoi6xQazbSqzDeSZf6+V3mx9chpL+tPtELw8YetEWc7I08RxsmDB1mqmyVGTwMknKpkecCehm4A2WCA70um7X54sKhJRhvEk/SW2yf+3tjT4NIgTyOqPujfnjW/RH47SJDw5i8okS+h/+vj9on+GtG1kFszAXwFmTjHej3E+w1V4Bd4A+VUV1nvh4wS8Mfw+09K/r4+lqhF4yX+wFkl+UrB08ASJWf7FRiP+NdzkaU7yRgDjCn0PF2mbwXWR/TxrGd418Ne5IeH9uTLsqnshUxZMoTeH/7twBI9CmfZdLMmyg8PsZniXwxvuDyvl0GWt7JKTuOB1gP4CCvBn/9PzstCRgA5RU7iEeENBRlRLP095d0HSyNOwxF4fQrxLrAAAnfmfPxujqlaUUk2COBs8BCIhfDnS8OZrOL/38/zK/wVvEElHw/i9+EPjBxXyF4SzH+FiL9elWcMAnlOLPP9yvMZg7UU/oxZluAQ9dobgIf8xznlnT8j+cKHVI8S/4icTxuaZ0kRtLKg8gF4sG9mFWyBRea+xXMgV+6v+GPmeeQQGY4ISg9emqWdfual4D0k+nb4+OdYX4rsIT2srwF9g1+N
*/