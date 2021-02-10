
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
C2vTdDKL3e/f7t0fYxaE1D3+r979JdzUjTzKUT3Zjy3Xmqw+xfK2CkWGYtN3RLY5csNJqOeeAXTsUN2m7q+o8nQPCTcceGqsqUczM65hhVhBV2fSdB3vvcHa6jw8wg1YY/1l0+XLkR8F1OQeKkVVkwlV8+GRuD6sLVtMscu6MDlViLhSagcQsrJdpzR5vFJyYwmHkyjyh3EXuN2l5MumqYr9AUGhjOKVTilfcgB0LTICUqgKhW0q2OVF0RRujbZ4XUpzsoi71ipppJAFjevd3T3YSR2Q1fFbx2kG6a8JtV3bcf5nPjvOVafx+8jiuUfbPPf8B/UHUEsDBAoAAAAIAC1nSlKw+y3lDgIAAFkDAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODMyVVQFAAG2SCRgXVNtb5swEP5uKf/hlqqq1CkiabW2ylgkSliLRCAKZFo/VY45ElSwI2Pa8e93QJpk+8LL+fHzcj7bBisjeIUzZucyU/R6w+ZD6bSaMX/hLFnsxEH3AGedPMPcf/LiZLSYf+uLrhO6XhA4iR+FbPXTvXm4nTDbOpHYVs/LLtgFxKjfUY+qPEVma9wXDQGqrijKdMb+l3CdpQNB9OSHcz92HgNvzlbeMnjpvHhh4rtO4sFX
*/