// Copyright (C) 2009 Andrew Sutton
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_MUTABILITY_TRAITS_HPP
#define BOOST_GRAPH_MUTABILITY_TRAITS_HPP

#include <boost/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost
{

// The mutabiltiy categories classify graphs by their mutating operations
// on the edge and vertex sets. This is a substantially more refined
// categorization than the MutableGraph and MutablePropertyGraph denote.
// Currently, this framework is only used in the graph tests to help
// dispatch test to the correct places. However, there are probably some
// constructive or destructive algorithms (i.e., graph generators) that
// may use these to describe requirements on graph inputs.

struct add_vertex_tag
{
};
struct add_vertex_property_tag : virtual add_vertex_tag
{
};
struct add_edge_tag
{
};
struct add_edge_property_tag : virtual add_edge_tag
{
};
struct remove_vertex_tag
{
};
struct remove_edge_tag
{
};

struct mutable_vertex_graph_tag : virtual add_vertex_tag,
                                  virtual remove_vertex_tag
{
};
struct mutable_vertex_property_graph_tag : virtual add_vertex_property_tag,
                                           virtual remove_vertex_tag
{
};

struct mutable_edge_graph_tag : virtual add_edge_tag, virtual remove_edge_tag
{
};
struct mutable_edge_property_graph_tag : virtual add_edge_property_tag,
                                         virtual remove_edge_tag
{
};

struct mutable_graph_tag : virtual mutable_vertex_graph_tag,
                           virtual mutable_edge_graph_tag
{
};
struct mutable_property_graph_tag : virtual mutable_vertex_property_graph_tag,
                                    virtual mutable_edge_property_graph_tag
{
};

// Some graphs just don't like to be torn down. Note this only restricts
// teardown to the set of vertices, not the vertex set.
// TODO: Find a better name for this tag.
struct add_only_property_graph_tag : virtual add_vertex_property_tag,
                                     virtual mutable_edge_property_graph_tag
{
};

/**
 * The graph_mutability_traits provide methods for determining the
 * interfaces supported by graph classes for adding and removing vertices
 * and edges.
 */
template < typename Graph > struct graph_mutability_traits
{
    typedef typename Graph::mutability_category category;
};

template < typename Graph >
struct graph_has_add_vertex
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          add_vertex_tag >::value >
{
};

template < typename Graph >
struct graph_has_add_vertex_with_property
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          add_vertex_property_tag >::value >
{
};

template < typename Graph >
struct graph_has_remove_vertex
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          remove_vertex_tag >::value >
{
};

template < typename Graph >
struct graph_has_add_edge
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          add_edge_tag >::value >
{
};

template < typename Graph >
struct graph_has_add_edge_with_property
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          add_edge_property_tag >::value >
{
};

template < typename Graph >
struct graph_has_remove_edge
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          remove_edge_tag >::value >
{
};

template < typename Graph >
struct is_mutable_vertex_graph
: mpl::and_< graph_has_add_vertex< Graph >, graph_has_remove_vertex< Graph > >
{
};

template < typename Graph >
struct is_mutable_vertex_property_graph
: mpl::and_< graph_has_add_vertex_with_property< Graph >,
      graph_has_remove_vertex< Graph > >
{
};

template < typename Graph >
struct is_mutable_edge_graph
: mpl::and_< graph_has_add_edge< Graph >, graph_has_remove_edge< Graph > >
{
};

template < typename Graph >
struct is_mutable_edge_property_graph
: mpl::and_< graph_has_add_edge_with_property< Graph >,
      graph_has_remove_edge< Graph > >
{
};

template < typename Graph >
struct is_mutable_graph
: mpl::and_< is_mutable_vertex_graph< Graph >, is_mutable_edge_graph< Graph > >
{
};

template < typename Graph >
struct is_mutable_property_graph
: mpl::and_< is_mutable_vertex_property_graph< Graph >,
      is_mutable_edge_property_graph< Graph > >
{
};

template < typename Graph >
struct is_add_only_property_graph
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          add_only_property_graph_tag >::value >
{
};

/** @name Mutability Traits Specializations */
//@{

//@}

} // namespace boost

#endif

/* graph_mutability_traits.hpp
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
*/