//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Copyright 2009, Andrew Sutton
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_GRAPH_CONCEPTS_HPP
#define BOOST_GRAPH_CONCEPTS_HPP

#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/numeric_values.hpp>
#include <boost/graph/buffer_concepts.hpp>
#include <boost/concept_check.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/not.hpp>
#include <boost/static_assert.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/concept/assert.hpp>

#include <boost/concept/detail/concept_def.hpp>
namespace boost
{
// dwa 2003/7/11 -- This clearly shouldn't be necessary, but if
// you want to use vector_as_graph, it is!  I'm sure the graph
// library leaves these out all over the place.  Probably a
// redesign involving specializing a template with a static
// member function is in order :(
//
// It is needed in order to allow us to write using boost::vertices as
// needed for ADL when using vector_as_graph below.
#if !defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP) \
    && !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
#define BOOST_VECTOR_AS_GRAPH_GRAPH_ADL_HACK
#endif

#ifdef BOOST_VECTOR_AS_GRAPH_GRAPH_ADL_HACK
template < class T >
typename T::ThereReallyIsNoMemberByThisNameInT vertices(T const&);
#endif

namespace concepts
{
    BOOST_concept(MultiPassInputIterator, (T)) { BOOST_CONCEPT_USAGE(
        MultiPassInputIterator) { BOOST_CONCEPT_ASSERT((InputIterator< T >));
}
};

BOOST_concept(Graph, (G))
{
    typedef typename graph_traits< G >::vertex_descriptor vertex_descriptor;
    typedef typename graph_traits< G >::edge_descriptor edge_descriptor;
    typedef typename graph_traits< G >::directed_category directed_category;
    typedef typename graph_traits< G >::edge_parallel_category
        edge_parallel_category;
    typedef typename graph_traits< G >::traversal_category traversal_category;

    BOOST_CONCEPT_USAGE(Graph)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructible< vertex_descriptor >));
        BOOST_CONCEPT_ASSERT((EqualityComparable< vertex_descriptor >));
        BOOST_CONCEPT_ASSERT((Assignable< vertex_descriptor >));
    }
    G g;
};

BOOST_concept(IncidenceGraph, (G)) : Graph< G >
{
    typedef typename graph_traits< G >::edge_descriptor edge_descriptor;
    typedef typename graph_traits< G >::out_edge_iterator out_edge_iterator;
    typedef typename graph_traits< G >::degree_size_type degree_size_type;
    typedef typename graph_traits< G >::traversal_category traversal_category;

    BOOST_STATIC_ASSERT(
        (boost::mpl::not_< boost::is_same< out_edge_iterator, void > >::value));
    BOOST_STATIC_ASSERT(
        (boost::mpl::not_< boost::is_same< degree_size_type, void > >::value));

    BOOST_CONCEPT_USAGE(IncidenceGraph)
    {
        BOOST_CONCEPT_ASSERT((MultiPassInputIterator< out_edge_iterator >));
        BOOST_CONCEPT_ASSERT((DefaultConstructible< edge_descriptor >));
        BOOST_CONCEPT_ASSERT((EqualityComparable< edge_descriptor >));
        BOOST_CONCEPT_ASSERT((Assignable< edge_descriptor >));
        BOOST_CONCEPT_ASSERT(
            (Convertible< traversal_category, incidence_graph_tag >));

        p = out_edges(u, g);
        n = out_degree(u, g);
        e = *p.first;
        u = source(e, g);
        v = target(e, g);
        const_constraints(g);
    }
    void const_constraints(const G& cg)
    {
        p = out_edges(u, cg);
        n = out_degree(u, cg);
        e = *p.first;
        u = source(e, cg);
        v = target(e, cg);
    }
    std::pair< out_edge_iterator, out_edge_iterator > p;
    typename graph_traits< G >::vertex_descriptor u, v;
    typename graph_traits< G >::edge_descriptor e;
    typename graph_traits< G >::degree_size_type n;
    G g;
};

