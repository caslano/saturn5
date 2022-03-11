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