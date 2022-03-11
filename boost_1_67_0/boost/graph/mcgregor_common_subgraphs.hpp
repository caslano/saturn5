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