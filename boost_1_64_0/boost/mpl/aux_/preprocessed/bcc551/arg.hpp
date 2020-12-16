
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
2INLrA9Kfk//19tBlr4kvrecpN6Pu1Uh4ZGhdIrPDzymPc5sl5yyVF0fOdXIuJXjQ8axnChS3zm9yDiRM4jUY84oMq7lHEPGtZxJpF5zZnXczDmJtGvOstbMSXumvi5ysrX2nEJk/pdTjrR7Tg0yH81pEhXHRdo1p1vHHTkDyPWZM4q0c8440s45U8h4mjOjteec1Jo5y8g8Mkc9S8rvyMlD2jenBJnP5lQg/S9nh9bMier1jpxupP1zBsTV9wg5I8SDOIl7cBYjuIx+dJxznmrAdGzFcmzEOmzBbgzhEDbhGIZxDpslH9yF2Wn0F9yBAexK+/f0j7+3zJD/ws/dqveXbjW6sNJvfu1Wdb+Rz6vL1O9W45218fe32R8+T319rWHk47ewGB/EUpzBcvwuVuIDWI3fxBr8NvrwIQzgdzCKb2aA7sAvEu/CtxHvwS8T78Pj+PeXZLXoWS/PCcqWvF6eD1SaaDGvQ75/VuXibLLaIS4kq4BYl6J69PZKDYqjKeqYOJ6ipvT2KWpO7ExRi2KvUo4UyS9FpSHfn6o85HtVVYp8r6qqke+/VQD5HlZ1Id/Xq37k+3M1gjyXqHG9n1Od0Ps51aLez0lJ5DxSVL5YmKIqRJWiAmJZiuoWrRQ1LA4qNSmOKnVCHFfqpNjLPPZpsp56QPn6rRh5vlM1yPf5qkenu9QY8hyqppHnQLWo17tU3tPleC5Vg1xnqhe5ftQocv2rKeT7dHVSb+dQ6hnImJOP/P5AVSHf36sY8r256ke+51dTyPfVagn5XlqlpUp52V4cZHtxlO1TZX2SmtLrk9RJvT5JOZ4p5XGpfLGO8mlN1YmMV2oQGa/UMeS5U53Q6S5lPEvSXaoYeZ5VTcjzoxpAnp/VqI6bahp5nlVzyHiojHPkvFwqXaxSqlisU6oa+Z2EiiG/E1CDyPinJsRZ6lNcoD7FMM2aJsdXqkQ0uM6Q8Ud1IOOj6keeX9UY8pytJpHfSagTyPf9akGsSlHGs2V7+p9YRn0jvx9QpSIduUrHk5VP5Kcu/WKhUmN6e6WmkPFOndTb25XjXDmuXaUh46zKQ8ZZVYL8nkVVIOOtiiLjrBrU23nUNHJ/VfN6O7uyrZN87cpCxlFVitxfVSVyP1E+ne5WHch9Qw3r9W41LU5RjnSpN46L3CdUQCyjn4qjzC/EccYqvZ2b13zIuDWL/G5FLSHP8yrpPCl/srLE8WRVKk5x3SPP+SqK/A5DdYvhFDUo9nLdi4Mpalpvr9QC8vsWZVsv55mkUsVernfk9y+qFPl9hapCfmeifOLK0kpDRIkPYBf2Yh/6UH7fcAuOEB+Ur/TwbbiAbZh2/np5/6ZkftGOJcT3YjXejDG8FXswJtvhPpxAP85hGMPx72Voq/WqBS28UY6Pd2Al3oAyf2nAOuKNUm5sknLjfik3RqW8+HY8hq/DE9iFJ/EAJmWsl/eLKhv7UOanPSjz0w6UedFBSWf9WyQdXy/Hw0PYjSFJL+S9JMq86U6UeWw/DrD+ejyKt0m9kX4tThO/CxdxF6Zmrpf7qMrHt2IF3i7HZ/uA1AvxPdiBnXJ+eBiHMSL543U4iW8Sua8ckXr1rP+P3o//X5eqrPX6e/b53PXKtmG9yiZI+snGLLVAWCQsEcwhfu/yfK4l73r1F5b4/NWde+wCPf7lHkfGydx5ZNzKXULmkbmpRXpcz83WunKLkflhbnWRHmdzfUV6/M+Nac3cviI9TuUO6e3Jv0jfL3Oni/R4lDuv4/bcZaTX56qNevzJLUTGydxKZDzMrUPGw9wwMh7mdiH399wBvd6Ze1S0yBcZJ3OXkPEm11Gsx8vcPOR+mluCzINzdyD3o9wm5Pc=
*/