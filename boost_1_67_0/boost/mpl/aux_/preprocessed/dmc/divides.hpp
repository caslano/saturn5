
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