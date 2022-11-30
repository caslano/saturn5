
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