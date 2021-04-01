// Boost.Geometry Index
//
// R-tree nodes static visitor related code
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_VISITOR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_VISITOR_HPP

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/get.hpp>
#include <boost/variant/variant.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// nodes variants forward declarations

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct variant_internal_node;

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct variant_leaf;

// nodes conversion

template <typename V, typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
inline V & get(
    boost::variant<
        variant_leaf<Value, Parameters, Box, Allocators, Tag>,
        variant_internal_node<Value, Parameters, Box, Allocators, Tag>
    > & v)
{
    return boost::get<V>(v);
}

// apply visitor

template <typename Visitor, typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
inline void apply_visitor(Visitor & v,
                          boost::variant<
                              variant_leaf<Value, Parameters, Box, Allocators, Tag>,
                              variant_internal_node<Value, Parameters, Box, Allocators, Tag>
                          > & n)
{
    boost::apply_visitor(v, n);
}

template <typename Visitor, typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
inline void apply_visitor(Visitor & v,
                          boost::variant<
                              variant_leaf<Value, Parameters, Box, Allocators, Tag>,
                              variant_internal_node<Value, Parameters, Box, Allocators, Tag>
                          > const& n)
{
    boost::apply_visitor(v, n);
}

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_VISITOR_HPP

/* variant_visitor.hpp
/L323g3qxn3itdpJIvmFTUuqU8Nultr5C8oL1CkqqR64v+h8yQEmxozRz4opU4yOQDfu7J2URsDw6pABGoDMe7PX1XuEwdHb70xsB5YCu7FOEMCJIg3xDOPSdXq9zb2/Vx3tVCkBnf2mwafIYi/PAvT3YlqA7sHWhTIkZFTsI6NfBXenMU3uo1TdZ4F9wZBQszlkcy4zGbCVAMggf73crUweIy/RHGnlRtRaQ7xlG6Gpk5B8vj2Ip9vUmt8rM5vIVu51htAE7L2VCTj/xsKgJD1gWdTqIUAZj2pSb+VeodvG8ZY7wiepmm1Fq9rNIDrGUe4a2yBqYLujj3NCFuPSmKY0/TYUqsSlcqJcttkwUJE3fXjJbP2pfCMHe8TEGCb9/S8lkyewUAtyVzNfmNhcbzGtcVrazbA3g2MXLDS/b/Kip/xB4jkOkbr2y28A8alUcC2xwaMj5DOxiwEWqVmGgtkh2unyOnfKodb/+KdxOdCeDQ3p5DwKK3OyvAJATtNAqV4fWxG4ywH0toKuNPnn1kFV6FLFpF39z3283dg+EnVkk/7mXT5ONqb8CA==
*/