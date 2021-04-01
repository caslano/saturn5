
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
m9c/+Vvwqj5AfExXOO1gTOzrLC7dyHx7JD3IPOeYPO4o00WL2nzh8V8kH0Nsd9ZbYYNH+a2hnvLH1MY+3HEVLmPv6IaoyyYYl0A9RCQNbc3c6ROH/X5ckj0xHDlbV37J1xiDyP8bFgE5EGNZBiLNwu3WWzA0AzWc+dUlENDdvnDqpGmofTmhTGCbCr+3Gfa3QjAhFi9ELkkqDaTxfkyt2pDFTng+ZIkhApv+y0eAphnfW8Ye+IL0SNarjhOGpDRk7GVnQN2dAzxuHjuHRuznZJJaXp1B/Z8KNtdds/4RaQZ0hbXF8msQn+zZZOAajvwMdrcdaTMgGYDNyuYBZ49mRIl7zXqNBsuzHytH/cfRVKsf15XHCDMsKo7qnek1urJqHcbeFUh6Qx+ysBbVUE04Y2QZpgLrc2kU0+Alv4mfpF2UhjBy+uhJfGlJf6qryex99YPXTgk2aZ/G/FS4xghq2ulq9eWkxuse5kc0kFH+ndTwYekcaSXXy8floPFkVo+f7Lm9QrX3mnYW2UxqHB/x+AK8fvnzdbSXWo4y8/NUn9yKSilSmID9BD9HKg==
*/