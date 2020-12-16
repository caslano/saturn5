
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitand.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitand_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitand_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitand_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitand_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_
    : bitand_< bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitand_< N1,N2,N3,N4,na >

    : bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitand_< N1,N2,N3,na,na >

    : bitand_< bitand_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitand_< N1,N2,na,na,na >
    : bitand_impl<
          typename bitand_tag<N1>::type
        , typename bitand_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {
template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  & BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitand.hpp
6efZ/4cOZ79/kf1Y7bPvIf1UsX1o+1ICafpy1b4szdjy+5S+fE2febP0HWahCUi/K+mSsdCKWyXpWok80Y+0LfFIlyXb3m/oUx+zpE/TJ6W1Xcatu9mKXc78Pi52zRC7piEHaAg1L5P9/GyWIrWLrBX2EL/WHvoEnX1krjxH0vKL8mxebNTm3Uzply8UG/ORn5DmY4mqjVZlzIaagdKpdaF5526Dtl/tnNjwhNjwGPIAYc2L3W1gIIbEj/4W++w/W+zWnyr2pBfa7HVVjgsL0jT2yZgMt3qYbmDzMcmA18TmV5Aj6Ktd6m6zrYB63er7yVG+NkVutGYAXb+vdYxrvkf7DhyPdc01GI2FxH/esneMFciU/sx05KiShiSDNFgKbQWt6D91TweGSzqknorfDak5RRlueXtS7CqRvC1G9qEv1K1Oqjfzd1AfS6WfP13iT0EqCRu1xC1+fqzOyPOhPhrnyQJiU5Q5nyVSdlkav7MGdjbD2ku89QV76zv23kccH6D4x/w9YnjimZI7qmYsD27suGW9977jD9XrX3sr6bPHcvqf/nbH/rh3hzzzJf1jlyv+1R8vG7w75WCXTZfVtOt95tEj9Pupfc22fnd+vWHBnuWbRi69PzC6cwOZE6z4n9qYvu2RPl89e7rXqg9PlL0y8vvrmz6oxlv26N63P3kjKmrDG4uKs7c+0vj99Vl/X33TUWrf9MRPwkpGVD330zcLrf8M2tbxbW996G3bZ11qkvcReAuSJOsV2xDF3SB9mMWwN7wRXglvhtGwBE6Et8BYeCuMh+vhXLgBZsHbYA7cCG2wDN4IN8Evodkk7w9wldjREcaJHWvFjhyxIxdOgPlwJrTCZfB6uBIWiN6ZJvn7D2eI3h/AGNGbJnrT4SCYASfBTDgZrobTYJazj0b+VsNC0afto5kl+mbDEJgAw+BcOAbOg/PgfJgKzTAfLhT9FSb5OwyfEP3dYJnoHyP6x8MB8CoYDifAcXAinAqvhglwEsyEP4RZMAZeD6+BO+C1cCecAvfCOPgonA4fg/Fi136T/K2Fr4ld3aFjzNVmsetOKZ8tYs82OB1uh7NgBUyHPxJ7dsA18MewAN4DbXA3LIV74BNwH3wK3gefgfvhC/Ah+AqsFDtTTPL3FGaKnZ1hoth5QPrQHoOd4UGxu0rK6Ql4FXwSzoE/hRZYLXY/Be33jfx9hCUG901/0TsQDoaD4HAYCkfBwXA8DIOxcIjkTzhMhkNhCoyA2XAELISjYDGMFDusJvk7CdPFjstgutuevktgEFwKB8AkOAwugyPhchgDr4NTYTKMhyvgddAi9qTAug6uvsSKvR1b7E8M3UD/1Fz6yhBH3+LxDa7+xfB59Dcpx0jcPFd/Y85t9Ichjn7HA/zOmYceXf8jcptnH2QkjEWaORe4kf42pBn/FPyy+F2MlMxHFzTqp6ze6OqrbFCuhY0cB5m5vow0IbFIOlKJHEOSzOiVPs19sAm/Q9vbm04g1fhV4VcHgzfp+zobkNJN9j7PA7AG6bDA3v8ZDhuU62939YUm4FcOg/CrhNHQvV808Xbic+sfLcOvnt9nkQBeZBqxy9FnWsO5RNgAzyHFk9F/B+Er2tOPShz8joG7FD38Tua3Dank93HE0cfayO8Om119rRGbXf2tWZuxiWtqkWSOm6FH/yvXHN0MOW6E4cRfpvgjHe4kLngaCUi098/GcD5G8ed3EozE3wrrOd4Jjfptj+JfAhMSiRemwDLE3o8LE7kGmu6ijJEkpC6W+PA/gZRy3MTxYRgwBXvwq1F+LybvYBS0KfnGucTFLff9Bi3heiRyC/Eo/ktc/cAV8BBSh5i36PuFA5bq+4b3bXE=
*/