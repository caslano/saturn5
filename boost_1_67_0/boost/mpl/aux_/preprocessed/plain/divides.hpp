
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