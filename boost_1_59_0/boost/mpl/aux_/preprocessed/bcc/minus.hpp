
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus
    : minus< minus< minus< minus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct minus< N1,N2,N3,N4,na >

    : minus< minus< minus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct minus< N1,N2,N3,na,na >

    : minus< minus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct minus< N1,N2,na,na,na >
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {
template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  - BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* minus.hpp
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
*/