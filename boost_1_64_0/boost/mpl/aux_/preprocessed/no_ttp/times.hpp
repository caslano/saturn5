
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct times_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times
    : times< times< times< times< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct times< N1,N2,N3,N4,na >

    : times< times< times< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct times< N1,N2,N3,na,na >

    : times< times< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct times< N1,N2,na,na,na >
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct times_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 * n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::times_wknd<
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

/* times.hpp
b2D6NPEEZXGnc76Rclrvmzi8lvfiCTxDrOS1/gaWU9OBeynIi9cJuElZFq8zeG0i7uT1IaL1PotGXrvdaL/XIozX/uRlvecin+m9zHeEmMF0Mybyd+f7MIyk7WTeA8TTTeRDeiOvgynP6hlME91uIm88SXRPs9yvkcDfE5R0XqdjOOlGbGB6I7q6j+MA6VWYkkb+mImr06xjjWAa86DuZsu9HYmYrrxOJM801p1YzXQT0/vRfQzr/SXlIv2wMj2TOsUINCn1yd/TZp77HhD9LOYnhq8jLyV9lv1+kBrcRzxKTCaf1HWO94i4z3a8T2TLOvu9Ivt5vfdJ8lU+f157rGe9SQ9DV/ePpJC+nvRDzL8XjxAbiS3dVxJAmon3NDN/M9Mblfcrnwnp/qfcdAeYTud1A54mVss9KP4b2JYxEdX3oxwlLQNXk27ELXgmnXnxBNF3DtvBLY73q/gzvR+TMIa/5+MxptdjBtO1WIUb5X6WBqb38foI8TTTvreSD8e//cRjxCZixx08Y5iYTMwnrifuIx4jniH67+ykSyBmECuJm4j7iceIzUSPXZ104cQUYhHxRuJ24gHiMeLpXdq9MlrQgha0oAUtaEELWtCCFrSghUtx/39eWUZlTnaOcl29eQCAn37//5/1Ott9+B3lwtZDXThHIN5Ph7Oxk/m606TxMwzW3CmP5R6SpHNeC+vuCVx7yvtV083eTKNyP9K2HubXwSlToyN1krbWnhZhTVtsS4sabk1Ls6fFW9NG29PirGn97WnDrGnu9rRYa9rXeltajDXt+a62tChr2kP2NFuZf2VPs5W52pYWaStzoT3NVuYZ9jRbmUfa02xlDrGnUWb7tcYfqcaUc2c6wM08JpjL8Qa85Zr4nXyuZTwuILe8yHa/tS/OH8yyKvJs91L4W9OKl5rnCZBplr/UOk8wmohsF0xb7rX+diBpFMp6f4uljFG2+4bNZZJ8G+S+2MqSUqlP+/MeWEaE7V5lSSPv2RGSdtI6H4nWtGOq+SIlrVE1H2nqe9spl7I4+/X61B91IPe02ctmK8cR+/ts5W22lzdSfY31bl3br6l1fe11S9dqt/3a4tdLlfTdz2X8o/nV+4fp+753/QNXPr1ProVtL/u77P81OImYRrp5XeVcrQ92Rz8MRH+8BnvjW9gHP8K+OIqFBeBdGIS7MBgfwf4y/nwI5mAorsQwPI4DZNz2gTgGB2EqhmMGDsZCHILX4lC8FSOwCSOxPfUThQsxGoswBiswFhdRT8OwAuNwDcbjbTgct+MIfBRH4iFMwP6XU8cYh6NxCybiHhyD3fgcx6IJx+EyTMI3cTwOZuedgJNxIu7CZHwCJ6FnJ64ZxH44GWMxBa/CKWjAqViHv8TAzpxbxFCchoNxOkbhDEzANLwTZ+JunIXtOQk4G/WYjiE4B0fi1ZiKc3E8B5cMnIzzcBpmogGzsA6zMZANJBcnYB4acAFehwvlmhJjxRW61UTOK3F+Rjk3gkzvI3KegX59pT/c0sesv1/rd9WCFrSgBS1oQQs/33DR2//c1B7FfZwXavy/43qWIe3/fe1krJ0O/L7HQNyt3Afc3tb+J3cWYTCVGJRCyFh0Na6rYhVtBcoywtym8ta1t7VXPT3s9+a7S3uSpdnaUh72tChru6yKZZwZSFqZZdpkva9a3mOUaXs7t4PnPnlG+3vEBR3s92Rfw7wB5s9JNYaX1MF2aed8x8w+2Ih7lDq43EUdmO+n/Wl1wLS6Dn70uu6nnFsoewDOuuLc60q7lGv8W7qH8sK1M13fg9v2ezQvVPvZrUxJ/zxo2ct+mW+eLBn9dM97u105knavuT5kO5ftvwn7EM+ortH2wSg=
*/