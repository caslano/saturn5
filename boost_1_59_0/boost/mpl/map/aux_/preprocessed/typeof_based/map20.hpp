
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

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10
    >
struct map11
    : m_item<
          typename P10::first
        , typename P10::second
        , map10< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9 >
        >
{
    typedef map11 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11
    >
struct map12
    : m_item<
          typename P11::first
        , typename P11::second
        , map11< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10 >
        >
{
    typedef map12 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12
    >
struct map13
    : m_item<
          typename P12::first
        , typename P12::second
        , map12< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11 >
        >
{
    typedef map13 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13
    >
struct map14
    : m_item<
          typename P13::first
        , typename P13::second
        , map13< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12 >
        >
{
    typedef map14 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    >
struct map15
    : m_item<
          typename P14::first
        , typename P14::second
        , map14< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13 >
        >
{
    typedef map15 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15
    >
struct map16
    : m_item<
          typename P15::first
        , typename P15::second
        , map15< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14 >
        >
{
    typedef map16 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16
    >
struct map17
    : m_item<
          typename P16::first
        , typename P16::second
        , map16< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15 >
        >
{
    typedef map17 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17
    >
struct map18
    : m_item<
          typename P17::first
        , typename P17::second
        , map17< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16 >
        >
{
    typedef map18 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18
    >
struct map19
    : m_item<
          typename P18::first
        , typename P18::second
        , map18< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17 >
        >
{
    typedef map19 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18, typename P19
    >
struct map20
    : m_item<
          typename P19::first
        , typename P19::second
        , map19< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18 >
        >
{
    typedef map20 type;
};

}}

/* map20.hpp
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
*/