
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitxor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_
    : bitxor_< bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitxor_< N1,N2,N3,N4,na >

    : bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitxor_< N1,N2,N3,na,na >

    : bitxor_< bitxor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitxor_< N1,N2,na,na,na >
    : bitxor_impl<
          typename bitxor_tag<N1>::type
        , typename bitxor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct bitxor_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 ^ n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitxor_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* bitxor.hpp
y4tf5bJzkGLEvWTMzU1cxebili5I5VT88Xwm7unFYajTWnY9WVbYk2rVIuiDmR3N0eIpYN0MmVqZp7T4Y+FpdXDSCAMuPWnxfdO8uiTXGom/QzLk4PxS45ETiG5q4jNbvOuJO/W9qe7GEXKIhVC2aLVJBRw6wRgdEtQ7vGvVK3UAYSaHKkgXkLfniXfg74e85uHOzi0zyavyGXPC7ZSIVncXJqdv0tuTutpo4UnCNSjYDXZQeJnd7ntn1jC0d5lhEjz5pWnD8OZR1dz5ca9+3fQThyuDK/DsSQ3RIvHZTCBeDSYJpkRQlnRluEKw+KeU9UauPud1vk8kZy0aNqOAvrtgnC4M0WD5LmxBDNwg61xsUbz3GA1Pw4J6v+U4/dUWczmYuIvI5wlP12isSCVLYwV3n0JwSZBFl9s6lisZHCcbR81ujb5v8kmneCDOucG6wTqtq+lYVlTk4rd76WcFAKyOJ374eJikq8w/fV76aO5t/XghRdaCFckFB5W5vhU1R2Dd9Q6cwz/xO/rIdLt6lNqYz53J9g7H/Vj4QdInXRCuITjD1wXJtrXk7QsPOjef+fHs1WotvJRUWSVTDCQumPrqmiYvb0NW4S0p4RXLC/mOwVfqHtTdsvzWiKxIIupaDcshup9YFi86u13JtOTlC0gZ4+GHP4iYFGJjVZCbVd1+MzQ/qTDDbR3zT9ks8iVSX31nD9cXrNA5mW0F
*/