
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