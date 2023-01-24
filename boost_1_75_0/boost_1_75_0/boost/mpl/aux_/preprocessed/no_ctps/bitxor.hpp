
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitxor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitxor_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_

    : if_<

          is_na<N3>
        , bitxor_2< N1,N2 >
        , bitxor_<
              bitxor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitxor_2
    : bitxor_impl<
          typename bitxor_tag<N1>::type
        , typename bitxor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitxor_2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {
template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  ^ BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitxor.hpp
BJPUO/OEYGAxPEsa+IV63fp49bXa4tk71FiQycSKaJ3Ou7JnlH38UH1ExJi8fKOmDL0XfXPq7iAzJS2VKhgDyBNOROhE0IVryhy2J7XCZbpBAybQschjNeXwjhUb3Y5cbdYWp8RTjdrksH1BuOZk9dMQLXrGiVYYMneTdcTFqlhHPD2ngpNafAQTjg+O751XjJ/uN5xyDAFiTKNNRZQ+viJoSuCTjEKYAofpxCMYfOU4yUX3hdnmLHgz695jJvxQsx0Os+xvYej5003u+VjU0mKD54jkOFBdOHVKnEfCMw+nzLg8Z0SDRazfJTFAvl/CJgT/mShHIWdEhzXTWa1rSiCxc2r8PRHWCZ98J7Z7Hl351xmm4dtp5GtSFcwFQiEoCN+02GVG0LiASxGAzdxP/N1cdtxRpYkUgRp9SVOyOTX2ZrSA712hoJiiaVH5ybhrjO2J3PtSHs8Em2ym1EoPDB0N5L9qksh8oYgFmwVfC5w1vuPxqkQUUM/0FDAnhb6tHv5COufwTjAvgvqBiGHsVG0Gw74Ae00x8pf6CG4AbiP74M87Of8wNQ2htLBiQrKc/sbQ/AhTUYZ8Io6oT9e2e3GCLFNSa8uDyhaxAxlrsuib0uN2fJsKOaMy9y1fDU8R1hRw5ovviLPmnGVKWPNtbWvVOz1N2CmFbuID+YlTylCC4b3hzqU6EOKO8My1ZPE/wkNG7JISij252IpF
*/