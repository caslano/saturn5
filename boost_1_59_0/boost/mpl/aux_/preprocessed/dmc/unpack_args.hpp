
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
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
*/