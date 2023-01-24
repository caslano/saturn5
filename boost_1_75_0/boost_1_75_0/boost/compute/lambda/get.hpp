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
/+1JEfKOZwh/l+oS7ONg+lh3MqXp8+jOa6Q7OSNxsqM/pZDmhzubt4KZieg2fd6krBFSgXCJ+XSjBd52tKi+BrspWvvaX+ttVeVh1grVFvn2TlZ8VLyxT2rCgwP7MVnKRxv8VIFlQgdF/3lULfcZkSCmFuUj6Jorr+RblEeKXOlsMQ8jokrymuTrOH9MjGilh/fnMelw8NPUyYIFf/ter63lLZUW2PZKGfXskB/CrozKmUYXYvgb4bX0FtWHXParV16yMDKI6fPgsoYtPrLEwZ0/SscGezVYAfYgPPO03lgrcwVHVaef2CvpjbIQi3KMndtkam70BjFjPn1eI62PLCDm9nmawUdWW+QnC+U4Mr+5x/mIteIdWE0ri1gt4kEm0QxaN/oX2OFeWZbqyn9m+iBTcy4aE17aRfo+ehAG+WuZTsIiXVAb2Lv0ebPFjMBg0At+gVx3cLCY2URlITJ5IB6rw/lb5Qdwx/FV9v6tQvolZozkit+oLQ3SgsvheVFDK6Ux6+3k7Bjh0si3M8uGDutCtnu0dB4BHUhkvMBu7ecFPHxMAWJ/Y5o1OIVali59Hk+g6/Ok3FSm961k1ZhzHvlxcN7UfWATTp83ab2JxddN81dbVg2MPXxa4JHpJZ7dqxgSfdpIP1CPwNcLrBrMxvVmf6keVoqiC92P1VI+nsZvP3zDjd6XGxf+M/4p3IZ40kyRiRmq65V/QH9j
*/