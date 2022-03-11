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