
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