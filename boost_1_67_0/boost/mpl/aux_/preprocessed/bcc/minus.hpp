
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