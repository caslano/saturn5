
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