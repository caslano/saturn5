
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct plus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus
    : plus< plus< plus< plus< N1,N2 >, N3>, N4>, N5>
{
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct plus< N1,N2,N3,N4,na >

    : plus< plus< plus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct plus< N1,N2,N3,na,na >

    : plus< plus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct plus< N1,N2,na,na,na >
    : plus_impl<
          typename plus_tag<N1>::type
        , typename plus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {
template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  + BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* plus.hpp
pjo2pY03aTWpmFRGijuDNt6klaQtpCOk6GbUM1IuaTXpEdJBUp24UFvv0BJaQktoCS2hJbSEltASWkJLaAkt/x9LVdLs37r9f2aO0fr/V7f9z44Mc44dz70Zj7HFS40xpr8028sNGTneHGeWBjWBt0v2Njce4buNWf+k9ruBVFe/d3/IenFfOdul5hfQRm9+mP82slHab3Jrfs/OKcxOS81bzEPt3/c8EdZ4xqh/wZkqh9akQ7yutDyeCUljk4nGHGg94HK4N4I6kas4NPb7InS0mzvYhrhmlj+OMPZLJgvRbS4yL3EdZjvhx9zjYuKMoGIzjtHMXxlbmvoptCNVUYxH2E6CK7aFzCaSbgQWzPxM9nLbqNisY+If8rLvT1lvuX3fFEyw+1fZeN3/IO3/GlXIttp/G9JR1iv2sX/V5qBi8HYO6fjwd/c2lwVhajNrO0Z1qnme35+xrbDjZpxnjx05NslZs4Mto8wcZ5vH/q15rInRrPs/rv1fovP8IpVTvGX/rlriv92lff/28mlgKR9j8jn+6bWMoiztLc05WJKzXfND6PlZxpwset7RXvdRzQXERtyuH1mneZbzF8RUQj5dc0ZQG4KYm8HzHPW8jh7yst8y4/h+XUNzQ/z6/aps3c6/q2jL5j7Hqo6rx35V84OsW7+m7vsZ79tHe8H//vG7vbfn89X+Mvj2fL7aHZ402y+OuHLj9G7FY24/uOes/DUX7G1/6sb79tVOVOO+6rOKcQ54jvsar3ZHXbExdne289FnDX0GsY9L10DtfCIwFiOxBUZhG2yEnTEa+2BjTMAmeDbG4GyMxXxsikuwGd6AcbjO7X64Pmvovcw+3lwn13q89we2XoLWa+dnveUBrBdPKtZ6bb2U81kq5wSVzxDL68KO+z4+k/W6KTo+05DXod4j9N5hHyc2ScdnOJ6BI7AXjsQBOApH4RiciOPwIpxoiavEZ1youForrjbW/Hzt+3Xt9Lr2el0H5+tIel1LL6/ro9f1xebYH3O9jBe3zzJmHG0dQuPG/cHjxqXVrBIaO07tCBbVrPKbjx/3/z52XCDjxqWMreq8v786jjpE2k46RKranPyQEkhzSFeRHiBtI5U2D93HDy2hJbSEltASWkJLaAktoSW0hJbQElrCwv7g8f/S8/PLh//79eP/5UfyG63tXvz3ukf3Dekn4x7zYesYUemZuQWT0i8sTM8v0Og58QHcmzfGljlx2DI+FI9Lyx/P5wnnPZ84NqJ53C3jbDAMiu7Jheu51KysnLzZmXn5BTyv+z8TyUteeYBjMvmD8Xy0+/P5k3Nc4wadJG/s2u1+blvdZ2+k+1m81Jzof8InPsrAnB438Htaxj5T0Tqu1Qntc7H2udCQfeb63Kc5bhlDmPAgiPtpyq/beIa5syhta9lW5TlX4TrvrVUy4skySlVj+TieyyugRFWGtnELGyo/xpNVWTf8iK/80LQkgHxY99FRle0m1dUbSKexj3jXPlLT0rradhTIfeVq9a874lkvX+TH+nzXOGYqS/cxwPLc7yfz97T0PKqudZynuKp63pafEuVnrfJzPakm+Slz5YeDbstPEONv2eOvbh67PGf8XYiCG7S2c8O9rcVk3WM+WYXzAz/H2myn6J/OMbUUXvKC9LzM2Yt1TAuCGH/q4s98jkfprLc85ny+MNlxL3i1pfxP15hRRn5zyLDxmgccbX3ULsE6zlRaZob5+EnbOG4bNO4Uf3eOO3Wbs1xc41DV7c3jWeXnySPGfnua+813HPONKtv5+exI+96k9VjNXGcdjzuyTo7Z0KB8nWt4TsfM7RhE6377AdWTv5MmEFPR585jwFBaOWnpjkOhYxDrp84=
*/