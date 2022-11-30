
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