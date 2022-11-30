//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_LAMBDA_FUNCTIONAL_HPP
#define BOOST_COMPUTE_LAMBDA_FUNCTIONAL_HPP

#include <boost/tuple/tuple.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/proto/core.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <boost/compute/functional/get.hpp>
#include <boost/compute/lambda/result_of.hpp>
#include <boost/compute/lambda/placeholder.hpp>

#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/type_traits/scalar_type.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/make_vector_type.hpp>

namespace boost {
namespace compute {
namespace lambda {

namespace mpl = boost::mpl;
namespace proto = boost::proto;

// wraps a unary boolean function whose result type is an int_ when the argument
// type is a scalar, and intN_ if the argument type is a vector of size N
#define BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_UNARY_FUNCTION(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef typename proto::result_of::child_c<Expr, 1>::type Arg; \
                typedef typename ::boost::compute::lambda::result_of<Arg, Args>::type result_type; \
                typedef typename ::boost::compute::make_vector_type< \
                    ::boost::compute::int_, \
                    ::boost::compute::vector_size<result_type>::value \
                >::type type; \
            }; \
            \
            template<class Context, class Arg> \
            static void apply(Context &ctx, const Arg &arg) \
            { \
                ctx.stream << #name << "("; \
                proto::eval(arg, ctx); \
                ctx.stream << ")"; \
            } \
        }; \
    } \
    template<class Arg> \
    inline typename proto::result_of::make_expr< \
        proto::tag::function, BOOST_PP_CAT(detail::name, _func), const Arg& \
    >::type const \
    name(const Arg &arg) \
    { \
        return proto::make_expr<proto::tag::function>( \
            BOOST_PP_CAT(detail::name, _func)(), ::boost::ref(arg) \
        ); \
    }

// wraps a unary function whose return type is the same as the argument type
#define BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef typename proto::result_of::child_c<Expr, 1>::type Arg1; \
                typedef typename ::boost::compute::lambda::result_of<Arg1, Args>::type type; \
            }; \
            \
            template<class Context, class Arg> \
            static void apply(Context &ctx, const Arg &arg) \
            { \
                ctx.stream << #name << "("; \
                proto::eval(arg, ctx); \
                ctx.stream << ")"; \
            } \
        }; \
    } \
    template<class Arg> \
    inline typename proto::result_of::make_expr< \
        proto::tag::function, BOOST_PP_CAT(detail::name, _func), const Arg& \
    >::type const \
    name(const Arg &arg) \
    { \
        return proto::make_expr<proto::tag::function>( \
            BOOST_PP_CAT(detail::name, _func)(), ::boost::ref(arg) \
        ); \
    }

// wraps a unary function whose result type is the scalar type of the first argument
#define BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_ST(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef typename proto::result_of::child_c<Expr, 1>::type Arg; \
                typedef typename ::boost::compute::lambda::result_of<Arg, Args>::type result_type; \
                typedef typename ::boost::compute::scalar_type<result_type>::type type; \
            }; \
            \
            template<class Context, class Arg> \
            static void apply(Context &ctx, const Arg &arg) \
            { \
                ctx.stream << #name << "("; \
                proto::eval(arg, ctx); \
                ctx.stream << ")"; \
            } \
        }; \
    } \
    template<class Arg> \
    inline typename proto::result_of::make_expr< \
        proto::tag::function, BOOST_PP_CAT(detail::name, _func), const Arg& \
    >::type const \
    name(const Arg &arg) \
    { \
        return proto::make_expr<proto::tag::function>( \
            BOOST_PP_CAT(detail::name, _func)(), ::boost::ref(arg) \
        ); \
    }

