
// Copyright Peter Dimov 2001-2002
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/arg.hpp" header
// -- DO NOT modify by hand!

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
template<> struct arg< -1 >
{
    BOOST_STATIC_CONSTANT(int, value  = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<1>
{
    BOOST_STATIC_CONSTANT(int, value  = 1);
    typedef arg<2> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<2>
{
    BOOST_STATIC_CONSTANT(int, value  = 2);
    typedef arg<3> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U2 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<3>
{
    BOOST_STATIC_CONSTANT(int, value  = 3);
    typedef arg<4> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U3 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<4>
{
    BOOST_STATIC_CONSTANT(int, value  = 4);
    typedef arg<5> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U4 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<5>
{
    BOOST_STATIC_CONSTANT(int, value  = 5);
    typedef arg<6> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U5 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1,int, arg)

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

/* arg.hpp
8VUseTt0aHiQn/Y9GN3R9fF00FXaXvzurcWKK9zNHW+8OfeNNVfb3Vz2D9V8LZ1v/WbdzF8s2Nhv7v0BQ5qd9H4u/kR/5fmRZ8L7JHxbdMuBSQuCqv1uv4n5rOrzv370F8+++crysze2PRwY0fQMk3pfaKk8f/Dj+d13Je9vvrFFeZMO3+494v2ceG/n+rtew+D9vSBcz613P9d/v9rOG/be9/YnL0VHr3tpdmHm1oeqDYZH1Dn9RTsXDcz6Q957q+578RcRHy5of/nvXeBuzcBppd/cIH2A0jcYQ9qtsIioBOMVzLnFHGyHudgZV2J/XI2DcQ0Ox+0YhzswAe/GeXgvJuNOzMJdaMH7cCXuRlkbIH1xah8d5XFcG7C2CeXBDdgBN2IX3IxheCv2xdtwMBbjRLwL43A7JuAOvAHvxhS8B5fivbgWd+LNuAu34H14H/4GS7AU9+EBfAwfxafwEB7DI/gCHsU38UN8F6vwBP4NP8KT+Cl+gp/jp1iDf8dv8BR+h/9Apa/yczyt1kv6BaW/UGmnAdZ2UcPX0k7fSjudwRD8QdrnRxyDBtp9MvjgGvTFjeiHr2EzrER/DFb6TLEnBuBSbIPLMRCPYHs8hkHYlDJ1wtYYjNdjV1yIoViK3fER7IlvYy88ib3Rl8/bPjgQwzEG++JE7IfTMQp/jQNwHw5GZZBzCPrhdbgIR6ERx+DTOBafxYkYxGfLJAzBaViAsbgaE/BBnIv7cSFewEXoQ7unYFNcLMdvtEH6NjFI3k8+GGa7F2sTXocpsl9SZX+OIB6U17WW1/lipLzuXlkD8AA2xd9gSyyxrakhVji9vgnKbxbm9NflU9NAPqWSz2OSzyHJ5wlNPgF73eezV7abTIyW7brLdtq1K+9JPh+gP/4VA/BD7IxVGIIfafJNbiDf47JdIXGtbHenbOeP2bLdOKnPNEl/OkbiDByN8TgOZ+JknI+zcBHOx8W4DNNxMxbiVlypKWdMqftyjpXtYojJsl0P2U67lupZaZ+XsA2WYRd8GUPxFU1+xQ3kd0yz3w+Wut/vPeS47INNMRzV80+0H18N5NNdcxzXNJBPc8mnteQTIPm0Qfvxtc99Ps00+UTvc5/Pp9J+n2NTrJb9/oWm3eIbyOcTTbuZG8ing9Sni9QnWOrTFe37p4F82mvf/w3kc0Hq4yv5XCn5XKXdPw3k86PUJ5lYI9stle2aYYJsF26Q/Y5dMRL7Yn+8DqMwDqMxAQdiKg7BdBxa9/6XPgte6+L9v0Hy2YiBuA2DsRh7412S73aU+tEP4b5+62W7aGKVbNfcxefvYWnHp7Ep/l6Tfk0D6T9lf9/KOT12cvG+LZf035D038S2+BZ2xEpNfpy7u83vVU19OPd2W581kt9ayW+d9vOygfRXy3YZymtlO4ts1xwTZbt0Oc6WYGfMxFBcimGYjaNwOU5CC6bgSszCIjTjarQef3J+i6NcHH+T5P00BZvhVGyBsdgOZ2IQJmB3nI+9MRFH4kK0tZtZ8mnjot16SruFYWvspXm/F8vrAl28D0dL+cZIu4zFtjgOpd0533Tf7qPY7nnfi98j5wCx9nY/g/8WP0M4cTwxkWgmbiEeIh4n+m71M8QQC4k7ieXEamLoHX6GeGIGcQNxN7GMWEtsus3PEEaMJWYT9xCPEquJ/sWkR0wm7iAeJFYRa4kBd7I96+K2EEuJzmvlwlgLN57ovGau9GbrurktTmvnRpCe8/q5SIwh1vLvZHS3lu7gesf1dNX8OzCeNInHNtC2WChr7HbjoW0+staOtuVxJVY7rbk7KevuSjdeYfCdaV1/VzPhSkPYzLp1eLEzqQcGbnK9Hu+A05q8KjxLdLU=
*/