
//=======================================================================
// Copyright 2008
// Author: Matyas W Egyhazy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_METRIC_TSP_APPROX_HPP
#define BOOST_GRAPH_METRIC_TSP_APPROX_HPP

// metric_tsp_approx
// Generates an approximate tour solution for the traveling salesperson
// problem in polynomial time. The current algorithm guarantees a tour with a
// length at most as long as 2x optimal solution. The graph should have
// 'natural' (metric) weights such that the triangle inequality is maintained.
// Graphs must be fully interconnected.

// TODO:
// There are a couple of improvements that could be made.
// 1) Change implementation to lower uppper bound Christofides heuristic
// 2) Implement a less restrictive TSP heuristic (one that does not rely on
//    triangle inequality).
// 3) Determine if the algorithm can be implemented without creating a new
//    graph.

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/concept_check.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_as_tree.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/lookup_edge.hpp>
#include <boost/throw_exception.hpp>

namespace boost
{
// Define a concept for the concept-checking library.
template < typename Visitor, typename Graph > struct TSPVertexVisitorConcept
{
private:
    Visitor vis_;

public:
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;

    BOOST_CONCEPT_USAGE(TSPVertexVisitorConcept)
    {
        Visitor vis(vis_); // require copy construction
        Graph g(1);
        Vertex v(*vertices(g).first);
        vis.visit_vertex(v, g); // require visit_vertex
    }
};

// Tree visitor that keeps track of a preorder traversal of a tree
// TODO: Consider migrating this to the graph_as_tree header.
// TODO: Parameterize the underlying stores so it doesn't have to be a vector.
template < typename Node, typename Tree > class PreorderTraverser
{
private:
    std::vector< Node >& path_;

public:
    typedef typename std::vector< Node >::const_iterator const_iterator;

    PreorderTraverser(std::vector< Node >& p) : path_(p) {}

    void preorder(Node n, const Tree&) { path_.push_back(n); }

    void inorder(Node, const Tree&) const {}
    void postorder(Node, const Tree&) const {}

    const_iterator begin() const { return path_.begin(); }
    const_iterator end() const { return path_.end(); }
};

// Forward declarations
template < typename > class tsp_tour_visitor;
template < typename, typename, typename, typename > class tsp_tour_len_visitor;

template < typename VertexListGraph, typename OutputIterator >
void metric_tsp_approx_tour(VertexListGraph& g, OutputIterator o)
{
    metric_tsp_approx_from_vertex(g, *vertices(g).first, get(edge_weight, g),
        get(vertex_index, g), tsp_tour_visitor< OutputIterator >(o));
}

template < typename VertexListGraph, typename WeightMap,
    typename OutputIterator >
void metric_tsp_approx_tour(VertexListGraph& g, WeightMap w, OutputIterator o)
{
    metric_tsp_approx_from_vertex(
        g, *vertices(g).first, w, tsp_tour_visitor< OutputIterator >(o));
}

template < typename VertexListGraph, typename OutputIterator >
void metric_tsp_approx_tour_from_vertex(VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor start,
    OutputIterator o)
{
    metric_tsp_approx_from_vertex(g, start, get(edge_weight, g),
        get(vertex_index, g), tsp_tour_visitor< OutputIterator >(o));
}

template < typename VertexListGraph, typename WeightMap,
    typename OutputIterator >
void metric_tsp_approx_tour_from_vertex(VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor start,
    WeightMap w, OutputIterator o)
{
    metric_tsp_approx_from_vertex(g, start, w, get(vertex_index, g),
        tsp_tour_visitor< OutputIterator >(o));
}

template < typename VertexListGraph, typename TSPVertexVisitor >
void metric_tsp_approx(VertexListGraph& g, TSPVertexVisitor vis)
{
    metric_tsp_approx_from_vertex(
        g, *vertices(g).first, get(edge_weight, g), get(vertex_index, g), vis);
}

template < typename VertexListGraph, typename Weightmap,
    typename VertexIndexMap, typename TSPVertexVisitor >
void metric_tsp_approx(VertexListGraph& g, Weightmap w, TSPVertexVisitor vis)
{
    metric_tsp_approx_from_vertex(
        g, *vertices(g).first, w, get(vertex_index, g), vis);
}

template < typename VertexListGraph, typename WeightMap,
    typename VertexIndexMap, typename TSPVertexVisitor >
void metric_tsp_approx(
    VertexListGraph& g, WeightMap w, VertexIndexMap id, TSPVertexVisitor vis)
{
    metric_tsp_approx_from_vertex(g, *vertices(g).first, w, id, vis);
}

template < typename VertexListGraph, typename WeightMap,
    typename TSPVertexVisitor >
void metric_tsp_approx_from_vertex(VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor start,
    WeightMap w, TSPVertexVisitor vis)
{
    metric_tsp_approx_from_vertex(g, start, w, get(vertex_index, g), vis);
}

template < typename VertexListGraph, typename WeightMap,
    typename VertexIndexMap, typename TSPVertexVisitor >
void metric_tsp_approx_from_vertex(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor start,
    WeightMap weightmap, VertexIndexMap indexmap, TSPVertexVisitor vis)
{
    using namespace boost;
    using namespace std;

    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< VertexListGraph >));
    BOOST_CONCEPT_ASSERT(
        (TSPVertexVisitorConcept< TSPVertexVisitor, VertexListGraph >));

    // Types related to the input graph (GVertex is a template parameter).
    typedef typename graph_traits< VertexListGraph >::vertex_descriptor GVertex;
    typedef typename graph_traits< VertexListGraph >::vertex_iterator GVItr;

    // We build a custom graph in this algorithm.
    typedef adjacency_list< vecS, vecS, directedS, no_property, no_property >
        MSTImpl;
    typedef graph_traits< MSTImpl >::vertex_descriptor Vertex;
    typedef graph_traits< MSTImpl >::vertex_iterator VItr;

    // And then re-cast it as a tree.
    typedef iterator_property_map< vector< Vertex >::iterator,
        property_map< MSTImpl, vertex_index_t >::type >
        ParentMap;
    typedef graph_as_tree< MSTImpl, ParentMap > Tree;
    typedef tree_traits< Tree >::node_descriptor Node;

    // A predecessor map.
    typedef vector< GVertex > PredMap;
    typedef iterator_property_map< typename PredMap::iterator, VertexIndexMap >
        PredPMap;

    PredMap preds(num_vertices(g));
    PredPMap pred_pmap(preds.begin(), indexmap);

    // Compute a spanning tree over the in put g.
    prim_minimum_spanning_tree(g, pred_pmap,
        root_vertex(start).vertex_index_map(indexmap).weight_map(weightmap));

    // Build a MST using the predecessor map from prim mst
    MSTImpl mst(num_vertices(g));
    std::size_t cnt = 0;
    pair< VItr, VItr > mst_verts(vertices(mst));
    for (typename PredMap::iterator vi(preds.begin()); vi != preds.end();
         ++vi, ++cnt)
    {
        if (indexmap[*vi] != cnt)
        {
            add_edge(*next(mst_verts.first, indexmap[*vi]),
                *next(mst_verts.first, cnt), mst);
        }
    }

    // Build a tree abstraction over the MST.
    vector< Vertex > parent(num_vertices(mst));
    Tree t(mst, *vertices(mst).first,
        make_iterator_property_map(parent.begin(), get(vertex_index, mst)));

    // Create tour using a preorder traversal of the mst
    vector< Node > tour;
    PreorderTraverser< Node, Tree > tvis(tour);
    traverse_tree(indexmap[start], t, tvis);

    pair< GVItr, GVItr > g_verts(vertices(g));
    for (PreorderTraverser< Node, Tree >::const_iterator curr(tvis.begin());
         curr != tvis.end(); ++curr)
    {
        // TODO: This is will be O(n^2) if vertex storage of g != vecS.
        GVertex v = *next(g_verts.first, get(vertex_index, mst)[*curr]);
        vis.visit_vertex(v, g);
    }

    // Connect back to the start of the tour
    vis.visit_vertex(start, g);
}

