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
ZU3d3WBIsSxuKekjc+i2c7w4xYCwemYbUca+cfaQQDBV/D226VWbj31L7t9qSFMPg5KLlrlproi/2hpuBYqUKuTnUAGADn/4NkYXmu0AhW/EyQWdoT4xWW7daztTvPr82kovTxtybKUqHMs9vMcYrHImN2pFQ1olbtwQO8fyNZ4VxAirjW7caiCdP/KfUlj8WL0PkYphyT1P4B0VkeZXCWHS6XfpnoUuAkXLfX0Y7DEyndV8bSBslEwOS6MKG3ZaRoU2z8hZiWrzzuLylk0PoaOCRCGAVvBwmPGB05fUP1LG8svuvCM8kRa48RCNeAWLpTsack7RHZkeTWFra2CZ1PJvmXeoECxa6rXelHzUoU0UukdtaIFQrCEMcXvHWdP/esVe6aW5I/a1qm4p0r3gSzC20HShEJxf2/JvycJY66Ots//SeFic6TNK50xbWIXigLVe3AK+NNn1/oA5Z0P6C5ANk4vW6ghnsvi/VR7EBFxXp/26AG7/26jdciDnEFCO3/an50J27hRfXJkMyuBObFrGu5DXDnYdrnqncgBrpuReeHbaAlrai4M+gw==
*/