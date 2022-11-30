
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