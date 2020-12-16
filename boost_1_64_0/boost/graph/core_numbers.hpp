//
//=======================================================================
// Copyright 2007 Stanford University
// Authors: David Gleich
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_GRAPH_CORE_NUMBERS_HPP
#define BOOST_GRAPH_CORE_NUMBERS_HPP

#include <boost/graph/detail/d_ary_heap.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/concept/assert.hpp>

/*
 * core_numbers
 *
 * Requirement: IncidenceGraph
 */

// History
//
// 30 July 2007
// Added visitors to the implementation
//
// 8 February 2008
// Fixed headers and missing typename

namespace boost
{

// A linear time O(m) algorithm to compute the indegree core number
// of a graph for unweighted graphs.
//
// and a O((n+m) log n) algorithm to compute the in-edge-weight core
// numbers of a weighted graph.
//
// The linear algorithm comes from:
// Vladimir Batagelj and Matjaz Zaversnik, "An O(m) Algorithm for Cores
// Decomposition of Networks."  Sept. 1 2002.

template < typename Visitor, typename Graph > struct CoreNumbersVisitorConcept
{
    void constraints()
    {
        BOOST_CONCEPT_ASSERT((CopyConstructibleConcept< Visitor >));
        vis.examine_vertex(u, g);
        vis.finish_vertex(u, g);
        vis.examine_edge(e, g);
    }
    Visitor vis;
    Graph g;
    typename graph_traits< Graph >::vertex_descriptor u;
    typename graph_traits< Graph >::edge_descriptor e;
};

template < class Visitors = null_visitor >
class core_numbers_visitor : public bfs_visitor< Visitors >
{
public:
    core_numbers_visitor() {}
    core_numbers_visitor(Visitors vis) : bfs_visitor< Visitors >(vis) {}

private:
    template < class Vertex, class Graph >
    void initialize_vertex(Vertex, Graph&)
    {
    }

    template < class Vertex, class Graph > void discover_vertex(Vertex, Graph&)
    {
    }

    template < class Vertex, class Graph > void gray_target(Vertex, Graph&) {}

    template < class Vertex, class Graph > void black_target(Vertex, Graph&) {}

    template < class Edge, class Graph > void tree_edge(Edge, Graph&) {}

    template < class Edge, class Graph > void non_tree_edge(Edge, Graph&) {}
};

template < class Visitors >
core_numbers_visitor< Visitors > make_core_numbers_visitor(Visitors vis)
{
    return core_numbers_visitor< Visitors >(vis);
}

typedef core_numbers_visitor<> default_core_numbers_visitor;

namespace detail
{

    // implement a constant_property_map to simplify compute_in_degree
    // for the weighted and unweighted case
    // this is based on dummy property map
    template < typename ValueType >
    class constant_value_property_map
    : public boost::put_get_helper< ValueType,
          constant_value_property_map< ValueType > >
    {
    public:
        typedef void key_type;
        typedef ValueType value_type;
        typedef const ValueType& reference;
        typedef boost::readable_property_map_tag category;
        inline constant_value_property_map(ValueType cc) : c(cc) {}
        inline constant_value_property_map(
            const constant_value_property_map< ValueType >& x)
        : c(x.c)
        {
        }
        template < class Vertex > inline reference operator[](Vertex) const
        {
            return c;
        }

    protected:
        ValueType c;
    };

    // the core numbers start as the indegree or inweight.  This function
    // will initialize these values
    template < typename Graph, typename CoreMap, typename EdgeWeightMap >
    void compute_in_degree_map(Graph& g, CoreMap d, EdgeWeightMap wm)
    {
        typename graph_traits< Graph >::vertex_iterator vi, vi_end;
        typename graph_traits< Graph >::out_edge_iterator ei, ei_end;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
        {
            put(d, *vi, 0);
        }
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
        {
            for (boost::tie(ei, ei_end) = out_edges(*vi, g); ei != ei_end; ++ei)
            {
                put(d, target(*ei, g), get(d, target(*ei, g)) + get(wm, *ei));
            }
        }
    }

