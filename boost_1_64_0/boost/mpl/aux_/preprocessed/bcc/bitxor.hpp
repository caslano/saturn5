
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitxor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_
    : bitxor_< bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitxor_< N1,N2,N3,N4,na >

    : bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitxor_< N1,N2,N3,na,na >

    : bitxor_< bitxor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitxor_< N1,N2,na,na,na >
    : bitxor_impl<
          typename bitxor_tag<N1>::type
        , typename bitxor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {
template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  ^ BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitxor.hpp
4TQ+fkC8zbpqEKd//WvUX+c/83o6pzdvfn/zQPufgji9cmXrlZFxn2zh9MEHpzx4ueebb3O6cGHbhaGrGu/h9JlnUp7ZXNZjKKfduq3t1mtvQiNOg4PLgpf9bHyf05KSn0u+GjFzPKdffTXnq3aPnL7JadOmg5sWhHSYxukHH9g/+PLFt0I4LSwcWOh4p/1tTvfu3b/36RmG7pyePNniZLfPFnzDaWhoeeh7V7MXcRoXNyTuL/lFwZz+/vsnv2/1u5LG6V/+8sNfflxxexmnRUV/Kbr99RAjp+nphvT9Q/c+y6kgFArti8OHcJqd/V72pA/Km3Latm1223Jb6DFOX3tt9mttAiLe4nTXrq93HX04fyanaWmj0p5ps+UUp6tXT119/YtBj3PaufPCzo1fie7DqdG4zNjgq7IsTm/cuHLjk+a/9+TUbj9jf3/jlyc4bd48rnnRA36zOQ0Pbx8+8KHCv3Dq4SF4hPvr4zg9cOC+A2OvrXuC0+vXn7oe8uihzzn95JORnzxZtHUUpxs27N1g6JheyumyZU2W+c5psJLTIUNuD/nh6F/KOH3qqYlPnbgR8iCnOs11+nS70/3Oz/mJ0/vu23ZfzIKxeZxOnXpo6lM7r1/idPbs4NnGkjZfcvrhh49/+NvL2/05bdfO3O7CtH4HOH3jje/e2PfgNAenr78+//VmPaL2cvrII288Mu3z8+05TU5+KPmdxsVfcxoT0zCmecLi+zm9deubW8d9fgnjNDCwNPDZyoxXOf3++3Xf3+c4cJDTYcPuDvviwGMfczpmTPyYVb6vHOF048YdG6frx3/C6ddfr/jazXT0K05NpkWmptePPcLpO++cfeft7Bw3Tvv02dPHtPrhEZyWlnYvTfzbs8s5/eyz9M/2ztqQwamvr9W3whx2l9Nffz3367u9/zac01GjeoxKMT7TkdNVq2yrrlYMmMppfv7R/BV7vv6Z0/r1feoHdvDqx+nixc0X+61t+BqnO3bc3PFT+PSRnH755ftfZo0/M4/TJk3Cmlj7+T7GaceOMzreyRr6N04zM5/I7P/jwTGcnj8/7fx3m94YyOmWLc9s6RE8ahanTz6Z+eTB20EpnP7004Gf1g38PpPTQ4dCDk38+1ObOO3adU3XvttH6DkdP376+JvCjq2czp3bc27aay3LObXZPrC99dLVQ5wOGHB1wAef2q5zmpDQK+EBw9pWnD78sOnhY4P2rOG0oODXgr/Nq3yeU+yGDvv0gvULTpcu9VzqPb/eWk7PnMk6c3jH+605feGF116IaHT/VU4vX379ctSov27g1GB42tDnzv5ETnfu/PvOGzGPRnLaqdPcTi1fiAzldP36EevXfNjVg9MOHQo6VE4c/B2nUVHNojqnzDdweuTIoCNT767ezundux/d3XnfF0mcurvr3QVvDz9OR48eP3qHx8YrnD799MNP7znSpyunubkv5yYd/Lgzp40bhzbOHtDWxOnPP5/+eU7fr6Zz+vnnD37+5txNOZw+9tgXj3207u7LnPr5FfkN2RXXhtNBg64POvTR1N843br1ya1BQ0Y+w+mpUx1PDT0zq5LTZs2imy0c0/lpTlesqL/Ca5HbHE4TE7smjpi83p3Tt9768q0zo+0TOf3mmyXfNMo4XsHp4MGVg389UbCP01mzhs6a8X7HXzlds+aRNed/6xvO6Y8//vLjN163fDl9++3P3t4wyeLDaYsWCS3WpndbwmlAQEnAzPXjRnN67tzkcx/ufrcep3/727t/mzzh3FJO8/JeyLv/+MUBnB482P9g3q0nXuHUzc3Lzadp/Xacjh0bM3Zxi20XOY2ObhzdNn7hw5w+/vilxz9/7rdiTl8=
*/