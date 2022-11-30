
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