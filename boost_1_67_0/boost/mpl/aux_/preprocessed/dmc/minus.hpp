
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