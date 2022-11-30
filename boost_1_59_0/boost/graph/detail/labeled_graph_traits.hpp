// Copyright (C) 2009 Andrew Sutton

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_LABELED_GRAPH_TRAITS_HPP
#define BOOST_GRAPH_LABELED_GRAPH_TRAITS_HPP

#include <boost/graph/graph_mutability_traits.hpp>

namespace boost
{

// Extend the graph mutability traits (and metafunctions) to include options
// for labeled graphs.

// NOTE: the label_vertex tag denotes the fact that you can basically assign
// arbitrary labels to vertices without modifying the actual graph.

// TODO: We might also overlay the uniqueness/multiplicity of labels in this
// hierarchy also. For now, we just assumed that labels are unique.

struct label_vertex_tag
{
};
struct labeled_add_vertex_tag : virtual label_vertex_tag
{
};
struct labeled_add_vertex_property_tag : virtual labeled_add_vertex_tag
{
};
struct labeled_remove_vertex_tag
{
};
struct labeled_add_edge_tag : virtual label_vertex_tag
{
};
struct labeled_add_edge_property_tag : virtual labeled_add_edge_tag
{
};
struct labeled_remove_edge_tag
{
};

struct labeled_mutable_vertex_graph_tag : virtual labeled_add_vertex_tag,
                                          virtual labeled_remove_vertex_tag
{
};
struct labeled_mutable_vertex_property_graph_tag
: virtual labeled_add_vertex_property_tag,
  virtual labeled_remove_vertex_tag
{
};
struct labeled_mutable_edge_graph_tag : virtual labeled_add_edge_tag,
                                        virtual labeled_remove_edge_tag
{
};
struct labeled_mutable_edge_property_graph_tag
: virtual labeled_add_edge_property_tag,
  virtual labeled_remove_edge_tag
{
};

struct labeled_graph_tag : virtual label_vertex_tag
{
};
struct labeled_mutable_graph_tag : virtual labeled_mutable_vertex_graph_tag,
                                   virtual labeled_mutable_edge_graph_tag
{
};
struct labeled_mutable_property_graph_tag
: virtual labeled_mutable_vertex_property_graph_tag,
  virtual labeled_mutable_edge_property_graph_tag
{
};
struct labeled_add_only_property_graph_tag
: virtual labeled_add_vertex_property_tag,
  virtual labeled_mutable_edge_property_graph_tag
{
};

// Metafunctions

template < typename Graph >
struct graph_has_add_vertex_by_label
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          labeled_add_vertex_tag >::value >
{
};

template < typename Graph >
struct graph_has_add_vertex_by_label_with_property
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          labeled_add_vertex_property_tag >::value >
{
};

template < typename Graph >
struct graph_has_remove_vertex_by_label
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          labeled_remove_vertex_tag >::value >
{
};

template < typename Graph >
struct graph_has_add_edge_by_label
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          labeled_add_edge_tag >::value >
{
};

template < typename Graph >
struct graph_has_add_edge_by_label_with_property
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          labeled_add_edge_property_tag >::value >
{
};

template < typename Graph >
struct graph_has_remove_edge_by_label
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          labeled_remove_edge_tag >::value >
{
};

template < typename Graph >
struct is_labeled_mutable_vertex_graph
: mpl::and_< graph_has_add_vertex_by_label< Graph >,
      graph_has_remove_vertex_by_label< Graph > >
{
};

template < typename Graph >
struct is_labeled_mutable_vertex_property_graph
: mpl::and_< graph_has_add_vertex_by_label< Graph >,
      graph_has_remove_vertex_by_label< Graph > >
{
};

template < typename Graph >
struct is_labeled_mutable_edge_graph
: mpl::and_< graph_has_add_edge_by_label< Graph >,
      graph_has_remove_edge_by_label< Graph > >
{
};

template < typename Graph >
struct is_labeled_mutable_edge_property_graph
: mpl::and_< graph_has_add_edge_by_label< Graph >,
      graph_has_remove_edge_by_label< Graph > >
{
};

template < typename Graph >
struct is_labeled_mutable_graph
: mpl::and_< is_labeled_mutable_vertex_graph< Graph >,
      is_labeled_mutable_edge_graph< Graph > >
{
};

template < typename Graph >
struct is_labeled_mutable_property_graph
: mpl::and_< is_labeled_mutable_vertex_property_graph< Graph >,
      is_labeled_mutable_edge_property_graph< Graph > >
{
};

template < typename Graph >
struct is_labeled_add_only_property_graph
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          labeled_add_only_property_graph_tag >::value >
{
};

template < typename Graph >
struct is_labeled_graph
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          label_vertex_tag >::value >
{
};

template < typename > struct graph_mutability_traits;

namespace graph_detail
{
    // The determine mutability metafunction computes a labeled mutability tag
    // based on the mutability of the given graph type. This is used by the
    // graph_mutability_traits specialization below.
    template < typename Graph > struct determine_mutability
    {
        typedef typename mpl::if_< is_add_only_property_graph< Graph >,
            labeled_add_only_property_graph_tag,
            typename mpl::if_< is_mutable_property_graph< Graph >,
                labeled_mutable_property_graph_tag,
                typename mpl::if_< is_mutable_graph< Graph >,
                    labeled_mutable_graph_tag,
                    typename mpl::if_< is_mutable_edge_graph< Graph >,
                        labeled_graph_tag,
                        typename graph_mutability_traits< Graph >::category >::
                        type >::type >::type >::type type;
    };
} // namespace graph_detail

#define LABELED_GRAPH_PARAMS typename G, typename L, typename S
#define LABELED_GRAPH labeled_graph< G, L, S >

// Specialize mutability traits for the labeled graph.
// This specialization depends on the mutability of the underlying graph type.
// If the underlying graph is fully mutable, this is also fully mutable.
// Otherwise, it's different.
template < LABELED_GRAPH_PARAMS >
struct graph_mutability_traits< LABELED_GRAPH >
{
    typedef typename graph_detail::determine_mutability<
        typename LABELED_GRAPH::graph_type >::type category;
};

#undef LABELED_GRAPH_PARAMS
#undef LABELED_GRAPH

} // namespace boost

#endif

/* labeled_graph_traits.hpp
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
*/