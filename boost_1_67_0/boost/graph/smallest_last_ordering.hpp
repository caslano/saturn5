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