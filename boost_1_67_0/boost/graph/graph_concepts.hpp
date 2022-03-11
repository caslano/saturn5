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
    && !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
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