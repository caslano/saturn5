//=======================================================================
// Copyright 2009 Trustees of Indiana University.
// Authors: Michael Hansen, Andrew Lumsdaine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_MCGREGOR_COMMON_SUBGRAPHS_HPP
#define BOOST_GRAPH_MCGREGOR_COMMON_SUBGRAPHS_HPP

#include <algorithm>
#include <vector>
#include <stack>

#include <boost/make_shared.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/shared_array_property_map.hpp>

namespace boost
{

namespace detail
{

    // Traits associated with common subgraphs, used mainly to keep a
    // consistent type for the correspondence maps.
    template < typename GraphFirst, typename GraphSecond,
        typename VertexIndexMapFirst, typename VertexIndexMapSecond >
    struct mcgregor_common_subgraph_traits
    {
        typedef typename graph_traits< GraphFirst >::vertex_descriptor
            vertex_first_type;
        typedef typename graph_traits< GraphSecond >::vertex_descriptor
            vertex_second_type;

        typedef shared_array_property_map< vertex_second_type,
            VertexIndexMapFirst >
            correspondence_map_first_to_second_type;

        typedef shared_array_property_map< vertex_first_type,
            VertexIndexMapSecond >
            correspondence_map_second_to_first_type;
    };

} // namespace detail

// ==========================================================================

// Binary function object that returns true if the values for item1
// in property_map1 and item2 in property_map2 are equivalent.
template < typename PropertyMapFirst, typename PropertyMapSecond >
struct property_map_equivalent
{

    property_map_equivalent(const PropertyMapFirst property_map1,
        const PropertyMapSecond property_map2)
    : m_property_map1(property_map1), m_property_map2(property_map2)
    {
    }

    template < typename ItemFirst, typename ItemSecond >
    bool operator()(const ItemFirst item1, const ItemSecond item2)
    {
        return (get(m_property_map1, item1) == get(m_property_map2, item2));
    }

private:
    const PropertyMapFirst m_property_map1;
    const PropertyMapSecond m_property_map2;
};

// Returns a property_map_equivalent object that compares the values
// of property_map1 and property_map2.
template < typename PropertyMapFirst, typename PropertyMapSecond >
property_map_equivalent< PropertyMapFirst, PropertyMapSecond >
make_property_map_equivalent(
    const PropertyMapFirst property_map1, const PropertyMapSecond property_map2)
{

    return (property_map_equivalent< PropertyMapFirst, PropertyMapSecond >(
        property_map1, property_map2));
}

// Binary function object that always returns true.  Used when
// vertices or edges are always equivalent (i.e. have no labels).
struct always_equivalent
{

    template < typename ItemFirst, typename ItemSecond >
    bool operator()(const ItemFirst&, const ItemSecond&)
    {
        return (true);
    }
};

// ==========================================================================

namespace detail
{

