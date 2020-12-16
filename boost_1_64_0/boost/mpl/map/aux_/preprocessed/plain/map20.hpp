
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
EifjJpyCO3Aa7sfp+Becga/jTP47ibMkn2fjOzgHv8Q8yee5Mt7fPPTG+VgR87EyLsQgXITBWIANcDE2xyXYGpdaxq+Q5zR8Rc6DepyHQ5JPr0g+HcYaeETy6a/YFo9K/hzD4fgqjsfjOBH/hgV4Atfja7gNX5d8+Ts+j2/IdfcPy3Uiz2XYz8F10lm+t8KxHHZBb+yKAdgNm2EEtsbu2Ad74G432sY6Gr9Bxmz4TdvJMh7Db95WljEV/uvayzKmwe+uzax+P2ki7CecIRQTAg9468IIIwkzCTsIJwiXCPe/zHgAhL4EA6GQcIRwnnCLEHTQWxdBSCTkHfS0v3VluUf1/2OSMu5O/f/bATqpu7GOLfsooSKhGyG4I7+VCtT1BBlJWXEGKm4oSU12fW50Xx9t3dVGChNlF5by/VNskMAaddnweUmTuq66NmlqvthBmia0KrGs3SY9lnLKXZWNcVvK9cKlXkldvk5lhyZtsVJnX5/gRahHqKuUoarSRhwt0+OUWU9cL7+zzavaShmi7ETdv7+v1G9/L3nzDaGBcr5M8cfpuaoSY5Jy9TrX6/AfZnumv9aUHbKHGNOYA1JeLuukONw4f7S/ar3DvsbyN31corZ/P13XM8dZ61QbdpT4pL91U/OxSj3wbi+OVXyfHwQ+S61lpgnxrsyPXcFUBv+4dX7H55db5mhso5N1C5fbz++YsNx+fscOy+3nd6xiWdcizLzu+DLLutbmdWnWdbI/6/ln8mJ+ztnVu0udhanuNz7VQD6znWrcAwP5qa4XUp/PYqmzniDzq6jrzVJ12rlccqSiVcq1LX2+A6TuTOKSa4BtVXV0E1RzKl9arp1D+YHHta9b2bweanmtvdZ3SB32nlJy/rFxR14/YT3/xokgda7VX9ZeaYwnnsvRku/W49bOV5tNrVNqZobUYVjuFVJ/aTd2Bde71Gkaa0etdQURNazzH92yucfclLoCJu20q7/0U50n/k7uWs/VGj9T+viTse4vsizPTOTVIF53XaGaT13i4/CUfNXkbZrUly+X+8hiwqt8iIpWauojWnJdlXgfUV/DvJ/NHFzDfAabduScDlfum4YMriPjumas4yGZtBm4gVjzKUfJB7meujxpvj60dUChUsc9ryzHILZgf8ue1B6D6fTKnLAu3CeK17K16vWZtdb7RuAay2ff8jnPX21/j9ixyvI5b2te13aV/Rywx5+yrGuhk+u0t2VdmPG1n+V1G+M2L641X8fK4cl+rOuSM7PSnX6vGAjKG+IMMl6Lg8/AWakDz0rkzKGfjHXyRmU+58qJM3/25frNkgYp6vtERmZMTkZOdpLMvW659uNke/W1eEvO4z65Fp8ncJ/noc14Hk23POOdvuS2Pr/mfmqeX5qPtcxLbW0PwPuYac10PW4xpot6gGra4yiWn8vrZI7iJdiK61G/wXgcqp8spuNgnhq7xdm4IMc3m9telPx7Ro7P7h7lr75Hyfmqe9tUv5qgn8TFZJ07tudt7b2qwW1pbyDf/c3lNXMA2333R96W73TVtRLGOq4V47zB5vtdxG3tmDFB6n3Kd4zyvnDZVi/76iDvU9Jsnl84RN6TmZU6xhiBbBtsOT7TtqG89pM4zNtGsS6I9BpvGMoNzHxPt6bH8v3aV9axrea3ygmp398l1/B2uYbDtxjPvfJLjiu45Lm6Xbl+eS3Xr3zPy7Vr/c2orquWNg2qunZOi/Iu47U8fov63mo/f/5W5btXbE0eBfMP/mcadosdj+HpQqdzpX2G6V66Z5v23rpum/XeWm2b/f2xknVdK/M6L+s6y/32m63q+6g2H+W3j+YeKL9X3GqjdE3uBbxNmXbRku9Xayk=
*/