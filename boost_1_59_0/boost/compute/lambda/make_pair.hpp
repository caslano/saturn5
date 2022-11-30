//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_LAMBDA_MAKE_PAIR_HPP
#define BOOST_COMPUTE_LAMBDA_MAKE_PAIR_HPP

#include <boost/compute/types/pair.hpp>

namespace boost {
namespace compute {
namespace lambda {
namespace detail {

// function wrapper for make_pair() in lambda expressions
struct make_pair_func
{
    template<class Expr, class Args>
    struct lambda_result
    {
        typedef typename proto::result_of::child_c<Expr, 1>::type Arg1;
        typedef typename proto::result_of::child_c<Expr, 2>::type Arg2;

        typedef typename lambda::result_of<Arg1, Args>::type T1;
        typedef typename lambda::result_of<Arg2, Args>::type T2;

        typedef std::pair<T1, T2> type;
    };

    template<class Context, class Arg1, class Arg2>
    static void apply(Context &ctx, const Arg1 &arg1, const Arg2 &arg2)
    {
        typedef typename lambda::result_of<Arg1, typename Context::args_tuple>::type T1;
        typedef typename lambda::result_of<Arg2, typename Context::args_tuple>::type T2;

        ctx.stream << "boost_make_pair(";
        ctx.stream << type_name<T1>() << ", ";
        proto::eval(arg1, ctx);
        ctx.stream << ", ";
        ctx.stream << type_name<T2>() << ", ";
        proto::eval(arg2, ctx);
        ctx.stream << ")";
    }
};

} // end detail namespace

// make_pair(first, second)
template<class Arg1, class Arg2>
inline typename proto::result_of::make_expr<
    proto::tag::function, detail::make_pair_func, const Arg1&, const Arg2&
>::type const
make_pair(const Arg1 &first, const Arg2 &second)
{
    return proto::make_expr<proto::tag::function>(
        detail::make_pair_func(), ::boost::ref(first), ::boost::ref(second)
    );
}

} // end lambda namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_LAMBDA_MAKE_PAIR_HPP

/* make_pair.hpp
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
*/