    // Return true if new_vertex1 and new_vertex2 can extend the
    // subgraph represented by correspondence_map_1_to_2 and
    // correspondence_map_2_to_1.  The vertices_equivalent and
    // edges_equivalent predicates are used to test vertex and edge
    // equivalency between the two graphs.
    template < typename GraphFirst, typename GraphSecond,
        typename CorrespondenceMapFirstToSecond,
        typename CorrespondenceMapSecondToFirst,
        typename EdgeEquivalencePredicate, typename VertexEquivalencePredicate >
    bool can_extend_graph(const GraphFirst& graph1, const GraphSecond& graph2,
        CorrespondenceMapFirstToSecond correspondence_map_1_to_2,
        CorrespondenceMapSecondToFirst /*correspondence_map_2_to_1*/,
        typename graph_traits< GraphFirst >::vertices_size_type subgraph_size,
        typename graph_traits< GraphFirst >::vertex_descriptor new_vertex1,
        typename graph_traits< GraphSecond >::vertex_descriptor new_vertex2,
        EdgeEquivalencePredicate edges_equivalent,
        VertexEquivalencePredicate vertices_equivalent,
        bool only_connected_subgraphs)
    {
        typedef typename graph_traits< GraphSecond >::vertex_descriptor
            VertexSecond;

        typedef typename graph_traits< GraphFirst >::edge_descriptor EdgeFirst;
        typedef
            typename graph_traits< GraphSecond >::edge_descriptor EdgeSecond;

        // Check vertex equality
        if (!vertices_equivalent(new_vertex1, new_vertex2))
        {
            return (false);
        }

        // Vertices match and graph is empty, so we can extend the subgraph
        if (subgraph_size == 0)
        {
            return (true);
        }

        bool has_one_edge = false;

        // Verify edges with existing sub-graph
        BGL_FORALL_VERTICES_T(existing_vertex1, graph1, GraphFirst)
        {

            VertexSecond existing_vertex2
                = get(correspondence_map_1_to_2, existing_vertex1);

            // Skip unassociated vertices
            if (existing_vertex2 == graph_traits< GraphSecond >::null_vertex())
            {
                continue;
            }

            // NOTE: This will not work with parallel edges, since the
            // first matching edge is always chosen.
            EdgeFirst edge_to_new1, edge_from_new1;
            bool edge_to_new_exists1 = false, edge_from_new_exists1 = false;

            EdgeSecond edge_to_new2, edge_from_new2;
            bool edge_to_new_exists2 = false, edge_from_new_exists2 = false;

            // Search for edge from existing to new vertex (graph1)
            BGL_FORALL_OUTEDGES_T(existing_vertex1, edge1, graph1, GraphFirst)
            {
                if (target(edge1, graph1) == new_vertex1)
                {
                    edge_to_new1 = edge1;
                    edge_to_new_exists1 = true;
                    break;
                }
            }

            // Search for edge from existing to new vertex (graph2)
            BGL_FORALL_OUTEDGES_T(existing_vertex2, edge2, graph2, GraphSecond)
            {
                if (target(edge2, graph2) == new_vertex2)
                {
                    edge_to_new2 = edge2;
                    edge_to_new_exists2 = true;
                    break;
                }
            }

            // Make sure edges from existing to new vertices are equivalent
            if ((edge_to_new_exists1 != edge_to_new_exists2)
                || ((edge_to_new_exists1 && edge_to_new_exists2)
                    && !edges_equivalent(edge_to_new1, edge_to_new2)))
            {

                return (false);
            }

            bool is_undirected1 = is_undirected(graph1),
                 is_undirected2 = is_undirected(graph2);

            if (is_undirected1 && is_undirected2)
            {

                // Edge in both graphs exists and both graphs are undirected
                if (edge_to_new_exists1 && edge_to_new_exists2)
                {
                    has_one_edge = true;
                }

                continue;
            }
            else
            {

                if (!is_undirected1)
                {

                    // Search for edge from new to existing vertex (graph1)
                    BGL_FORALL_OUTEDGES_T(
                        new_vertex1, edge1, graph1, GraphFirst)
                    {
                        if (target(edge1, graph1) == existing_vertex1)
                        {
                            edge_from_new1 = edge1;
                            edge_from_new_exists1 = true;
                            break;
                        }
                    }
                }

                if (!is_undirected2)
                {

                    // Search for edge from new to existing vertex (graph2)
                    BGL_FORALL_OUTEDGES_T(
                        new_vertex2, edge2, graph2, GraphSecond)
                    {
                        if (target(edge2, graph2) == existing_vertex2)
                        {
                            edge_from_new2 = edge2;
                            edge_from_new_exists2 = true;
                            break;
                        }
                    }
                }

                // Make sure edges from new to existing vertices are equivalent
                if ((edge_from_new_exists1 != edge_from_new_exists2)
                    || ((edge_from_new_exists1 && edge_from_new_exists2)
                        && !edges_equivalent(edge_from_new1, edge_from_new2)))
                {

                    return (false);
                }

                if ((edge_from_new_exists1 && edge_from_new_exists2)
                    || (edge_to_new_exists1 && edge_to_new_exists2))
                {
                    has_one_edge = true;
                }

            } // else

        } // BGL_FORALL_VERTICES_T

        // Make sure new vertices are connected to the existing subgraph
        if (only_connected_subgraphs && !has_one_edge)
        {
            return (false);
        }

        return (true);
    }

