// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017.
// Modifications copyright (c) 2015-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_BOX_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/expand/indexed.hpp>

#include <boost/geometry/strategies/expand.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace expand
{

struct cartesian_box
{
    template <typename BoxOut, typename BoxIn>
    static void apply(BoxOut & box_out, BoxIn const& box_in)
    {
        geometry::detail::expand::expand_indexed
            <
                0, dimension<BoxIn>::value
            >::apply(box_out, box_in);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<box_tag, cartesian_tag, CalculationType>
{
    typedef cartesian_box type;
};


} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_BOX_HPP

/* expand_box.hpp
zOntaOqvnvuxcp9Wzk21+7HOew5/H6Rux1VdzNd5ZZdK+wAfNf1XI+nn5R7P9FuenHs15N3xZv5PD7HaP8zXp539zeXX7npW7v6+chq496khzwrMfWCEu/rAkOdX5veR41x9/SQlGd5X/96tPWQybmUYy4lPt6n7SVe2/XryT9kf44Jd+0mUvgwbjYsYZvr2gz07ZXa2/u2UWUO07WIuV6H91QzMlPp5jpc8yxjqHN/qUYZskYaUK3M5UtLR8nJzOuTZBOVY3k33VevsD1BJh/1yi3QoR/9sbkVx9c/DH+WKspH9JzTz97taLyeW/Snk6d9qcuj9K0W5tvlceSShl5fhhu8YSTmTbcOlXwLTu/djwu6Z5XC1PbtGXTYrpY470tSHVGwS5zrSZ5WhTwzlBrJWPt3KW7RpelfdvVt9J56ESr8oUq8yTB1PjhO7/NX1NB/vzG2QKvXxlEtaV3kdSZkKHag+g6kZZvhGkEX9po2fxviHlWP1cFc/B4X4hp/5uKGV5+6h6niVLF/5/ZLhWrlSf//yKutyFjyI//HzhJT3R72kHg3zLGdywW6sjhpwL8/9npicA6vrYU91q9fLJT0bJD3rJT15o+pOT2Jmhq1h9brn/vf0KOt6oOIydcJcuQ+XjUo6okbXmQ61OpB0JNeTDrspHeSRW50bbCivYNnP0Ej9vkearJu5zMt5iPl8xfw80pkHy8ZaH6NaDlETHctvQXgtKnlQNs4zDyxv5mhtTurpK8TX21UP7ZzuqoeU+3ePyO9JsQzRjrHe5ryrNuRda+nz5j3n+RV1mfn4JX0M6f04JTq7cZL55hqOWV1M9RtVFr1oJbKrex7/UjyPb6Z+kOxkiZr34Rbbo9itL7uOpmNjQg6ZGpuS6N5HSKpe11ZZHDOP4BHn+meQZVL/GtKTSOHsYurLR9YvKpMmKlJO9LJFnyJSj1WyTxRwt3ViUyLCVY+VYzPnOig1g9RtpuXZXX3UOIcpKVDneZg7tdGD1XPMOw3zLDWMK+2E9fHzGX8xwyZc5xq/0mJ8Qk93OdO8yMjbxrumKXGVCyWLTePXMP5pho2Y7Bq/wP0eq9S9aZKOefIdtpunW9e1M+XjEzHy7GQqKs/t7DO1/cn8EFQ+JCjVSv1tJJz7S6x5f7Huf9L8vEz71txK87HFrR6izMo286Ne8B2qfifhZTXtUt949gOljR/KH+9mWNNY1/gj3Y9/kp9/lnkukvxsf4v6+5X+5vrprOTnIbm2PSDPmEvifi4/DVVUg9o41P+80djf1chh8g4U+1UA/tBMfZZYFq+lyZUcdhZpVVJ/v2TKth0027Rtrfscs3g2kOe6H2Fjy8o5ljnvpXzLuRSnyjL/mW592eVatOmPcNWn+nlUqLn+sy5Lkrdt1fMtZYb6OZfdol5M1uur2cpmdSagrbGelrpKyqKcx5n7g2raXF+Ws2yeZ8TDV6jPKXokuMpmtFVZlvF9hqntYB8yjB9juv9hHj+U8TcybIdNzuVMxwK2E6mWZZjuQdqlYH7WRL1PdAyLlTbIKZ5lKZVuEZNtDTn34Fw/zXyub3crQ7lWZcji+nyosQx5tN9LkW3jXl4kr9S6hgOBe3lJ0MtLhD4sm2Gu8rKrrTNtNDNWBrv1wzZc+raUPOsjeXY8zTLPbKTA1pC61dluKEPPN+t61SLf7A3It7rWP8x9/SlPDkYsGq6+T5+eTnrqyPcIU757lq3CK5X/M5z7DoPwVFM1n0oyLfNpdqbcjyuv55qyxHBNuTDbnF+VbvlVZZFf1Zb32Mz51U3K43I/+f6rqX8693OlaDqSVM93wp3z064rnccBvb4JMz1DjJc60pyHHc39DDO9evY=
*/