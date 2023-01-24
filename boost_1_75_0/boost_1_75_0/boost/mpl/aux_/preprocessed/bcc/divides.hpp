
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
vC2HUlhvVUiKG1V98nbBchH7eIvqryWqvTH1Nfcb6gy9Cv4NKt9m9Xy1qsutib/Gij9AZVlmPabwn1Bt/wkFF9tVprLraa5F+fx2xadLVPseJ7yX0PhiPNaSbNij+OVB1a4HFW0yCofXW88WwKNN4bhelUHeupBraYP7WrpvpHsL3TfT3U73Vrq91H0L3Hvg3ld3H1T3YM09Avc9cN9Xc49Cax4EraDZXbTuR+B+3LqfUPeb6X4H3M/SfbrJ/YEG9w+o+0es+xNwf0rdv6fuPzX3V9X9N3D/g7q/Ye5/o3uZXCavgPuVdF8F93U1t2fdu+jeTfctcN8G9351HzT3IXPfbd2zqfvt5n6a7mfhfo+632/dPwj3Wbo/Yu6Pm/tn6f4lc/+6df8e3F8291/X3f9s3f9p7m+Ze4mTvleZ+1JzvwLuq6z7+qb33ib3nXX3/eb2a+4i3OXU/Zi55awze8lsy+yS2aWzy2aXz66YXTnLcYv5X5fDXzqkoemY2pRmJWQTOCtnV82unl2TSqnNma4rSW0GrXnbW5rWU59uxzRLTbe2cbtr29GoZKN6lzSkQdIvjfBo3sLm8JvX1zgl3f9p3JqXaJaneRubccfCPb0wBs2oiDPx5bTOX0ez3BrQAlwI18P/W2AGOyreC09+t//3YHbsBE1vO2gIu2BW2QthDDTbfTDz3QmzYh9oK7fDfH4QILiwQhoUl8jP
*/