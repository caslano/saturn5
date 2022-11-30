
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