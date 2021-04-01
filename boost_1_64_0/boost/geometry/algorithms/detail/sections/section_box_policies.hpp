// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_SECTION_BOX_POLICIES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_SECTION_BOX_POLICIES_HPP


#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/expand.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace section
{

template <typename ExpandBoxStrategy>
struct get_section_box
{
    template <typename Box, typename Section>
    static inline void apply(Box& total, Section const& section)
    {
        geometry::expand(total, section.bounding_box,
                         ExpandBoxStrategy());
    }
};

template <typename DisjointBoxBoxStrategy>
struct overlaps_section_box
{
    template <typename Box, typename Section>
    static inline bool apply(Box const& box, Section const& section)
    {
        return ! detail::disjoint::disjoint_box_box(box, section.bounding_box,
                                                    DisjointBoxBoxStrategy());
    }
};


}} // namespace detail::section
#endif


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_SECTION_BOX_POLICIES_HPP

/* section_box_policies.hpp
ulY3+WQWhKmgUpb2TUpPPP2LfyMh/DvFZZd9PQhyKwt3DBFvCzSO2YkP5p3qZG4P74lfHoVEZEtqdy2OVYdc9f0v8Nhrakr8qtR89Ok4p8RQIJyxR54jnLkeKVOtRAWRoCpZrga00Khxi+aEeVzica/w80zEjY3moGc/033KNJ+7xAnZJhWHmMqVXC7HePWpZG4CQjfKsG7Oya+Odu/di+os+Vpoannfk7AHl3QVpdp2yI7/0QbHL9fcBHIQx8mFFtt10jDcjjbyAm403gHTgau8qkb+UkbkmYHvvxLPyTaDYn5tMJloZta7BM0rKJ/3Li+bGi8UCLvABgTkS6uI5INm25qUg8JCou034m3T1WwvkX7pIdFsMVC56/SPHJJoATTZcX6chAL4CuaTC58huyTBFj1r7MZHtuTIDYytWxR0bQnPBj6OFPM+KRHherLVxmDZh+OzXmdeQKrJXWu1xrrZl4bKPz0/YoSxGLNFC94mwbjSwqZ+WmrO1r9IS4f0igctPZUxFzuvq1QmuXpV8/1Oo8kAgWMp3N3nsrOlZ5l2XvAnQI9D3LcSAg==
*/