
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

template< typename T1 >
struct inherit2< T1,empty_base >
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1, empty_base))
};

template< typename T2 >
struct inherit2< empty_base,T2 >
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, T2))
};

template<>
struct inherit2< empty_base,empty_base >
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, empty_base))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , inherit3
        , ( T1, T2, T3)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , inherit4
        , ( T1, T2, T3, T4)
        )
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , inherit5
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1 = empty_base, typename T2 = empty_base
        , typename T3 = empty_base, typename T4 = empty_base
        , typename T5 = empty_base

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
Wc7wmgL6Gs7eX1S5sS0sve3Z7G4KFucoNXPW4tcdrzBU9cgaA2inlkmlDUncZ4zu1i7a4NTWcDKnVGF5VxiqH+vfVcatAy4eJRSEeVoiR7+baQxrVKPNDQnljrBPRJIomhkrlqbs7Nh80x3TAGBbG01rEYtw6PYkOwqM1nFY8X4idiWPFUrvl1lU40z4YiKrTa7b/2tBT6ObafEP0B+zVUk2X6xN7tvukB6xjoweF4VHdsKKyT6HHglm3SYUJmQWt/+Bg+jKuQ4lF12i0Hq6Xt4GsL5x6SlIG6EIfvcDgM19FPsJMDfr8ZmO/93L9tETjCNd1+zmweRXuDZHKSG5Pl/EHkt5KoGRRmr26O43DRq42Xfqz62FgSfGdnPhDjgtv06MWMj8iFoieNJO3y56vbl2NbypsrX5PLWzBJC5iJRNgYzlYXpOSJiJtgMXFMz65V7a3z6PjEGNDQBgg9zFrJxXn9uDqz/fZ62MuutXzwv8vp3G64pw5uGzmg+B86AcaFrK1p1ZRGl97pLrmESOUV0Mp39J2grHPjsjKWpGmBCXGcBrBad9DoByK8tTPqcNwisHa5gw3Fu7N+5dij8a8XzJezIdOPDdu6LkVp7BqY2I1dEiHH68+bl37e4svampTaA5Iz39qItP7yqD0aqkms0sujKrcZom2+AccisAyu8w33s3+quOn+GP+9NyK9KCAz1tV570p3alp1k6
*/