    // Recursive method that does a depth-first search in the space of
    // potential subgraphs.  At each level, every new vertex pair from
    // both graphs is tested to see if it can extend the current
    // subgraph.  If so, the subgraph is output to subgraph_callback
    // in the form of two correspondence maps (one for each graph).
    // Returning false from subgraph_callback will terminate the
    // search.  Function returns true if the entire search space was
    // explored.
    template < typename GraphFirst, typename GraphSecond,
        typename VertexIndexMapFirst, typename VertexIndexMapSecond,
        typename CorrespondenceMapFirstToSecond,
        typename CorrespondenceMapSecondToFirst, typename VertexStackFirst,
        typename EdgeEquivalencePredicate, typename VertexEquivalencePredicate,
        typename SubGraphInternalCallback >
    bool mcgregor_common_subgraphs_internal(const GraphFirst& graph1,
        const GraphSecond& graph2, const VertexIndexMapFirst& vindex_map1,
        const VertexIndexMapSecond& vindex_map2,
        CorrespondenceMapFirstToSecond correspondence_map_1_to_2,
        CorrespondenceMapSecondToFirst correspondence_map_2_to_1,
        VertexStackFirst& vertex_stack1,
        EdgeEquivalencePredicate edges_equivalent,
        VertexEquivalencePredicate vertices_equivalent,
        bool only_connected_subgraphs,
        SubGraphInternalCallback subgraph_callback)
    {
        typedef
            typename graph_traits< GraphFirst >::vertex_descriptor VertexFirst;
        typedef typename graph_traits< GraphSecond >::vertex_descriptor
            VertexSecond;
        typedef typename graph_traits< GraphFirst >::vertices_size_type
            VertexSizeFirst;

        // Get iterators for vertices from both graphs
        typename graph_traits< GraphFirst >::vertex_iterator vertex1_iter,
            vertex1_end;

        typename graph_traits< GraphSecond >::vertex_iterator vertex2_begin,
            vertex2_end, vertex2_iter;

        boost::tie(vertex1_iter, vertex1_end) = vertices(graph1);
        boost::tie(vertex2_begin, vertex2_end) = vertices(graph2);
        vertex2_iter = vertex2_begin;

        // Iterate until all vertices have been visited
        BGL_FORALL_VERTICES_T(new_vertex1, graph1, GraphFirst)
        {

            VertexSecond existing_vertex2
                = get(correspondence_map_1_to_2, new_vertex1);

            // Skip already matched vertices in first graph
            if (existing_vertex2 != graph_traits< GraphSecond >::null_vertex())
            {
                continue;
            }

            BGL_FORALL_VERTICES_T(new_vertex2, graph2, GraphSecond)
            {

                VertexFirst existing_vertex1
                    = get(correspondence_map_2_to_1, new_vertex2);

                // Skip already matched vertices in second graph
                if (existing_vertex1
                    != graph_traits< GraphFirst >::null_vertex())
                {
                    continue;
                }

                // Check if current sub-graph can be extended with the matched
                // vertex pair
                if (can_extend_graph(graph1, graph2, correspondence_map_1_to_2,
                        correspondence_map_2_to_1,
                        (VertexSizeFirst)vertex_stack1.size(), new_vertex1,
                        new_vertex2, edges_equivalent, vertices_equivalent,
                        only_connected_subgraphs))
                {

                    // Keep track of old graph size for restoring later
                    VertexSizeFirst old_graph_size
                        = (VertexSizeFirst)vertex_stack1.size(),
                        new_graph_size = old_graph_size + 1;

                    // Extend subgraph
                    put(correspondence_map_1_to_2, new_vertex1, new_vertex2);
                    put(correspondence_map_2_to_1, new_vertex2, new_vertex1);
                    vertex_stack1.push(new_vertex1);

                    // Returning false from the callback will cancel iteration
                    if (!subgraph_callback(correspondence_map_1_to_2,
                            correspondence_map_2_to_1, new_graph_size))
                    {
                        return (false);
                    }

                    // Depth-first search into the state space of possible
                    // sub-graphs
                    bool continue_iteration
                        = mcgregor_common_subgraphs_internal(graph1, graph2,
                            vindex_map1, vindex_map2, correspondence_map_1_to_2,
                            correspondence_map_2_to_1, vertex_stack1,
                            edges_equivalent, vertices_equivalent,
                            only_connected_subgraphs, subgraph_callback);

                    if (!continue_iteration)
                    {
                        return (false);
                    }

                    // Restore previous state
                    if (vertex_stack1.size() > old_graph_size)
                    {

                        VertexFirst stack_vertex1 = vertex_stack1.top();
                        VertexSecond stack_vertex2
                            = get(correspondence_map_1_to_2, stack_vertex1);

                        // Contract subgraph
                        put(correspondence_map_1_to_2, stack_vertex1,
                            graph_traits< GraphSecond >::null_vertex());

                        put(correspondence_map_2_to_1, stack_vertex2,
                            graph_traits< GraphFirst >::null_vertex());

                        vertex_stack1.pop();
                    }

                } // if can_extend_graph

            } // BGL_FORALL_VERTICES_T (graph2)

        } // BGL_FORALL_VERTICES_T (graph1)

        return (true);
    }

