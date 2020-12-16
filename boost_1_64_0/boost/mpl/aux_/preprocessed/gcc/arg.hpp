
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
AtwDP4al8O/wCKyGP4SfQNd1WCX+DWxgvA7LxL9jsBV8FkbCcjgYvgCHwxfhaHgcWuHLsBD+GO6GFfAwPAGfgz+Br8BX4KvwJHwDvgr/CF+DX8BTsrbPz2AkfB32g6fVNZtkXDlsZnKff1+e9z6ATeCHUF27y4cefQPokS/YBB6H6tpLPvRaynNFGGwCW0GXXokPvatE72rRa6zRK/Wh90fx8yPx808aP8t86EWLvfZiL0Zjr8KHXrXY+4fY+6fGXqUPvZFib5TYG62xVyV6kSZ6E0VvEoyAkzV6lgPe7X0pfl4WP7+C6vuBD713RO9d0XtPoxfrQ6+7+NlD8tdT9RPxoTdQ9AaJ3mCNXrwPvZPi56vi5081fib40Pul6FWK3htQvY5EL9xEr4+8x/aFYbCfXH+VSLHoRUj70UbxT/S2SfuxHfaC98IBcAdMgDvhLLgLzof3wXy4G9rhXrgF3g/vgvvhY/ABeBCWwmfgQ/A4fBi+DA/AU/BR+HN4EL4Hn4B/hYekfTkMQ/H7CAyDT0K1Xj7qvV4ek3J8FkbA56BaLx+T50QTvRA5381hCGwB1frlQ6+B6DUUvSBtPfGhVyV+vg9D4Afa8+1Dr43YixR7baHa/vnQ+6vYuyD2PoZqO+ZDb6jYGyb2hkNZw41xhtr+BP0abo+KvcdgBHwcRsGDGrvVoh9tYnes2B0H28Hx2vPxuPfzXyp2HxK7D0P1fDzuPZ+fid6/YAi8pD0fPvTeEr1fi95vtPcjH3qdJH+dYQjsor2v+NDrK3r9RK+/9v7go1wOi59HYAR8EqrXkw+9MtH7keg9rb2eDnr388eiVwFD4Alte+1D73XROy16Z7Tn76D3dnCAtIMDYRgcpFnLNEX0Vpr07/xC2sE3YF/4JhwA34K3wF/D5fA3asxFGXMEWiIliDbm4gfqcYgc17SG4+LkuNY1HJfg53E2jX8pHscN0xxXovrn+7hSP9OrUP3zfVyVn8dZDnk/bri2nOW4ljUcF+/ncSl+Hlfsp3+lfh5X4edxVYe816tUbQxRNT3fx4Uervm4IiROjtsg11EItMpxP5Dr6DYYA2+HsXA17AqL+W8kXANvhmvhArgeroAb4Eq4Ga6GW+AauFXsn0KqxP4YeZ5R2qPjYv9QA/qVYBmMhT+CI+EzcDI8CmfBYzARPgdTYDnMhM/DLHgc2uCP4WZYAUvhK/AJeBIeg6/CP8OfQqV/6zUYDU/BGPgz2Bu+DvvCM3AQ/Dk8epV/MVktTYMtkUgcoqyZFHuHsq6MPkZrn11Blip4kr9dhpZfBqnxWt9W9iFmcVut7FuHuOK3HlxjFsMVYX8SNlyxXIeSviGeK8cUcUzoWv6OuOK7Zq1lP7KKf2+F3mK9lq11x3s9t1Yf87XxOvKNxCPpyAGkAvGMBVu9Th8PNnI9ZYuvBxB9bFiIr8X8fTD74iqDLAfXsw/Rxos9x7ZlgzFubDj7DsDB0DN+bOIGYwzZdRuMcWTPsC8RbirHDv++jBSxHb7RGVt2MHTFl123kWPwV40zu9Eda/bkRne82Qv8O3iTO+5s+H1BljikxyZ9DNqsTTXHoa0qxwbHHUdcMWkvbHLHpU2kzII3a+LTPq+PUTuCv63imJNsJ212xqu1wUT8qWLfjs3msWuPb3bHr41/3mcMWzpAOQaxkWYS1Ma0LWa7mu1yqI1tW8KxZ9gXMod8wQq2zWLdHsX3s/cF+RXzts8W73FvL5HGWZiwpeb4t/u2uGPglvPvIxx3AYZudcbD7QHNYuKm8MFk2lZ9bNz3KoNqjI9rR+ci/94BR7B9HCbBKngJccXMjb6LcoLx0Cx27jr22+A+eJl9FfAcosTSDb4=
*/