// wraps a binary boolean function whose result type is an int_ when the first
// argument type is a scalar, and intN_ if the first argument type is a vector
// of size N
#define BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_BINARY_FUNCTION(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef typename proto::result_of::child_c<Expr, 1>::type Arg1; \
                typedef typename ::boost::compute::make_vector_type< \
                    ::boost::compute::int_, \
                    ::boost::compute::vector_size<Arg1>::value \
                >::type type; \
            }; \
            \
            template<class Context, class Arg1, class Arg2> \
            static void apply(Context &ctx, const Arg1 &arg1, const Arg2 &arg2) \
            { \
                ctx.stream << #name << "("; \
                proto::eval(arg1, ctx); \
                ctx.stream << ", "; \
                proto::eval(arg2, ctx); \
                ctx.stream << ")"; \
            } \
        }; \
    } \
    template<class Arg1, class Arg2> \
    inline typename proto::result_of::make_expr< \
        proto::tag::function, BOOST_PP_CAT(detail::name, _func), const Arg1&, const Arg2& \
    >::type const \
    name(const Arg1 &arg1, const Arg2 &arg2) \
    { \
        return proto::make_expr<proto::tag::function>( \
            BOOST_PP_CAT(detail::name, _func)(), ::boost::ref(arg1), ::boost::ref(arg2) \
        ); \
    }

// wraps a binary function whose result type is the type of the first argument
#define BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef typename proto::result_of::child_c<Expr, 1>::type Arg1; \
                typedef typename ::boost::compute::lambda::result_of<Arg1, Args>::type type; \
            }; \
            \
            template<class Context, class Arg1, class Arg2> \
            static void apply(Context &ctx, const Arg1 &arg1, const Arg2 &arg2) \
            { \
                ctx.stream << #name << "("; \
                proto::eval(arg1, ctx); \
                ctx.stream << ", "; \
                proto::eval(arg2, ctx); \
                ctx.stream << ")"; \
            } \
        }; \
    } \
    template<class Arg1, class Arg2> \
    inline typename proto::result_of::make_expr< \
        proto::tag::function, BOOST_PP_CAT(detail::name, _func), const Arg1&, const Arg2& \
    >::type const \
    name(const Arg1 &arg1, const Arg2 &arg2) \
    { \
        return proto::make_expr<proto::tag::function>( \
            BOOST_PP_CAT(detail::name, _func)(), ::boost::ref(arg1), ::boost::ref(arg2) \
        ); \
    }

// wraps a binary function whose result type is the type of the second argument
#define BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION_2(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef typename proto::result_of::child_c<Expr, 2>::type Arg2; \
                typedef typename ::boost::compute::lambda::result_of<Arg2, Args>::type type; \
            }; \
            \
            template<class Context, class Arg1, class Arg2> \
            static void apply(Context &ctx, const Arg1 &arg1, const Arg2 &arg2) \
            { \
                ctx.stream << #name << "("; \
                proto::eval(arg1, ctx); \
                ctx.stream << ", "; \
                proto::eval(arg2, ctx); \
                ctx.stream << ")"; \
            } \
        }; \
    } \
    template<class Arg1, class Arg2> \
    inline typename proto::result_of::make_expr< \
        proto::tag::function, BOOST_PP_CAT(detail::name, _func), const Arg1&, const Arg2& \
    >::type const \
    name(const Arg1 &arg1, const Arg2 &arg2) \
    { \
        return proto::make_expr<proto::tag::function>( \
            BOOST_PP_CAT(detail::name, _func)(), ::boost::ref(arg1), ::boost::ref(arg2) \
        ); \
    }

// wraps a binary function who's result type is the scalar type of the first argument
#define BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION_ST(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef typename proto::result_of::child_c<Expr, 1>::type Arg1; \
                typedef typename ::boost::compute::lambda::result_of<Arg1, Args>::type result_type; \
                typedef typename ::boost::compute::scalar_type<result_type>::type type; \
            }; \
            \
            template<class Context, class Arg1, class Arg2> \
            static void apply(Context &ctx, const Arg1 &arg1, const Arg2 &arg2) \
            { \
                ctx.stream << #name << "("; \
                proto::eval(arg1, ctx); \
                ctx.stream << ", "; \
                proto::eval(arg2, ctx); \
                ctx.stream << ")"; \
            } \
        }; \
    } \
    template<class Arg1, class Arg2> \
    inline typename proto::result_of::make_expr< \
        proto::tag::function, BOOST_PP_CAT(detail::name, _func), const Arg1&, const Arg2& \
    >::type const \
    name(const Arg1 &arg1, const Arg2 &arg2) \
    { \
        return proto::make_expr<proto::tag::function>( \
            BOOST_PP_CAT(detail::name, _func)(), ::boost::ref(arg1), ::boost::ref(arg2) \
        ); \
    }

