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
0sU3aGHzMqHw0sk3YiHrmkvlqR8qemrvXqX0NAD8006C8cmFwEus9HUnV+mp1yjvMoo57zJehGmh64ZRbJMR+qP0pcZk3r4zRbDJcQzcc5dPN1nj5t7GiosiNbIH+ZDZYO834gjmt99/3TXJc+//dOatDkcObZ8hRZceOSwKgsAsviKFTGGJP4C3STOtP+wFhp4obo2Zt+Uf9jvOAim9eIYLSpg3SaKipBaZ00DZEYR8M+zDe1IrkSS/nZzxnLfaBFwYdp52N5hXXbup16dbTNdfkm2Bu8yrHos5V/WvIeK/hUpTozEb8J9Pzb5jteRTmf/NU2ywzCnr3W0tVN/9wcEqS1b/IbAxJeAmt7VW10zjnahAZe5F7NOZ5IPsEnG8f/9ZiBEwdY/iqdAsmMPKo0rmjST82nDv4QmrD3Y7oW48z1OQwO+J0ff1czds34bCvVN2EUCsJWOiFLaoPWqPhe5HroXehGMg6pqmAt6rJyAFX9Q3DgiqN14iFE5fmuLomdGTqOmaJ5T0I7hbwVd+O9dhfntuu6CILNs8h/SFJRF/jjG+xQHktuPA1K6wXeRbeDUnMicC6sGVoKqh1LeSHqz/ZNLiPw3se0De9Tg1vNLbKY0WluhBBWbzlVjcRzKetB+0J/60SnlQw/8y6lxiJ/G5HokNadmx+3o1dqwY1zKlLXofTa48tIjiSLaF4ptVXMHxu2A80LWEmJ10
*/