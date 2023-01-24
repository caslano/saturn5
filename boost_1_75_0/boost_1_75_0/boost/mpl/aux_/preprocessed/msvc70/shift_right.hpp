
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
    : tag< T,na >
{
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
zjGc52m+fHhkaw6OlwJNhikskYYN2LZpjjVIPqyeF6q16481yNwYn+T7yR3M0yJYZjew0WwLKwoVuVhKXY39pEkSrrl1jISyQHNGa7d/gnJ/w7OTtzVIWCe/1D0zyYdp/mw2lmtf+VIvVx2mma6RY5OLwZOYM/l50vqLRwddJ5skgsOvK3crqsv2XaEvbKjCAiL8zEXu7ZlL9pUntUEhM6KX4WNfUqKfQupy5QAyttK7af0ATKwBNF60dROeWGuGCi6Jp9ZdlmpqYUqNau5D0oIX/2cEKDYMI0CCGSrk/PaHXxKn9DppKOCf1ZyBwDmgqC8ivcmGsE72dbytMi0eLBQ4x6cja56OzsaH98ddBV6Gtk2+9Kym7bFam9S3RGsB234+JS+07D+Wvdmse62HsoyVCn3Vu8Sxx1NQozyu//Url7dPYpdOWPAtUaTQ2JR/cr0yTMejN8VW7zi7RSMyue2DnpPwa53CwSJ1LU66VrRWKAeIrERAaw9FP7LTmdLntBufaK6RovJEJ1pvtiWJNskUuaZXUTsWMBOp2IYq+J7QsomKRl44o8c7pVxTIHXHoJ/AURqVe9/Qbd+HpW+I9s2niwzcxy+6PMSbgqErxUf2flY3fKjtfWphnF4diqcJTYspoGYIWTtu3InGYdi+DY/s2tBuQH8p1lP7TX09tfkPMFwU5/eU+fpy5xpCGoTs4HK3ktsdggr1tarC
*/