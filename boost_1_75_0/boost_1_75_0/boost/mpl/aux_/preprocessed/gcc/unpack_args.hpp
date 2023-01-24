
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/unpack_args.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< int size, typename F, typename Args >
struct unpack_args_impl;

template< typename F, typename Args >
struct unpack_args_impl< 0,F,Args >
    : apply0<
          F
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 1,F,Args >
    : apply1<
          F
        , typename at_c< Args,0 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 2,F,Args >
    : apply2<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 3,F,Args >
    : apply3<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 4,F,Args >
    : apply4<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 5,F,Args >
    : apply5<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        , typename at_c< Args,4 >::type
        >
{
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply

        : aux::unpack_args_impl< size<Args>::value,F, Args >

    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
paDWYlQ7Q0h+QPDc80bAe6knVJrzw3wlEo1u5dFA7VORFPUnH4nG7DcTYhT7LrKqAPjF9arAMlJhwB1CvUFRjoJijy9aiZo90dR8rcBJIBrzWH99KjJoJ2f0ln49Bvrq+GbQ5pkg9+af+Q7noRGPbckLmNP9srj/Na1OnyXYQKj3FtvP6NUs9WHZjwr2YVzocjakeygA9cDgcUV8OyKQ8iAPgD/ZdS2V6rUTkPqwk8cA6lEq7KYXS7gNeEWTha6obJf9tVaDcU763gkxgPKZjXR1/xYM15kcWwcpJduTCGMDv8/2v3ul0//O7Izfudcms0z3t2A4Sp9Ct//1XaA3noOu/nb1kSvnHyTvE6TuqAsZ3hoxs3ESH6786rbxIkfjCrbxY7DfDXaOkaF+H3tE08zoe4bUQj+5rSY++hnVZT9R1M9GZne2/5A3+SbcCwa9h0gPzl+HZ15hSUsN3gao3DUFUKlQW0vFMTC8YZW3vcEQzccBE7261ftVI4L/2Dqnq0asSiicAg9bXqpgj7yc5FCRduKFHUbnLJgQ4BKdr8+D+vrWqxTYvdfncX6EbUThv59j9Lqu/gDZUHOo6wWP1K1l/AB6TXF0G9bE+9DDItgzKAY6We8l5wHzjyaN4wUMgcY8uqyT/vuKt5RK8V3V8zfzN2nmddjaejVKaiDZ9Xk564dQhPUE5Y+T5evKwQ7zGhVDtx+xjMXyJcW8
*/