    // the version for weighted graphs is a little different
    template < typename Graph, typename CoreMap, typename EdgeWeightMap,
        typename MutableQueue, typename Visitor >
    typename property_traits< CoreMap >::value_type core_numbers_impl(
        Graph& g, CoreMap c, EdgeWeightMap wm, MutableQueue& Q, Visitor vis)
    {
        typename property_traits< CoreMap >::value_type v_cn = 0;
        typedef typename graph_traits< Graph >::vertex_descriptor vertex;
        while (!Q.empty())
        {
            // remove v from the Q, and then decrease the core numbers
            // of its successors
            vertex v = Q.top();
            vis.examine_vertex(v, g);
            Q.pop();
            v_cn = get(c, v);
            typename graph_traits< Graph >::out_edge_iterator oi, oi_end;
            for (boost::tie(oi, oi_end) = out_edges(v, g); oi != oi_end; ++oi)
            {
                vis.examine_edge(*oi, g);
                vertex u = target(*oi, g);
                // if c[u] > c[v], then u is still in the graph,
                if (get(c, u) > v_cn)
                {
                    // remove the edge
                    put(c, u, get(c, u) - get(wm, *oi));
                    if (Q.contains(u))
                        Q.update(u);
                }
            }
            vis.finish_vertex(v, g);
        }
        return (v_cn);
    }

    template < typename Graph, typename CoreMap, typename EdgeWeightMap,
        typename IndexMap, typename CoreNumVisitor >
    typename property_traits< CoreMap >::value_type core_numbers_dispatch(
        Graph& g, CoreMap c, EdgeWeightMap wm, IndexMap im, CoreNumVisitor vis)
    {
        typedef typename property_traits< CoreMap >::value_type D;
        typedef std::less< D > Cmp;
        // build the mutable queue
        typedef typename graph_traits< Graph >::vertex_descriptor vertex;
        std::vector< std::size_t > index_in_heap_data(num_vertices(g));
        typedef iterator_property_map< std::vector< std::size_t >::iterator,
            IndexMap >
            index_in_heap_map_type;
        index_in_heap_map_type index_in_heap_map(
            index_in_heap_data.begin(), im);
        typedef d_ary_heap_indirect< vertex, 4, index_in_heap_map_type, CoreMap,
            Cmp >
            MutableQueue;
        MutableQueue Q(c, index_in_heap_map, Cmp());
        typename graph_traits< Graph >::vertex_iterator vi, vi_end;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
        {
            Q.push(*vi);
        }
        return core_numbers_impl(g, c, wm, Q, vis);
    }

