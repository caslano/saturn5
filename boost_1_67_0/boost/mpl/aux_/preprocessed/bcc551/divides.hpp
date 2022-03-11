
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