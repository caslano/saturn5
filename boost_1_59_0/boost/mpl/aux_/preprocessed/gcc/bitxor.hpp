
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