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