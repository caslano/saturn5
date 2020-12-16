
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
A/fiTnwJd+GnuBu/xGfxK/wjXsXnUNqFUZaovj617cIayPXSEP2xETbBxtgDQ3AkNpXzFEsokv0Nkv2VwyiCTlHyZTD64xCsjkOxJkbjwzgMW+JwbI8jsD+OROIhf6U8EFMkngcwT+Ipks/xW1gOT0m8/5TzcRofxLexDr6DTVE9Z0NnfE/Oz/sYiR/gEDyLcfghJuM5VX4WSbrCHORnX0lHPzn+/pKOAdgCIyX+gShzxEiZHPcK2Z96jpjPZH+XsC5+gY3wS9nfV9gOr2BXvCr5+DVG4XXU4w2chDflOv8OZ2ExrsfvcRv+gDvwJ3xWxl45oIAH0Us9h8oC+R1uTLd2LpQcua4mYAWcaNmOcIftMmS7TNlOj+YxdiJlu6qynXqMncWy3RLZbilWwWWqOWX0sn172V49pn+CbJ8o2yfJ9slYE8dgfUzB5piK7XCsas6cI7L/YNm/es6cAbL/SNn/QNn/INn/Y6p0XrtDOjvIfjrKfjrJfjrLfsIlnV0knV0lnd2s+U95hPP8nyr7nyb7n67aLla283aw3cfyefwXlsMLaN5OL9sFO9iul2zXE2sir2U7eR7HKg62i5DtumNl7KHa7ohs18RJfBUlvoaq+HJ18owLc2S7Cpgm28XIdnESXzxWwwSsjUnYFpOxI47BQZiKKTgWJ+A4nIxpOAPTrX2ieS513ie6nep9RfI+3xLed83F9/kUuBZv8wLX9hdZwv6CpG/3CtrP7r3uXWIf79xp5XWJm8vpZhLS8srptoSX053dfr8ud/19usBWZXUVjin9Rq19wXdY+oNr+4JHEFYdtbZhNlzTzqGh7f/ttO+39Pd2bU4Nc9/uMIJtP+69S710JwjSl9tuvo1C0ncRQzuq+2+r+207m4ND20/7JPvx6WTto32ZOG3n5dAt86LdtaVftvTJtvbD3n/Udp4Ox32vAx/T9r8uvmbqe12X/Uvfa/t+1/ztGIZEOZvTw3kf6zNH1f2s1X2rrfN9NPia+KKsbcMNxHf5qHv9qp31qT5N6Pm1s/7U2vbluw84mx/Evb7TN7GAY+gQzfYEc1/pIwRHfaT1hFv8O3CY/Xwioaw7gyPR2vdZ3e8Z+YzeJATd8NaFExIJBYQ9hNOEW4S6N5k3hJBGWEE4RLhIqPANc9UQEgn5hB2EI4RLhPu/5W+EWEIBYT/h4reeNvWexbN4Fs/iWTyLZ/EsnsWzeJbf73IP2v9LE7tf3/9facP/QYDOMp9dXWmzrozzXBH9MUlpezaFMhyZz07Vxs+Fuf/K+r463b6N6NXKSptAaz11U2KPU7W/bcZrpblgnCEnyzwHmT96kblkgWWOrYG+1nZGfqo5tOJzkmklrLPO5ae0hzBo2yHT1kQ7/1lGmnoOM/abQTNW7Zxo6Ymsk/bee9GH/HoFG0yTeUtk3q6hQeb2LdY23+XkPckdZZ4gyfM8aafvxb4q4s+8KYX3FM6w5Llkt2vzmi2bZZ/f3yj53TLR5fw2t5HTk5cynZPTPC92kOc3S8jza9Y8l7nJ5LWc6/OyT72TPFXyM3MmxynHprw+bH2tmvPCWf2/s3YQztoFOGuP4Ky9w92rt3fcrsFZPbyz9gjO6ufdb+/gbr29u+0d7lY7FMftHZy3a7hibKfwyoHVhcEV3kz62+yizV1OTVvhrN2Bs3YoztojOGsP4rz9i7F+v5Tce+We3IC0tOXfx5QVUm9aEYejP47AGjgSa2MsNsA4DMd47IlJOBKTcSKOwRk4FufjOFyMabgV0/EZHI9vYBZewmz8CnPwBk7A+0nbRKyDk7ABTsGBOAuH4mwciXMwAfMwBefhTJyP8zAft+BC3IlL8DAuxQ9xGf4Ln8A=
*/