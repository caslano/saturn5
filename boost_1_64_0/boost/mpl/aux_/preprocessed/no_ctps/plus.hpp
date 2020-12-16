
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

template<> struct plus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct plus_impl< integral_c_tag,na >
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

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct plus2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus

    : if_<

          is_na<N3>
        , plus2< N1,N2 >
        , plus<
              plus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct plus2
    : plus_impl<
          typename plus_tag<N1>::type
        , typename plus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, plus2, (N1, N2))

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
jpic5Hhdz53mXlsnn1v5PG/Pd21dOblmrzyWwLuwLlbAIKyIwVgJpTz5LPEZMyjvXimvppTngw+gL4ZibeyEdbCzh+m649+MlavryQo4Lv5vv54s4gZfU+a5ievGNqnxcBUqVKhQoULFzYl/pv9PD9J2CcDf7//fq+v/B0n/v4r0oSux9NLm4nslb/9fW7sr85vp+8yl9f1/XX+5VL5+sP68ZC/p24dKvdqz7PLjPCWDekWaB7q9Xtq59okJKZxClHeuKkua9OsN+vBjbHVjDpl84xTHpC2+0hYflihes1vfFq0hLmzf641TSDscbdO3oxoHLKtztCMj97H2KhmfcL5fTsj5pBHSlu4sW9kvpfTjRbJTXDlebnR78u/Pavb9KWXXMNifraUvHe2fdxtMN5gbcAfbYPw124BJ1TLSCrwNdOuXbeCYD41p4q5ug73SljTdNtgrx6ZW79VS7xg1lvS/HEu6L057/qt6hT6wVPrxs02Jmyuej3mlvXvHkvy1Rb7PqrBszzf/WUkZ+ymFlfBOx5iRfEdjaAHHoOphBWyLFbE9VkKph3xP8v1pUI+qUl419EFvRz3kOwkjDOpRU97nI/WohY+gL4ZjbeyOdXTljf+TsTU/Kc9fyquHdbE+BmEDDMaG2FuNhamxMDeOhU1gHGw5y26Wsyyem9W4mAoVKlT8E/HP9P9TebF7+v8+tv5/yTz34mtRhL4DNkWzdk3tMJknmlXn78tU07fd4Pr/ZSPt1/+7t28j/btr+oWV8/UL9dfPh8vjSzyW9TnmFNDPt35Mdw1yObne/iW/3GvY9dfl/yLvS5R1n+Wxbi53mYNad61+vv5zDek/Z7IUZ8mQ/nPv0bbtre3kyKsbveDzgv/7+s+522qnH2WZ8l4Xvy//fQGl/2waY7AN5MBzZSzBHcca9XXMk/GMXCMfVljuH4jaWJS/cX35V25d/a8zT0aDsfbPiWvnzejHqBJSIrUmyPknjuco0ck4lRyfsj30+8kxz/oxOcb1+/ukff4HeXxCXpMuj3c75qGX+SLkM8BF+f0jbavOO/cFnyuZ++Laz09Ovs+Pfo6OZHnNPnlNjFRSv7+2yDwBn8hnbI+cFzRrXP79JScHybHldZ39FTTevr8K/rm7MecL5Zkb37FPtc8xWyzvZ0+33bV1yTZ2zLnA61lN3s9nkHQf6sm8MHVROyds+Xjj7Zd7xBfsmF898a8d8wU7V4xjN9/3/gGDuSXk2M9zPGbUz3ec647Fl+xzs+i+3/Pfv+OwvZx6cnza53TJiNYOf9nm1x7XJ3THtX6sznhsyfUxOVfvGWA8hue+uQpcHXszHrtyPiZnPMbmfEzOeOzQ2Zic+8YsjcfqnI/R9raN+TVeuOuV+y9aGta6PKXB6ek1B+SO1R3wkN9r8juulEfu8b8T7edplcCaWBZ9sDb6Yj2sg42xLobh/ZiIfmjB+jgMG+AMbIiv4YO4CBtjFjbB3fgQfopN8TN8BI9ic/wGA/ActsCfsCXeTuVboTcGYk1sjQ/jYxiGQRiOwRiPIZiMbfFZbIdjMAzHY2fMxq54ALvhEeyBRzECz2NPLMG2isQyGI0+mIDNsS8GYiJGYxIOwmR8GtNwJvbDNWjBdWjFA9gfL+JALFGI335YBp/Asvg0NsBh2B6HYxiOxFQchWNwNI7D53EujsM1OAF34EQ8gZPwFE7G2zkup2ANnIq+OB0fxBkYizPxaZyFQ3EODse5OBNfw7dxHq7DRfg+LsYDuASP4VI8icvwHK7AH/FNvIXjciUWx7ewLK5Gb1yDdTELm+BabIpvo21uE5P8Pka2ne34LooRuntxFMfyWAXvwqZYAVtiRQzBStg=
*/