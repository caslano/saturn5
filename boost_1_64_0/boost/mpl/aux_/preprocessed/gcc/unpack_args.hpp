
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
HAvZNAZpa+FYgx4O1Wd4i2dZrOWvDEpUFNirCGISzk+SGhI7cW2Vf2GYFTwQAkYnhaKWLHVPSEsRT5dV8FOWIzU9xcRnW1tfQbF18ilRAOe9u++tiGan2U++wmBLYes5r7ANAtE+Cd6sn/GHhRwfG7eKL/Jes8WzooJfZFKxos6RmWG26ZJ3HFwPzqap90pYEnhceACUnTP4OWsvEQ14BLU+qilT0bhjeqX/D9sdVscNHjLrvgUGl9bzS4IMm2r3LnGSokgGwQiw8Zv6WHP/84w0Ad2aeXUR4HpipJ8UPjRjQH2Tx4/G4k/KqyOCc7vG9+poRGXVtfZXnSTyc94xx5eko/1m+4XKRC1x50KEz5ahfympylNl2IdjEeTU99QyL9J9OaAoNqMiufX/bZdixaTvN6WLHNalQDB0TSVmmxLfvHNBmCGmxDidwWVw5Mv4HH1F+kr2voV6HJZzhXCnKUXZPXEakxgyzjnVJaceUaESHjjDKeyXRCreF7aJ/ji9fEuuXiXjLBwB121Wwh80Hx0l1yWT1Q6/GIsltlGPa3WjOIBfeCsaFqpMkA==
*/