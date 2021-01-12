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
g4Ob1SmBeZj9AephDaqHWeDvQU35mJL0eLEM1cPaPtYDRmeG2My2q8JhM4k983Hieh/3jaqglQo4OFitCubAfeJu6BOLU59AZ4s97/0Ml06MhCLXB+lH6FefAF9C9Am0WQkmC8F6NNTD1FQP2N5r9l0URxjuLI4PqG/b+lYP4G2b79+lanVk6EzMuljkMPCBorpAee/77TraSRwtvptWfbs+4FNdjFQLw2mII2i1Lhwmk5kj
*/