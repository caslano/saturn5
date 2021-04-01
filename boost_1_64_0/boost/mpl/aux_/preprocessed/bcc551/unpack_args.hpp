
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
hp3au4aHOJlusV6d1EaqPjTjY3McdAEDGJk7JrDRBZOJx1vzF0fFR3Gky4KgvXSJyJDt6UpqUnSFy+FbvTddL6Tce/9WwMi+leRcPGX4sRM+fjZW3/Cau9sx9A0syhPsxkMIzq5ULNl1EaPrpylBCGaGq/f8FllJnIllHZoP9fL0aGlE3CtoHVBsZ5JNG29l105cFGDdOdLw1LA+QwlF6rtvyhGTwjYZ66lij35Y2kGqZl6JOfRzklLYwpvIJGC29IuefMQrygvmdTJ2yTkBaRT2xpM1bUncSt2kEGd9EOSnD6J30ioWD4QSWwu16bvXxMPm8UB0zOZIfqHtmwRyhExbEFUGUp1ShlpE50ii8bCqun89+VSrrUZg2+ZCUzzQ6lSmkL6irIx41DvgTRgqOFUEh8CpwGl1OdaFGe6VPZ1fu5ywhw6J93qmU6zwxp5G9PBuxibpxvrggcmzL1+ni2+t3EYPoQ6kzB2rA4XoXwS6fNef95fmXWGZ3ZxEfbCC7FB6n3FUoQ57LxMWbK0GyaE3jb5rOIB9Sh79N+aLxT0eeMs9Vj3eW8BO5g==
*/