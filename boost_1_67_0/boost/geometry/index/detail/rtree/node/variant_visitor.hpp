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