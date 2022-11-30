
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