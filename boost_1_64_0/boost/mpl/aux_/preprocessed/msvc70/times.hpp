
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct times_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct times_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct times_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct times2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , times2< N1,N2 >
        , times<
              times2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct times2
    : aux::msvc_eti_base< typename apply_wrap2<
          times_impl<
              typename times_tag<N1>::type
            , typename times_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, times2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct times_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 * n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::times_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* times.hpp
ZFTm4kzBAEzFYEzD/piOA3EqDsdMjMQsjMZpqMPpOBlnYB7m4b04Cx/G2fgUzsG9OJf/XsV5+CbOl+O8xU5+U3GZfD/qEzfIebxUxrWulPNuFXrjGuyB63Ao3oVxeDcm4Xo5Dzfgk3gvvo4b8SfchDewv/vQFe/HZrgZO+ODOBQfwrn4COptGU/6N9otYmmjWEQsJB7V2iu0oAUt/EPhatT/q+r5f0r9/z3Vc/4WSf3/R6nfncOXueYtbmFSvyt7zp81fX/G6/Y9lp/zp6rbynNqVH3DFdVLk4nK9bR/S9O6yf2tLd9T7iT9xNPQBSfhK0q+2pjly8I9wyHqY2tF/cRSPnkWxmWfoyT3rpo8M6nYrG/9mIUyOW32DMRTUgdMTIlLyvK1M3kmRLjquSevks6s+Mw4ffyk0rL0NC3Lk2bLxW1Nl93bmS4vNlt+uZ3l8RFbyJ9BZd5fvAv3kZYQ74qPhbLYKUDuQb5Kx8NYV9yteq6VpWN0shLH6ISVx2i/2TFa5W1axlE+LEsaleWtPqbvu7U3XY5sb/n7ESB19+/lOScn5PtR0MHsmKjbdSr5vJPKHo+r/f04YFb25zuY3Qfua7qcb7ac19F0eZnZ8oWOlr8f+xyk/1J+qxqg8v1Y4W/xWPyvvx+vmx2jE/6mZewQaPr92MCy+v3HzZabdrL8nKc8ObETiPbSvvaGl1LxMT8m8vwzG56vZV7+2dKuoG7zDFe1ZUnZlpW/uizVaQ6qZUdAMlQXA/AtL+WFi9Isz+iyvp3amOb6qnMmLT0tnvIx+Xuepvp7LueOPLfP9O95uFnaj0naY6WdPZp4WPkOdDFJe6Weq7XHyudqqdM32GxslP4GmRdX0pdDvI6GG8euxrFRnQJi4nRWXR9ZGhulPhcYYnXJsVI5cSmqtBHkWX1jJG0jZdxWoSptVT1uy9D2/R8ct9W4v/L6+36/T4jw9Gw45sx9tz+0+uXCyrVrhlST62i5vi7C1vK9VEJP1X2/jbAXumNvbIF9MBT74lTsjzNwAG7GgbgfB+EhDMd3cDB+hEOwunJM0BOH4VCMwOk4HO/HEbgPI/EcjkR3aX/ri6NxCkZhJo7BaTgWN+A4LMJoPI3jpf1sAnbHGIzDWJyEOrwDE/BxTMRPMQlP4yQ8h8ko49/kul25nr94/NsxPueCH2I7PI5++BF2wxMYhidxDH6BejyFa/E0Pohf4hN4BnfgV/g8nsW38Gv8GL/FL7AEv8Fz+DP+Iu1lv2IjVObgvQWr4zdYA6+nfK7HeuiALlgTW2AtbIO10RfrYC+si9F4I67DeliI9fEgNsD3sCF+iY2wGeXkjCPRFRPRDSehO8r5KdfgyrX5xednupI+zMR2mIV+qMduOAPDcCaOwVmox9m4FufggzgXn8B5uANvwedxPr6FC/BjXIhf4G34Dd6Of+BibEqalqAn5qMvLsUuuAx74XIMwxU4GldhHN6JWbgal+Ia3I9r8VO8G//A9ViTcrgHG+O9OAw34kLchGvxfrwLN0s5Lqom181yPV2EHYh5Uo4LZI7o29BLNd/A7dgdl2MfXIGZuBKX4iosxDtxN67GfbgGD+NaPILr8DTehT/hevwTN6BDNfKBnrgRw7AAh+B9GIVbcQU+jvuwEIvxSTyHT+EF3IF+5Ps5TMQXMB13Yi7uwnn4Ii7EIlyBe/ARfAkP4Mv4Ge7F8/gK3ki5vYreuB/74QEcjgdRh2/g3fgmHsJD+Cm+jSfwiPxeTKom185yTV2EXsRoOR43y3ntJ+e1v5zXAXJed5XzuhtOxR6Yjz3lPA7GFzEEX8NQPIS98G3sjacwDH/EvngB++H1pGEAtsGB2BsH4WAcjNE=
*/