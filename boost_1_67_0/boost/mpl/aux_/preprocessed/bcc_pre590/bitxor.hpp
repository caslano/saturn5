
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