
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

template< BOOST_MPL_AUX_NTTP_DECL(int, size) > struct unpack_args_impl
{
    template< typename F, typename Args > struct apply;
};

template<> struct unpack_args_impl<0>
{
    template< typename F, typename Args > struct apply
        : apply0<
              F
            >
    {
    };
};

template<> struct unpack_args_impl<1>
{
    template< typename F, typename Args > struct apply
        : apply1<
              F
            , typename at_c< Args,0 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<2>
{
    template< typename F, typename Args > struct apply
        : apply2<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<3>
{
    template< typename F, typename Args > struct apply
        : apply3<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<4>
{
    template< typename F, typename Args > struct apply
        : apply4<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<5>
{
    template< typename F, typename Args > struct apply
        : apply5<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            , typename at_c< Args,4 >::type
            >
    {
    };
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply

        : aux::unpack_args_impl< size<Args>::value >
            ::template apply< F,Args >

    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
hmc/pybUGM1y30ZMPUVHCAZUxUt1tlyiWcMEFZmh0E8X7jwUiGpwCZIif4bryEpGxQUvWNLw+kLEC7Qss09/TDZiG3CYNnM3iQrQ+JNZzt+K4hYXCRmlYFixXs3HuFz4Kyb5AF6/UIWGmZCAx6TEV8LojF5rYs+ieWBYiNOqCgm9wGMymH7ltGdBQ55tWSdFTBBlVpyK60TKvnAV4WNkRIwjojcOWP6cELSIOO4ovTaMN8qCafvVeRo89354vha4b5PjV44OuTVn3QkpN42E6t+g3tdSrixF3fOWqsprzjChZ9lCCJ+LgJRU6SNVI3Qvea7F/EFYpJdSWbItZOPAVC71RCihdlJjqmiW76QbGwQQAlVND+VAtIZU9x0Nz6S6ildtCtPcaiV/RjbPmLcsPo/SC4CVx4zpoqjtQBls/x4thl62BAofjCOlReXNMweWZDA0AIe14GPbvTQyzCVOZ4XRI3jGtU8BvRzRBKHfjPdv1nx7ic5lOtv3395lKbE0Fh2CE0/5BMZqztX5rxBfFohykjkjUiGCklQwmZFDndQCKwJARzkVDKXiEw==
*/