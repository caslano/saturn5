
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct shift_right_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct shift_right_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< integral_c_tag,na >
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
    : aux::msvc_eti_base< typename apply_wrap2<
          shift_right_impl<
              typename shift_right_tag<N1>::type
            , typename shift_right_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_right_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n >> s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_right_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_right.hpp
jLUT0O/O3FxuCB1Wc2yzE+N0jGRWsh8roWI3OP3JaoB5E4xh4BYKlhu9Mpts5/NiIa1KxneaFAPW+41RJ5N8Yc+PsvXUECVOFAQrNQ6UuEdobDNOxw2GMRstnmwqdLAGxoEoVlxXMyb7nSXvLW1/HDQ9tciemoagmF7UWJpMsxk6xkp3yfqKMkxzyNEjhD9IxWZQzB1ecVhPcFL/oPX8uqJpnQNYDvhW2D2u+w1lonZYWWBNRZkFdUXVRt3RQl05GLUamsxTq5h2vS1C7ZIjhfMTo4yoQYZNj0Sn0WxRq8bUsobdNSiaKiEDnCd1qkl1uxhdUntN2xLHejMYqAtaNQ1jK1rrolH6yHEf8hNVnsQmGae6dGy1ptICWw13HkbWrcOUxodB2BwxEpM5xfSomcUojKz6cS/KYoAbrNQhs3nacsm+2UTE0oJxPDadmBeF5dLJqLWKl11zKAnLUO97mudYSjR39Z7n7YrRGoxm1roMeH8W9FfWIuK6QOmP+7lhkgai4e5cltZ9T+WyZZhLxxjHqdx3ulzg7ZsqpW/xsaCVToYDYekpnu+pW4rX9soILo5AXmxcZxiPBJfw5C2ylu1Zq1vXFjyVl+l+Fvi2sug1eByX8oBZ6YPDQtKtIsSXk0RUs1KUB5wryPrI
*/