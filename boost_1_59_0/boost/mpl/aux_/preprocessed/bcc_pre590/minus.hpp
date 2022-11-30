
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