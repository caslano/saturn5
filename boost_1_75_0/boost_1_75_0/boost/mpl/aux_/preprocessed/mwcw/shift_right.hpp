
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
EYLoATv3N/uf7tuAFf77NPhz0S3lrSN6Ix+lqyhbUx4oZmZmbOJtgeSiuvuVoVHem2UrTW8YTSEWRX9mQJ0I/S4u0Ijth6zPrhPKWxUi7CQLV9h9nR2cDeFX4y2RE5RhiFwqjn2qN1tvjIzz4J29OziK89CA19ddQduDH8rbkcXc+sff+ofksTCXfCq3/zj/vrX7xzCP22HMh2SWQ63JOTHxDWpRW1ph0z9/yJ1qlxPzZ5rXoHBKqg+agaurEh/w/nS2KoeymhFanxY6BLN7cb/4WC1DISDgm5jjY+DZkh8NUcjpYfbAXW2KxDATmAJZ1JA7OeQ8fGxned52i8K9AMAYTB5ilFWOqN1/Lbj7uRruGp38Z1+fF0OwuImRE1LwFcnqiQRCWMPFdHphFzeA8YXSgzqNwrtkujYFgUoR3Af01NkLFMjed3hByKY9y60gXJFAyG3IaihbS+0oQqEFNN5AviKUwFDFordrmBcoNWGvQ855VWh+aPzyHqbVMgD0JRQs8T/Z/RkbReUHbhGRHVIS8mjogTizG7IdNdxJyuutHbpgaBGxUEJG3mdfwCxyEGNX6OIPoj2BIsPvIpUL5V/Kztg/ByN9+hMbCnvNb/4F5lAkIx1rjDI6N6xPaLLH84+7b0RGqtZtjVRyt32oCrgHs1Jbo5/pRqZSCpSTKwYqhA71LUHWlYJRjzxWlR8IZqGC919P/fAI2Y0b
*/