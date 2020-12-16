
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct bitor_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< bitor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitor_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitor_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitor_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitor_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_

    : if_<

          is_na<N3>
        , bitor_2< N1,N2 >
        , bitor_<
              bitor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitor_2
    : aux::msvc_eti_base< typename apply_wrap2<
          bitor_impl<
              typename bitor_tag<N1>::type
            , typename bitor_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitor_2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitor_)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct bitor_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 | n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitor_wknd<
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

/* bitor.hpp
jIpyXSvXuUofUfp7qtx/myRjrcVgE5yMLTAO22E8+mIydscU7IVpGIxTcThOwwmYjvE4HR/Gh3AtPqwa8zIbZ+IZfATP4mP4Pc7DCko/xsq4GJvhEmyJy7AnLsdR+AQ+gE9iDK7GR/EpfAzX4DO4Fp/HZ3AzPouHcAN+gZmYi8/jNXwBK9BGm7AHvorjcAuG42towNcxAbdiCmbhInwDl+N2fBF3Yhbuwk9wD57FvXgO96OH0s+xBf4N2+Db2AWzsQe+i6PwPXwAD2M4HsEU/ABX44e4E4/jPszBL/EEfoV/x3/hSRlj8lO8Az/D5vg59sDTeBeewT74JY7FXAzDsxiHX+M0/AZXYB6uwm/xgvl+r1wb0wbSD/kKwHnFdqyxr7EJfqMaa6wdfou++CN2x/PYC3/GYPwFh2MBTsBfMR4v4MN4EdfiJdyG/8RsvIxn8Aqexd/xD7yGHjKmWEO8jl1kLLGuWBFD0BVHYGWcjLdhElbFNKyGD2ENfAJr4lNYC1/HOngE6+Fx9MAz2AAvYkP8DRthHdqqMXpgM/TEO7A7euEwbI6h2BKN6I1p2AZfww74EfrgSeyIn+Od0h874Xfoi9fRD93oJ12wEXZFb+yGgzAAR2EP6Y+B+Dj2kn7YG9fhPbgJ++NrOACP4L14HAfhSbwPf8TBeB2D8Tb6y1CsicOwFoZgfbwffXE0DsIxOAnH4hQch9NwAs7EB3EhhuGTGI5bMQK3YaT014IKch0v1/dKf71L6Y+oTD/IefM8NsGfsQX+gu3wV+yNF3A0XsQwvIzT8QquwKu4Fq/hVvwTD+G/8Au8jt+gqzKWKLrhZayEFZV+h3XwNvTCKtgLq+JorIaxWB1nYQ2ch/VwKbrjS1gfX8WGeAgb4WFsgl+hJ/6OzfA6Nke27dICO6E3+mNrjMa2GI/tcQV2wC3og2/gnbgbO+FR9MM87IKutLc/VsJu6I3dsTX2wP7YE+/FQAzDuzECe2M0BuGj2Bcfw364AvvjMzgAd+O9uA8HIsedMXfl/oLcb6ANTL/xO4PK1FXOU92xCQZgC+yB7fAu7I2BGIp343gMwqnYBxfhPbgSB+DLeC++iQPxYxyEp3EI5uNQ/AmH4W8YglWo03BsgCOwK47EwRiKE3AUJuP9OA3H4tM4DnfieNyND+KnGIanMAIvYiT+E6OwNsfHgHUxGttgDPrgZOyMcdgdE3AYJmIoGjEOk3EOpuICnIYrMR334EP4Js7AAnwEL+BcrMnxeAxb4zzsi/NxKC7EUFyED+BinIRLMBmX4mJchstwOaaWMJ581W9udjHl3rPt48oZH/B/Oracse/+K+LLt+y99THme+gjp0jXSF6/MxYbKZw0g7SelE06T3L/wxlj7pyck3NyTs7JOTkn5+ScnJNzck7O6X93ujXx/xEGYznE/yux/cepaWfLeGpy728jNsDVWEWJvX/JFIdkjusfcu8Ay5hx41FnmsNzbOrQ0xSf4+FS0RQn9N0m+zghLzf7cY3qkggdshlHLcVgiFKNo4bmZaxnjRVS3psdFZ1ifXfpZsv4Z8pasv0seSd2rMzvYD6IHZ0o8weYT/RQ8pjntzBflf2fmJhqmt8o20yeai5jj2xPXo9qM+7gKXne047kSmpDqs62jJuLGHdwWJ/+IS4ljyEvj3HoTO0n6xkjkiMSZJmnrGeU9dTj7mXIrZ3V7GMDXIA12bes4vYtLCF6kl/p+07LV2/OGHwl3XelTC+Ud7Ob1vGWeWWPlGUeqv6j9E3p19JP7PviDk0s2haJNYuKlP5rnVe2ZF6WJXkMMqhfXemTrCefEds+GF9J3oMmfbADqRYVL3jV8fiIcqRuaR/UjIU=
*/