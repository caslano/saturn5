
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

template< BOOST_MPL_AUX_NTTP_DECL(int, size) > struct unpack_args_impl
{
    template< typename F, typename Args > struct apply;
};

template<> struct unpack_args_impl<0>
{
    template< typename F, typename Args > struct apply
        : apply0<
              F
            >
    {
    };
};

template<> struct unpack_args_impl<1>
{
    template< typename F, typename Args > struct apply
        : apply1<
              F
            , typename at_c< Args,0 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<2>
{
    template< typename F, typename Args > struct apply
        : apply2<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<3>
{
    template< typename F, typename Args > struct apply
        : apply3<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<4>
{
    template< typename F, typename Args > struct apply
        : apply4<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<5>
{
    template< typename F, typename Args > struct apply
        : apply5<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            , typename at_c< Args,4 >::type
            >
    {
    };
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply

        : aux::unpack_args_impl< size<Args>::value >
            ::template apply< F,Args >

    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
9eAv0D2pfPAg3D3og5iYRmyTpnZf/Bq17/oM6TViLVxoYGx8XxvD8qYgZEpi33jSqgG8fcLR60EciD37R6cUO8q1iId0DkwSdPmgkh4uE0Hnl87ldsKiGgX+ex88ul+I52291kXJEpmVJvitSp71514m0/qxonvt3yWio8o+Ujt0ZBK4EnVdSQF87ZcLTnAyYhldnZVyIcc8DPESLhbAiyws/M1EBB2ifGpJGLi6yYgfMyj7mKnAH75eX9ttmdVNywPMuZYUvOegB/Ptj3a/ao1zfbrj7Vxdftu62mzyrFH2bLTZGff8eBvbHIYu6ZeH7aAfhMuaL77Bjb0F5K5bFI0FQuaa9UkGuk0QPt5OqnHIR7Ss0JWnA0QauvCTvX7XXFvJOxatz8Au7asA166nO0LBPwczcrxaMrjSEbSMvaOk0YSCWLn6y1Vc+Q+BqdceghuIvEmfVpRGytaQ3YcfK0htVABKDeb6CwP0jshdcF3q7qoxPgyFH4UfjR8VgLqOXYXpxNTVHNmMBkBfx+tA10Gv+oMT+ny5WEDEX+7kwkG4PTk90pvsm9RzTkLUX3xGP3gAJARpojw3s4K9UO/+rGxhvVFk3m4PDi+9cRENQ4fXTVfTvKKg0gKKOGAoiDrgusfHvq3WEhCjfPm2vqtM0CxLq7gkHtms9yMwiVmoaD6CoGnwLGDUtGGDGodsvyd/zWxF9Vpnlc9sbYBF
*/