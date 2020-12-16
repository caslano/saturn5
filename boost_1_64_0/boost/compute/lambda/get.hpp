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
OuIHewdwficDaO9EPqDr5bWs93PS356vLozwahq++8B4fed9U48cDOiIY4AcuQE9eCt6KKAHPoN3gO7pQJBL8eidRzCB/+q7xjCBrH8BQ/vcP0fu3WWIsV3in/lHMKFP59vvOsTAp9Me0IZ0V91+P+tjXPkP6tri0XS5/h4Yv4flXTc0767eH6df3B20fqz8b/o9QKd97GPuCQxpF+pgMPfSGNz50zq8/d6gjdahvQ/oc+vw8CPAhHXAvvPac+i5pyy4ypvytu06/vn2K67PcWSb2sMN9k6/WABmxNGoL+tPBz0c9YkA5vohYIhDjq+jf7wzMKHjTX/3fjdghh4YXlk3hjhIfALydg4xkOj1/dtJ3+esqvI4SeSt3/1NLg1yTF9duGB07iWFMTCReMGgIZEoiYlzlyGd2qg0HRgkG/XmOKU5dtxxPelwR98wl8/4/ZX3dL+bHG/eWelt97W/6+wf57Zsrj0/VvH9DM3myjZJrjRdF7rW09MHDui7Pv2Oo4a+MdEN1Zdnr58l4/Zkf+Shlr4968btDUNEDq7HeLSLkzVdCtryiyc4mm6OX5626eL3rk9x7/UMR7NNdQV6/cNOOvrmyQukzGf3v7sywXN02dA0wVTSG78vMPwO/cA84qANxh/ftxiY0THeF5pu83DoMbtwGXX9gvR+33iDzrnV1/VtytBsJBw7iDi/Z/jdFua3/VoOWlcgyrtagGYHHTFcnxW8BU2zuDTxn8+cfvHqGamzbcby9JlMZXF0xj0GJXmpvmzj/5g2uNfDLz7brwkLhK67xMdg7+Aws7oB4K2Lf6QYUhDxvXkaPRuoLJfmqduwBXRt+BJtA9r3xwWfBrGgHz6o6UHdD/i6E9BRgLfWtc8J8jc0opXyNh6wj6x1X7QyV/VLQhu1A7S/3cmnzSJ2IJ7NQZ+GsOqIE98+7j46TryW5nLxT6/oNK773ru5peDMkIo4yzMW1S/TuVpPZy8xnb+krYyBX/FVn69iSRHVTZMzwhH6orxrKYgdW6q2LETOnKO5FGMivTgvz6Z9LhXnlShuu8/hu+uPYcuEzKVMeMtM7uHpeFUWEZvbb0vJKp6Lpok469Pb0nMz82Vp1a6TtC3jGrICNgZ/vKcTvrqKVJW2JkH+kKnr57c7HvgV8yZVEc/Z2ZVTi4vazWeMWQ+tvz58oZ8/IrWpI6f9fvxOPp18gIHZOtRhMAdRDvYVdxlgWoOY7Nngd8BdPRzixmXe814Gh3nrg1DWb+9DMIFQ4PTJi+JCoSe7vfr9/hvu3N6uTvuh/fL0dPZiXxA9Loy/q0ir+nbVmKznn+/7x17OuXtKrIch/ZzRbuM94N5K9Os6sOhrg0esDZvrNsSMlon67d3Z4NFHKPAJXXl3GaH3nYh2HD/8X3HGZQPYJ909xA4riPPaPQjWbzTK+9UQM6jnM3AO+p9YU1fgr91nHB/WFzaiIxqPs9hyuMEBTtx/Hu7VO/7+48gDNW4WL2h5J9g7vvIhhGZZ4Qf0cE3DeWx+PdpHAjdWD/QxOwbcsLdcmRqLGI1zsa5c5FoK5lstVZFl6S0n33cTjsy3z9nxMq9yMQn6HJx393Jp7u2uT3cu9/GTF4O4DKKqmkowab2Sl3Shxil8OtV/X9xdm066PIuwgS7SthQq0t+trLzdtuSdPdgvT0hW8VQqqRrmxC9tTk0s3G2TZHxb3+senyWTsj/qyLoT4+vbfROP+t/EFd3Laaqk6L/u7kOzjdxjBC9rPSiNEKzK4lMrcSmj0zMG4Jd9/HJal3ldN3KGb+ryZWH5KcHndZu2eRszrhOArpx5WSs7fPeNPuvjG2Ycydu4jJnJ+qg5tM+aSVW+qPuA+r8=
*/