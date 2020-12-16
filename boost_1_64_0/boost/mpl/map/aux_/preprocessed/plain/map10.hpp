
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
jMR80PS/Ip+k35e2n9cpu35gZx3mIpA+URJvsRv9ryz9qEiG9jeLzC2wSsr4k4Q7g5Sbwtb8lLyMz027V1/uNclf8s+hn472mks22s5z9b6WqfJC6dt0guP9EmlUjuGXpjTJXLqyHH2Z2JyM0a/qr9hGmtgjZL/CCT5KOXlF1ccyTxmONrncc1Zzrhgkf+UaarC7XjaQAauDpXy2xzrEW6iNV/LUnbHz1XHLOIMu8tfHSf762fWraqDtV2U/14WMjy15y0rgsL/q8RVXy/5OkGtDrOXawIAH/KfMSeHsAnWTrgkyHq+MxX+n5HlX9FOu06/a+q5xTZAfDeXPx62JW90/zdN2zvrINSEn3ZbPcn5Zz9HmdvOJNJc81p6fdnN93Oo414e/8hthi21fKD+yL+WPl2dXfpydhy7nOzEt4+r4S3lfK+kdIcd/uPxmC9xqSy+FlLpavD4jSZ9yo/UsdbpNG0JLn73Yyj570mfP1Xh0//19+W5fo3w+8fstQ+JyZ743wMsw9EBn3bg/pi9flE7aDaQ9odiub12U9K0bjTUwGr1xDDbFGAzFsRiO4/ACpuqkbQDjZbs1MU62O17G/YnDRjgRA3AS9sJ47IcJOBqTcBwmYyym4N2oV8W3VuJLcxLfd1KlPYc18DzWxlJsiN9jN7yAPfEiDscfMQl/win4s7Uvo9T50VviU/dlnCX59ifJt/tRnkeU+jt5J+upn0e8LOkqw7p4Fevjr9gUr2ErZAP0PQTsjVVxKHrgCPTCKLwFLeMzFEq8rSVe9fgMQyW9wyS9w9EbI7EljkDLfhdfZ79nyHbyZTv3WNeTujXWdLJeqqyXhtVxqnU9qSNDbSfrZch6mZLeLOt6Uq/F25ys10HW64i1sZOsV6iTOit+LevVxfWyXg1Z3hvrYm1siLdiU7wN26Avdse6OAz9cAzWw+noj/djfVyJDXAdNsQXMABfwdtxGzbBwxiIn2Jz/AJbWI+v1Fuxk5Pj21r29w4MwDbYCoOwA7a15Rv1TdfHN0e2kyvH14gyvojUHTm3ZT31+CIhkm9dsSV2w7bYHQdiDxyKPTEae+FYDLOmS+qFWM8+XdKXyvQe62Ir9Xl6nfXayHpBsl5bWa+gitS7pD5WTOhg2l/bHOy1sTPWwy7YGLtiM+yGrbE7hmAPDMc7MRJ74jjshfEYhlOxN2ZhH5yOffFBDMcF2A/XY398BQfgVozAXTgQ9+Ig3I+D8T0cgidxKJ7BYfgTDscrGIlXcQR6sI8jsRaOwvoYhQEYjS1xDLbHGByCY3EY3oWxGIsTcAJm4t04FxNwCSbhSkzG51CP/2LvTgCjqM4Aji8EqhDAJIQQIELkkCvcAYJcAQJyEzBAOHOHBHIsyQbCfQUIEC4F5SYgp2BFBQuChRakaLFGioqKiAUVFQEBNSpi/7P77e7MHmRXkdp2p77+2MnOvDdvZmd33vknTMZDOEbOQ5FOntdwrZy/qsixGZe35DycQn/8J1bH01gL38Z6+A42xncxFM9gR3wPO+MH2B3PYn/8ECPxHA7DjzAGz2MSfozj8F9owAs4DS/iDPxMztclXI6f41P4haVNuzyvYYSD790X5bj2yvW1D+viS9gK/4TtcT+G4wE0tUmU5zF5Tjtv0ybxSdnvU7LfNdgC10o+rJN8WI9xuBFzsBCfwE24ATfLdfg0HsAt+DfciqdwG36O2yVdO/Am7pTrbJdcZ7vRH/8o19Vzcl3tQbmvyPMW15KD+0oV+fxWw3JYHf2wBnbFIByAD+IQrIXRGCz7534qz1J8NiW/lM+vPyrLOMmvNMmvdAxCveTbeAzDLOyB2RKfQeLLwRicgIk4EdMxFyfhJHw=
*/