    // Internal method that initializes blank correspondence maps and
    // a vertex stack for use in mcgregor_common_subgraphs_internal.
    template < typename GraphFirst, typename GraphSecond,
        typename VertexIndexMapFirst, typename VertexIndexMapSecond,
        typename EdgeEquivalencePredicate, typename VertexEquivalencePredicate,
        typename SubGraphInternalCallback >
    inline void mcgregor_common_subgraphs_internal_init(
        const GraphFirst& graph1, const GraphSecond& graph2,
        const VertexIndexMapFirst vindex_map1,
        const VertexIndexMapSecond vindex_map2,
        EdgeEquivalencePredicate edges_equivalent,
        VertexEquivalencePredicate vertices_equivalent,
        bool only_connected_subgraphs,
        SubGraphInternalCallback subgraph_callback)
    {
        typedef mcgregor_common_subgraph_traits< GraphFirst, GraphSecond,
            VertexIndexMapFirst, VertexIndexMapSecond >
            SubGraphTraits;

        typename SubGraphTraits::correspondence_map_first_to_second_type
            correspondence_map_1_to_2(num_vertices(graph1), vindex_map1);

        BGL_FORALL_VERTICES_T(vertex1, graph1, GraphFirst)
        {
            put(correspondence_map_1_to_2, vertex1,
                graph_traits< GraphSecond >::null_vertex());
        }

        typename SubGraphTraits::correspondence_map_second_to_first_type
            correspondence_map_2_to_1(num_vertices(graph2), vindex_map2);

        BGL_FORALL_VERTICES_T(vertex2, graph2, GraphSecond)
        {
            put(correspondence_map_2_to_1, vertex2,
                graph_traits< GraphFirst >::null_vertex());
        }

        typedef
            typename graph_traits< GraphFirst >::vertex_descriptor VertexFirst;

        std::stack< VertexFirst > vertex_stack1;

        mcgregor_common_subgraphs_internal(graph1, graph2, vindex_map1,
            vindex_map2, correspondence_map_1_to_2, correspondence_map_2_to_1,
            vertex_stack1, edges_equivalent, vertices_equivalent,
            only_connected_subgraphs, subgraph_callback);
    }

} // namespace detail

// ==========================================================================

// Enumerates all common subgraphs present in graph1 and graph2.
// Continues until the search space has been fully explored or false
// is returned from user_callback.
template < typename GraphFirst, typename GraphSecond,
    typename VertexIndexMapFirst, typename VertexIndexMapSecond,
    typename EdgeEquivalencePredicate, typename VertexEquivalencePredicate,
    typename SubGraphCallback >
void mcgregor_common_subgraphs(const GraphFirst& graph1,
    const GraphSecond& graph2, const VertexIndexMapFirst vindex_map1,
    const VertexIndexMapSecond vindex_map2,
    EdgeEquivalencePredicate edges_equivalent,
    VertexEquivalencePredicate vertices_equivalent,
    bool only_connected_subgraphs, SubGraphCallback user_callback)
{

    detail::mcgregor_common_subgraphs_internal_init(graph1, graph2, vindex_map1,
        vindex_map2, edges_equivalent, vertices_equivalent,
        only_connected_subgraphs, user_callback);
}

// Variant of mcgregor_common_subgraphs with all default parameters
template < typename GraphFirst, typename GraphSecond,
    typename SubGraphCallback >
void mcgregor_common_subgraphs(const GraphFirst& graph1,
    const GraphSecond& graph2, bool only_connected_subgraphs,
    SubGraphCallback user_callback)
{

    detail::mcgregor_common_subgraphs_internal_init(graph1, graph2,
        get(vertex_index, graph1), get(vertex_index, graph2),
        always_equivalent(), always_equivalent(), only_connected_subgraphs,
        user_callback);
}

// Named parameter variant of mcgregor_common_subgraphs
template < typename GraphFirst, typename GraphSecond, typename SubGraphCallback,
    typename Param, typename Tag, typename Rest >
void mcgregor_common_subgraphs(const GraphFirst& graph1,
    const GraphSecond& graph2, bool only_connected_subgraphs,
    SubGraphCallback user_callback,
    const bgl_named_params< Param, Tag, Rest >& params)
{

    detail::mcgregor_common_subgraphs_internal_init(graph1, graph2,
        choose_const_pmap(
            get_param(params, vertex_index1), graph1, vertex_index),
        choose_const_pmap(
            get_param(params, vertex_index2), graph2, vertex_index),
        choose_param(
            get_param(params, edges_equivalent_t()), always_equivalent()),
        choose_param(
            get_param(params, vertices_equivalent_t()), always_equivalent()),
        only_connected_subgraphs, user_callback);
}

// ==========================================================================

namespace detail
{

    // Binary function object that intercepts subgraphs from
    // mcgregor_common_subgraphs_internal and maintains a cache of
    // unique subgraphs.  The user callback is invoked for each unique
    // subgraph.
    template < typename GraphFirst, typename GraphSecond,
        typename VertexIndexMapFirst, typename VertexIndexMapSecond,
        typename SubGraphCallback >
    struct unique_subgraph_interceptor
    {

        typedef typename graph_traits< GraphFirst >::vertices_size_type
            VertexSizeFirst;

        typedef mcgregor_common_subgraph_traits< GraphFirst, GraphSecond,
            VertexIndexMapFirst, VertexIndexMapSecond >
            SubGraphTraits;

        typedef typename SubGraphTraits::correspondence_map_first_to_second_type
            CachedCorrespondenceMapFirstToSecond;

        typedef typename SubGraphTraits::correspondence_map_second_to_first_type
            CachedCorrespondenceMapSecondToFirst;

        typedef std::pair< VertexSizeFirst,
            std::pair< CachedCorrespondenceMapFirstToSecond,
                CachedCorrespondenceMapSecondToFirst > >
            SubGraph;

        typedef std::vector< SubGraph > SubGraphList;

        unique_subgraph_interceptor(const GraphFirst& graph1,
            const GraphSecond& graph2, const VertexIndexMapFirst vindex_map1,
            const VertexIndexMapSecond vindex_map2,
            SubGraphCallback user_callback)
        : m_graph1(graph1)
        , m_graph2(graph2)
        , m_vindex_map1(vindex_map1)
        , m_vindex_map2(vindex_map2)
        , m_subgraphs(make_shared< SubGraphList >())
        , m_user_callback(user_callback)
        {
        }

        template < typename CorrespondenceMapFirstToSecond,
            typename CorrespondenceMapSecondToFirst >
        bool operator()(
            CorrespondenceMapFirstToSecond correspondence_map_1_to_2,
            CorrespondenceMapSecondToFirst correspondence_map_2_to_1,
            VertexSizeFirst subgraph_size)
        {

            for (typename SubGraphList::const_iterator subgraph_iter
                 = m_subgraphs->begin();
                 subgraph_iter != m_subgraphs->end(); ++subgraph_iter)
            {

                SubGraph subgraph_cached = *subgraph_iter;

                // Compare subgraph sizes
                if (subgraph_size != subgraph_cached.first)
                {
                    continue;
                }

                if (!are_property_maps_different(correspondence_map_1_to_2,
                        subgraph_cached.second.first, m_graph1))
                {

                    // New subgraph is a duplicate
                    return (true);
                }
            }

            // Subgraph is unique, so make a cached copy
            CachedCorrespondenceMapFirstToSecond new_subgraph_1_to_2
                = CachedCorrespondenceMapFirstToSecond(
                    num_vertices(m_graph1), m_vindex_map1);

            CachedCorrespondenceMapSecondToFirst new_subgraph_2_to_1
                = CorrespondenceMapSecondToFirst(
                    num_vertices(m_graph2), m_vindex_map2);

            BGL_FORALL_VERTICES_T(vertex1, m_graph1, GraphFirst)
            {
                put(new_subgraph_1_to_2, vertex1,
                    get(correspondence_map_1_to_2, vertex1));
            }

            BGL_FORALL_VERTICES_T(vertex2, m_graph2, GraphFirst)
            {
                put(new_subgraph_2_to_1, vertex2,
                    get(correspondence_map_2_to_1, vertex2));
            }

            m_subgraphs->push_back(std::make_pair(subgraph_size,
                std::make_pair(new_subgraph_1_to_2, new_subgraph_2_to_1)));

            return (m_user_callback(correspondence_map_1_to_2,
                correspondence_map_2_to_1, subgraph_size));
        }

