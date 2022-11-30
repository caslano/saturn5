
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides
    : divides< divides< divides< divides< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct divides< N1,N2,N3,N4,na >

    : divides< divides< divides< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct divides< N1,N2,N3,na,na >

    : divides< divides< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct divides< N1,N2,na,na,na >
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {
template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  / BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* divides.hpp
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
*/