// Boost.Geometry Index
//
// R-tree node concept
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_CONCEPT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_CONCEPT_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct node
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_TAG_TYPE,
        (node));
};

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct internal_node
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_TAG_TYPE,
        (internal_node));
};

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct leaf
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_TAG_TYPE,
        (leaf));
};

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag, bool IsVisitableConst>
struct visitor
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_TAG_TYPE,
        (visitor));
};

template <typename Allocator, typename Value, typename Parameters, typename Box, typename Tag>
class allocators
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_TAG_TYPE,
        (allocators));
};

template <typename Allocators, typename Node>
struct create_node
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_NODE_TYPE,
        (create_node));
};

template <typename Allocators, typename Node>
struct destroy_node
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_NODE_TYPE,
        (destroy_node));
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_CONCEPT_HPP

/* concept.hpp
ixUVKyoqiK2KGypVUGxRcUdFRYsWBRERW5d+97//m7z3ch8Ea89pz2k4w/dm5p/tn7kzd+6dOzOtah+cJvWocoRuS6x9+FIyxbTpQQMmyjCudWRkG0rYs7B3FPsiazT5uQoTGraUzomgpi9pJ7I3WRfx/7zgO00TJ32Ojm1cS3IJarZFl0Uh+bzUOp2wthuzOnGrFdmvmD6wl/h3k35F+0AN46vSNx2nvxkerb9JC+tvjL7EPQuqu9FFhl67ZBH3sHKG9VPzddO+1zG1Ma9grrSvb6dOpxRNzZmSN8O5WYv+fE3liSU7ZI1d1hZt/1HGAMKY9QSjsceJ/JaQd9zjS6bzHCND6zVG/J+0ruH/2zAPa5+XbeJK45+Z4xdcmUO5y7Rv0TUMS7Y4z0wzjByPMQpLJhjRkHeOzUS2ntWMfmEDbT8dXeXY/YKvB71AXH2WZfgSa9ajM4htHLKu0/RT7SR8Tthz09xfcb6gfba+1xZdhfXBMzo6kU7GBDAFmPj6/PeE1K25AZ84rWSKfpzrWlfUr4apbeqqttgvttzKXVf8Rpxw32Lpg6qML7HJC8ijyZzWS5nuT74Iv7XSho1H2D3zfi1zGqammmE8yFrqlLlscs7Ybpm9cs4eMHJIjt1Cpk4vLkYk5Dm33sdGfcccnt72U6um93Fd5pku6ZWWlIatW62fLO/BqR4z1mm4NOnfHpJ6sEPY31+bvtHImHWq1chzsE2RJrqWNE2fQjq4mXTC2tDO05xYtJhWRx3Hd2n5QhaP5+QVF5dcWTAhyjiuYYgp3ozb5Vom4xfy/j9/YnHI87a3xL8V8w5PiEw5MpXj7Rsi07ba7S70+qoVNvaFz0fXddLzaDF1lAXIJT1ZVQfFJSWTp5dGv5chjLnvPR97O7E/b6Xw/1OYKGtBNFw9Mx62FvsLXJE1rC2YoE7RiXk+Mkxk1llLrOTQ69Q8+8gW/9usxWi1EX3cLup6KGUdb69Dy0pokdA8YXhMTGI8S8gi60XHRZ5/SByFOnZ6gnGSo2LXekqGY0SmPWWx7RqGkdrP6F5i+X+le3LVH2u2Hpf4mTvWD792s7pUjn2pmO2YCchkPlW1XssmF5VGWxudFtS3hHuEksRY95hnUhqfrsHySLhSotS6Nf5p5v7lDLE/aS3i/4cw9viznnrZ3dlZ18yo4+2R0NJe3JzAf/5abutqNO5iiasdcTv3umvFnm/V5F8nq2XU9TZFItfk364Lj7hpeamLlXa8uL9Yx7FvNPbw+xJ+yN/ftG72YH5LXFlPm7qZklc5e4h2val8U6PbPLH/2eqiurXDneP0ReNpo6YuL33auS47kacHMKpPjc+sUdV7fye9bOOfLtfDKOxjxT6K2me+IW7sKytuNZGRexCNQ/TvXEcmnknWUOTEzYTrjAttyYQtmVoycSIyQ5LPIRxjgIb1yLqxbFuVtJ/BtPUJ3XRe45+aGEjktsUXn8hUeliVCY4vgGdMatT5jeZxi6NbtdM7PXPi9aCFhPuThLtU7Sac2/zG6P1hCTNd2uMvuX922iN2cXPqOiXs3tmpx7Sw+2atF5XNNu6ic2m/6552b79Le2iGHFjDMOPtd5jPmPbL0u8Tz31FnlhOsDZX5RqZtbn3YuffCevCCXeG2k24Ku1L69zkx7WutM1PcOL8ReNwRtg3AmFlFb902Ez8wsojcTUJr5+wMXxtb13PSf7qKWfazxFd6kNfWoRc4zSCKaZONExzM4Z/IvaWnjqk+GeM0Z32qVpHGq6JhEvHvlfsbTzp/L9Dde5Dp7Tzsmn4p+l75g9Erp3HHsWfw5i161rn2ofxp+1a+7AWW23/fbxnqWPG/1iryHy7kyn+bzM=
*/