    private:
        const GraphFirst& m_graph1;
        const GraphFirst& m_graph2;
        const VertexIndexMapFirst m_vindex_map1;
        const VertexIndexMapSecond m_vindex_map2;
        shared_ptr< SubGraphList > m_subgraphs;
        SubGraphCallback m_user_callback;
    };

} // namespace detail

// Enumerates all unique common subgraphs between graph1 and graph2.
// The user callback is invoked for each unique subgraph as they are
// discovered.
template < typename GraphFirst, typename GraphSecond,
    typename VertexIndexMapFirst, typename VertexIndexMapSecond,
    typename EdgeEquivalencePredicate, typename VertexEquivalencePredicate,
    typename SubGraphCallback >
void mcgregor_common_subgraphs_unique(const GraphFirst& graph1,
    const GraphSecond& graph2, const VertexIndexMapFirst vindex_map1,
    const VertexIndexMapSecond vindex_map2,
    EdgeEquivalencePredicate edges_equivalent,
    VertexEquivalencePredicate vertices_equivalent,
    bool only_connected_subgraphs, SubGraphCallback user_callback)
{
    detail::unique_subgraph_interceptor< GraphFirst, GraphSecond,
        VertexIndexMapFirst, VertexIndexMapSecond, SubGraphCallback >
        unique_callback(
            graph1, graph2, vindex_map1, vindex_map2, user_callback);

    detail::mcgregor_common_subgraphs_internal_init(graph1, graph2, vindex_map1,
        vindex_map2, edges_equivalent, vertices_equivalent,
        only_connected_subgraphs, unique_callback);
}

// Variant of mcgregor_common_subgraphs_unique with all default
// parameters.
template < typename GraphFirst, typename GraphSecond,
    typename SubGraphCallback >
void mcgregor_common_subgraphs_unique(const GraphFirst& graph1,
    const GraphSecond& graph2, bool only_connected_subgraphs,
    SubGraphCallback user_callback)
{
    mcgregor_common_subgraphs_unique(graph1, graph2, get(vertex_index, graph1),
        get(vertex_index, graph2), always_equivalent(), always_equivalent(),
        only_connected_subgraphs, user_callback);
}

// Named parameter variant of mcgregor_common_subgraphs_unique
template < typename GraphFirst, typename GraphSecond, typename SubGraphCallback,
    typename Param, typename Tag, typename Rest >
void mcgregor_common_subgraphs_unique(const GraphFirst& graph1,
    const GraphSecond& graph2, bool only_connected_subgraphs,
    SubGraphCallback user_callback,
    const bgl_named_params< Param, Tag, Rest >& params)
{
    mcgregor_common_subgraphs_unique(graph1, graph2,
        choose_const_pmap(
            get_param(params, vertex_index1), graph1, vertex_index),
        choose_const_pmap(
            get_param(params, vertex_index2), graph2, vertex_index),
        choose_param(
            get_param(params, edges_equivalent_t()), always_equivalent()),
        choose_param(
            get_param(params, vertices_equivalent_t()), always_equivalent()),
        only_connected_subgraphs, user_callback);
}

// ==========================================================================

namespace detail
{

    // Binary function object that intercepts subgraphs from
    // mcgregor_common_subgraphs_internal and maintains a cache of the
    // largest subgraphs.
    template < typename GraphFirst, typename GraphSecond,
        typename VertexIndexMapFirst, typename VertexIndexMapSecond,
        typename SubGraphCallback >
    struct maximum_subgraph_interceptor
    {

        typedef typename graph_traits< GraphFirst >::vertices_size_type
            VertexSizeFirst;

        typedef mcgregor_common_subgraph_traits< GraphFirst, GraphSecond,
            VertexIndexMapFirst, VertexIndexMapSecond >
            SubGraphTraits;

        typedef typename SubGraphTraits::correspondence_map_first_to_second_type
            CachedCorrespondenceMapFirstToSecond;

        typedef typename SubGraphTraits::correspondence_map_second_to_first_type
            CachedCorrespondenceMapSecondToFirst;

        typedef std::pair< VertexSizeFirst,
            std::pair< CachedCorrespondenceMapFirstToSecond,
                CachedCorrespondenceMapSecondToFirst > >
            SubGraph;

