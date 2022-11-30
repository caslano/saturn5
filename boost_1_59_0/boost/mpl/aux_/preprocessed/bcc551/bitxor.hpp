
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
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