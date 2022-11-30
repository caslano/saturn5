//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_LAMBDA_GET_HPP
#define BOOST_COMPUTE_LAMBDA_GET_HPP

#include <boost/preprocessor/repetition.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/functional/get.hpp>
#include <boost/compute/lambda/placeholder.hpp>

namespace boost {
namespace compute {
namespace lambda {
namespace detail {

// function wrapper for get<N>() in lambda expressions
template<size_t N>
struct get_func
{
    template<class Expr, class Args>
    struct lambda_result
    {
        typedef typename proto::result_of::child_c<Expr, 1>::type Arg;
        typedef typename ::boost::compute::lambda::result_of<Arg, Args>::type T;
        typedef typename ::boost::compute::detail::get_result_type<N, T>::type type;
    };

    template<class Context, class Arg>
    struct make_get_result_type
    {
        typedef typename boost::remove_cv<
            typename boost::compute::lambda::result_of<
                Arg, typename Context::args_tuple
            >::type
        >::type type;
    };

    // returns the suffix string for get<N>() in lambda expressions
    // (e.g. ".x" for get<0>() with float4)
    template<class T>
    struct make_get_suffix
    {
        static std::string value()
        {
            BOOST_STATIC_ASSERT(N < 16);

            std::stringstream stream;

            if(N < 10){
                stream << ".s" << uint_(N);
            }
            else if(N < 16){
                stream << ".s" << char('a' + (N - 10));
            }

            return stream.str();
        }
    };

    // get<N>() specialization for std::pair<T1, T2>
    template<class T1, class T2>
    struct make_get_suffix<std::pair<T1, T2> >
    {
        static std::string value()
        {
            BOOST_STATIC_ASSERT(N < 2);

            if(N == 0){
                return ".first";
            }
            else {
                return ".second";
            }
        };
    };

    // get<N>() specialization for boost::tuple<T...>
    #define BOOST_COMPUTE_LAMBDA_GET_MAKE_TUPLE_SUFFIX(z, n, unused) \
    template<BOOST_PP_ENUM_PARAMS(n, class T)> \
    struct make_get_suffix<boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> > \
    { \
        static std::string value() \
        { \
            BOOST_STATIC_ASSERT(N < n); \
            return ".v" + boost::lexical_cast<std::string>(N); \
        } \
    };

    BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_LAMBDA_GET_MAKE_TUPLE_SUFFIX, ~)

    #undef BOOST_COMPUTE_LAMBDA_GET_MAKE_TUPLE_SUFFIX

    template<class Context, class Arg>
    static void dispatch_apply_terminal(Context &ctx, const Arg &arg)
    {
        typedef typename make_get_result_type<Context, Arg>::type T;

        proto::eval(arg, ctx);
        ctx.stream << make_get_suffix<T>::value();
    }

    template<class Context, int I>
    static void dispatch_apply_terminal(Context &ctx, placeholder<I>)
    {
        ctx.stream << ::boost::compute::get<N>()(::boost::get<I>(ctx.args));
    }

    template<class Context, class Arg>
    static void dispatch_apply(Context &ctx, const Arg &arg, proto::tag::terminal)
    {
        dispatch_apply_terminal(ctx, proto::value(arg));
    }

    template<class Context, class Arg>
    static void apply(Context &ctx, const Arg &arg)
    {
        dispatch_apply(ctx, arg, typename proto::tag_of<Arg>::type());
    }
};

} // end detail namespace

// get<N>()
template<size_t N, class Arg>
inline typename proto::result_of::make_expr<
    proto::tag::function, detail::get_func<N>, const Arg&
>::type const
get(const Arg &arg)
{
    return proto::make_expr<proto::tag::function>(
        detail::get_func<N>(), ::boost::ref(arg)
    );
}

} // end lambda namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_LAMBDA_GET_HPP

/* get.hpp
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
*/