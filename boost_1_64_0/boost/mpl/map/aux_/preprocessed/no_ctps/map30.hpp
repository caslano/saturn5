
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/map/map30.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<>
struct m_at_impl<20>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item20 type;
    };
};

template<>
struct m_item_impl<21>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item20;
    };
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18, typename P19
    , typename P20
    >
struct map21
    : m_item<
          21
        , typename P20::first
        , typename P20::second
        , map20< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19 >
        >
{
    typedef map21 type;
};

template<>
struct m_at_impl<21>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item21 type;
    };
};

template<>
struct m_item_impl<22>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item21;
    };
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18, typename P19
    , typename P20, typename P21
    >
struct map22
    : m_item<
          22
        , typename P21::first
        , typename P21::second
        , map21< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20 >
        >
{
    typedef map22 type;
};

template<>
struct m_at_impl<22>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item22 type;
    };
};

template<>
struct m_item_impl<23>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item22;
    };
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18, typename P19
    , typename P20, typename P21, typename P22
    >
struct map23
    : m_item<
          23
        , typename P22::first
        , typename P22::second
        , map22< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21 >
        >
{
    typedef map23 type;
};

template<>
struct m_at_impl<23>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item23 type;
    };
};

template<>
struct m_item_impl<24>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item23;
    };
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18, typename P19
    , typename P20, typename P21, typename P22, typename P23
    >
struct map24
    : m_item<
          24
        , typename P23::first
        , typename P23::second
        , map23< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22 >
        >
{
    typedef map24 type;
};

template<>
struct m_at_impl<24>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item24 type;
    };
};

template<>
struct m_item_impl<25>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item24;
    };
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18, typename P19
    , typename P20, typename P21, typename P22, typename P23, typename P24
    >
struct map25
    : m_item<
          25
        , typename P24::first
        , typename P24::second
        , map24< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23 >
        >
{
    typedef map25 type;
};

template<>
struct m_at_impl<25>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item25 type;
    };
};

template<>
struct m_item_impl<26>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item25;
    };
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18, typename P19
    , typename P20, typename P21, typename P22, typename P23, typename P24
    , typename P25
    >
struct map26
    : m_item<
          26
        , typename P25::first
        , typename P25::second
        , map25< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24 >
        >
{
    typedef map26 type;
};

template<>
struct m_at_impl<26>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item26 type;
    };
};

template<>
struct m_item_impl<27>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item26;
    };
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18, typename P19
    , typename P20, typename P21, typename P22, typename P23, typename P24
    , typename P25, typename P26
    >
struct map27
    : m_item<
          27
        , typename P26::first
        , typename P26::second
        , map26< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25 >
        >
{
    typedef map27 type;
};

template<>
struct m_at_impl<27>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item27 type;
    };
};

template<>
struct m_item_impl<28>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item27;
    };
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18, typename P19
    , typename P20, typename P21, typename P22, typename P23, typename P24
    , typename P25, typename P26, typename P27
    >
struct map28
    : m_item<
          28
        , typename P27::first
        , typename P27::second
        , map27< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26 >
        >
{
    typedef map28 type;
};

template<>
struct m_at_impl<28>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item28 type;
    };
};

template<>
struct m_item_impl<29>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item28;
    };
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18, typename P19
    , typename P20, typename P21, typename P22, typename P23, typename P24
    , typename P25, typename P26, typename P27, typename P28
    >
struct map29
    : m_item<
          29
        , typename P28::first
        , typename P28::second
        , map28< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27 >
        >
{
    typedef map29 type;
};

template<>
struct m_at_impl<29>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item29 type;
    };
};

template<>
struct m_item_impl<30>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item29;
    };
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18, typename P19
    , typename P20, typename P21, typename P22, typename P23, typename P24
    , typename P25, typename P26, typename P27, typename P28, typename P29
    >
struct map30
    : m_item<
          30
        , typename P29::first
        , typename P29::second
        , map29< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27,P28 >
        >
{
    typedef map30 type;
};

}}

