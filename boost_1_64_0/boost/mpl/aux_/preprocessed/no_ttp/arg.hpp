
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
br9rP0bHmD5HfRnlHvxj+jMqoEx1n0anDpb0a1TM3zyD3Uv1bzSxk5shAM8f5PuhivV15B/sftP9HU2RPo8igt3/sH6Pkhj3ctJ20iFSAcnQi2WZ1Jc0hbSAtJGURyokefR2NwSRYkirSPtI50lN+9CXLymGlE3aTTpFqtKXvqRJkaR00ipSLuk0ydCP4UihpATSUtJm0iHSOZJHCOsHKYKUTlpFyiHlk4pCXH02uT6uj+vj+rg+ro/r4/q4Pq6P6+P6uD7/W58/of9/5VGapN+r//853gbb8yMBcj24McmN1JB0TXlv8vPm5yLUz/FE8zxKqjPP5FufjZhJrrh0eTZCnunIQnUfY8ek/ERSLVIs6Qblh1rLj+ahFUvJTj83rF9uyTMZJlLatGnyrI08R2p5ZEj17L5UCJ8plYkNJyKBG/IssSWkRavDc66fpEMvWp81url4vZVr69TPDPPjevLci87zR4XqZ5RkOpWRJcZnmjJkuGLNM0nW5zK1zyae13ke6ZzmeaQuUmdJUmfNpPp8SB1ZqHKelecozX3VlL8MWZ+T9G5ofSZY06eDtLdMluUmkdRYybvXWk48T5Gqu+5x/tkjyix5pke+x2GpPueiY6X+1b/F2cW5XeJcInHeTQpifHnP2eJMS5+rDtT5Z49upQRTGnGp4lT6vzEY9N/rqn7e1beqtI+V+eQv8ynbFtfM5MxMNh2q0Jx5dszRfDNKuUHSz1uYsk6J/chr2GEtVxmK13tkpDjx7J6HeZxNd8lz5KxfP+40/791xChjN4P8ll/ym9H6W17Jb4HW33JKfguw/rbA9ltgD+tvJ4lVfgswyHodYPstiDwl80fqQJYlWZfTGY/q+bDYjDsCwbZ+u1Ux/2a0PjPfmnl16BbuGfK99w6ZVtVziJnyHmgv1TPCSfKbdZntQiyxKSXlFJb8ZpR5ZCsrgHn0ML+dUZVVoFPWeZ2yLuuUdVqnLPV2NleWiSxZR0yyLBbYthmZiTyTnmyaq2w8yu97QbsMqtcHxs020DwauxiyZMPwtcTwBemu1qynuRJDQhJblEx6oVX2y87vi462YhucXFL+402IiZfX2PrSYtpNZEzj+y/msmSeSX8IbF+ZAsZnX7el6nCz9Gm3UvoNWI5K/AUv2cefmFoSf2Q5+6pBr2r2VZrpOWcfo0yj7BcoSP0e6/1MtzLZDVTL45yMWDahTAwfu30xw7JDMufNNf8meVnOtMuUSYZX9wmhTKw6bx6/a9fFvRL7rBkzGbZkfzkjYZo8CV+y3E9oavl9ZoKsY+r5KOM7IsNnzLbkOSbfKdK2b81RlWHtk+AQvw1V5mkaP8h0nDDHJtPM7tq6rCxgBmxkPh9S6uPlkmUl3/JcKdNNaRLPPpkPst232/avlP74qktbhyrYtxP3oV+zX1Yy6Y+PWC17AEP5736yrnf2y7htu0d8MuXye1FJfcxMkN/Vz/fGp02LjTelZaiXD+28uKapU/W+t7r0GzdbpjMDKxtZJ/JKT2d6YmLGDHle3L+c9aLngdL9OWiXBw+UddW2rdeuK7Y+TMxLCL/JutLQk+Fmx6aott+y/CpR2q8rsbKw1lb3fSLfCzXLZIFmWZP6k2VHGbdlOVtVk2WCCptInpD9JX06FNnikD4dbMc96aWWsYnSR52/7OdbYxXqPu9A6bq3nP1EJ6dOS3Oq/l875Fz9q7dVRZq6rq06ruXNYTI99vV3SrWNsNY52zHW6RmUJH1iqOrY2heJsa4lT3J6EmMuqecult9ZJEr6gFQvI4WabYZ6+x4m/eO5ybL8G+kW5eGl16U+GciyohqVJaLc/ZO13kzKNiJdGaTkOPKCp/KbeQG0Lbs=
*/