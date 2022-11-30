
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/map/map10.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename Map>
struct m_at< Map,0 >
{
    typedef typename Map::item0 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 1,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item0;
};

template<
      typename P0
    >
struct map1
    : m_item<
          1
        , typename P0::first
        , typename P0::second
        , map0<  >
        >
{
    typedef map1 type;
};

template< typename Map>
struct m_at< Map,1 >
{
    typedef typename Map::item1 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 2,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item1;
};

template<
      typename P0, typename P1
    >
struct map2
    : m_item<
          2
        , typename P1::first
        , typename P1::second
        , map1<P0>
        >
{
    typedef map2 type;
};

template< typename Map>
struct m_at< Map,2 >
{
    typedef typename Map::item2 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 3,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item2;
};

template<
      typename P0, typename P1, typename P2
    >
struct map3
    : m_item<
          3
        , typename P2::first
        , typename P2::second
        , map2< P0,P1 >
        >
{
    typedef map3 type;
};

template< typename Map>
struct m_at< Map,3 >
{
    typedef typename Map::item3 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 4,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item3;
};

template<
      typename P0, typename P1, typename P2, typename P3
    >
struct map4
    : m_item<
          4
        , typename P3::first
        , typename P3::second
        , map3< P0,P1,P2 >
        >
{
    typedef map4 type;
};

template< typename Map>
struct m_at< Map,4 >
{
    typedef typename Map::item4 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 5,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item4;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    >
struct map5
    : m_item<
          5
        , typename P4::first
        , typename P4::second
        , map4< P0,P1,P2,P3 >
        >
{
    typedef map5 type;
};

template< typename Map>
struct m_at< Map,5 >
{
    typedef typename Map::item5 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 6,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item5;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5
    >
struct map6
    : m_item<
          6
        , typename P5::first
        , typename P5::second
        , map5< P0,P1,P2,P3,P4 >
        >
{
    typedef map6 type;
};

template< typename Map>
struct m_at< Map,6 >
{
    typedef typename Map::item6 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 7,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item6;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6
    >
struct map7
    : m_item<
          7
        , typename P6::first
        , typename P6::second
        , map6< P0,P1,P2,P3,P4,P5 >
        >
{
    typedef map7 type;
};

template< typename Map>
struct m_at< Map,7 >
{
    typedef typename Map::item7 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 8,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item7;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7
    >
struct map8
    : m_item<
          8
        , typename P7::first
        , typename P7::second
        , map7< P0,P1,P2,P3,P4,P5,P6 >
        >
{
    typedef map8 type;
};

template< typename Map>
struct m_at< Map,8 >
{
    typedef typename Map::item8 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 9,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item8;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8
    >
struct map9
    : m_item<
          9
        , typename P8::first
        , typename P8::second
        , map8< P0,P1,P2,P3,P4,P5,P6,P7 >
        >
{
    typedef map9 type;
};

template< typename Map>
struct m_at< Map,9 >
{
    typedef typename Map::item9 type;
};

template< typename Key, typename T, typename Base >
struct m_item< 10,Key,T,Base >
    : m_item_< Key,T,Base >
{
    typedef pair< Key,T > item9;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    >
struct map10
    : m_item<
          10
        , typename P9::first
        , typename P9::second
        , map9< P0,P1,P2,P3,P4,P5,P6,P7,P8 >
        >
{
    typedef map10 type;
};

}}

/* map10.hpp
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
*/