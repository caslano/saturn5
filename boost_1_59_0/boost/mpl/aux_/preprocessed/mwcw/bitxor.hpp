
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