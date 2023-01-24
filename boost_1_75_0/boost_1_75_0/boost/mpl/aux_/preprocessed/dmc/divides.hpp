
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
sP5+sHlMHu3YDZjuz9kN41Z/rhItHyMrC2HpYakOa0uTDYapY21gPUYihH65Lb44H2jHlniao5vqDW+gwBYv/zjuwL2fabSvVwfZf7fN1hNRDAPiP9ATtC0eVNXZOGpOnn1vA9o9+Rg4KlbfvWfi9a13O37otik50OtsPqLbZlS+bemFVOKUa3hW8o5UIHz8Lpq81gQ7OvVMXHq8ZbGoLv04f4DDb6prmDjR6q4smjaisB+GcyJiNDxGoWFx7NMsewPPxOIr3jOWrf9cVP8QjUvPkTomTRlv1r/lnvC3rvXtia7ZcJGHYH1MzaQfclWjl9huVsrNv69tQn5WWjFP8lrN4U5m5mwLjlClkWQ652vfIsbfK5a1iZ5W62h3fq6caPs23lyXMs7WNN6+fX4fgbpzVft856KQ6dmyVrSa7YFyGb/1ocMfPXZyUkLbRrLaUrHcO61h4rWas/1zKDZqVZvdT7v3s80zmypFn1c3ndBiapPzSmkkLYYc9rIO3CZvmxwy830tMv08gmBgwcnBhbKbajPvyvZZb2bOD9yWmZJvdT3PtmrviCu+61fuZMI+Vws1XCscAYczvAey35l16lVLtBx5yUUCnq6U2LI7AnbnjqrGNgx7WVzl1PKEvY5aCAGQe1S6Hf7ADytCIGDhXk9kxVecsNErq0v01CsRVt4FoQ3hextJcaJ1k9DKfRQhG6T2gHSm7LH/PGdL
*/