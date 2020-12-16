#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_EMPTY_STRING_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_EMPTY_STRING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Ignore = int>
        struct empty_string
        {
          typedef empty_string type;

          static constexpr char value[1] = {0};
        };

        template <class Ignore>
        constexpr char empty_string<Ignore>::value[1];
      }
    }
  }
}

#endif


/* empty_string.hpp
euuDZSo9MYE7MYCdQX5ATa7mKKk8U1kPX6kStp1w/cUV/yqDkcfV1Ie7RB9uegDl8Tq+02VcH5jdoj5enyRY30DcB6J/Glh8z/CwecUthvcpDGwktntoNBYn6ECwD1Vj4Lv37KKnmwnkp681sMGheGwwPjQCWJ0PG7X5Do2MUrYW3mXLp6fjUM5lJryrm1bZh70zxR5WT4c9kUiR9roXujwDTL/ucXz+mokx74VU23BDGF5mw2d7wTp4jQ1v9zbDD3Nfh7OvsGMPHum2X1TYpD0N8FzokMQoPZZKK809tEpNHN47MEJ7cXvPbmnh53OpR5xRwpu6CthVJrm1d6tEndTeSsz2rWFadkM/sX2r1/fBu4P9Gu+0/UvCe5PZ8VSmFw9tyntctd4IrRL0ZYJ+do71ddQ9Tmva1i1Br+hPQ7YP9qezycBpQZCjv97ZTzzUdUVZNm49zcBsubZfBmmH/XdpD/P+1ybsh51j/SHVLtkh2mZLOd7b1irP2CsoL24/z1tkO2pIocOWp4Fdi2hq2rN15Lff+qMyfBxgPnJx4OOA5UXByiPNQJadQ+HqyuuxaHkkvll7Ml4b8GxR5f1X+ObeXX5iKVf0xPvw+dS0eBt+t2snZSbSB3GGAd+UY5DfapkfwjXI70zkN+TqiYyTYZCj0YGUpz2LTGkey2nsHv943jw/WSjSdXqzBTpBvsYzmZliHvnMg8D3/Wgvyu45Rr+tTPthg6PkPsrPD4Ew7WiHn/bZ4TgRO2ReTkR3T2dLqdih1HjJAHjcmIMTJ3eY41PBGMLxg6kCDYphEG9ZyfSZTJpqtSc7S/7A8KZ1NfT+XqKNLmn2xoZHacwxIxVdAh4w39idi4zzx73IPV6Z20iM9gmh1zUU6077OtxzLOdT2OjJPR18Lu08+l5u/M7Q3wsWLnPHAJ0N6dYEzI8SttVFHcLHrv1m/xWPs3I1mDoEeX281QU7k9mJTCpP6S+AzCZkH3iAaPu6o7t6fVvtPLtXL/yt+m8rGbDre48WeBXuCs9uuQ7ZR3sFvNaHx1MZ8tVu/GIAvsaO30AXea+z8AAd5z/ONGPPSGo/3WyhCU8+JXzCZrw4rb+l6nGP2dofScGvGS9hHu0aNaeP4917zXGdWLdlUgS83J3SReZh9prrcG7AuBp7r2MTYET2hwvB6758vTxTQuFtkr8UbpB8pfDZIryGwo2ew8f8YxAet2O33c6LJ2mrm99JiKf27yiE4ctNuJ/DV5pwjMOvMuE+Dr/Wi02kRZlv9GIFGX6rFxs7JMLXEL4Mv9uLjcvw+71YUoavpfQzIny9F0vL8A2Gnl6m5yYvZrkq5emzRJNMc4tJE/fTTBBfbiO9VjST84lAvgpWJ59kdgaEHN22JFonS/+N1eLN2f3o6/K8YRudO3gn9ztXb09wu1QzXNbH6rIajhtJjds+yO8dcFz3xATNWQqekBf/NES4ZYS4NOW5htMNZO01M1/vd+AM0gHBh+FF6GOpg0nXaR3sr5B04Iwj3omZ6pgPf5mX7cA9bfDDi+aHTVsd9DXE9ECfzpTTp8NDA9SqI3GukQsvpx8WmYeRj3yHeye50IE3qPCGQLED/gmBhzTOWulsh3tf6VAHxx1EHP21+V2C/J6E/Nj/OvvUeQri5Ptma9fCJ6CNY596S3DP8WkEN+H1uMs13sznpUI/9PjdpfwqPpPSbnXOVE3SKQbaDEz648TaNYDhBU9a9zDtt+zZth/025442s92kd1bfzq/ZbVB2OX8zmAvjS+Z3H5nnAMMwxHrYD7H93jMM5/nntEY2N29I5Ywr0IajdA/sIP+9MUSpql3jODY5p4FsagGkWtcD2D+/1oi9A7mZ1w=
*/