// wraps a binary function whose result type is the type of the first argument
// and the second argument is a pointer
#define BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION_PTR(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef typename proto::result_of::child_c<Expr, 1>::type Arg1; \
                typedef typename ::boost::compute::lambda::result_of<Arg1, Args>::type type; \
            }; \
            \
            template<class Context, class Arg1, class Arg2> \
            static void apply(Context &ctx, const Arg1 &arg1, const Arg2 &arg2) \
            { \
                ctx.stream << #name << "("; \
                proto::eval(arg1, ctx); \
                ctx.stream << ", &"; \
                proto::eval(arg2, ctx); \
                ctx.stream << ")"; \
            } \
        }; \
    } \
    template<class Arg1, class Arg2> \
    inline typename proto::result_of::make_expr< \
        proto::tag::function, BOOST_PP_CAT(detail::name, _func), const Arg1&, const Arg2& \
    >::type const \
    name(const Arg1 &arg1, const Arg2 &arg2) \
    { \
        return proto::make_expr<proto::tag::function>( \
            BOOST_PP_CAT(detail::name, _func)(), ::boost::ref(arg1), ::boost::ref(arg2) \
        ); \
    }

// wraps a ternary function
#define BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef typename proto::result_of::child_c<Expr, 1>::type Arg1; \
                typedef typename ::boost::compute::lambda::result_of<Arg1, Args>::type type; \
            }; \
            \
            template<class Context, class Arg1, class Arg2, class Arg3> \
            static void apply(Context &ctx, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3) \
            { \
                ctx.stream << #name << "("; \
                proto::eval(arg1, ctx); \
                ctx.stream << ", "; \
                proto::eval(arg2, ctx); \
                ctx.stream << ", "; \
                proto::eval(arg3, ctx); \
                ctx.stream << ")"; \
            } \
        }; \
    } \
    template<class Arg1, class Arg2, class Arg3> \
    inline typename proto::result_of::make_expr< \
        proto::tag::function, BOOST_PP_CAT(detail::name, _func), const Arg1&, const Arg2&, const Arg3& \
    >::type const \
    name(const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3) \
    { \
        return proto::make_expr<proto::tag::function>( \
            BOOST_PP_CAT(detail::name, _func)(), ::boost::ref(arg1), ::boost::ref(arg2), ::boost::ref(arg3) \
        ); \
    }

// wraps a ternary function whose result type is the type of the third argument
#define BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION_3(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef typename proto::result_of::child_c<Expr, 3>::type Arg3; \
                typedef typename ::boost::compute::lambda::result_of<Arg3, Args>::type type; \
            }; \
            \
            template<class Context, class Arg1, class Arg2, class Arg3> \
            static void apply(Context &ctx, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3) \
            { \
                ctx.stream << #name << "("; \
                proto::eval(arg1, ctx); \
                ctx.stream << ", "; \
                proto::eval(arg2, ctx); \
                ctx.stream << ", "; \
                proto::eval(arg3, ctx); \
                ctx.stream << ")"; \
            } \
        }; \
    } \
    template<class Arg1, class Arg2, class Arg3> \
    inline typename proto::result_of::make_expr< \
        proto::tag::function, BOOST_PP_CAT(detail::name, _func), const Arg1&, const Arg2&, const Arg3& \
    >::type const \
    name(const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3) \
    { \
        return proto::make_expr<proto::tag::function>( \
            BOOST_PP_CAT(detail::name, _func)(), ::boost::ref(arg1), ::boost::ref(arg2), ::boost::ref(arg3) \
        ); \
    }

// wraps a ternary function whose result type is the type of the first argument
// and the third argument of the function is a pointer
#define BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION_PTR(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef typename proto::result_of::child_c<Expr, 3>::type Arg3; \
                typedef typename ::boost::compute::lambda::result_of<Arg3, Args>::type type; \
            }; \
            \
            template<class Context, class Arg1, class Arg2, class Arg3> \
            static void apply(Context &ctx, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3) \
            { \
                ctx.stream << #name << "("; \
                proto::eval(arg1, ctx); \
                ctx.stream << ", "; \
                proto::eval(arg2, ctx); \
                ctx.stream << ", &"; \
                proto::eval(arg3, ctx); \
                ctx.stream << ")"; \
            } \
        }; \
    } \
    template<class Arg1, class Arg2, class Arg3> \
    inline typename proto::result_of::make_expr< \
        proto::tag::function, BOOST_PP_CAT(detail::name, _func), const Arg1&, const Arg2&, const Arg3& \
    >::type const \
    name(const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3) \
    { \
        return proto::make_expr<proto::tag::function>( \
            BOOST_PP_CAT(detail::name, _func)(), ::boost::ref(arg1), ::boost::ref(arg2), ::boost::ref(arg3) \
        ); \
    }

