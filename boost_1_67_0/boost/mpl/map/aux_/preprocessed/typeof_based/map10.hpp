
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