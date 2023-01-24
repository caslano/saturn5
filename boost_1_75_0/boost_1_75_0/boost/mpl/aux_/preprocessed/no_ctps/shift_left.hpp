
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
lCWV8ruUAeKEoqRIgHetUnLaRpKa2XDn6tx/iwNm9wK10XKnzUIUwkrH3shX7OJ95ki+zMbfIsuk21Sx+mHUbTkDH9kFG4ZzVlpkQBdkxexgvhVz1srVz1rWLFrlNsrNzEREx0yvL5lEC3GWXsutm5UlOp8+7xCzUvw8cK2XqyLmR9eKit1mqsescCCh+G33uU5uXlW4EOnYKJoHPne1UK8iPQ466B+KtjRidQsdG7UwYr/G5aqdEpQxdqnDoV+j03rHj8ba70ik/emabj7Mq1f4Uih3T5bmavEbh6BIPQ+YR9ZsKVSCMsHvs0LNvbxrSYOWGxRzmoH8d6wZkTT/O1Uyk3KVh9gPw6KuvttrZ3tuGQtdbgvOiPAJ7Zn9WJoHCbajI1wPQM/dS/HPR0pbnGpeL+KT2qLvMcofI2p/tCXZvDliL5Qsaw9PULnDxwpr82qVKfOL2pFYUxahe4OIllizNiA8UtqRLTjjTf/Kf311XwhX7rjqeM9eO9dB6UIXOl3fCuYglMF43WxefPbx/uykjkhZx7RhUhFHSJXbJP570Q5lb+aIKN8j5vdTAvm/IdV1R9+IWxTJ9vbq31BvZJx4YZpNe8OK7eFF9dNl2AvuwqOk0fT5EfouM3Cy2fNVBC7xpTeQXc1+62t1GH0TSdysXhR9U4Mcfjywyl8R0sDxgjocsdWkcZ8TPuof6ffbfVBm7LCTYJAPq0Rk
*/