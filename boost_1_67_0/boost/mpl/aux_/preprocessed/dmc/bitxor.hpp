
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