BOOST_concept(BidirectionalGraph, (G)) : IncidenceGraph< G >
{
    typedef typename graph_traits< G >::in_edge_iterator in_edge_iterator;
    typedef typename graph_traits< G >::traversal_category traversal_category;

    BOOST_CONCEPT_USAGE(BidirectionalGraph)
    {
        BOOST_CONCEPT_ASSERT((MultiPassInputIterator< in_edge_iterator >));
        BOOST_CONCEPT_ASSERT(
            (Convertible< traversal_category, bidirectional_graph_tag >));

        BOOST_STATIC_ASSERT((boost::mpl::not_<
            boost::is_same< in_edge_iterator, void > >::value));

        p = in_edges(v, g);
        n = in_degree(v, g);
        n = degree(v, g);
        e = *p.first;
        const_constraints(g);
    }
    void const_constraints(const G& cg)
    {
        p = in_edges(v, cg);
        n = in_degree(v, cg);
        n = degree(v, cg);
        e = *p.first;
    }
    std::pair< in_edge_iterator, in_edge_iterator > p;
    typename graph_traits< G >::vertex_descriptor v;
    typename graph_traits< G >::edge_descriptor e;
    typename graph_traits< G >::degree_size_type n;
    G g;
};

BOOST_concept(AdjacencyGraph, (G)) : Graph< G >
{
    typedef typename graph_traits< G >::adjacency_iterator adjacency_iterator;
    typedef typename graph_traits< G >::traversal_category traversal_category;

    BOOST_CONCEPT_USAGE(AdjacencyGraph)
    {
        BOOST_CONCEPT_ASSERT((MultiPassInputIterator< adjacency_iterator >));
        BOOST_CONCEPT_ASSERT(
            (Convertible< traversal_category, adjacency_graph_tag >));

        BOOST_STATIC_ASSERT((boost::mpl::not_<
            boost::is_same< adjacency_iterator, void > >::value));

        p = adjacent_vertices(v, g);
        v = *p.first;
        const_constraints(g);
    }
    void const_constraints(const G& cg) { p = adjacent_vertices(v, cg); }
    std::pair< adjacency_iterator, adjacency_iterator > p;
    typename graph_traits< G >::vertex_descriptor v;
    G g;
};

BOOST_concept(VertexListGraph, (G)) : Graph< G >
{
    typedef typename graph_traits< G >::vertex_iterator vertex_iterator;
    typedef typename graph_traits< G >::vertices_size_type vertices_size_type;
    typedef typename graph_traits< G >::traversal_category traversal_category;

    BOOST_CONCEPT_USAGE(VertexListGraph)
    {
        BOOST_CONCEPT_ASSERT((MultiPassInputIterator< vertex_iterator >));
        BOOST_CONCEPT_ASSERT(
            (Convertible< traversal_category, vertex_list_graph_tag >));

        BOOST_STATIC_ASSERT((boost::mpl::not_<
            boost::is_same< vertex_iterator, void > >::value));
        BOOST_STATIC_ASSERT((boost::mpl::not_<
            boost::is_same< vertices_size_type, void > >::value));

#ifdef BOOST_VECTOR_AS_GRAPH_GRAPH_ADL_HACK
        // dwa 2003/7/11 -- This clearly shouldn't be necessary, but if
        // you want to use vector_as_graph, it is!  I'm sure the graph
        // library leaves these out all over the place.  Probably a
        // redesign involving specializing a template with a static
        // member function is in order :(
        using boost::vertices;
#endif
        p = vertices(g);
        v = *p.first;
        const_constraints(g);
    }
    void const_constraints(const G& cg)
    {
#ifdef BOOST_VECTOR_AS_GRAPH_GRAPH_ADL_HACK
        // dwa 2003/7/11 -- This clearly shouldn't be necessary, but if
        // you want to use vector_as_graph, it is!  I'm sure the graph
        // library leaves these out all over the place.  Probably a
        // redesign involving specializing a template with a static
        // member function is in order :(
        using boost::vertices;
#endif

        p = vertices(cg);
        v = *p.first;
        V = num_vertices(cg);
    }
    std::pair< vertex_iterator, vertex_iterator > p;
    typename graph_traits< G >::vertex_descriptor v;
    G g;
    vertices_size_type V;
};

