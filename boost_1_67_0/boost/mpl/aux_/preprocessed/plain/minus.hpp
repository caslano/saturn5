
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