
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