BOOST_concept(EdgeListGraph, (G)) : Graph< G >
{
    typedef typename graph_traits< G >::edge_descriptor edge_descriptor;
    typedef typename graph_traits< G >::edge_iterator edge_iterator;
    typedef typename graph_traits< G >::edges_size_type edges_size_type;
    typedef typename graph_traits< G >::traversal_category traversal_category;

    BOOST_CONCEPT_USAGE(EdgeListGraph)
    {
        BOOST_CONCEPT_ASSERT((MultiPassInputIterator< edge_iterator >));
        BOOST_CONCEPT_ASSERT((DefaultConstructible< edge_descriptor >));
        BOOST_CONCEPT_ASSERT((EqualityComparable< edge_descriptor >));
        BOOST_CONCEPT_ASSERT((Assignable< edge_descriptor >));
        BOOST_CONCEPT_ASSERT(
            (Convertible< traversal_category, edge_list_graph_tag >));

        BOOST_STATIC_ASSERT(
            (boost::mpl::not_< boost::is_same< edge_iterator, void > >::value));
        BOOST_STATIC_ASSERT((boost::mpl::not_<
            boost::is_same< edges_size_type, void > >::value));

        p = edges(g);
        e = *p.first;
        u = source(e, g);
        v = target(e, g);
        const_constraints(g);
    }
    void const_constraints(const G& cg)
    {
        p = edges(cg);
        E = num_edges(cg);
        e = *p.first;
        u = source(e, cg);
        v = target(e, cg);
    }
    std::pair< edge_iterator, edge_iterator > p;
    typename graph_traits< G >::vertex_descriptor u, v;
    typename graph_traits< G >::edge_descriptor e;
    edges_size_type E;
    G g;
};

BOOST_concept(VertexAndEdgeListGraph, (G))
: VertexListGraph< G >, EdgeListGraph< G > {};

// Where to put the requirement for this constructor?
//      G g(n_vertices);
// Not in mutable graph, then LEDA graph's can't be models of
// MutableGraph.
BOOST_concept(EdgeMutableGraph, (G))
{
    typedef typename graph_traits< G >::edge_descriptor edge_descriptor;

    BOOST_CONCEPT_USAGE(EdgeMutableGraph)
    {
        p = add_edge(u, v, g);
        remove_edge(u, v, g);
        remove_edge(e, g);
        clear_vertex(v, g);
    }
    G g;
    edge_descriptor e;
    std::pair< edge_descriptor, bool > p;
    typename graph_traits< G >::vertex_descriptor u, v;
};

BOOST_concept(VertexMutableGraph, (G))
{

    BOOST_CONCEPT_USAGE(VertexMutableGraph)
    {
        v = add_vertex(g);
        remove_vertex(v, g);
    }
    G g;
    typename graph_traits< G >::vertex_descriptor u, v;
};

BOOST_concept(MutableGraph, (G))
: EdgeMutableGraph< G >, VertexMutableGraph< G > {};

template < class edge_descriptor > struct dummy_edge_predicate
{
    bool operator()(const edge_descriptor&) const { return false; }
};

BOOST_concept(MutableIncidenceGraph, (G)) : MutableGraph< G >
{
    BOOST_CONCEPT_USAGE(MutableIncidenceGraph)
    {
        remove_edge(iter, g);
        remove_out_edge_if(u, p, g);
    }
    G g;
    typedef typename graph_traits< G >::edge_descriptor edge_descriptor;
    dummy_edge_predicate< edge_descriptor > p;
    typename boost::graph_traits< G >::vertex_descriptor u;
    typename boost::graph_traits< G >::out_edge_iterator iter;
};

BOOST_concept(MutableBidirectionalGraph, (G)) : MutableIncidenceGraph< G >
{
    BOOST_CONCEPT_USAGE(MutableBidirectionalGraph)
    {
        remove_in_edge_if(u, p, g);
    }
    G g;
    typedef typename graph_traits< G >::edge_descriptor edge_descriptor;
    dummy_edge_predicate< edge_descriptor > p;
    typename boost::graph_traits< G >::vertex_descriptor u;
};

BOOST_concept(MutableEdgeListGraph, (G)) : EdgeMutableGraph< G >
{
    BOOST_CONCEPT_USAGE(MutableEdgeListGraph) { remove_edge_if(p, g); }
    G g;
    typedef typename graph_traits< G >::edge_descriptor edge_descriptor;
    dummy_edge_predicate< edge_descriptor > p;
};

BOOST_concept(VertexMutablePropertyGraph, (G)) : VertexMutableGraph< G >
{
    BOOST_CONCEPT_USAGE(VertexMutablePropertyGraph) { v = add_vertex(vp, g); }
    G g;
    typename graph_traits< G >::vertex_descriptor v;
    typename vertex_property_type< G >::type vp;
};

