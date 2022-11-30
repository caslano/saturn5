
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