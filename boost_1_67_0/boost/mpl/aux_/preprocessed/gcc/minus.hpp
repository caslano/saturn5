
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