BOOST_concept(EdgeMutablePropertyGraph, (G)) : EdgeMutableGraph< G >
{
    typedef typename graph_traits< G >::edge_descriptor edge_descriptor;

    BOOST_CONCEPT_USAGE(EdgeMutablePropertyGraph) { p = add_edge(u, v, ep, g); }
    G g;
    std::pair< edge_descriptor, bool > p;
    typename graph_traits< G >::vertex_descriptor u, v;
    typename edge_property_type< G >::type ep;
};

BOOST_concept(AdjacencyMatrix, (G)) : Graph< G >
{
    typedef typename graph_traits< G >::edge_descriptor edge_descriptor;

    BOOST_CONCEPT_USAGE(AdjacencyMatrix)
    {
        p = edge(u, v, g);
        const_constraints(g);
    }
    void const_constraints(const G& cg) { p = edge(u, v, cg); }
    typename graph_traits< G >::vertex_descriptor u, v;
    std::pair< edge_descriptor, bool > p;
    G g;
};

BOOST_concept(ReadablePropertyGraph, (G)(X)(Property)) : Graph< G >
{
    typedef typename property_map< G, Property >::const_type const_Map;

    BOOST_CONCEPT_USAGE(ReadablePropertyGraph)
    {
        BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< const_Map, X >));

        const_constraints(g);
    }
    void const_constraints(const G& cg)
    {
        const_Map pmap = get(Property(), cg);
        pval = get(Property(), cg, x);
        ignore_unused_variable_warning(pmap);
    }
    G g;
    X x;
    typename property_traits< const_Map >::value_type pval;
};

BOOST_concept(PropertyGraph, (G)(X)(Property))
: ReadablePropertyGraph< G, X, Property >
{
    typedef typename property_map< G, Property >::type Map;
    BOOST_CONCEPT_USAGE(PropertyGraph)
    {
        BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept< Map, X >));

        Map pmap = get(Property(), g);
        pval = get(Property(), g, x);
        put(Property(), g, x, pval);
        ignore_unused_variable_warning(pmap);
    }
    G g;
    X x;
    typename property_traits< Map >::value_type pval;
};

BOOST_concept(LvaluePropertyGraph, (G)(X)(Property))
: ReadablePropertyGraph< G, X, Property >
{
    typedef typename property_map< G, Property >::type Map;
    typedef typename property_map< G, Property >::const_type const_Map;

    BOOST_CONCEPT_USAGE(LvaluePropertyGraph)
    {
        BOOST_CONCEPT_ASSERT((LvaluePropertyMapConcept< const_Map, X >));

        pval = get(Property(), g, x);
        put(Property(), g, x, pval);
    }
    G g;
    X x;
    typename property_traits< Map >::value_type pval;
};

// The *IndexGraph concepts are "semantic" graph concpepts. These can be
// applied to describe any graph that has an index map that can be accessed
// using the get(*_index, g) method. For example, adjacency lists with
// VertexSet == vecS are implicitly models of this concept.
//
// NOTE: We could require an associated type vertex_index_type, but that
// would mean propagating that type name into graph_traits and all of the
// other graph implementations. Much easier to simply call it unsigned.

BOOST_concept(VertexIndexGraph, (Graph))
{
    BOOST_CONCEPT_USAGE(VertexIndexGraph)
    {
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
        typedef typename property_map< Graph, vertex_index_t >::type Map;
        typedef unsigned Index; // This could be Graph::vertex_index_type
        Map m = get(vertex_index, g);
        Index x = get(vertex_index, g, Vertex());
        ignore_unused_variable_warning(m);
        ignore_unused_variable_warning(x);

        // This is relaxed
        renumber_vertex_indices(g);

        const_constraints(g);
    }
    void const_constraints(const Graph& g_)
    {
        typedef typename property_map< Graph, vertex_index_t >::const_type Map;
        Map m = get(vertex_index, g_);
        ignore_unused_variable_warning(m);
    }

private:
    Graph g;
};

