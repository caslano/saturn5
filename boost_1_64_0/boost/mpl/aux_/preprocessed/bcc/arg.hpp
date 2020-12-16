
// Copyright Peter Dimov 2001-2002
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "arg.hpp" header
// -- DO NOT modify by hand!

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
template<> struct arg< -1 >
{
    BOOST_STATIC_CONSTANT(int, value  = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
JbfMm+jeouAljklI4L/ZmCudGhhl4pzKTXnO5VJDp/SulcleKa0Wu73GeLVy8qyVa+PVyDTxUpq4JoKwbecmsJ3JpDUaotX8kVwsdt29w4H1/pGcgrl3OGy0kx5UCzfBNblBH2hqcIhz2bgBIc7CJl2m0nIqU5bWH7uhrDp3p81pbdwF38Md5bhmOeWay2xAI+Vv2t3CsYimwMAhnt3OTC7LUQAG8aB6BFlV4dKiCahkHotawQc8KX9LG06SotJi0tJTMVGcGCu7JZjQPDvzoXXjXM2qXroLuTl2cV5EsZ9CEFeiVT1PzCkwGfmuAqXBkdyKmw1jhSz2YRvimy1Zk6XpmBxpi3ogoq5RVlWL4iTPJHElCpvGMOSxV/+C2ZRH8qo9A2YsvjA547EJEDb3wRbHkwPnbqi7rpGjMMxmZzzn4dJch9FiknJCRamUsRAycyaJ/qEitJuB+gnME5vmmGTLN+Uxt4KRZFNqlgmm6iIq3Yk5NkRpyXKYHALNn4n8HDM79MIsIA3KaRcyB2l9hXbejdIvLUdXy0gb1DwznedLz3ySSA5AKWNjgVyjimcxmKzySeB2lYwSquFpEq+U2e2qoLQy1u9CulR8xqPEqvjUJ1PxCoAcVbNf1Mej2dmpiNDEzveeQmniSqPVL7PBaVWxuUja+MNHcMRHm8pP0ZBsiHbu6EguqyF2aKOyrUgCXaxspZ1TcK+YdORlKOIh7UfgflgnzakfMQo28qzCQnluz66cjpTDUpStJq7qcuqMTZedkBu7eWqIYLNIO+8EvOihDXiKOUYZ1xi+qGWsr0x1puJTGcg+atxDRE6quSHdF+ys8+00DBa3nDjncllhtXLlbLJ2LpRLlHZWu/46OrF17uPjjV+d/bA+aG33YXA/rMeh9JPIdB+NWq39w31d42Q2Aj/V5o1YA9oliMUu+E+0WXKFGBtsEzPEeZN61Cl8u73OabJODlKVd33crriLrmEe7yvM3X2tHu9n6FqKz5XEL6mUqPU7cqe5hFsSP+O2LC/+wVtf/Iv0XNezVqrSral08OSRIOE1fIu9M4vJYOUYxSjDVp2ij8Wxmng0/mIbl+1aHnATmMmYinGRcgzH4qj2LBpvHfJmg938M2VTh3Xl5AdlYLHXVXfqsv+J+4Gkzmlj9aUtkC0bFvWYO2tevfNnD7cqP3egRVpytLdvs8bttxUvDfDrVK/rhNGj2odHRbn56D18fJs36ZA8OqLZ3coTg8v2H/PMyIrq4i94+EeHR7sLgk5Yv3JZ+4qKUqHi8v7OZaVlHt4tGrTevGFe16VzVjTVubm5FdhHDtq9c8kgfQu3FuVn9ze/fvlUb6s1PHBp4VKvwSFNh20pXugfGOwafPHMyfa3bx7u57BGh16vOBGwZuW8lh5ujRqlpca2npCc4DsudWS7PduXDcGhyC5+grufr97L12qPCllbtNBHj7VhJ0pPeFXe3B984czRNgGCV8DVK0e6W22RwYVz5ritXb2kXfmZfc3mzp5fv2zf0YYZGeFCcnK4vnjTnC7Xrhy/z8ulceNdO+b3W79qeYeEqKSmu3Yu6D8uZUTbg/sP1y+wxoVt3ji/m765a/Ntm1b0OX/mUMsMQ0Sn0gMH3HaVzA0Nj4hwSU6JbD5jyqghS2cta+yh8/DwbdG049qVi9qwsvZp1rCNu87dPTk1qsXtW0f6V1za1+nujZNDHLbh/QK6NO3j16VB95KSwsCFc5Y08nJt0mTLpiX3FW+c3dmcmdi7aPWcFgkRoxpnG+J7zLAmDPZwadjQw9XTc8/OFcOuXzndp/LWgZCD+w7VmztnQQNvvbv33Zunhhozov0unj3VIaBzk95xUSMb+TQ=
*/