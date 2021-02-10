
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
y1njfUfyUzkFb0wLykHfSE8FHByC0s6jrMDUcFkebHvJRJDlrFXb6+U17Y8lA6HlHvMzNtgqLe0AvfIN4H6LVYUV/ENrQOoKtAFvpWqV3o2LZMCjA4jS7PekiREzzi9W5Pdjk10E8836V8Hj0W86ejx2N87lN1pVDxCAgKw9WvANjiyhkQ62iBomrjF+wsTrqA1YvFVdzv48E5D0dkdu2dUs8InrorPGm5IIaaOxp9z4dTKgm+Rs7DZEgtPUE7YyzmfwLnjCbssSO3o147P3w1x+Oa8VQ0ffiey6VpXSK6P537Tv+7Q2dp/SJFCXhoiG8ReNch/C5MYWj9zH7kf4Up/5Pz4/UE+nXgK5NwD8/Ev8B1BLAwQKAAAACAAtZ0pS1DWQ9dIBAABbAwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDU0NlVUBQABtkgkYJ2TTW/bMAyG7wT8H4gMxU6dU7TuodC8DamHBRgWL3ZSdDfVpmchtmRYStf8+1FymuwwYMB80Qf5ks8rycKRdZW0lIJQujE87Ojwy4y1TeFzmUP+qdjCOivX0O87p0DE57iIJ8kbLGh8pvHSqppAjDR0B47W0knUpmqp2r2fHcjOUvB7gPw5EwZESwSulQ59Ny68sxyw
*/