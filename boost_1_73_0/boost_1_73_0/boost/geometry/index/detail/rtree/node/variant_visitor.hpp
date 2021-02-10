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
LBV6gwgJvprBMew+2+0WG0OBLmVYjmDK5TFX3I2w0JEh1TcuFguLBUNTI4paGhj2oIpY8ThjuRBjGvInbYtVKLp5eLr02ikwR+P5R8VSeux+zCbXo0FleI7K3pUDD6U0ueTKCzsatVVWlAHzA/Wmwgm1s/kRrcSQyjptG+TRjWRKXZ8ik8Tsq9J7gbmBvqtZqldkDTSaK6y5dA3UPAY+izgWWrpacvVBS5VhJhVuKEYHnMNKKBCpYWhlrMRNNzBMcMmSNDP1mGRu6oWaeld7fZcSbpN2N3f87kF1a7UrbRgqMml1Bx4q7yxC365xJOY5N4vUBkdW2euUO6hNN8O7zZMD2gC00ufoGI5xBsOMDqF17R82g0UjobDpcSzoZLoJBlS+3DNZ7nauys5jnvxHTaWdaKoZC7WBElYzzXavaf2rXjNKUgUfi6WuSnh8i1XLfN/mEkmBwmN4VcBxU0et6qJ9X2S3prdptpZlmgtgTZ5q7KXNTrSZdfc/1L5yMO8YNt++aT6LpEq/Kh0JKiXA6jymrpRZHRri6dlQPmzW0pIYK/0s6ayaBaUV6/RZKZ90faoxp/Vw6QoLAV5Vmd+EDT23AmOMyNST9CxMawby5vpmhbM14lTrmjWo6TRhgfu504DSimmUnHaK7FQi
*/