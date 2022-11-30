
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