        typedef std::vector< SubGraph > SubGraphList;

        maximum_subgraph_interceptor(const GraphFirst& graph1,
            const GraphSecond& graph2, const VertexIndexMapFirst vindex_map1,
            const VertexIndexMapSecond vindex_map2,
            SubGraphCallback user_callback)
        : m_graph1(graph1)
        , m_graph2(graph2)
        , m_vindex_map1(vindex_map1)
        , m_vindex_map2(vindex_map2)
        , m_subgraphs(make_shared< SubGraphList >())
        , m_largest_size_so_far(make_shared< VertexSizeFirst >(0))
        , m_user_callback(user_callback)
        {
        }

        template < typename CorrespondenceMapFirstToSecond,
            typename CorrespondenceMapSecondToFirst >
        bool operator()(
            CorrespondenceMapFirstToSecond correspondence_map_1_to_2,
            CorrespondenceMapSecondToFirst correspondence_map_2_to_1,
            VertexSizeFirst subgraph_size)
        {

            if (subgraph_size > *m_largest_size_so_far)
            {
                m_subgraphs->clear();
                *m_largest_size_so_far = subgraph_size;
            }

            if (subgraph_size == *m_largest_size_so_far)
            {

                // Make a cached copy
                CachedCorrespondenceMapFirstToSecond new_subgraph_1_to_2
                    = CachedCorrespondenceMapFirstToSecond(
                        num_vertices(m_graph1), m_vindex_map1);

                CachedCorrespondenceMapSecondToFirst new_subgraph_2_to_1
                    = CachedCorrespondenceMapSecondToFirst(
                        num_vertices(m_graph2), m_vindex_map2);

                BGL_FORALL_VERTICES_T(vertex1, m_graph1, GraphFirst)
                {
                    put(new_subgraph_1_to_2, vertex1,
                        get(correspondence_map_1_to_2, vertex1));
                }

                BGL_FORALL_VERTICES_T(vertex2, m_graph2, GraphFirst)
                {
                    put(new_subgraph_2_to_1, vertex2,
                        get(correspondence_map_2_to_1, vertex2));
                }

                m_subgraphs->push_back(std::make_pair(subgraph_size,
                    std::make_pair(new_subgraph_1_to_2, new_subgraph_2_to_1)));
            }

            return (true);
        }

        void output_subgraphs()
        {
            for (typename SubGraphList::const_iterator subgraph_iter
                 = m_subgraphs->begin();
                 subgraph_iter != m_subgraphs->end(); ++subgraph_iter)
            {

                SubGraph subgraph_cached = *subgraph_iter;
                m_user_callback(subgraph_cached.second.first,
                    subgraph_cached.second.second, subgraph_cached.first);
            }
        }

    private:
        const GraphFirst& m_graph1;
        const GraphFirst& m_graph2;
        const VertexIndexMapFirst m_vindex_map1;
        const VertexIndexMapSecond m_vindex_map2;
        shared_ptr< SubGraphList > m_subgraphs;
        shared_ptr< VertexSizeFirst > m_largest_size_so_far;
        SubGraphCallback m_user_callback;
    };

} // namespace detail

// Enumerates the largest common subgraphs found between graph1
// and graph2.  Note that the ENTIRE search space is explored before
// user_callback is actually invoked.
template < typename GraphFirst, typename GraphSecond,
    typename VertexIndexMapFirst, typename VertexIndexMapSecond,
    typename EdgeEquivalencePredicate, typename VertexEquivalencePredicate,
    typename SubGraphCallback >
void mcgregor_common_subgraphs_maximum(const GraphFirst& graph1,
    const GraphSecond& graph2, const VertexIndexMapFirst vindex_map1,
    const VertexIndexMapSecond vindex_map2,
    EdgeEquivalencePredicate edges_equivalent,
    VertexEquivalencePredicate vertices_equivalent,
    bool only_connected_subgraphs, SubGraphCallback user_callback)
{
    detail::maximum_subgraph_interceptor< GraphFirst, GraphSecond,
        VertexIndexMapFirst, VertexIndexMapSecond, SubGraphCallback >
        max_interceptor(
            graph1, graph2, vindex_map1, vindex_map2, user_callback);

    detail::mcgregor_common_subgraphs_internal_init(graph1, graph2, vindex_map1,
        vindex_map2, edges_equivalent, vertices_equivalent,
        only_connected_subgraphs, max_interceptor);

    // Only output the largest subgraphs
    max_interceptor.output_subgraphs();
}

// Variant of mcgregor_common_subgraphs_maximum with all default
// parameters.
template < typename GraphFirst, typename GraphSecond,
    typename SubGraphCallback >
void mcgregor_common_subgraphs_maximum(const GraphFirst& graph1,
    const GraphSecond& graph2, bool only_connected_subgraphs,
    SubGraphCallback user_callback)
{
    mcgregor_common_subgraphs_maximum(graph1, graph2, get(vertex_index, graph1),
        get(vertex_index, graph2), always_equivalent(), always_equivalent(),
        only_connected_subgraphs, user_callback);
}

// Named parameter variant of mcgregor_common_subgraphs_maximum
template < typename GraphFirst, typename GraphSecond, typename SubGraphCallback,
    typename Param, typename Tag, typename Rest >
void mcgregor_common_subgraphs_maximum(const GraphFirst& graph1,
    const GraphSecond& graph2, bool only_connected_subgraphs,
    SubGraphCallback user_callback,
    const bgl_named_params< Param, Tag, Rest >& params)
{
    mcgregor_common_subgraphs_maximum(graph1, graph2,
        choose_const_pmap(
            get_param(params, vertex_index1), graph1, vertex_index),
        choose_const_pmap(
            get_param(params, vertex_index2), graph2, vertex_index),
        choose_param(
            get_param(params, edges_equivalent_t()), always_equivalent()),
        choose_param(
            get_param(params, vertices_equivalent_t()), always_equivalent()),
        only_connected_subgraphs, user_callback);
}

// ==========================================================================

namespace detail
{

