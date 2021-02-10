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
XJJfgd5O5PIsXPpEsu4AqUH6ek/6oHdg1YzmzvQ+rOF46mF37n99c+rIw24jMsBNfk7dHB3HCdST+B8N/Jji2BtpzfVUbktSfFxrrWRYEC4z0n5/a4+lZ8DnW8tqmdT/X1BLAwQKAAAACAAtZ0pSUDtHzWQAAACCAAAAHwAJAGN1cmwtbWFzdGVyL2xpYi9saWJjdXJsLnZlcnMuaW5VVAUAAbZIJGDz8HRxcfXjquZSUMjJT07MsQIyFBTi47WsIYyi1OISGLs4sSwVyK615uJyDg3yiXcAkz4h8cEePp5O8WGuQcGe/n6uLvFuPo5h/qFBDiZgc9Nz8pOABisklxblQMyF2KQAMQsAUEsDBAoAAAAIAC1nSlLHuNX/oAQAAPMMAAAXAAkAY3VybC1tYXN0ZXIvbGliL2xsaXN0LmNVVAUAAbZIJGCtVm1v20YM/u5fwWYfaruKnXZf1iTNGqTYZqxIiiZFESCAIEtUdIN8J9yd7HhN/vvIu5Mlvy39EBnWC0U+5JEPeRoPX+7owRCePWL3j+mgq7P4otU/mNrd2nH8CP5HVnd0fc7JGFqTx3gAz5s8Qt+ZxMHLKd/H8XOO7jg2Po3Z8i7mW5KQGVteqGqpxX1hoX8xgLfv3/8Gh/Du6N1RBJ8SKbCE
*/