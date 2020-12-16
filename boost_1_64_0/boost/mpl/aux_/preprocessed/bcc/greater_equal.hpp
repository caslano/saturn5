
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater_equal.hpp
tOMKNgyJ6UeNzcGMR84+tDanrRgCjjo5uAZ3uuxV6ocXwjA3fAtUbncVARsOt1eZ4aqQ8ryO6U+RpIdK0U+FvUh8isZW4SyV/SocdvY96ZpV+ApHsd1b42R+KUbQvrPQF5Dv5G6XCTDcFnptP6s+Hfq3Rco2XE34mHYucptKJJxsQz/nfC0hr5cEtKgMt4vtOATKGtJFX9B43STUCC75fl62r5L0TtFiTXQTNH1gmPuFTsRURfuQgoSb5gLBflY9jX3a5HW4tY8lMX/nWunsI+IgvKIxrogbjSY88dvWMIyEy+WnkLIEVL1PEULXidE60C0TwvApARyIEIMBrYPu2xVBn/51rc2dPc08y9TGafj6br7+yJd8yluzhjYzLUNb30GMBV6I30EEkV4wAlxmV61Z//7Pnq4un8yK+rwTfgdqt0x3xvZe1Q1M8H2/0vbkju6MdB0TIgJCcRVaniAIFXtVKVlAw99J+fQV9tW+qq5ZP0pJ5biAMobjxyjtHA9SjuD4ccoWjrfJ9icEDY6fk+1PUiJeU6wKRdB7StDjOJci2p+muDhupIj+uyiXcLxVtj9DeY7jN2X/31LGvc59VIpof1bgc3yNPH+OspfjY/+s0vsdJZvjMsoRI+4H6bC0WPosPZYgpdXSb1Esdku3pd3is3TTErD4gbhZR7VRAwud28DxUBfRc62ll149rKz20d5LTyjS5gpRXcOZHyp9BzXewdBVOE6z8EYay3/yr1OsNei+V1bBOd7WaXiFOKlDSxHanxqPoZ5qv9B5aOLGk7C9A/0GAuF+oW+YeTsDawKd4XMldK4kpOWFHJoFy/Q8bhjyRKGpn8hCuvO2UB4ERgqUuGIpRXvHdbn8/kqOkpZnC1117fVFZbaqUruSIL9Tk8hQtIWuXvIHt1k3wd6gXi+s4YtzwKwfqBNbT6BfgJVm8cUfPwsMsl1LzFq7OE/ShlZB5Eh+W7SqGVTbPKpJLelIecJ0ONfT4eqrzgxK5COuBv7DF6AhmDIEC7EUNOCrkyQVJscM9ZFwYaTgAHmub21Sep52DZKiZeaJrcbqVzHxgiQlO89lr1QdgrO0xXn19fVJSkZ6nvyGlchtoeuS+dFRs5+peV/yQyfj9UBlqlmdNyYpYb5UtjLyjAKbBwu59pC1TN8aEW1SPE3hcyob5hj7ilfny33gw/qG2nBBJU8Jhp4cV+H7W2dWJxbBRrG222t8Y6xHXt3DvDGTlTsUdO3qyKEm/wRzX13cSYyR2omtUWhr3zbSOhuvPbhk+FJtaise1sZ3SC2ha3Je6mDofGDQ4usgevncJiC1P7FHqISml1zTvWKGkqB97xcUvgInUDU8obMQnnA08dE1gav9yettnpmuH3x/j0Za463eYpdrN/5AniLG0K63oVUsMb0KuYca+3lSGaPg9DEt6uuW7+XP49ZMSImyk6FfKBiHJp1DzbY1/KoSP6VCiUg+s8UnnhSNlsLZhHAuF7YKpwDRaWhUHNI4bilJiP1GuvRAZtXhFBmiKDQiCDAflj1JdTqjQHamWoE+ERH4VA45TzB1ck/fib4+fkVKzLAcoXPxoVjFJbOE7lO9igY0fgpYttEqNaY+lKAIJsOwGqN+tD6aXFon+gjqYXSzbUSCCBm2VShCN36JzDshQsqc+OCcMN/c6ja25+vainzd8/qV0Mqn/sIJivwLfyFZ+ya0fH5Bnlfyo84pZ/PD85dUatgntM+N9/SZMMw5DEMafZnATwp5yJAHS+8e2Z21GBNjqrrr57OI7EhTP31A6IdRh9qDhpjZJ21VcerOguF8S7/yTLA4mV/ZuQPn4b8Ki9dSy8yr09LB3OxE3sMZz1kS/6Za0tk=
*/