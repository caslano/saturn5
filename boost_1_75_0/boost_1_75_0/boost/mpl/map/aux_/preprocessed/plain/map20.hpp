
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/map/map20.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename Map>
struct m_at< Map,10 >
{
    typedef typename Map::item10 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 11,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item10;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10
    >
struct map11
    : m_item<
          11
        , typename P10::first
        , typename P10::second
        , map10< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9 >
        >
{
    typedef map11 type;
};

template< typename Map>
struct m_at< Map,11 >
{
    typedef typename Map::item11 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 12,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item11;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11
    >
struct map12
    : m_item<
          12
        , typename P11::first
        , typename P11::second
        , map11< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10 >
        >
{
    typedef map12 type;
};

template< typename Map>
struct m_at< Map,12 >
{
    typedef typename Map::item12 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 13,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item12;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12
    >
struct map13
    : m_item<
          13
        , typename P12::first
        , typename P12::second
        , map12< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11 >
        >
{
    typedef map13 type;
};

template< typename Map>
struct m_at< Map,13 >
{
    typedef typename Map::item13 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 14,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item13;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13
    >
struct map14
    : m_item<
          14
        , typename P13::first
        , typename P13::second
        , map13< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12 >
        >
{
    typedef map14 type;
};

template< typename Map>
struct m_at< Map,14 >
{
    typedef typename Map::item14 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 15,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item14;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    >
struct map15
    : m_item<
          15
        , typename P14::first
        , typename P14::second
        , map14< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13 >
        >
{
    typedef map15 type;
};

template< typename Map>
struct m_at< Map,15 >
{
    typedef typename Map::item15 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 16,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item15;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15
    >
struct map16
    : m_item<
          16
        , typename P15::first
        , typename P15::second
        , map15< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14 >
        >
{
    typedef map16 type;
};

template< typename Map>
struct m_at< Map,16 >
{
    typedef typename Map::item16 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 17,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item16;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16
    >
struct map17
    : m_item<
          17
        , typename P16::first
        , typename P16::second
        , map16< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15 >
        >
{
    typedef map17 type;
};

template< typename Map>
struct m_at< Map,17 >
{
    typedef typename Map::item17 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 18,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item17;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17
    >
struct map18
    : m_item<
          18
        , typename P17::first
        , typename P17::second
        , map17< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16 >
        >
{
    typedef map18 type;
};

template< typename Map>
struct m_at< Map,18 >
{
    typedef typename Map::item18 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 19,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item18;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18
    >
struct map19
    : m_item<
          19
        , typename P18::first
        , typename P18::second
        , map18< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17 >
        >
{
    typedef map19 type;
};

template< typename Map>
struct m_at< Map,19 >
{
    typedef typename Map::item19 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 20,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item19;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18, typename P19
    >
struct map20
    : m_item<
          20
        , typename P19::first
        , typename P19::second
        , map19< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18 >
        >
{
    typedef map20 type;
};

}}

/* map20.hpp
fv19+7O/NcMde9K+p2lL8KLqQlfrlDxuDvNP2YzOzwtF3cgm5HChExKile2IdWx4mbYpUQr0rKbF+bPTmjAb0sSvle2H2cGEsHpg8NZz3W/N+6xn4V01Fx7F/bGH4lA7Leq3vV3r/PP8VDLgMgXUXyv5zsGXKsUa+j30MnEpuy0LrlW2ob/yfq6w+ytu0esMXucLiU44I0zKXcu1MdUBcvpdiUX8Vtgihi4sW6t6C13WAq0PvT7cT7mKNhrkjuNWPa42EDQwedTgk/cMVZOlT0WfeqAEfBjQQxwaP/jBWZwke5ShsdZfxUhvYN9fIWTTtPXp3dY3oTDBGiJ1A1I7Ct2TL+RnfQg6E6gS+7gB3+H34V0d3AzwWIa4m8maNu1sBtVOulmE/IWXQmWrkdS3BVYj2hxYkS6kT/rthKIKhbfe6g2gjm3ymbI2LI4lDu0Dqs53ZNmUPTkFEEwIxdQQOMlUqv0nT7hEAhA8UCUv4U0bK4ulMQmUir1XfguPFFS4pdhWnzgJiaX9FksbPQZkzp58yUSLp6xy+nI2xOmBP7nLMyW+E9Tm1NmY6N0c5816JWZ/l7NxKZg6whyvyrUhQwR4dS95by33J0V8HFoLzDG769iknIToansBGAZErOAPfkHScpsUkZP92d3m0w15uI4acMlbdOTzLOvAH1fvMfIlXFyn3uHgwt11c1dvUTmQ6uUQzs9YNH7PnCch
*/