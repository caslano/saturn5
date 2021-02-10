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
e7cD1N/bKoNBQUVRug4i5EoFl+Tmgsq1KaIYcbjZFjiehbAu8ABN0tJpMEcDNdCRbP95Dhj11QIiR39drQCSnTiZlCgFSud/K9ysMmd/xoVzWs1ybCum68axt8KY61StG7SkXcFzH/3Ly3zqt2UEvN6D1fCekJnctc+Dxv4loKrav80Zx8o1zzca886h540OOLV/m1XL0+xvwH1hb2V5GMpaLW8tL/zcGd7D7zkr56brTnU1RhqdtjdVt2oCsrcvbhMU0j20scsXZGiyn+BH+flYmNi8FEivcvMHBAD10TTrRcivRuEHQ2WJOQgWQmETn3+I4lWKUiaMLSV3qnPKOBBOHnPmBzhmGWWBwSs6LHl3O0eaNCKXsKleagiYfvsRnOlKS0qNPiw0sU8rgmbEMbnGiIWKKa0mIwhTC+UCsIKBwQCy/IFT0WEQGp6nus7bmogh3VXg1nKpkut9b2uZTC9x4SOhXQeKqiIcQS3DmXM16uO+Suf4ivNt2PCLQeucItnte6jOtD6KenNbh0jY3l8HkTjgAFGBH02QYmVRmDrgoRapdRNaJyg4AUHYqEgZqAZTAhN1IWJzWlibfhS8cOBfXs9lEn6Q63ljCRyfTIfwNftab0s5NtfsNfwQzz5QynFMLj9FN1JAoeo1
*/