    // Binary function object that intercepts subgraphs from
    // mcgregor_common_subgraphs_internal and maintains a cache of the
    // largest, unique subgraphs.
    template < typename GraphFirst, typename GraphSecond,
        typename VertexIndexMapFirst, typename VertexIndexMapSecond,
        typename SubGraphCallback >
    struct unique_maximum_subgraph_interceptor
    {

        typedef typename graph_traits< GraphFirst >::vertices_size_type
            VertexSizeFirst;

        typedef mcgregor_common_subgraph_traits< GraphFirst, GraphSecond,
            VertexIndexMapFirst, VertexIndexMapSecond >
            SubGraphTraits;

        typedef typename SubGraphTraits::correspondence_map_first_to_second_type
            CachedCorrespondenceMapFirstToSecond;

        typedef typename SubGraphTraits::correspondence_map_second_to_first_type
            CachedCorrespondenceMapSecondToFirst;

        typedef std::pair< VertexSizeFirst,
            std::pair< CachedCorrespondenceMapFirstToSecond,
                CachedCorrespondenceMapSecondToFirst > >
            SubGraph;

        typedef std::vector< SubGraph > SubGraphList;

        unique_maximum_subgraph_interceptor(const GraphFirst& graph1,
            const GraphSecond& graph2, const VertexIndexMapFirst vindex_map1,
            const VertexIndexMapSecond vindex_map2,
            SubGraphCallback user_callback)
        : m_graph1(graph1)
        , m_graph2(graph2)
        , m_vindex_map1(vindex_map1)
        , m_vindex_map2(vindex_map2)
        , m_subgraphs(make_shared< SubGraphList >())
        , m_largest_size_so_far(make_shared< VertexSizeFirst >(0))
        , m_user_callback(user_callback)
        {
        }

        template < typename CorrespondenceMapFirstToSecond,
            typename CorrespondenceMapSecondToFirst >
        bool operator()(
            CorrespondenceMapFirstToSecond correspondence_map_1_to_2,
            CorrespondenceMapSecondToFirst correspondence_map_2_to_1,
            VertexSizeFirst subgraph_size)
        {

            if (subgraph_size > *m_largest_size_so_far)
            {
                m_subgraphs->clear();
                *m_largest_size_so_far = subgraph_size;
            }

            if (subgraph_size == *m_largest_size_so_far)
            {

                // Check if subgraph is unique
                for (typename SubGraphList::const_iterator subgraph_iter
                     = m_subgraphs->begin();
                     subgraph_iter != m_subgraphs->end(); ++subgraph_iter)
                {

                    SubGraph subgraph_cached = *subgraph_iter;

                    if (!are_property_maps_different(correspondence_map_1_to_2,
                            subgraph_cached.second.first, m_graph1))
                    {

                        // New subgraph is a duplicate
                        return (true);
                    }
                }

                // Subgraph is unique, so make a cached copy
                CachedCorrespondenceMapFirstToSecond new_subgraph_1_to_2
                    = CachedCorrespondenceMapFirstToSecond(
                        num_vertices(m_graph1), m_vindex_map1);

                CachedCorrespondenceMapSecondToFirst new_subgraph_2_to_1
                    = CachedCorrespondenceMapSecondToFirst(
                        num_vertices(m_graph2), m_vindex_map2);

                BGL_FORALL_VERTICES_T(vertex1, m_graph1, GraphFirst)
                {
                    put(new_subgraph_1_to_2, vertex1,
                        get(correspondence_map_1_to_2, vertex1));
                }

                BGL_FORALL_VERTICES_T(vertex2, m_graph2, GraphFirst)
                {
                    put(new_subgraph_2_to_1, vertex2,
                        get(correspondence_map_2_to_1, vertex2));
                }

                m_subgraphs->push_back(std::make_pair(subgraph_size,
                    std::make_pair(new_subgraph_1_to_2, new_subgraph_2_to_1)));
            }

            return (true);
        }

        void output_subgraphs()
        {
            for (typename SubGraphList::const_iterator subgraph_iter
                 = m_subgraphs->begin();
                 subgraph_iter != m_subgraphs->end(); ++subgraph_iter)
            {

                SubGraph subgraph_cached = *subgraph_iter;
                m_user_callback(subgraph_cached.second.first,
                    subgraph_cached.second.second, subgraph_cached.first);
            }
        }

