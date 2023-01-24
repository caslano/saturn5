
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
4rMEbI3dBKdDU5RyekYXEK3WFTDCazSpRZZT5KyoLH2GlLOYyttoRDLJZCQ48WK6UKLHI9N4X8mERJZfUwWW81zCC6JTWlMUDozzzkRQQji4BIrupAO3/Mhk2YsUX3BmrEj9deM+O1kvvDfI+s16aPY1ftEtWRYZXpSflM92Cs7TFtxrz4r0FU1Swm/6jYSeujjIjkm7YF7G9cmLNol4ih5lmkZ7BHUtQyIqtrL5mB9LwE60jKQyQEdq9CeT0EVee53miDxtCsij464oem/ZVEEhQTcrycLsmzIfK673SLKVdRF4/0e7Z1b5hvLkfOLBmF4Te5BZ7Kr8wup2o3k1GLzJKal6n7yW8JLHhLEn6oxhtYBKHqZNuZHhysowScdwPqcsJJKb+BgSKjcgbxMjb308js5YbP0Y+l4o3sxBeIzBIyvk93OaTamnMD7d5ipEJngSihlcUHwjPtRXniRPJJDqSSo0nFKvbr2TgbgWFDHqrazEgVU1mHIelxN/1tMzJ7cyblo5UVYLHTlMZ8xlYkwTcbcRDIy/oCHKzmyhWc27UNR/T+6/kLrr0qtXrv2FEoiEVZCwA58VGFAtVpAi+0eg1W1pk7X/rlGP7F7PjRQz4sP8sm/wQv6I8exkp/s4f7G1HnWX02Fdzjt0OeWkxncMvJ4lZzUlGWf3SXvkB0OHpHqHOzi1I0MhUiuamQjtJu2XY4FmKQV9K8of
*/