    // the version for the unweighted case
    // for this functions CoreMap must be initialized
    // with the in degree of each vertex
    template < typename Graph, typename CoreMap, typename PositionMap,
        typename Visitor >
    typename property_traits< CoreMap >::value_type core_numbers_impl(
        Graph& g, CoreMap c, PositionMap pos, Visitor vis)
    {
        typedef typename graph_traits< Graph >::vertices_size_type size_type;
        typedef typename graph_traits< Graph >::degree_size_type degree_type;
        typedef typename graph_traits< Graph >::vertex_descriptor vertex;
        typename graph_traits< Graph >::vertex_iterator vi, vi_end;

        // store the vertex core numbers
        typename property_traits< CoreMap >::value_type v_cn = 0;

        // compute the maximum degree (degrees are in the coremap)
        typename graph_traits< Graph >::degree_size_type max_deg = 0;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
        {
            max_deg = (std::max<
                typename graph_traits< Graph >::degree_size_type >)(max_deg,
                get(c, *vi));
        }

        // store the vertices in bins by their degree
        // allocate two extra locations to ease boundary cases
        std::vector< size_type > bin(max_deg + 2);
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
        {
            ++bin[get(c, *vi)];
        }

        // this loop sets bin[d] to the starting position of vertices
        // with degree d in the vert array for the bucket sort
        size_type cur_pos = 0;
        for (degree_type cur_deg = 0; cur_deg < max_deg + 2; ++cur_deg)
        {
            degree_type tmp = bin[cur_deg];
            bin[cur_deg] = cur_pos;
            cur_pos += tmp;
        }

        // perform the bucket sort with pos and vert so that
        // pos[0] is the vertex of smallest degree
        std::vector< vertex > vert(num_vertices(g));
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
        {
            vertex v = *vi;
            size_type p = bin[get(c, v)];
            put(pos, v, p);
            vert[p] = v;
            ++bin[get(c, v)];
        }
        // we ``abused'' bin while placing the vertices, now,
        // we need to restore it
        std::copy(boost::make_reverse_iterator(bin.end() - 2),
            boost::make_reverse_iterator(bin.begin()),
            boost::make_reverse_iterator(bin.end() - 1));
        // now simulate removing the vertices
        for (size_type i = 0; i < num_vertices(g); ++i)
        {
            vertex v = vert[i];
            vis.examine_vertex(v, g);
            v_cn = get(c, v);
            typename graph_traits< Graph >::out_edge_iterator oi, oi_end;
            for (boost::tie(oi, oi_end) = out_edges(v, g); oi != oi_end; ++oi)
            {
                vis.examine_edge(*oi, g);
                vertex u = target(*oi, g);
                // if c[u] > c[v], then u is still in the graph,
                if (get(c, u) > v_cn)
                {
                    degree_type deg_u = get(c, u);
                    degree_type pos_u = get(pos, u);
                    // w is the first vertex with the same degree as u
                    // (this is the resort operation!)
                    degree_type pos_w = bin[deg_u];
                    vertex w = vert[pos_w];
                    if (u != v)
                    {
                        // swap u and w
                        put(pos, u, pos_w);
                        put(pos, w, pos_u);
                        vert[pos_w] = u;
                        vert[pos_u] = w;
                    }
                    // now, the vertices array is sorted assuming
                    // we perform the following step
                    // start the set of vertices with degree of u
                    // one into the future (this now points at vertex
                    // w which we swapped with u).
                    ++bin[deg_u];
                    // we are removing v from the graph, so u's degree
                    // decreases
                    put(c, u, get(c, u) - 1);
                }
            }
            vis.finish_vertex(v, g);
        }
        return v_cn;
    }

} // namespace detail

// non-named parameter version for the unweighted case
template < typename Graph, typename CoreMap, typename CoreNumVisitor >
typename property_traits< CoreMap >::value_type core_numbers(
    Graph& g, CoreMap c, CoreNumVisitor vis)
{
    typedef typename graph_traits< Graph >::vertices_size_type size_type;
    detail::compute_in_degree_map(g, c,
        detail::constant_value_property_map<
            typename property_traits< CoreMap >::value_type >(1));
    return detail::core_numbers_impl(g, c,
        make_iterator_property_map(
            std::vector< size_type >(num_vertices(g)).begin(),
            get(vertex_index, g)),
        vis);
}

// non-named paramter version for the unweighted case
template < typename Graph, typename CoreMap >
typename property_traits< CoreMap >::value_type core_numbers(
    Graph& g, CoreMap c)
{
    return core_numbers(g, c, make_core_numbers_visitor(null_visitor()));
}

// non-named parameter version for the weighted case
template < typename Graph, typename CoreMap, typename EdgeWeightMap,
    typename VertexIndexMap, typename CoreNumVisitor >
typename property_traits< CoreMap >::value_type core_numbers(Graph& g,
    CoreMap c, EdgeWeightMap wm, VertexIndexMap vim, CoreNumVisitor vis)
{
    detail::compute_in_degree_map(g, c, wm);
    return detail::core_numbers_dispatch(g, c, wm, vim, vis);
}

// non-named parameter version for the weighted case
//    template <typename Graph, typename CoreMap, typename EdgeWeightMap>
//    typename property_traits<CoreMap>::value_type
//    core_numbers(Graph& g, CoreMap c, EdgeWeightMap wm)
//    {
//        typedef typename graph_traits<Graph>::vertices_size_type size_type;
//        detail::compute_in_degree_map(g,c,wm);
//        return detail::core_numbers_dispatch(g,c,wm,get(vertex_index,g),
//            make_core_numbers_visitor(null_visitor()));
//    }

template < typename Graph, typename CoreMap >
typename property_traits< CoreMap >::value_type weighted_core_numbers(
    Graph& g, CoreMap c)
{
    return weighted_core_numbers(
        g, c, make_core_numbers_visitor(null_visitor()));
}

template < typename Graph, typename CoreMap, typename CoreNumVisitor >
typename property_traits< CoreMap >::value_type weighted_core_numbers(
    Graph& g, CoreMap c, CoreNumVisitor vis)
{
    return core_numbers(g, c, get(edge_weight, g), get(vertex_index, g), vis);
}

} // namespace boost

#endif // BOOST_GRAPH_CORE_NUMBERS_HPP

