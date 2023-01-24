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
YnL8uvqOeh8tv/RZjVws8uaMe4by7Bm7MttvaE6NEUs4pA9HNYIu1QF82IH1uo2GX/RR51XGTIRNxuHCnaz7OEZ0u8PRYLmhEd+vlzjIQcXHgSeN3zZ8BkDc3MSX7CGi1aCyP/6JXSzU13D8qRiCtWjdP5X7LFXfaqyL8Y564AZLt7qWSzSenqhpid9lPV4Kn3+lQIYm9nkIelahJcPQbifpcroFp97oJ+RC85z7bv5i9Md3LmYXopUh4jiewmSJzEViURYBD0sIPTgZYDXoFARXEIK6x/v9x4XB8ZiFRw2ComeeQZ+HQroTqqKSg+YD7/3pS0y6yECNjwNidE8/on19c+5fHVOuFwSVzNfSPzA9kj5GB4qZffi9VXNuBzMxMeV5Mmd92nRboGfFay81hySVZWzKEus8qPeasX0Ra5Tp1dQgVrsqvT0ujf1jSBwlXrDZWPLl17UdcU1H9/aD2JxPe69Zr5uGW+6Rnd8wrE6fltFBo8wudEQtUNnrti59NxDhK6CXo1PEPpnmwNZYtGRfpWHQOzb1TgDTpkbKRJ7iBsXpowG1w5TXBKNTNJojgb6yE2SuTLy80UFLqGDMlqnRwK6yb73L5GiKQ/XW68eSHjL4uks86GGdegT+a+pOef8db+AwX8q6yYpib1eQj9CD/fYi2eN1eEnmw1NE/7RTZfiTl+jKQmvVNJ5aUiClXfw91c2fo6JxxZkp
*/