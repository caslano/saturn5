
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