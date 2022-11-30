
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitxor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_
    : bitxor_< bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>, N5>
{
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitxor_< N1,N2,N3,N4,na >

    : bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitxor_< N1,N2,N3,na,na >

    : bitxor_< bitxor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitxor_< N1,N2,na,na,na >
    : bitxor_impl<
          typename bitxor_tag<N1>::type
        , typename bitxor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {
template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  ^ BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitxor.hpp
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
*/