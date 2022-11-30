
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
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