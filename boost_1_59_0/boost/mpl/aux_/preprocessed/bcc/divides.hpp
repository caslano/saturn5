
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "divides.hpp" header
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