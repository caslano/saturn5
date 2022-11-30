
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

template<
      typename P0
    >
struct map1
    : m_item<
          typename P0::first
        , typename P0::second
        , map0<  >
        >
{
    typedef map1 type;
};

template<
      typename P0, typename P1
    >
struct map2
    : m_item<
          typename P1::first
        , typename P1::second
        , map1<P0>
        >
{
    typedef map2 type;
};

template<
      typename P0, typename P1, typename P2
    >
struct map3
    : m_item<
          typename P2::first
        , typename P2::second
        , map2< P0,P1 >
        >
{
    typedef map3 type;
};

template<
      typename P0, typename P1, typename P2, typename P3
    >
struct map4
    : m_item<
          typename P3::first
        , typename P3::second
        , map3< P0,P1,P2 >
        >
{
    typedef map4 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    >
struct map5
    : m_item<
          typename P4::first
        , typename P4::second
        , map4< P0,P1,P2,P3 >
        >
{
    typedef map5 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5
    >
struct map6
    : m_item<
          typename P5::first
        , typename P5::second
        , map5< P0,P1,P2,P3,P4 >
        >
{
    typedef map6 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6
    >
struct map7
    : m_item<
          typename P6::first
        , typename P6::second
        , map6< P0,P1,P2,P3,P4,P5 >
        >
{
    typedef map7 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7
    >
struct map8
    : m_item<
          typename P7::first
        , typename P7::second
        , map7< P0,P1,P2,P3,P4,P5,P6 >
        >
{
    typedef map8 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8
    >
struct map9
    : m_item<
          typename P8::first
        , typename P8::second
        , map8< P0,P1,P2,P3,P4,P5,P6,P7 >
        >
{
    typedef map9 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    >
struct map10
    : m_item<
          typename P9::first
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