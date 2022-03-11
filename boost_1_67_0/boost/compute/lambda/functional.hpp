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