    private:
        const GraphFirst& m_graph1;
        const GraphFirst& m_graph2;
        const VertexIndexMapFirst m_vindex_map1;
        const VertexIndexMapSecond m_vindex_map2;
        shared_ptr< SubGraphList > m_subgraphs;
        shared_ptr< VertexSizeFirst > m_largest_size_so_far;
        SubGraphCallback m_user_callback;
    };

} // namespace detail

// Enumerates the largest, unique common subgraphs found between
// graph1 and graph2.  Note that the ENTIRE search space is explored
// before user_callback is actually invoked.
template < typename GraphFirst, typename GraphSecond,
    typename VertexIndexMapFirst, typename VertexIndexMapSecond,
    typename EdgeEquivalencePredicate, typename VertexEquivalencePredicate,
    typename SubGraphCallback >
void mcgregor_common_subgraphs_maximum_unique(const GraphFirst& graph1,
    const GraphSecond& graph2, const VertexIndexMapFirst vindex_map1,
    const VertexIndexMapSecond vindex_map2,
    EdgeEquivalencePredicate edges_equivalent,
    VertexEquivalencePredicate vertices_equivalent,
    bool only_connected_subgraphs, SubGraphCallback user_callback)
{
    detail::unique_maximum_subgraph_interceptor< GraphFirst, GraphSecond,
        VertexIndexMapFirst, VertexIndexMapSecond, SubGraphCallback >
        unique_max_interceptor(
            graph1, graph2, vindex_map1, vindex_map2, user_callback);

    detail::mcgregor_common_subgraphs_internal_init(graph1, graph2, vindex_map1,
        vindex_map2, edges_equivalent, vertices_equivalent,
        only_connected_subgraphs, unique_max_interceptor);

    // Only output the largest, unique subgraphs
    unique_max_interceptor.output_subgraphs();
}

// Variant of mcgregor_common_subgraphs_maximum_unique with all default
// parameters
template < typename GraphFirst, typename GraphSecond,
    typename SubGraphCallback >
void mcgregor_common_subgraphs_maximum_unique(const GraphFirst& graph1,
    const GraphSecond& graph2, bool only_connected_subgraphs,
    SubGraphCallback user_callback)
{

    mcgregor_common_subgraphs_maximum_unique(graph1, graph2,
        get(vertex_index, graph1), get(vertex_index, graph2),
        always_equivalent(), always_equivalent(), only_connected_subgraphs,
        user_callback);
}

// Named parameter variant of
// mcgregor_common_subgraphs_maximum_unique
template < typename GraphFirst, typename GraphSecond, typename SubGraphCallback,
    typename Param, typename Tag, typename Rest >
void mcgregor_common_subgraphs_maximum_unique(const GraphFirst& graph1,
    const GraphSecond& graph2, bool only_connected_subgraphs,
    SubGraphCallback user_callback,
    const bgl_named_params< Param, Tag, Rest >& params)
{
    mcgregor_common_subgraphs_maximum_unique(graph1, graph2,
        choose_const_pmap(
            get_param(params, vertex_index1), graph1, vertex_index),
        choose_const_pmap(
            get_param(params, vertex_index2), graph2, vertex_index),
        choose_param(
            get_param(params, edges_equivalent_t()), always_equivalent()),
        choose_param(
            get_param(params, vertices_equivalent_t()), always_equivalent()),
        only_connected_subgraphs, user_callback);
}

// ==========================================================================

// Fills a membership map (vertex -> bool) using the information
// present in correspondence_map_1_to_2. Every vertex in a
// membership map will have a true value only if it is not
// associated with a null vertex in the correspondence map.
template < typename GraphSecond, typename GraphFirst,
    typename CorrespondenceMapFirstToSecond, typename MembershipMapFirst >
void fill_membership_map(const GraphFirst& graph1,
    const CorrespondenceMapFirstToSecond correspondence_map_1_to_2,
    MembershipMapFirst membership_map1)
{

    BGL_FORALL_VERTICES_T(vertex1, graph1, GraphFirst)
    {
        put(membership_map1, vertex1,
            get(correspondence_map_1_to_2, vertex1)
                != graph_traits< GraphSecond >::null_vertex());
    }
}

// Traits associated with a membership map filtered graph.  Provided
// for convenience to access graph and vertex filter types.
template < typename Graph, typename MembershipMap >
struct membership_filtered_graph_traits
{
    typedef property_map_filter< MembershipMap > vertex_filter_type;
    typedef filtered_graph< Graph, keep_all, vertex_filter_type > graph_type;
};

// Returns a filtered sub-graph of graph whose edge and vertex
// inclusion is dictated by membership_map.
template < typename Graph, typename MembershipMap >
typename membership_filtered_graph_traits< Graph, MembershipMap >::graph_type
make_membership_filtered_graph(
    const Graph& graph, MembershipMap& membership_map)
{

    typedef membership_filtered_graph_traits< Graph, MembershipMap > MFGTraits;
    typedef typename MFGTraits::graph_type MembershipFilteredGraph;

    typename MFGTraits::vertex_filter_type v_filter(membership_map);

    return (MembershipFilteredGraph(graph, keep_all(), v_filter));
}

} // namespace boost

#endif // BOOST_GRAPH_MCGREGOR_COMMON_SUBGRAPHS_HPP

/* mcgregor_common_subgraphs.hpp
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
*/