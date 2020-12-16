
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct minus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct minus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct minus2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus

    : if_<

          is_na<N3>
        , minus2< N1,N2 >
        , minus<
              minus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct minus2
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, minus2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {
template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  - BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* minus.hpp
xa7oj92wFXbH/tgDB+PjmIY9cQIGYQb2xrcwGN/FPvg59sWvMQSvYT8lX+yPFamzAVgNB2IzDMXWOAgH4GAcgmE4HIfjeAzHyRiBizASl2IUbkM97sZo/B5H4CkcibcxBl1caXdYC0djPYzFThiH3TAR+2ASjsRkjMMUTMAxOBefwgWYhhvwadyCY/EDnIgnMB1P4yR0K8z3LhbDKVgHp+IjOA074HTsgjMwEp/HkTgTZ+AsfAHn4Cp8EdfhXDyA8/ATXIDncSFewEX4EO13MRbHTGyAS7AhLsOm+Bq2xxX4OL6OQbgS5fxJ4hs4Z9I4f+rjxipjX6yFIWj+3Hr5nLfG5wbK50KxOg6Sz3m4SH+/xAHwOeO9P4VRmd6We2DWoye+g1VwAzbCjdgUN2EHfA+74mYMwq3YD7fhWNyO6bgTn8Vd+BbuxnfxA9yCH+IJ3IsncT/+iB/heTyASqE/xkJ4EN3xENbAT7EmHsZ6mIXt8HMMwK+wKx7DEPwGB+C3SL2wvtJ/L/36Sr0o67lC6uWK3KN1FT3xOlbD37AO3sQGeAtb4u/YDm/jIPwTh6EL+Y3CQpiGrjgNC+PL6IYrsQhuwqK4Dd1xNxbDz7A4XsMSeAtLyvqXwoexNNZHD2yPZTAQy+IQLIfDsQoasCqmYzV8BqvjK1gDt6I37sKaeAJr4WmsreSPdfA2UvfG41J9rIyPYENsgI2xEQZhYwxGHxyOvhiBfhiDzTABm+NYbIHPYUucga1Q7g2T+AA+K/uB+t6wJ+X3RyKWxSSsicnoiymWZ/dJPz8aZDnqZ/elynLSZLs/LcsZi21wHLbH8bK9J+ATmK5jfXAyxuMUNJc74y7lHiX5jZZyx0p+cVLueFkOC5C+eb6jZH9WyndVlvOBtNsPpd3uxSq4X5b3kbTXA1L+g9gbD2E4fooj8DNMwcM4FrNwMn6B0/BLfBuP4Dv4NW7Go/gDHsNs/BZP4XeYg8fxL/weXSj7CSyK2VgdT6I3nsV6eB6b4k/YHC9Y7i2U/nj01DgeXpb6/FnqM9fyzEPpR8dJ8jn1Mw+HyOeGYil8AivhMNnvw6TehmMQhst2j8BYjEQD6vFpjMaJOMLcDlykP1362cnfeJ3WH5Vpmmy/6bL9Zsj2m41t8QUciBlyfJmLUTgPE/ElTMX5ku9CfB4XIUm3GJdhJr6OS3E7LsM9uBy/wBV4GV/HK7hSttcbWB/fxEa4Crvganwc38JRuA4T8G0cj+vxDXwHV+FG3IabcAe+h5dwC17FbaijfrZjCdyBpXGnZX+S/nYM1tifVrmatuNqbIBrsQmuQ+M9zijtiP5x++3oXVnOBiyLG+Vz7pTFVz6XLr93jMd/2Y5b5Lx2Bxr7eOS8do+c136ArXAvdsV92B/34zA8gFH4MSbiJ5iKBzEdP8OZeBgXYxauxs/xffwCD+CX+BkekfPbk5iLp/Aankbl+/UM1sCzWAfPYTvMwU54HsPxJ4zGS5iEl/F5/FnOa3NxLf6C7+Cv+ClewS/wKl7Ba3gDr8v57W9YRdkf0BtvYlu8hR3wd4zA2zgCdYU5DqELzsJCuApdcR0WxvXojofxITyCxfAaFsffsCRWYPuVwopYFpthOWyB5TEcK2IcVsI0rIzjsArKWAjSx813pRyX1WMhPC+/f2eiJ86W378Z2BLnYEeci91wHg7Al3AozsdIXIgJuAgn4GKchZk4F5fgS7gUN+Ey3IzL5ffzq/gNvoancAXewtfxNr6JrpR9DZbGtVgF38LqyLmyjMUh/dvYVvYb9VgcIXLPcj8si/2xJg5AXxyIrTEU5fuY/mr738dDZHlDsRo+Icsbhm0wzEWOyzgIw13kuIw=
*/