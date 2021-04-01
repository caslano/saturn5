
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
R3eyh3MoI5QjDSHIRT4+Cj7TJaSnjv5yBA2i/32FIA6cmSzHJpQs/72aMnOl+J+UnArGlIIzR6cCjsZqLNczSQ8GwW0W2uCq46Kua7+YUzsQlOdrGEDJtNagRs2eNqBqCxe4ne26a3ExD/rh04riZon/7sOL7WKvrJSmsbpSeBsFIxjdvpJ67iEp64nuf6DmEI41E6/8U6nmiMHwMMaepqgmXVtyJe95O658SrRG7rMuEXyxe4hl0xCicIBDJyVw91UIn85MT9U/a8YNjKm6zFo1EoBC7CHyTSyVpxptGaRlxM7n7jwgIYBrAer1pYpKVaasrc+NQXuZ0apnKwGHx2h/gMtXbz+Qli6P4ib7y8bNv/PC0Lgv5G1iy2FdAOb7x0PiF2dmkpMDGQQ2TRo11A0shTea8e2iU/sjbk0d0TN6hEDe18J67dAg4raHxkmd1EuY47i58sQN7yFCOyqDqACcrOQ+8ASPKRu0jXKK3jJk1PHE37hw1FX8zS8lsGNhhFgLRq2bxqWjPCIIrXMvSuOmZjCzAgWZB4tLG6ORyjiC47YA4A7n54Zeeg==
*/