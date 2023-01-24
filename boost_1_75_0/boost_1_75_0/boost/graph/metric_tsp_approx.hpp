
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
z71MPTbW1Am77WUH7S14wwIBdsQGubhVi/ODDPRTuI0ggXoxf45aguHAvD3q+oy10tyM3/11J4bUVBwbUUykQYYO9ne9jt+8/tBOosFXt4qGz/KAU922RY1Nkn17DtuT573f5Yc8f0G6WDjC4idF0gpQSpnAoadAat7wH8z8Vj/aMUsdIySFkb6HUbl8z9ju4/xb5NAalR2oHfWowynoB8eufRZO+DX2AiRY48aeu+P7YBCn8AeCzFrVIN47N+DkNjwEayvLd+n5qa85Sw2af0p1+jF3zgX3+qF9ZEiMP3KSqY0J/0HOYrOJo6VfjMDpQQFtcPoq7lk5o1TAWzon4ycdoVN399SZyzKfjo+OLr/Oz9pWASHdulp78Oc6L+26Ku/atnq3NTZW0vSMvEYbXoKvN5Xrqqg67jUsU3aX61YtA/Kyj4nReBCKD3rRuZde3QeMfqVbKT4xxH8onph7GCaTPd+qeJ0N++Xzu/B6cxetZNTbsBNjS8sL/nTjLaGhXb5s/lKFBKYJp+oUlPQQS4bmmpZhN1XTD3/gDmr5uWpl0mzgVQcMJFNIIEsrar1agga4yQ2Xjc1iJ2D3mf1oRArpWu1rKm7Cc3FxH7nBjoBBh+z7BhzhRSmfXvR6p/pXAz7JKN2gJaZOExISxlKPr+mJrp4diV+KbQXY2bM3qa2ZVchs0loGWuJZUhGNN/I5bB7gjtLFOrATjU93
*/