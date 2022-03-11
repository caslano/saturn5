
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