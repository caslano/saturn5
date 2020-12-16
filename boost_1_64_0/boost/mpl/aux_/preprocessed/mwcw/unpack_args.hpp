
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
y05abRdjFadfoSotNsvCC1Vx2izLKLT9fpcu26yO02bZaXWcskx5RrhB9T4PrTEAIxo4ekbo3PM6c9yLNeKOso+bA3Yt7mKNuI0O4iaTORW3ZfwrjXH5MhzGDU4+xzSnPU8j/hyH8Ye4FLe3xjh5udZxS2HmWrrjNeLOs45bCm3X4t6uEXe+fdyTXc0rARpj7xXYx53sarrnasRd6CDuSS7GfVAj7iKbuKVQcCpucx4P0RhrT9fQPm65IXAqfnPaF2nE72MdvxSurp2XIo24A6zjpkB0vcwK1xhbz2AXt+tl1hqNuEPt4na9zNLX0CjH7eIuX5kVqxF/lF38rpdZ+RpxG+3idr3M8vfWKMvt4na9zErXiDvHLm7Xy6wDGnHn2sXtepllqKlRjtvF7XqZla0Rd75d3K6XWWc14i6wi7t8ZVZYLY2yvKFtPabr5cpKjbiL7OJ2vVzR1dYoy/1s43a9XInSiNvHLu7ylStbNeIPsIvf9XLFz0ejLLeL2/VyJVUj7lC7uF0vVwo04o6wi9v1cqVTHY1y3C5u18uVLI24jXZxu16unNSIO8MubtfLlQF1Ncpxu7jLV67kasSfaxe/K/dCJf2sI+s5Hks39KdaStzEqx40oOLG0X1PNY7ui6RFxtG1SnuGDFIWyklpiEGopD2nVm1z2ikLrdNuQAfTfNLO+b3FtO8GOo+bchwniWsbaSYRpvEGTvP5g858ViKU8Qai2H4uG/pygBt8SLecw0LzuJkzStYLZJ10wlDm9aoj68n4mlkkJDV6sqU/ubp//9gG/I/pMc5NbfFzjqlIb3WOKL8S7cYD1dtdW++SMt2bbVWf+8rnuroqdX6oYfp36/C7g3roZF566bxu5nlXq5vndetpnre3dF5387yPS+cFmec9WzqPy0k6mLeomnleD9PnrpbPwdbXUolDrmWqEmYZ40CuJ58J0SmTLdezMtfbmJoiY5XaX79MVvLhHP+Dz7vYp3pMgBaSF7gelnVHse4g5nOerK4haTPlqwZ8LlLtZ4Iyk8l2zAl9Q/7HdFq+tyfN473WVF9Xy+AN5f7eOjt2g4ynYUm37Viunn7S7seD7yqu9ZAxu/2s0puaiOrva6e/2PfVW0k8xzIAPJpofw/V1yq4kePxvn0uWcpY9VDfFTbW93uqsb71HNNBQoIyZiLp0hzrW9b1bERczH9TtW6xxroG1p3I/HaXS9ctKmM8laJGjsfKjipWn6+QChkrpqwxf+X8Wb83tbHjtOddVKe9Yt5n62ra45s4HuNb93Np2lNTKj7taU6kfYC/4/G9oy6Y064ehOfPG9v7vTLG9j5IWmVsb6tj29xU/oZ7cGw430PKDw9L2TnZcp9zA+N6O3ts5rJ+G8cyWVU2hvkTB2ntz+eDHnJPoD7OtMSp8nfBsn4E69/CvKaVS9cvLmP9jKYlZW+8av2iMtbPY/3ezNugWv+s7fq25XUz/sc0i1BTjnuncr6v1LI634lx0UlpRhfvidHR+VPfswUEyFgdPOevLX7Otnmq/bt6z7b5N7ZVfc7ms/mebeN/asm9UnfLPduea5Z5BvO8vpZ5Qb3M8+b8aplnuT9bf1Xmqe7t7pF56ns7ncxT38fF/iLz5D7u/JVaN/0+zlHeDWlGnm1OW20+eyrnQz1ulvo+Ttb1DygpJzl3mvdxxar9aN3HFci1Hiv3BqMqyX2crvS7/Wfcx0m67e7jYlvyP6bHpSx6VMqiAH9Veh3cx/lrpVmue1YzticJKSl/TPmkrHPa5jfVgQDOfwvud5Rr3vT65RXrmwbe6QmDm16/vFLWN7Qsif+dptcvr5T1o1i/O/OuNr1+eWUuLwyt+J+SNMlDzSQ=
*/