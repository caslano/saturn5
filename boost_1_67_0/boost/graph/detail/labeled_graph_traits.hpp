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