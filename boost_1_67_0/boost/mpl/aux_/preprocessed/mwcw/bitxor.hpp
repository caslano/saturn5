
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