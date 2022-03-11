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