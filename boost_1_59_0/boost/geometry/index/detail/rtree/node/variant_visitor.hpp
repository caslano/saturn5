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
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
*/