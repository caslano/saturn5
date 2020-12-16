
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
ElZ56+YQVhN2Ek4QylbdWP2q8lX5+k9+/UH1/7QM/c2p/x/219nGNJLfT+ukHriGsFUZL2ifqS7Tv1uoeQgS05RrbvX/d2/M/wwZF8QyvpWRIPfVTcs0UPfBV48NorrXaBprpFuoqW7UX9oz4qo6jpG+PYz/7TftT9TAEbI/DK5i2id6NtAAkVHRcXl+674pC6am5JjeBzg8byD7avfswwqp5waxj/WxMRaxbwXmfRszYuiIgTSnpE+OT84y3CPtKc536EGSTJnpaYrLn1jU+0baZd9s+6oei0rd/6HsyrVr51rThpKWSeGdbG5nuSLHZrJ5O1d4b2B5fZY5jy7ynu0ocxqa5itMYD+WsW8DKYst32ZPLG04shzrJWfyh7JsGMstIgzh842mZaWtRpZNkzyzn99xveRDCtbGBHyDvAs/oMo7ZYAmU6Go4JwCaVnWdqherXifnKUk125+C+kvYpujgmy2jee1k7SkEr0+J9e0XomTccl2swzj7TOAlW1uASl71nNkdC8pV9J+lch7Q06GZnxFg1IRkHuP9XEJ7r2T3/2HVXlhVAbUkXYfn5tXhi6dd9zXi3wm6Tbnh7JMINvIokRZ9pXPpMxojqunjDH3tQf7gkdxD9s/8r5tX9RXMGV/InQV3x+OscP5Xkd1vqckGrn+Oj3nZXwoGR9LmfwznhZF+TxAPtcrZUb5XLYRiJt9lba0xHQ2Yoq7pd1cKUekPU35ZohXTi7Jq0/43KDEJe8P2vVl2q9eTwYNVT4/bPk8d0q8kkx1/6i3wsiDrLxMS/r2yLLJ0uiqblsMJNNMSptvAO5j/cKPbGNbUR4Yii1eybZy233trrtyrqnzXc4127Fx63vF1bwyZXbzylyUc5bWSIqB3ffRdHO77vijVWTODmn3Vb1Xtx3OlHHqfpW8uYxvs0zgx9a8keKakcY4pKTJnbG/vHzrf2LpE+c6v9TlqZGqfTs1cbqe5+WmZWbNyJS+ctb+b+a0JGdlZCTK+Fu265I6H9IIlr5udwUo8Zjzt9j877xXCrf5Gt6yOnGSDzF8/rGy36i55k3X9q0jJ5QWd+sctSdlnb910Ja7BjIO3y757n+dcIC8XUve8B8/FUxXePPQsRX8LWM7/x1/l0iZc/xdoh6r2NtuPFH5nbXomCltaSEp5l8jxCO/SCqWvt/6e0T2yXR8AsjH6qR3Hp+/qKQP1ftGGjXzLRn5QNrkNcfjlOzzOmknf5awuyn7zCBL/Ge6/JiuKfHJqfrkaeXez7Dc/zF4mn9v8Kd6PErTZ3w/WK/L/E+uWdp9T2Ihy/2bT0xpYayRenI/x+59neO29+rz2EfG75sg5/E4/CvHM+G4bd/4PlPunfGVnZjh3ji9Xr45nzn2bR3di2PIxnTXud/l4+S+WJl8/2dICuRaxjllupYpq2v6uibrbGXaoBpj76xtHTZvzpejx7X3tU5a39vNsyX5dI+U+zxCKmnyOaHNp+QMg9vlfXIv1bzi8j4J1WUv+FbzitES70jCuxyfQrt4uZtG8Sj//pblWJh+u6Tww6Wce4+vKcuRYQ59I1O045aulnRmyzmSRYhlfwI/16TTjTmutXkkv6c0x+LgbeYFt0qZLcTDYWgXF2OzuvGd7OUb8KV9WXXMi1r25VLKoH2ZLnVSLi/ZlcsyN8pl6y+05bK73fs1du8Lre/t5jv3cSy38aS5+EtbXplOK6XkVuC7ZKJd2Z3opOyekrhHS9wjCO8r9bxi+7iV0uv+uMlSJhzLrWMZtR6nzcRrissujbH8X3lFSrkdRkhm+6WOaczRu9FnwFJ+Ens5j29IXamzcLzrix+QtqivNPHlmkqwHI9gt+u+5rFTj50=
*/