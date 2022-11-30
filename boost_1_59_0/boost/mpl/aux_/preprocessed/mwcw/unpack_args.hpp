
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