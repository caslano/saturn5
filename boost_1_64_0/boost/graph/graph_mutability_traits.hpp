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
K28/Ofms3aNwTtH96oCAQppPIv8+tPaY/+CaHW03IGa2fZH2QDPXUAcW0tsQWJc1N1C/TS/YVQ0wtwYuUTPnr9pC9ecHNAd73QUEFqbjZdjGtakHFSgeMMiue9+DRylTt2TEcSId5D8Uo1rMFS3trCzz894nqZ8RFLwBR7ZguGiWwGcKp2h0VyGXbwB++hKU5GmoUEgPlDduaitAtKvrqMtFlkm7sTzElHgBSIlu6mnVc7ytkf7l9AY2kt6aAY/B4m7TxQBWsdAR3dXJAkURzVRM8RKOWlNrTI1iR9DHQWopX1vRQFWNVxUFGWE+E2aNVl6ePAxcF8SIfHMNr024NcNqhZi5tkw7oa/YKJRwdEI6JcqukkkB/JSc60M2VJ/S45kseKcQDkrLrw5hxEqx3z5XHEDpPjpc432dHXJmLv9VmSWKAj2sclYX5Wp5+qekEdKdJNgubhS2+6fNi14kbXwWNvspzDwwIlJPXzb+eSvjLwKeBfDGV2aOEEHZwWZdaBAPAPYoVhMjfmHW6fl9RcKNn9Oln4EV5EexH3VAz5N5h8f8zqrn3nWp2Q==
*/