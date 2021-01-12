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
+hStyTCe9/XTX21J+YPxcX3FctxC664Qc3W7mEt0vwDGc7R1wrFSWlthvM+azJ+8juYtjLfv0IhWdD0nLJCvL2Ma9aLcwkKYLTS0NtAeJ8QcPitjFOUdFsOsXZ/xKZR3wWwt1g2g+Sf0y+SwpDiafzA+ll4/8MI+OvMJfX36xIUbdK7bWLl9CenBH1D+YLwNT9Ye0ITu+cN4HnaHruxL5zrB0ibWon2lg2A/1lr5PK27sAhm
*/