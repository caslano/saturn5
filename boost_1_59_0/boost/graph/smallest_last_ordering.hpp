//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

// Revision History:
//   17 March 2006: Fixed a bug: when updating the degree a vertex
//                  could be moved to a wrong bucket. (Roman Dementiev)
//

#ifndef BOOST_SMALLEST_LAST_VERTEX_ORDERING_HPP
#define BOOST_SMALLEST_LAST_VERTEX_ORDERING_HPP
/*
   The smallest-last ordering is defined for the loopless graph G with
   vertices a(j), j = 1,2,...,n where a(j) is the j-th column of A and
   with edge (a(i),a(j)) if and only if columns i and j have a
   non-zero in the same row position.  The smallest-last ordering is
   determined recursively by letting list(k), k = n,...,1 be a column
   with least degree in the subgraph spanned by the un-ordered
   columns.
 */
#include <vector>
#include <algorithm>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/pending/bucket_sorter.hpp>

namespace boost
{

template < class VertexListGraph, class Order, class Degree, class Marker >
void smallest_last_vertex_ordering(
    const VertexListGraph& G, Order order, Degree degree, Marker marker)
{
    typedef typename boost::graph_traits< VertexListGraph > GraphTraits;
    typedef typename GraphTraits::vertex_descriptor Vertex;
    // typedef typename GraphTraits::size_type size_type;
    typedef std::size_t size_type;

    const size_type num = num_vertices(G);

    typedef
        typename boost::property_map< VertexListGraph, vertex_index_t >::type
            ID;
    typedef bucket_sorter< size_type, Vertex, Degree, ID > BucketSorter;

    BucketSorter degree_bucket_sorter(num, num, degree, get(vertex_index, G));

    smallest_last_vertex_ordering(
        G, order, degree, marker, degree_bucket_sorter);
}

template < class VertexListGraph, class Order, class Degree, class Marker,
    class BucketSorter >
void smallest_last_vertex_ordering(const VertexListGraph& G, Order order,
    Degree degree, Marker marker, BucketSorter& degree_buckets)
{
    typedef typename boost::graph_traits< VertexListGraph > GraphTraits;
    typedef typename GraphTraits::vertex_descriptor Vertex;
    // typedef typename GraphTraits::size_type size_type;
    typedef std::size_t size_type;

    const size_type num = num_vertices(G);

    typename GraphTraits::vertex_iterator v, vend;
    for (boost::tie(v, vend) = vertices(G); v != vend; ++v)
    {
        put(marker, *v, num);
        put(degree, *v, out_degree(*v, G));
        degree_buckets.push(*v);
    }

    size_type minimum_degree = 0;
    size_type current_order = num - 1;

    while (1)
    {
        typedef typename BucketSorter::stack MDStack;
        MDStack minimum_degree_stack = degree_buckets[minimum_degree];
        while (minimum_degree_stack.empty())
            minimum_degree_stack = degree_buckets[++minimum_degree];

        Vertex node = minimum_degree_stack.top();
        put(order, current_order, node);

        if (current_order == 0) // find all vertices
            break;

        minimum_degree_stack.pop();
        put(marker, node, 0); // node has been ordered.

        typename GraphTraits::adjacency_iterator v, vend;
        for (boost::tie(v, vend) = adjacent_vertices(node, G); v != vend; ++v)

            if (get(marker, *v) > current_order)
            { //*v is unordered vertex
                put(marker, *v,
                    current_order); // mark the columns adjacent to node

                // delete *v from the bucket sorter
                degree_buckets.remove(*v);

                // It is possible minimum degree goes down
                // Here we keep tracking it.
                put(degree, *v, get(degree, *v) - 1);
                BOOST_USING_STD_MIN();
                minimum_degree = min BOOST_PREVENT_MACRO_SUBSTITUTION(
                    minimum_degree, get(degree, *v));

                // reinsert *v in the bucket sorter with the new degree
                degree_buckets.push(*v);
            }

        current_order--;
    }

    // at this point, order[i] = v_i;
}

template < class VertexListGraph, class Order >
void smallest_last_vertex_ordering(const VertexListGraph& G, Order order)
{
    typedef typename graph_traits< VertexListGraph >::vertex_descriptor
        vertex_descriptor;
    typedef typename graph_traits< VertexListGraph >::degree_size_type
        degree_size_type;
    smallest_last_vertex_ordering(G, order,
        make_shared_array_property_map(
            num_vertices(G), degree_size_type(0), get(vertex_index, G)),
        make_shared_array_property_map(
            num_vertices(G), (std::size_t)(0), get(vertex_index, G)));
}

template < class VertexListGraph >
std::vector< typename graph_traits< VertexListGraph >::vertex_descriptor >
smallest_last_vertex_ordering(const VertexListGraph& G)
{
    std::vector< typename graph_traits< VertexListGraph >::vertex_descriptor >
        o(num_vertices(G));
    smallest_last_vertex_ordering(G,
        make_iterator_property_map(
            o.begin(), typed_identity_property_map< std::size_t >()));
    return o;
}
}

#endif

/* smallest_last_ordering.hpp
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
*/