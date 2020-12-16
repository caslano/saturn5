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
X6R7gbxpqrTmJROyOLWSGYMDksZHyN3wrCDPfVFUUcQbZjaaI5t3vLV4WhD3l4uorGOllfqllG3ptHzRixFOBf40hF+yNsmUMo8C5rMipsj1JcobN1Wk4mJm07Bp2YUO9+viWSzBugE7z9abfTtP2VS6n4QupnJbEMTYWAriP2RKSqGY3N+ZrNtXAehPoTp7o88jWmaUgxcqY3ouTXbNF3jmZT7ZMMzGey7O2lS/8tOJtU0cE+RR88dF5ayOGqmiZk45M3dbk0lZZxDQ/6H/LWcHoH/+urOYprHgolRM192EZK1PPXvWhq0O3/r4Z1WyTaqCt8DP0F78lDMEL7NEq3hbzfDHA7vIWR9bsazMKyWkBq90/+MyyequX/eg2z7fs+ukzKpWFR6bbsUgHpTPs1JolrIoUo9H1sIJIuefz9I1FevtPQ8Smstc7L2/vQuh4yPqY47ey2Fmub76Rdv3wb6vwxj7wDltRt26sGYyXSIX9P17+mtnoUdBO/Yg0LbdtQe+f698mKNZw2qve26bhDLOP7LD7egVxzrJ4k5451GONusa8Lzn0fgdLcLb7Cc7musy+GY/lfxO7jw+cdzQ4EeO39sT+nd3B6W/Ifh941nmd+Nrr2eS15eHlszvw3Nn3enjs+hZrlYya/P8lvMfdt8xxODy17Xlpq5FJjnvVtPTZRevCDYvsg5Gei3jZWLeQp5ejcaOfnhH83TKl5dFLYo8ZeK/8533+Vq9pqWVTGXGZDzGZfUW8+IzdqxMU6zGOA3w/KLvNIaBfgN3z3sMcGSy4N7rPgYHHcDd3uOO6N/h7+HHf3D3mAP60Bdl8b4hhvrVXSd0xLSFjE/cL6TDtw4204/4ff0cKY2bQFUyd1lLvzVXfWzFZNO0RZ0mzLt1tgx++ddo+bmIaq5K5i59g5xcDosY+UVWpG1Zs+C617HdCf4DAV/Vtlmatg3l2wUf3ok9I8jboqKyTEXN5hwXwnfUxwh/ymSbq6QtCzZ+jBj0zfN9/merKpWpSAs2uyyeoXfxffSxJWtVKes0yx24rx3ePPv4lrVpkihZCEZvm2nsqR0qI+dFE9eRYv2Jhsq4w8c3rEkzWaVNAbzXavC86xlUh1qe5CLlzLtxH/gbfITKSYRsi7ItHA9pCvr2qs/znFjJkscqY+4CnLbjGq1TleZ1G2etA4/r9XVSfhKnUa5EytziTsu/QetfN6nKm7Zm5AsevLG/6XgQV68p6iovFWUajvvhZ1L/lqhKhUoEo198us895njgN16JVtVJETD5/cDg40J4OUvbKIrbnIU7A8fI4OPi8zUsz2q99mSOb5uMKe5EzzsevM9LqzwRac3mbBfCOH13+PzLehkSqeCt5cYImKpBV318zdJYz6IsUmDwOuRc15cfIXVMNLZJlHngO3q9R88r14L2ZTKNsqyJ2Jxrv3A9uhHwN7wSdZK3bM51YOjbcuA41TmZJ1WdRCX4Ue/g3fbx4KxT6oWgTBLwDWVGyFV4nOYqzAuZ11nDyO3+jOmNyB/n86xUTZSlUV0wbNJCGS2VEac8LqVMGdnVORldm86TNimW8aispKrZ2JVpmAuT8ApzthVJVko23HYM7v3fQ3h1HRup9LxoR3jJutTxf/t4EFskNZaWqg74wwmNsfz98TBPov5kFzW7YFJhX9C3HM9ePLXkHsWHZ5mL9UESezOu8qosZqzIOhnkf7x5nMyxRKuciirHNDEphbY2Lwc5VQ+cIDxxxE1iWTnjMY/Q1y+u7QY6euRE4LcV50rxUs2YLq29ZnPdPH+/dMHzT4Ttg/DGRmBcpjK3vPYGSpsh9b9hQD1eRngFq1SqG1hEM97X61msj8lUMnjPBnI=
*/