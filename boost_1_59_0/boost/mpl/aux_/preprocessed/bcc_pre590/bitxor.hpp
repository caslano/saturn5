
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