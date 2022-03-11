
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