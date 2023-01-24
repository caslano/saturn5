
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
xvcq5bYbxYYB1pSZfD+0Dk4dY1WYJVk+UCk9qC192cgzTLRbOM/9xcg68xgpQkKC2KqiGj/nnjMUkU6QaM/aXWxmm8FxX3Si39/UNFvxEOnvpU9TB9JEtYcr9gk1IAUhCClgf2Lsw+r0KKoXTt+tLi1q6qq9oLcvs0XizI94g3D2KHZtHXCW+K93dgCtbS0rI6qubGcOz1FWUx7CD6okEU63D9PLJF95Xl02H+cyl/Oso2HRoMipCdwwfkWntI2hL2SGtn0fNOxCleaeY5KZT3dUXM8NDETkkIFUDnN34IlDU6dhF3Cv62Mg0evfx90kjDfU5SPAwXEg/8+0XU6Bf3oqX50cLW1cHf7NVPnwN9puswQbzTtcIvaEpH4EDNyF22QWjAXRA1qOzI8heX8wIV9+xKz2TF3T+fJHrobpQued5iiPTUqjTlk4r0P1qOcFr43ZisMir8P6qMN+ic3CMj+Nh+7isGPvsg2ZE+xl9VdjNUHJ0UsyZEpkJ6vDDdTxIHx1ntv18kp41Ps4T09gVBTSHDd58lMe/+cksxmaZCW98jiIjytLvpUfvAjBSwuAW2J3xLQlm7o5MjOEr36nCV8VzNO/1q8rqfWZJ738xeb5Rt53HLm9RC2xCCDErduOnyqPXi7cdvRE1tEX0MoQqKj5cLQoOtPbfr/RQJgZsTKbYnG4JO1CgkwU8oAl40KEK1A0TIv+ZI0KrfrW
*/