// Default tsp tour visitor that puts the tour in an OutputIterator
template < typename OutItr > class tsp_tour_visitor
{
    OutItr itr_;

public:
    tsp_tour_visitor(OutItr itr) : itr_(itr) {}

    template < typename Vertex, typename Graph >
    void visit_vertex(Vertex v, const Graph&)
    {
        BOOST_CONCEPT_ASSERT((OutputIterator< OutItr, Vertex >));
        *itr_++ = v;
    }
};

// Tsp tour visitor that adds the total tour length.
template < typename Graph, typename WeightMap, typename OutIter,
    typename Length >
class tsp_tour_len_visitor
{
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT((OutputIterator< OutIter, Vertex >));

    OutIter iter_;
    Length& tourlen_;
    WeightMap& wmap_;
    Vertex previous_;

    // Helper function for getting the null vertex.
    Vertex null() { return graph_traits< Graph >::null_vertex(); }

public:
    tsp_tour_len_visitor(Graph const&, OutIter iter, Length& l, WeightMap& map)
    : iter_(iter), tourlen_(l), wmap_(map), previous_(null())
    {
    }

    void visit_vertex(Vertex v, const Graph& g)
    {
        typedef typename graph_traits< Graph >::edge_descriptor Edge;

        // If it is not the start, then there is a
        // previous vertex
        if (previous_ != null())
        {
            // NOTE: For non-adjacency matrix graphs g, this bit of code
            // will be linear in the degree of previous_ or v. A better
            // solution would be to visit edges of the graph, but that
            // would require revisiting the core algorithm.
            Edge e;
            bool found;
            boost::tie(e, found) = lookup_edge(previous_, v, g);
            if (!found)
            {
                BOOST_THROW_EXCEPTION(not_complete());
            }

            tourlen_ += wmap_[e];
        }

        previous_ = v;
        *iter_++ = v;
    }
};

// Object generator(s)
template < typename OutIter >
inline tsp_tour_visitor< OutIter > make_tsp_tour_visitor(OutIter iter)
{
    return tsp_tour_visitor< OutIter >(iter);
}

template < typename Graph, typename WeightMap, typename OutIter,
    typename Length >
inline tsp_tour_len_visitor< Graph, WeightMap, OutIter, Length >
make_tsp_tour_len_visitor(
    Graph const& g, OutIter iter, Length& l, WeightMap map)
{
    return tsp_tour_len_visitor< Graph, WeightMap, OutIter, Length >(
        g, iter, l, map);
}

} // boost

#endif // BOOST_GRAPH_METRIC_TSP_APPROX_HPP

/* metric_tsp_approx.hpp
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
*/