/* map30.hpp
o7Ae3oUNcC42xPXYCIuwMb6Jt+NxbIKXsCn6Ek8gtsJmGIQtsDe2xBRshQXYGufjHfgYtsElGCTl2aeq9N+Qfh2k3zR3oCcqr69k/pISbIInsRX+Azvht9gDT2NfPIPD8CyOwXM4Ac+jAS/gA/gDzseL+Cz+iK/gT1iEP+N+/AXfx8t4DK/gcSzDy3gVb1POdwzEa9gVdaZ5bADHYVXMRU9cgNXweayOb2MNPIw18TTeir/ibcix0/lgG/TFO7EORmNdnIp++Cj64xPYGFdhAK7H23ETNsEt2BR3YiAexmb4MbbAE9gSv8VWeA5b448YhDU5Tm2xMbbDUGyPQ7EDjsKOmIKdcBYG43IMwe3YBd/AUPwAu+JRtMyLRF5LHxLSKOW6AX8flnIdJte5PuiP4Xg7DsJOOBgH4BAcgcMxDiPxXhyBszEKH8bRuBCj8Qkch6/hXbgdJ+AhnIjf4iQ8h0n4EyajF+lMQV/UY32cjA0xFQNwquwf8Uo/EMqO7N8d/B0h1/Gn5HtzFTbG1dgcn8YgfAajcA2Ow7WYhs+iAZ/DhbgO/4zrcRu+gO/hBvwIN+I3uAl/wRfxV3wZPUnLZqyBhTgKX8ME3IJ63I7T8S+Yj2/gfNyBj+JuXI1v4jO4F1/BffgqvoN78QDux0N4CN/Fj/A9LMH38Qx+hKX4Mf6Mx/AyHrc+0yJ9QKRvSKzdMy1zJF/nYUucj33xERyACyQ/H8NpuBCz8XFcgIvwGVyMm3AJbsel+Douk3Ss0El/D9wr6fDBBZKOgZKOwdgYh2IIDsMeOByjMBJjcCSm4ii8F6NxPo7BJzAGV+FYXIfj8HmMk3RNxN04yZpP0jcD1znJp0IPnhXCV7EGvoYNcAs2wa3YAbdjD/wLhuEbaMAd+DjuxBW4G9fgHnwW38ILyPVP+lFwjsl5oGy/TNIxgOVqYwQ2xkHYHAdjGxyC/XAoDsZhGInDcQpGSnpG4GwciYtxFD6Fo3EVjpF0xeAbOBb34Djci+PxU5yAX+Ld+BXG4WmcKPszCZXzJR69MQHrYBK2wWTsgykYg3och5NR5lGS/hLcj5bjop5HaarkxzRshuk4ETMxD7PQMo9SoWwnWrajnkdppmynAOvibGyED8h252AoPoQ9cS72wYdxJM6zxiP9FzDbSTwrpBw9hTVwJXrjKmyBqzEMn8aB+AyOxzWYhWslHiXvCiWerVJOmvN3gFwv68v+NEA/bIimf8c2eDsOxiaS/qaYhoGYg83wQWyOS7EFrsJW+DTegeuwDe7FIDyAbfFrbIdnsD2WYQdU6iwd0Q+D0R9DsAN2wS4Yil2xK/bGbjgIu6Mee+AUvBPTMQwfwN64AvvgZuyLhRiuKkfFX7ouR7mSX0Y53nk4EadjHs6Q7cTqpC8CjpbtVMdI2c6jsp3HsS4uwka4GINxCXbDpdgTl+EIfEKVzlLZfqSTdK6T8rMeG+PzGIp/xmH4Al6QuROj5P7yWqkXjeLvOai8DPI72IjtcDp2xXwcgvfgaLwXY/E+fBBn4Sb8E27HAtyDs/EQPoglOAd/kPfBJOJR1ONjmI0L8T58HOfgInwKF+MGXIov43LchSvwHXwKz+BKvIir8BdcjcrvwqexAT6DLXENdsS12AOfxcH4HI7BdRiP63EaPo95+ALei5twLr6IS/BlfBILcR2+iqb6FG7HLfgubsXjuB2/xNfxDL6BP+IO/BV3YksO6C7siLuxL76Jw/EtvAv3YjLuwyzcj/fgO3gf/hUfxndxMX6Ay/FvuAY/xP34Eb6HR/FD/BjP4t/xHH6Cl/EY3uLJfWW8DY9jV/wMB+AJHIif4zD8EqPxa0zEbzAPS3AGnpT6Db8=
*/