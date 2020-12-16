
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
    >
struct bitor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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
    : bitor_impl<
          typename bitor_tag<N1>::type
        , typename bitor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitor_2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitor_)

}}

namespace boost { namespace mpl {
template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  | BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitor.hpp
pD4WS33cCYvgXbAa3g3nwiVSDw1Io+T/nOSfCBdK/udI/udCOzwfjoYXwLFwIZwGL4az4CWSfz08GV4KT4OXwyvgFbARXgkXwWvgA/Ba+BS8AS6HN0Ipv8Rn0KlT/uFi30gp/yFS/mwp/2iYDw+D5fBweA4cA+V5c4mv0HaSv/q8+bZyPtgejoCJcBTsAyfDvjAf2mE57Ae9MBmeBlPgWXDH0HlC4i1giM55IkP6wVCYADNhItwbpsEsuBvcJ9SvkBOM+/Hlkt8VcAd4pZKO+IhhP26QdNfAAfBaJV3dCcb9+EZJdxMcBBuVdE3t2HmrpFskdt6mHjft2LlY0t0pdt6lpLPNN7bzXkl3n9jZJOnqtLSS7lz+NIgPvFbS/ST97RfYD/4Gx8LfYR/2/QMOgRvhfvBPmA3/gmMhRtTNgFvAAtgDngp7wjNhHMQOxjrib4e5YocWQnOLHVOlX5bBfrAcHggr4EQ4B86BlbAOVsGl0AtfhsfDVlgNc8i7JlR+8Y3DF5DI8h8r5c+DdjgLjob5Ug8OmAud0Ald8ERYCM+DRfBi6IbXQA9cDEvgs7AU/gjTbeLvhr3Ejh4wVexYINfTU5T9W9vZf57sf4JynfHJ/nfpXGfuk3I+KO38ENwZPgyHwEdgJnwMngMfh1fBJ+DtcFnofkN8xfBYnfuNL0XP16JnHdwDfguHwu/gUfB7OBX6YKCdxDcM79dpp2HSP/aHI+ABcBQcDifDg+B0OAKWwYNhFRwJz4aHwAY4Cl4Ls+FieBi8Bx4Of4R8Jz5iyil29IHXix2Py31sMxwAl8Nd4TNwP/gsHA6fhznwBVgAX4Ie+DKshK/AOrgSXgVfhTfB1+Fi2AIfgG/ApXAVfAp+AFfCD0P3xeLThWN17ov/FnvZAXsB3A32gKNhTyl3GlIv+Wwv+WwB7ZLPX4q+JtlvTx19W8p5aCuYCOPhTrA3TIdbw2A/8kk+I3X6Ubn0owrYD86BA2AlHAi9MAMeD4fD6tB9kPhSoV3nPHm6HDdnwD7wTCjlx1dqXP465fpdJ/vN07l+j5N+egQcAcfDkXACnAgnwplwEnTDybAaHhV6n734POHFkr+67n+q1O9AmAR3gv3hILgP3Fn0DoaT4S5wKtwVlsLd4Mlwd3gKTIcL4R7KdaZV9G+vU3/XyjOS18Ft4fWhfiH+SjBBp1/Uy/6Xw37wCjgMXgnHwasknzrSOSWfrWScMJT/a6G2PST1+zC0w8dhKlwG0+GTMBM+BQ+ET8NDYDMcB5fDSfAZOA0+C2fBFdANn4eV8CV4BnwZng9fgZfAlfAG+Bp8DLbA5+EbcCV8E66Cb8Ev4LtSr+/BHvI+i23g+zAJfgD7ww9hKlwNM+FHcBj8GI6Dn8FJ8HM4Ba6Bd8Ev4BL4JVwG18Ln4FfwFfg1fBt+A9+F6+Ba+C38DiJ1NnmfRU/4Y+g+XXyecDoS2c9vkvZshHZ4CxwMb4V7wUVwNLwNHg3vgFPgYhg43sSvCfshzYh6vL2m7Fcn+yV1sF+jyfyaTe7X2sF+DT34ZyrP/iHZSB4yH2lAHkVWIax/xEWYfZA8/p8E21sLyZsb3+XrIdWTZ3BNJN/YXt26LlLKW3H/2tpISx6Lfn2k9tZGqsB2dX2kRdTbCmQtkjAt3paBTEK8yBVIE/I2shFJnx5vG4OUIguRJchKxIekHEs/QNxIPdKErETWI/Y8fkOcyAKkEVmBrEUSZ6ATyUW8SD2yFHkb2YCkziQtko+chSxB3kY2zrSeRbU2a7M2a7M2a7M2a7M2a7M2a/s/bd27/l9lCdPq8msLHdU1Lm0VgM6tAaA9wz8/E5v9z62TpTYlusLj//4kJlisZ0I=
*/