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
LMYTRkZaZn/jv7bqZeZIuEa3nsp7pWcbWUORDUrr38vWS9RxBn3Sh5kwk0TmTlHvzL7ptm4jT5hp/XxkJ6t/37iT7XEKJsymwesRiLyZkfvrNxd5z7SstJwMX/0WKpeU+chb6vmqDyM/1cjFh5G3Ch4Pgbzq8RCZMh7iJCmju8ItDuS8viJgLAHfmPF39GoZD5FfPFZ7onU8RE4dCzlisct8eNVtIv3X10ifZ77st+gdzzAUNrjGrfOGw29uuUwtt+eWNxOdMLMvQEuxT3TMs543ffm3iGyU2Ovy67FrsXM28eKOttgXcC9cIOn9Oknj8pnDfK3otFO7CUP0D3rSP5GUSdqzfNKufezm/Mqnl5p9ATKqPMfCktEB53iv6ERKXN9609bB3kdxgrjHOsRu0tbeb336MRKmPR4lWXSacU82lHCPSbjjC8ZY9v6LNURnjJmH7ZtPM+izbYxuH+1bPaB9sH2x98Oo3PDZOFunv9Gx3QZon20WHIgZJDq2PBsegAeOY+9Fd9/li5JWq3nBxJJCRNJP2R1SFul7lLJo5j1S/pCZ8ie6WfCgyD3XNdFv7qTftZT+y7N0rNBF0ZYcfyHyhsqYRvxYIfdGQcWEUs84i1yWBCjLLW3fwV6DwCHjPMw9on4ayZz1Ur2XasjYKrypXh+jd7rPfGyZ7ynuWca9mZWgaxs0E/tURwIhX2LvY6D+7Lna44zfk82YkpPFPsORZIVxl4X5+KWXmAnwZVrGEuAMj1/HK1Y3ZOlxA/DfyvKG6ZDzqjRrB0j8hRMk6d6xD3ClW7Op8Z8S4H+V5kulnDf3jsY/GN0y0WvpeNsn/tQA/2vVf00ZjzQqfyyRJ+g9v1H0vuJZ0J3+lCwdf8NVFHkEKwvcE7Q/SYLuJdFCdMod9S0no6qcco4nSRz5ZfljConF3kelregWO2rzt4DwfcctxWsdNkx0ujuSHQ1Nnkt6A+7rFaKXadXkLhEZtqMiu4i09rKCxtzouS7zpJcym1TlebrHfzwezj0RRR+deyyHq2dseFKsa+57vz6uBD+yhsCFbj815841Yz8CdBrV4DuqW+ekecO9Onfa40hEpxc6w2QcybwzYsNrWUYvIKwir174vOWBOi2xR2EfrnXPCEj9IuYCfl+EGYlx1zEZoesYGS8xfKWOl5g8WeqMUuQOqTPkPhbZNMg9i0zuWTOGgvvUb172ElO3mHswYByFub9EvsrMkTb3jIS91szL5l4IqJuKdbLnKy7uY/g0bE7a1q4MrJtKpXKidIWqm9RPM/55yvCjYr/XtZAYz6O8X4X5HrPO6ZQwZtZ1h0GIhNFMy9xu8dPHNcuKop92lrXIEcU+QqnWJOcSrdu88bQIVbepe1uzDk3IuixAl/yuqu4yYzMPrJJnrhnfGP0XGefl6M1o1Ru5R9IcM3zrNMI+vjrtAvd5S9ixdp1m/Ies04zfDeI32a7PAvxy/avcMykObrsOLXpqGcNo6pVb5bye5eXjNkcte8xap5SudttnoeikmLbP0Ovs9khLT51WXj65zGqpY+hekPRc4qrg7x3WPGsOfj7CXO1kxRpnO8t3zRrfOqizhLuE8nESMt+4GjgirfDgfaLVX+3Vsl+1tlNoV4ifMqtmiHBEz8hqOWLJ5nhd9ypDZB0cU6yNks7TNJ2jfZ5JTokvwrSTosR+kVVluNr+5S4uTZVmB/evxpUm+doSnSuY51lb4mvdSHV94ntf9Gpb7jVZ8qLpn6rlqaNiI+e+FRPNciwuV/+I2NhwxKZOvLiuJeElN9L7rswOb66UoWiT/ivEPsX3uWP2El8sbuVS/7cigoOYXByo+d+JDY+KdV34q/W/+DmGyZN6e+4=
*/