
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
piLTybt0mTJQSfk1dJpm8UgTC7XgT7KFs+GCxbahKn70huece31ZQ550HMlwv26OFqBjwMxRw5jmgJyLjnn/DOk8g6r1hoVbymJlZaYtNvnnpITuWYcjzM5RoO7WsUJjH87Ked9ytcODXdcPGaPiCdc//95XccBGPnqRejMDnaxK6d2oSaTzmuN7R543uTqj/MNExoqcnYlW0JfzVn4YPmuXZsVFctJU+mE6cmkq5/xRnfhvi0atOIMaYGJdU3uNfmrD4Lk63f7CQTOJf9lcUDefd9wrEtYK7ZHKEnaRLKv88P1FBePXIL/XIJ/XoADaVKji7JNLfU1CPXs128NKmTTwV5dbmZid05H72KJ5TeGQgPwgXCZDCAmmknKUl60PCHTQ8HAyVxic6paM0/tDwfBVReXMYzggG+CT1HzBp9tEIeRmCfFvE+6lyJenaCCo1WzRUfDT9nOPbT7pzwdxtTu8anyl2FYBPX8GaE5k+nhXJ/kVlYtrkK8ANgzDXCOBJuUXkzP7v8V++DtdoLpWqyXckChBmJgzLTPgbQcdFDS9dxYvejQ6w2vkI2dd0us1V8GqwoJit/EilVd0FsDvQJ29M63LyYHdXCjTpTSIoSYnwd8DuJDmqwTiNkmtmZycmCxr7AbrOpIKaO8MmhOL1LDngFCe3TWy1kNcP9AcYg99QOSDKCrVhnlMHTE3pt7mPyvb+OYznRWASwFB
*/