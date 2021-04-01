
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
PjeNnVAjsba5psxaNoqXEGC8ROoVz/UPd9dyojcrIMG6BzsvmdeJty1KuM90OKE0zl/6qC4TE/xWZvJMLaADHyfBPpY7uH3Xj+Zj3zePmt25LkqYHnA9YKqA2n3pWV8I8n87SxmY+6upIK8wl1Thvme7i/7+5qgaYAkuIefH7S06WdyRCrK9pUAOWP3SGfQyuTj5+Xy6qZ0Z6F1RZoJ3BObF8JAyzuaeOU/rlzFfsMdOQPGIk3UgoIRHZnNrB03Ypq7CyqRUQsz6I7/crbY0jgqV8IIxhnZ/0kTzje7JVeCvmXj1SK4wLKvpZuHO++HOsQB4ogHDa376xdQGZe8kuGldGkqta0xUlk2+p+zw8z8+Lyq8kpaP5zcYB6GAWsKWRXc88zsAgs3yiuFk9z6lysAHl30yceXodN4TRYvDJ+9jPRMPH43XCpQ4Jy02MBCjgA24z62gGULwjaA9vZBduy+7xrUnNLZZEYeZvADVnIbPs81+H1uM9+60rE0ZTUnhT4oBuOnAbq1esVmwnSGf0De3XrVQ+uRhuIGn42fBzO+ZhTMCD7yv76SOBw==
*/