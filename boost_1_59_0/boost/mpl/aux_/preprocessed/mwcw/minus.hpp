
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