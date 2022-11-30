
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

template<>
struct m_at_impl<0>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item0 type;
    };
};

template<>
struct m_item_impl<1>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item0;
    };
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

template<>
struct m_at_impl<1>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item1 type;
    };
};

template<>
struct m_item_impl<2>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item1;
    };
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

template<>
struct m_at_impl<2>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item2 type;
    };
};

template<>
struct m_item_impl<3>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item2;
    };
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

template<>
struct m_at_impl<3>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item3 type;
    };
};

template<>
struct m_item_impl<4>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item3;
    };
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

template<>
struct m_at_impl<4>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item4 type;
    };
};

template<>
struct m_item_impl<5>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item4;
    };
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

template<>
struct m_at_impl<5>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item5 type;
    };
};

template<>
struct m_item_impl<6>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item5;
    };
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

template<>
struct m_at_impl<6>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item6 type;
    };
};

template<>
struct m_item_impl<7>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item6;
    };
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

template<>
struct m_at_impl<7>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item7 type;
    };
};

template<>
struct m_item_impl<8>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item7;
    };
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

template<>
struct m_at_impl<8>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item8 type;
    };
};

template<>
struct m_item_impl<9>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item8;
    };
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

template<>
struct m_at_impl<9>
{
    template< typename Map > struct result_
    {
        typedef typename Map::item9 type;
    };
};

template<>
struct m_item_impl<10>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_< Key,T,Base >
    {
        typedef pair< Key,T > item9;
    };
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