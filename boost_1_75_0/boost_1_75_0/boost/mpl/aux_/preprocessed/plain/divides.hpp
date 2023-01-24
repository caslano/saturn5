
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
3q2ypl8ocPwe8pB7CcfZG6jpE8Hv4F/w7uBMggeuKWzCRQQzvJugsxwPZ2g/05/gu11BZ7GD3b0KlTFOUX6Rh5smkmEbXYOPzuX3d/H8SL/v4c6Dt0sVHPc4b+Dw4qfcmLIta7VUliSBRI75TvmbnknvipJguFDRbdvv7o+3V9VOnl1843DwDzwICxHnQ/ds2dgXfJaKDZ1buM3Wr6XZOg4jnfYc5UblkETLjdxJbTGNfTiFOlwNbdtkPaDM3sDf4M6d2XkY81hEuvAJjvOXno5HQxZ+xv5fL4hp/8sL4n9cv3ZysLB0/cdk3JtsUUvEq9FeiEmgnlkA6MdEp56lW9+YAqABylUYWc4P1TPSK0dtq+gpUNluzcfyC9jruWTHrrTSxFcdvQknqHdAd6EHpNDS0yNnxBMgFr9bQZSjZ45v/nym/vYSgcY2BRIwZncTTf2AugkVgqQ/8v+V7fLrhh3paHddT9PxADNLvvVqSjrtyNvqiRFrfBJHDhbfgwztuhq7nNJtMuP/le2yn+N9wL1iY0FJeaUQbNmz2+O6gb4hLyUgpDmh9pJ0HsjjnoDsLPuTtR93lZM7gDGNp5IqEDj+GN9dU2D4Q4SuYrXkDU/1MiykDyN6lqsmWQp4VEKNhVTw1UugiChI8m87qoVx4KSyeFfTSV8+sHu9gnKlO8Z27ssGjp5ugIbEuXJIRuTMDbfVaXrFV9ZQ1hQp
*/