// Common Built-In Functions
BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(clamp)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(degrees)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(min)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(max)
BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(mix)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(radians)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(sign)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION_2(step)
BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION_3(smoothstep)

// Geometric Built-In Functions
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(cross)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION_ST(dot)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION_ST(distance)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_ST(length)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(normalize)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION_ST(fast_distance)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_ST(fast_length)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(fast_normalize)

// Integer Built-In Functions
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(abs)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(abs_diff)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(add_sat)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(hadd)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(rhadd)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(clz)
#ifdef BOOST_COMPUTE_CL_VERSION_2_0
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(ctz)
#endif
// clamp() (since 1.1) already defined in common
BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(mad_hi)
BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(mad24)
BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(mad_sat)
// max() and min() functions are defined in common
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(mul_hi)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(mul24)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(rotate)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(sub_sat)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(upsample)
#ifdef BOOST_COMPUTE_CL_VERSION_1_2
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(popcount)
#endif

// Math Built-In Functions
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(acos)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(acosh)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(acospi)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(asin)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(asinh)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(asinpi)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(atan)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(atan2)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(atanh)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(atanpi)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(atan2pi)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(cbrt)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(ceil)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(copysign)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(cos)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(cosh)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(cospi)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(erfc)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(erf)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(exp)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(exp2)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(exp10)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(expm1)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(fabs)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(fdim)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(floor)
BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(fma)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(fmax)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(fmin)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(fmod)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION_PTR(fract)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION_PTR(frexp)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(hypot)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_BINARY_FUNCTION(ilogb) // ilogb returns intN_
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(ldexp)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(lgamma)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION_PTR(lgamma_r)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(log)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(log2)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(log10)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(log1p)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(logb)
BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(mad)
#ifdef BOOST_COMPUTE_CL_VERSION_1_1
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(maxmag)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(minmag)
#endif
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION_PTR(modf)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(nan)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(nextafter)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(pow)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(pown)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(powr)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(remainder)
BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION_PTR(remquo)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(rint)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(rootn)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(round)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(rsqrt)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(sin)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(sincos)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(sinh)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(sinpi)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(sqrt)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(tan)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(tanh)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(tanpi)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(tgamma)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(trunc)

// Native Math Built-In Functions
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(native_cos)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(native_divide)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(native_exp)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(native_exp2)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(native_exp10)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(native_log)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(native_log2)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(native_log10)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(native_powr)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(native_recip)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(native_rsqrt)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(native_sin)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(native_sqrt)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(native_tan)

// Half Math Built-In Functions
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(half_cos)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(half_divide)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(half_exp)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(half_exp2)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(half_exp10)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(half_log)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(half_log2)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(half_log10)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(half_powr)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(half_recip)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(half_rsqrt)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(half_sin)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(half_sqrt)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(half_tan)

// Relational Built-In Functions
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_BINARY_FUNCTION(isequal)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_BINARY_FUNCTION(isnotequal)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_BINARY_FUNCTION(isgreater)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_BINARY_FUNCTION(isgreaterequal)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_BINARY_FUNCTION(isless)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_BINARY_FUNCTION(islessequal)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_BINARY_FUNCTION(islessgreater)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_UNARY_FUNCTION(isfinite)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_UNARY_FUNCTION(isinf)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_UNARY_FUNCTION(isnan)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_UNARY_FUNCTION(isnormal)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_BINARY_FUNCTION(isordered)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_BINARY_FUNCTION(isunordered)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_UNARY_FUNCTION(singbit)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_UNARY_FUNCTION(all)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_UNARY_FUNCTION(any)
BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(bitselect)
BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(select)

} // end lambda namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_LAMBDA_FUNCTIONAL_HPP

/* functional.hpp
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
*/