/* core_numbers.hpp
h759Hb42kIcDjwnoJXmCX0UvnkrMeGKhaACVkVQj5SXp5rMH/Vn5nz3oj+D8UyNR2mGikvMJ9FM5ToiSQ8jIMJN2mbxXEP6RHkUtaf+riVO2/Yc5fHGbeeDZjMgo078XLUQai7FqjJ2fk5Zu2dYzFyU971yrEE3WgJlYFtEeWPXNtjoc7GeMLv0gPNCOc909MnSlnld6gFpm1/mNzFeOstGGPnnUGLMRz2CvBu51MZcsPy/b68ohMO0j/dl/rU1EZI8pYzM18VxalsYddp/uPZv4NGGAGpOfOG11v776ojgpFiIAg3YmN5PWiOZoaIYJnf/QvLVxKPI3/XzD3U1fxOtZ5ky/B5y9Rj9ykv3AcvIcJqHz9j9orsZAFXVJOR5oNivjQwYajUGTE425JuHIg3ZSNFOiXVJqP6mrDe0nsX66TuR7CDzViYxHV3c0u/0XaIujCYeMkY/PocVoVhaba708GZ3L9/H6i1NK8UBex6UBZ6vtvbX9FzokcTD57t074POdaEz6bEVfAn68QhNCLqrZVI9Evv/97y+BZ6NxPG48dpZQHdvloqvVjO9IArFdTiO0A+q6i0j8ux4WsPil2keTeF3K2BjVmIh2tg3y3SL+Ej6BwlieEdtwsVucqjJgQKoVTPQ7CKU8ALgq5/v3EkX0aEkrqlMptlL5fL3bWtCNIwfwUK/55eI3IfVnSqONgLkWmYNUhTO0dth/19vFRWZx5A+RQR1PxR6K3lg8xN5tuf3cw/CX2MtxXujQZ8jmgzVPmShjjoARnLkfcIBQcC1gMI5OFqwglfMzsswUECyVjDQjzeED7Zx53pWC8z662UdW+Y7A1hixmUaO1Szp8IhY5mV0zz14f54QCd6/aTsT+KiOOo7Pbu4lgRCOAnJsOAOSsAkBMSJCCAiYhjVZEas2125IbEjW3QUREVGxVkVE1IoVK9aqFVERKyIiRsV6Y0TFqqixH6wVq0bFihWrv/m/3847diPoR9M+vjv3vDn+c76Zbfxi3+vO7NKVj+uN/GPUZMDLgmrv5uzSqzlYR7nDLUf/A0f4a9fTzEktnHr0UoQIZ9ZDpGxPZ7dcDSRSIxmUGBr5ZFbt5IxSXnwWte//lOrV0+feKreVSzGrOQdrrVetjmzm3Cw89szPzsOwZJ6sG0Igm/TMXPbjRmV7vXi7c39dpDvdFYolTC9Ez2Pa9uEaL8A3WBXUP3nzpdi1z57TFoPJdnt/AoTpHdygYNSeDQov8+jXePYlyEYDnYLu/VosRUnp/3n3GlhdU8pD+c2IimfOhXg2QPxY08wVmD1TzvdoMLvwPPqMuMiIaHfMXe/thtGcSePcJ2FW8ZxL69yc4lmNH2GZ/T/xb1XjTXsYHPFPZd5n33+H5z57KfqL5KaG9GX1K7N+JyfllzvVZN17DY+RE2uQ2LIGLdXMtaJtBkBpjVZr6dpYSM8saEcxp5/Ghnjc1b8NPlds6ecZlOmzfEQ1PyDuMxyKoxueg53ke1nr110xdDJutH5tObBXO7z7SZ7NRRmpH7DIC0J1j09GSQHverZuZuq87mXX/bPlV8B89wBNd5/J/Tmm3NsoPT9G0n1bP/fLc3bEvACPxwxkmtsXsa5av0oLd/HGa49mnHrINO/rFyuot/onxZDd1ozob/oSMAgxSOegzEW5hl58K487rmOjZZI5cDuggMdef2cy7p4m4LSFmSfJvogvQl4KW10wq31OWcaixtw77nP1Ls06a3/iphZN0/ZlLHtzLjLXoa3BNE8QCba7pgK963PMINd6baUWLQuDlRg5IDjpy4qcFkErtmlfNkpaTjgZYVtjOtx4nTXTnphRf+R1VvZfbzaYf2Nf7ND8xh4=
*/