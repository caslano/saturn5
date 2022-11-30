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
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
*/