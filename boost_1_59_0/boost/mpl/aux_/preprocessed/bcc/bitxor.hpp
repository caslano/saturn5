
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "bitxor.hpp" header
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