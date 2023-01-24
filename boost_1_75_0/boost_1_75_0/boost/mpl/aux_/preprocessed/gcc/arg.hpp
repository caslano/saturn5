
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
L/vsw9apZUpoD4eqC1qUKj7m3pZBX3qVeSMsCG/LiVjkq6kvTtdTM5NidUzmi5m0wp7fXAg3/U31a5VTg798XCy1ZVG3qf/clYoqtvRnRfh125ROJG7K7GWEfj8JWfdPHsutlXKfJrnrnVedgju+Onyrx5QEH4Fzp+HWL1Ea+0e90KUCu+Q4FXyh1E+ktuTL9UtvdZizoc9KIF6QRRMff3hT+U5HLFqnDTqFpuNwAC2CECgXxX0CgfuZuiDgyzYNEi6oEB3wYVvuiQ2BY8L/UuhKbG7bFYk1nz4CTyS1eFdSzmQkycm6gFUtRzfjl6ym0B1/wURp5moovRNF6f3ogqKDs3ReDYjDxQf/eUTiWdVQCqGdnG/fr450a1lP8pnPZ+W+AEblMfnpupN4a6Tiqkr0z4eZ14gLhCdBoc845fctezadiL7efzzxRcErXNC5JyGJ5YuHtVimwFTD/MsZ4DSwj9wP88JBneijH9JmwQz5VQUfutlbcJNzUr7ZB41cdLom5xXND4TDrVy8TApM3dvyaqvJTsWeXSyJE8tTZ5DVgT8ZZFJlOxLyFEbcdNRR6Fc53Bk75urpnEVHnI91xpa53LjX0D1b1OgrLGyWORKwYg96996yC10hlBuzrChVMonXirjZLP6pUPet0uJg2Aa6GL8d9rkgqsqYtzKJzbJiWebo4+0PBL/mWOibgyuSzIzYO+ZKN3LAOcgS
*/