BOOST_concept(EdgeIndexGraph, (Graph))
{
    BOOST_CONCEPT_USAGE(EdgeIndexGraph)
    {
        typedef typename graph_traits< Graph >::edge_descriptor Edge;
        typedef typename property_map< Graph, edge_index_t >::type Map;
        typedef unsigned Index; // This could be Graph::vertex_index_type
        Map m = get(edge_index, g);
        Index x = get(edge_index, g, Edge());
        ignore_unused_variable_warning(m);
        ignore_unused_variable_warning(x);

        // This is relaxed
        renumber_edge_indices(g);

        const_constraints(g);
    }
    void const_constraints(const Graph& g_)
    {
        typedef typename property_map< Graph, edge_index_t >::const_type Map;
        Map m = get(edge_index, g_);
        ignore_unused_variable_warning(m);
    }

private:
    Graph g;
};

BOOST_concept(ColorValue, (C))
: EqualityComparable< C >, DefaultConstructible< C >
{
    BOOST_CONCEPT_USAGE(ColorValue)
    {
        c = color_traits< C >::white();
        c = color_traits< C >::gray();
        c = color_traits< C >::black();
    }
    C c;
};

BOOST_concept(BasicMatrix, (M)(I)(V))
{
    BOOST_CONCEPT_USAGE(BasicMatrix)
    {
        V& elt = A[i][j];
        const_constraints(A);
        ignore_unused_variable_warning(elt);
    }
    void const_constraints(const M& cA)
    {
        const V& elt = cA[i][j];
        ignore_unused_variable_warning(elt);
    }
    M A;
    I i, j;
};

// The following concepts describe aspects of numberic values and measure
// functions. We're extending the notion of numeric values to include
// emulation for zero and infinity.

BOOST_concept(NumericValue, (Numeric)) { BOOST_CONCEPT_USAGE(NumericValue) {
    BOOST_CONCEPT_ASSERT((DefaultConstructible< Numeric >));
BOOST_CONCEPT_ASSERT((CopyConstructible< Numeric >));
numeric_values< Numeric >::zero();
numeric_values< Numeric >::infinity();
}
}
;

BOOST_concept(DegreeMeasure, (Measure)(Graph))
{
    BOOST_CONCEPT_USAGE(DegreeMeasure)
    {
        typedef typename Measure::degree_type Degree;
        typedef typename Measure::vertex_type Vertex;

        Degree d = m(Vertex(), g);
        ignore_unused_variable_warning(d);
    }

private:
    Measure m;
    Graph g;
};

BOOST_concept(DistanceMeasure, (Measure)(Graph))
{
    BOOST_CONCEPT_USAGE(DistanceMeasure)
    {
        typedef typename Measure::distance_type Distance;
        typedef typename Measure::result_type Result;
        Result r = m(Distance(), g);
        ignore_unused_variable_warning(r);
    }

private:
    Measure m;
    Graph g;
};

} /* namespace concepts */

using boost::concepts::MultiPassInputIteratorConcept;

// Graph concepts
using boost::concepts::AdjacencyGraphConcept;
using boost::concepts::AdjacencyMatrixConcept;
using boost::concepts::BidirectionalGraphConcept;
using boost::concepts::EdgeIndexGraphConcept;
using boost::concepts::EdgeListGraphConcept;
using boost::concepts::EdgeMutableGraphConcept;
using boost::concepts::EdgeMutablePropertyGraphConcept;
using boost::concepts::GraphConcept;
using boost::concepts::IncidenceGraphConcept;
using boost::concepts::LvaluePropertyGraphConcept;
using boost::concepts::MutableBidirectionalGraphConcept;
using boost::concepts::MutableEdgeListGraphConcept;
using boost::concepts::MutableGraphConcept;
using boost::concepts::MutableIncidenceGraphConcept;
using boost::concepts::PropertyGraphConcept;
using boost::concepts::ReadablePropertyGraphConcept;
using boost::concepts::VertexAndEdgeListGraphConcept;
using boost::concepts::VertexIndexGraphConcept;
using boost::concepts::VertexListGraphConcept;
using boost::concepts::VertexMutableGraphConcept;
using boost::concepts::VertexMutablePropertyGraphConcept;

// Utility concepts
using boost::concepts::BasicMatrixConcept;
using boost::concepts::ColorValueConcept;
using boost::concepts::DegreeMeasureConcept;
using boost::concepts::DistanceMeasureConcept;
using boost::concepts::NumericValueConcept;

} /* namespace boost */
#include <boost/concept/detail/concept_undef.hpp>

#endif /* BOOST_GRAPH_CONCEPTS_H */

/* graph_concepts.hpp
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
*/