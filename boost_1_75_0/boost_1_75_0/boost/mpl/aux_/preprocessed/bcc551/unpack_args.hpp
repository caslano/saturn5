
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
    {
        typedef typename aux::unpack_args_impl<
              size<Args>::value
            , F
            , Args
            >::type type;

    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
0ytM0+mewPPKCKa3AMoGIJ4S91bzaCvf4UobZ78NdmMdkysopay0aMoIZ1TKJjemMb6IhECk3276jaPo2yosaOtkMVEDBXKI7wBB1/hSItuFN8LuI1tX0rR1BdlN37Mh4v6rtQ63kwctKC7jsyeORP0M9d33WGYnIbfqV4mX9FWFTJF/pm1r6TPUp2d9bt4hz1DMGpFZY7WS8vh5us1zG/VuO30E3/G0jwX66m7Na+7NM2kXQeKEPsKqPZe26CbSTjIG65reWPrrDS8Ci2zFEmaHMEYQPkt6NkjlcVvUIjQRpJ5F3POmM6aWww/snikA89p7bl9ssb6gedQMHIr72dIcJOVtnSjlHzX6FAI+fMCcZqD9M0PO6E+KjiCjwQFTLZerSsabyFR2uqWa65C6MVxfrUAXvf0/8FLljLQehgrZN+9jxoRA1q7+SCrxeEgg8DryqVUSPHW2cMwJcthzxa9lJ/rM5awu8iPwMt+GvBP2KotLrXwG6CBkW9l40iSw4uskIPbJQZ9pyiS0O0R8j3Ylplnyd55TafUK68MSaWP6Cm31J78vDvPs36Rzfqvatsx+jQUHpf0uN2ZFNOudEXYZPipM08FRuASiXF7itK19sbUGB9eon1xjKFT/c2/aJ7UJKJilc2Ifxa3SY4P/0LLSe0szSeP5zfPJIVHpqmkYst10ffhgq4KOUmveoPT2If57zQ287RCw8e7+
*/