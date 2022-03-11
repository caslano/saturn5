//  Copyright (c) 2006, Stephan Diederich
//
//  This code may be used under either of the following two licences:
//
//    Permission is hereby granted, free of charge, to any person
//    obtaining a copy of this software and associated documentation
//    files (the "Software"), to deal in the Software without
//    restriction, including without limitation the rights to use,
//    copy, modify, merge, publish, distribute, sublicense, and/or
//    sell copies of the Software, and to permit persons to whom the
//    Software is furnished to do so, subject to the following
//    conditions:
//
//    The above copyright notice and this permission notice shall be
//    included in all copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//    OTHER DEALINGS IN THE SOFTWARE. OF SUCH DAMAGE.
//
//  Or:
//
//    Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//    http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BOYKOV_KOLMOGOROV_MAX_FLOW_HPP
#define BOOST_BOYKOV_KOLMOGOROV_MAX_FLOW_HPP

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <vector>
#include <list>
#include <utility>
#include <iosfwd>
#include <algorithm> // for std::min and std::max

#include <boost/pending/queue.hpp>
#include <boost/limits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/none_t.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/lookup_edge.hpp>
#include <boost/concept/assert.hpp>

// The algorithm impelemented here is described in:
//
// Boykov, Y., Kolmogorov, V. "An Experimental Comparison of Min-Cut/Max-Flow
// Algorithms for Energy Minimization in Vision", In IEEE Transactions on
// Pattern Analysis and Machine Intelligence, vol. 26, no. 9, pp. 1124-1137,
// Sep 2004.
//
// For further reading, also see:
//
// Kolmogorov, V. "Graph Based Algorithms for Scene Reconstruction from Two or
// More Views". PhD thesis, Cornell University, Sep 2003.

namespace boost
{

namespace detail
{

    template < class Graph, class EdgeCapacityMap,
        class ResidualCapacityEdgeMap, class ReverseEdgeMap,
        class PredecessorMap, class ColorMap, class DistanceMap,
        class IndexMap >
    class bk_max_flow
    {
        typedef
            typename property_traits< EdgeCapacityMap >::value_type tEdgeVal;
        typedef graph_traits< Graph > tGraphTraits;
        typedef typename tGraphTraits::vertex_iterator vertex_iterator;
        typedef typename tGraphTraits::vertex_descriptor vertex_descriptor;
        typedef typename tGraphTraits::edge_descriptor edge_descriptor;
        typedef typename tGraphTraits::edge_iterator edge_iterator;
        typedef typename tGraphTraits::out_edge_iterator out_edge_iterator;
        typedef boost::queue< vertex_descriptor >
            tQueue; // queue of vertices, used in adoption-stage
        typedef typename property_traits< ColorMap >::value_type tColorValue;
        typedef color_traits< tColorValue > tColorTraits;
        typedef
            typename property_traits< DistanceMap >::value_type tDistanceVal;

    public:
        bk_max_flow(Graph& g, EdgeCapacityMap cap, ResidualCapacityEdgeMap res,
            ReverseEdgeMap rev, PredecessorMap pre, ColorMap color,
            DistanceMap dist, IndexMap idx, vertex_descriptor src,
            vertex_descriptor sink)
        : m_g(g)
        , m_index_map(idx)
        , m_cap_map(cap)
        , m_res_cap_map(res)
        , m_rev_edge_map(rev)
        , m_pre_map(pre)
        , m_tree_map(color)
        , m_dist_map(dist)
        , m_source(src)
        , m_sink(sink)
        , m_active_nodes()
        , m_in_active_list_vec(num_vertices(g), false)
        , m_in_active_list_map(make_iterator_property_map(
              m_in_active_list_vec.begin(), m_index_map))
        , m_has_parent_vec(num_vertices(g), false)
        , m_has_parent_map(
              make_iterator_property_map(m_has_parent_vec.begin(), m_index_map))
        , m_time_vec(num_vertices(g), 0)
        , m_time_map(
              make_iterator_property_map(m_time_vec.begin(), m_index_map))
        , m_flow(0)
        , m_time(1)
        , m_last_grow_vertex(graph_traits< Graph >::null_vertex())
        {
            // initialize the color-map with gray-values
            vertex_iterator vi, v_end;
            for (boost::tie(vi, v_end) = vertices(m_g); vi != v_end; ++vi)
            {
                set_tree(*vi, tColorTraits::gray());
            }
            // Initialize flow to zero which means initializing
            // the residual capacity equal to the capacity
            edge_iterator ei, e_end;
            for (boost::tie(ei, e_end) = edges(m_g); ei != e_end; ++ei)
            {
                put(m_res_cap_map, *ei, get(m_cap_map, *ei));
                BOOST_ASSERT(get(m_rev_edge_map, get(m_rev_edge_map, *ei))
                    == *ei); // check if the reverse edge map is build up
                             // properly
            }
            // init the search trees with the two terminals
            set_tree(m_source, tColorTraits::black());
            set_tree(m_sink, tColorTraits::white());
            put(m_time_map, m_source, 1);
            put(m_time_map, m_sink, 1);
        }

        tEdgeVal max_flow()
        {
            // augment direct paths from SOURCE->SINK and SOURCE->VERTEX->SINK
            augment_direct_paths();
            // start the main-loop
            while (true)
            {
                bool path_found;
                edge_descriptor connecting_edge;
                boost::tie(connecting_edge, path_found)
                    = grow(); // find a path from source to sink
                if (!path_found)
                {
                    // we're finished, no more paths were found
                    break;
                }
                ++m_time;
                augment(connecting_edge); // augment that path
                adopt(); // rebuild search tree structure
            }
            return m_flow;
        }

        // the complete class is protected, as we want access to members in
        // derived test-class (see test/boykov_kolmogorov_max_flow_test.cpp)
    protected:
        void augment_direct_paths()
        {
            // in a first step, we augment all direct paths from
            // source->NODE->sink and additionally paths from source->sink. This
            // improves especially graphcuts for segmentation, as most of the
            // nodes have source/sink connects but shouldn't have an impact on
            // other maxflow problems (this is done in grow() anyway)
            out_edge_iterator ei, e_end;
            for (boost::tie(ei, e_end) = out_edges(m_source, m_g); ei != e_end;
                 ++ei)
            {
                edge_descriptor from_source = *ei;
                vertex_descriptor current_node = target(from_source, m_g);
                if (current_node == m_sink)
                {
                    tEdgeVal cap = get(m_res_cap_map, from_source);
                    put(m_res_cap_map, from_source, 0);
                    m_flow += cap;
                    continue;
                }
                edge_descriptor to_sink;
                bool is_there;
                boost::tie(to_sink, is_there)
                    = lookup_edge(current_node, m_sink, m_g);
                if (is_there)
                {
                    tEdgeVal cap_from_source = get(m_res_cap_map, from_source);
                    tEdgeVal cap_to_sink = get(m_res_cap_map, to_sink);
                    if (cap_from_source > cap_to_sink)
                    {
                        set_tree(current_node, tColorTraits::black());
                        add_active_node(current_node);
                        set_edge_to_parent(current_node, from_source);
                        put(m_dist_map, current_node, 1);
                        put(m_time_map, current_node, 1);
                        // add stuff to flow and update residuals. we dont need
                        // to update reverse_edges, as incoming/outgoing edges
                        // to/from source/sink don't count for max-flow
                        put(m_res_cap_map, from_source,
                            get(m_res_cap_map, from_source) - cap_to_sink);
                        put(m_res_cap_map, to_sink, 0);
                        m_flow += cap_to_sink;
                    }
                    else if (cap_to_sink > 0)
                    {
                        set_tree(current_node, tColorTraits::white());
                        add_active_node(current_node);
                        set_edge_to_parent(current_node, to_sink);
                        put(m_dist_map, current_node, 1);
                        put(m_time_map, current_node, 1);
                        // add stuff to flow and update residuals. we dont need
                        // to update reverse_edges, as incoming/outgoing edges
                        // to/from source/sink don't count for max-flow
                        put(m_res_cap_map, to_sink,
                            get(m_res_cap_map, to_sink) - cap_from_source);
                        put(m_res_cap_map, from_source, 0);
                        m_flow += cap_from_source;
                    }
                }
                else if (get(m_res_cap_map, from_source))
                {
                    // there is no sink connect, so we can't augment this path,
                    // but to avoid adding m_source to the active nodes, we just
                    // activate this node and set the approciate things
                    set_tree(current_node, tColorTraits::black());
                    set_edge_to_parent(current_node, from_source);
                    put(m_dist_map, current_node, 1);
                    put(m_time_map, current_node, 1);
                    add_active_node(current_node);
                }
            }
            for (boost::tie(ei, e_end) = out_edges(m_sink, m_g); ei != e_end;
                 ++ei)
            {
                edge_descriptor to_sink = get(m_rev_edge_map, *ei);
                vertex_descriptor current_node = source(to_sink, m_g);
                if (get(m_res_cap_map, to_sink))
                {
                    set_tree(current_node, tColorTraits::white());
                    set_edge_to_parent(current_node, to_sink);
                    put(m_dist_map, current_node, 1);
                    put(m_time_map, current_node, 1);
                    add_active_node(current_node);
                }
            }
        }

        /**
         * Returns a pair of an edge and a boolean. if the bool is true, the
         * edge is a connection of a found path from s->t , read "the link" and
         * source(returnVal, m_g) is the end of the path found in the
         * source-tree target(returnVal, m_g) is the beginning of the path found
         * in the sink-tree
         */
        std::pair< edge_descriptor, bool > grow()
        {
            BOOST_ASSERT(m_orphans.empty());
            vertex_descriptor current_node;
            while ((current_node = get_next_active_node())
                != graph_traits< Graph >::null_vertex())
            { // if there is one
                BOOST_ASSERT(get_tree(current_node) != tColorTraits::gray()
                    && (has_parent(current_node) || current_node == m_source
                        || current_node == m_sink));

                if (get_tree(current_node) == tColorTraits::black())
                {
                    // source tree growing
                    out_edge_iterator ei, e_end;
                    if (current_node != m_last_grow_vertex)
                    {
                        m_last_grow_vertex = current_node;
                        boost::tie(m_last_grow_edge_it, m_last_grow_edge_end)
                            = out_edges(current_node, m_g);
                    }
                    for (; m_last_grow_edge_it != m_last_grow_edge_end;
                         ++m_last_grow_edge_it)
                    {
                        edge_descriptor out_edge = *m_last_grow_edge_it;
                        if (get(m_res_cap_map, out_edge) > 0)
                        { // check if we have capacity left on this edge
                            vertex_descriptor other_node
                                = target(out_edge, m_g);
                            if (get_tree(other_node) == tColorTraits::gray())
                            { // it's a free node
                                set_tree(other_node,
                                    tColorTraits::black()); // aquire other node
                                                            // to our search
                                                            // tree
                                set_edge_to_parent(
                                    other_node, out_edge); // set us as parent
                                put(m_dist_map, other_node,
                                    get(m_dist_map, current_node)
                                        + 1); // and update the
                                              // distance-heuristic
                                put(m_time_map, other_node,
                                    get(m_time_map, current_node));
                                add_active_node(other_node);
                            }
                            else if (get_tree(other_node)
                                == tColorTraits::black())
                            {
                                // we do this to get shorter paths. check if we
                                // are nearer to the source as its parent is
                                if (is_closer_to_terminal(
                                        current_node, other_node))
                                {
                                    set_edge_to_parent(other_node, out_edge);
                                    put(m_dist_map, other_node,
                                        get(m_dist_map, current_node) + 1);
                                    put(m_time_map, other_node,
                                        get(m_time_map, current_node));
                                }
                            }
                            else
                            {
                                BOOST_ASSERT(get_tree(other_node)
                                    == tColorTraits::white());
                                // kewl, found a path from one to the other
                                // search tree, return
                                // the connecting edge in src->sink dir
                                return std::make_pair(out_edge, true);
                            }
                        }
                    } // for all out-edges
                } // source-tree-growing
                else
                {
                    BOOST_ASSERT(
                        get_tree(current_node) == tColorTraits::white());
                    out_edge_iterator ei, e_end;
                    if (current_node != m_last_grow_vertex)
                    {
                        m_last_grow_vertex = current_node;
                        boost::tie(m_last_grow_edge_it, m_last_grow_edge_end)
                            = out_edges(current_node, m_g);
                    }
                    for (; m_last_grow_edge_it != m_last_grow_edge_end;
                         ++m_last_grow_edge_it)
                    {
                        edge_descriptor in_edge
                            = get(m_rev_edge_map, *m_last_grow_edge_it);
                        if (get(m_res_cap_map, in_edge) > 0)
                        { // check if there is capacity left
                            vertex_descriptor other_node = source(in_edge, m_g);
                            if (get_tree(other_node) == tColorTraits::gray())
                            { // it's a free node
                                set_tree(other_node,
                                    tColorTraits::white()); // aquire that node
                                                            // to our search
                                                            // tree
                                set_edge_to_parent(
                                    other_node, in_edge); // set us as parent
                                add_active_node(
                                    other_node); // activate that node
                                put(m_dist_map, other_node,
                                    get(m_dist_map, current_node)
                                        + 1); // set its distance
                                put(m_time_map, other_node,
                                    get(m_time_map, current_node)); // and time
                            }
                            else if (get_tree(other_node)
                                == tColorTraits::white())
                            {
                                if (is_closer_to_terminal(
                                        current_node, other_node))
                                {
                                    // we are closer to the sink than its parent
                                    // is, so we "adopt" him
                                    set_edge_to_parent(other_node, in_edge);
                                    put(m_dist_map, other_node,
                                        get(m_dist_map, current_node) + 1);
                                    put(m_time_map, other_node,
                                        get(m_time_map, current_node));
                                }
                            }
                            else
                            {
                                BOOST_ASSERT(get_tree(other_node)
                                    == tColorTraits::black());
                                // kewl, found a path from one to the other
                                // search tree,
                                // return the connecting edge in src->sink dir
                                return std::make_pair(in_edge, true);
                            }
                        }
                    } // for all out-edges
                } // sink-tree growing

                // all edges of that node are processed, and no more paths were
                // found.
                // remove if from the front of the active queue
                finish_node(current_node);
            } // while active_nodes not empty

            // no active nodes anymore and no path found, we're done
            return std::make_pair(edge_descriptor(), false);
        }

        /**
         * augments path from s->t and updates residual graph
         * source(e, m_g) is the end of the path found in the source-tree
         * target(e, m_g) is the beginning of the path found in the sink-tree
         * this phase generates orphans on satured edges, if the attached verts
         * are from different search-trees orphans are ordered in distance to
         * sink/source. first the farest from the source are front_inserted into
         * the orphans list, and after that the sink-tree-orphans are
         * front_inserted. when going to adoption stage the orphans are
         * popped_front, and so we process the nearest verts to the terminals
         * first
         */
        void augment(edge_descriptor e)
        {
            BOOST_ASSERT(get_tree(target(e, m_g)) == tColorTraits::white());
            BOOST_ASSERT(get_tree(source(e, m_g)) == tColorTraits::black());
            BOOST_ASSERT(m_orphans.empty());

            const tEdgeVal bottleneck = find_bottleneck(e);
            // now we push the found flow through the path
            // for each edge we saturate we have to look for the verts that
            // belong to that edge, one of them becomes an orphans now process
            // the connecting edge
            put(m_res_cap_map, e, get(m_res_cap_map, e) - bottleneck);
            BOOST_ASSERT(get(m_res_cap_map, e) >= 0);
            put(m_res_cap_map, get(m_rev_edge_map, e),
                get(m_res_cap_map, get(m_rev_edge_map, e)) + bottleneck);

            // now we follow the path back to the source
            vertex_descriptor current_node = source(e, m_g);
            while (current_node != m_source)
            {
                edge_descriptor pred = get_edge_to_parent(current_node);
                put(m_res_cap_map, pred, get(m_res_cap_map, pred) - bottleneck);
                BOOST_ASSERT(get(m_res_cap_map, pred) >= 0);
                put(m_res_cap_map, get(m_rev_edge_map, pred),
                    get(m_res_cap_map, get(m_rev_edge_map, pred)) + bottleneck);
                if (get(m_res_cap_map, pred) == 0)
                {
                    set_no_parent(current_node);
                    m_orphans.push_front(current_node);
                }
                current_node = source(pred, m_g);
            }
            // then go forward in the sink-tree
            current_node = target(e, m_g);
            while (current_node != m_sink)
            {
                edge_descriptor pred = get_edge_to_parent(current_node);
                put(m_res_cap_map, pred, get(m_res_cap_map, pred) - bottleneck);
                BOOST_ASSERT(get(m_res_cap_map, pred) >= 0);
                put(m_res_cap_map, get(m_rev_edge_map, pred),
                    get(m_res_cap_map, get(m_rev_edge_map, pred)) + bottleneck);
                if (get(m_res_cap_map, pred) == 0)
                {
                    set_no_parent(current_node);
                    m_orphans.push_front(current_node);
                }
                current_node = target(pred, m_g);
            }
            // and add it to the max-flow
            m_flow += bottleneck;
        }

        /**
         * returns the bottleneck of a s->t path (end_of_path is last vertex in
         * source-tree, begin_of_path is first vertex in sink-tree)
         */
        inline tEdgeVal find_bottleneck(edge_descriptor e)
        {
            BOOST_USING_STD_MIN();
            tEdgeVal minimum_cap = get(m_res_cap_map, e);
            vertex_descriptor current_node = source(e, m_g);
            // first go back in the source tree
            while (current_node != m_source)
            {
                edge_descriptor pred = get_edge_to_parent(current_node);
                minimum_cap = min BOOST_PREVENT_MACRO_SUBSTITUTION(
                    minimum_cap, get(m_res_cap_map, pred));
                current_node = source(pred, m_g);
            }
            // then go forward in the sink-tree
            current_node = target(e, m_g);
            while (current_node != m_sink)
            {
                edge_descriptor pred = get_edge_to_parent(current_node);
                minimum_cap = min BOOST_PREVENT_MACRO_SUBSTITUTION(
                    minimum_cap, get(m_res_cap_map, pred));
                current_node = target(pred, m_g);
            }
            return minimum_cap;
        }

        /**
         * rebuild search trees
         * empty the queue of orphans, and find new parents for them or just
         * drop them from the search trees
         */
        void adopt()
        {
            while (!m_orphans.empty() || !m_child_orphans.empty())
            {
                vertex_descriptor current_node;
                if (m_child_orphans.empty())
                {
                    // get the next orphan from the main-queue  and remove it
                    current_node = m_orphans.front();
                    m_orphans.pop_front();
                }
                else
                {
                    current_node = m_child_orphans.front();
                    m_child_orphans.pop();
                }
                if (get_tree(current_node) == tColorTraits::black())
                {
                    // we're in the source-tree
                    tDistanceVal min_distance
                        = (std::numeric_limits< tDistanceVal >::max)();
                    edge_descriptor new_parent_edge;
                    out_edge_iterator ei, e_end;
                    for (boost::tie(ei, e_end) = out_edges(current_node, m_g);
                         ei != e_end; ++ei)
                    {
                        const edge_descriptor in_edge
                            = get(m_rev_edge_map, *ei);
                        BOOST_ASSERT(target(in_edge, m_g)
                            == current_node); // we should be the target of this
                                              // edge
                        if (get(m_res_cap_map, in_edge) > 0)
                        {
                            vertex_descriptor other_node = source(in_edge, m_g);
                            if (get_tree(other_node) == tColorTraits::black()
                                && has_source_connect(other_node))
                            {
                                if (get(m_dist_map, other_node) < min_distance)
                                {
                                    min_distance = get(m_dist_map, other_node);
                                    new_parent_edge = in_edge;
                                }
                            }
                        }
                    }
                    if (min_distance
                        != (std::numeric_limits< tDistanceVal >::max)())
                    {
                        set_edge_to_parent(current_node, new_parent_edge);
                        put(m_dist_map, current_node, min_distance + 1);
                        put(m_time_map, current_node, m_time);
                    }
                    else
                    {
                        put(m_time_map, current_node, 0);
                        for (boost::tie(ei, e_end)
                             = out_edges(current_node, m_g);
                             ei != e_end; ++ei)
                        {
                            edge_descriptor in_edge = get(m_rev_edge_map, *ei);
                            vertex_descriptor other_node = source(in_edge, m_g);
                            if (get_tree(other_node) == tColorTraits::black()
                                && other_node != m_source)
                            {
                                if (get(m_res_cap_map, in_edge) > 0)
                                {
                                    add_active_node(other_node);
                                }
                                if (has_parent(other_node)
                                    && source(
                                           get_edge_to_parent(other_node), m_g)
                                        == current_node)
                                {
                                    // we are the parent of that node
                                    // it has to find a new parent, too
                                    set_no_parent(other_node);
                                    m_child_orphans.push(other_node);
                                }
                            }
                        }
                        set_tree(current_node, tColorTraits::gray());
                    } // no parent found
                } // source-tree-adoption
                else
                {
                    // now we should be in the sink-tree, check that...
                    BOOST_ASSERT(
                        get_tree(current_node) == tColorTraits::white());
                    out_edge_iterator ei, e_end;
                    edge_descriptor new_parent_edge;
                    tDistanceVal min_distance
                        = (std::numeric_limits< tDistanceVal >::max)();
                    for (boost::tie(ei, e_end) = out_edges(current_node, m_g);
                         ei != e_end; ++ei)
                    {
                        const edge_descriptor out_edge = *ei;
                        if (get(m_res_cap_map, out_edge) > 0)
                        {
                            const vertex_descriptor other_node
                                = target(out_edge, m_g);
                            if (get_tree(other_node) == tColorTraits::white()
                                && has_sink_connect(other_node))
                                if (get(m_dist_map, other_node) < min_distance)
                                {
                                    min_distance = get(m_dist_map, other_node);
                                    new_parent_edge = out_edge;
                                }
                        }
                    }
                    if (min_distance
                        != (std::numeric_limits< tDistanceVal >::max)())
                    {
                        set_edge_to_parent(current_node, new_parent_edge);
                        put(m_dist_map, current_node, min_distance + 1);
                        put(m_time_map, current_node, m_time);
                    }
                    else
                    {
                        put(m_time_map, current_node, 0);
                        for (boost::tie(ei, e_end)
                             = out_edges(current_node, m_g);
                             ei != e_end; ++ei)
                        {
                            const edge_descriptor out_edge = *ei;
                            const vertex_descriptor other_node
                                = target(out_edge, m_g);
                            if (get_tree(other_node) == tColorTraits::white()
                                && other_node != m_sink)
                            {
                                if (get(m_res_cap_map, out_edge) > 0)
                                {
                                    add_active_node(other_node);
                                }
                                if (has_parent(other_node)
                                    && target(
                                           get_edge_to_parent(other_node), m_g)
                                        == current_node)
                                {
                                    // we were it's parent, so it has to find a
                                    // new one, too
                                    set_no_parent(other_node);
                                    m_child_orphans.push(other_node);
                                }
                            }
                        }
                        set_tree(current_node, tColorTraits::gray());
                    } // no parent found
                } // sink-tree adoption
            } // while !orphans.empty()
        } // adopt

        /**
         * return next active vertex if there is one, otherwise a null_vertex
         */
        inline vertex_descriptor get_next_active_node()
        {
            while (true)
            {
                if (m_active_nodes.empty())
                    return graph_traits< Graph >::null_vertex();
                vertex_descriptor v = m_active_nodes.front();

                // if it has no parent, this node can't be active (if its not
                // source or sink)
                if (!has_parent(v) && v != m_source && v != m_sink)
                {
                    m_active_nodes.pop();
                    put(m_in_active_list_map, v, false);
                }
                else
                {
                    BOOST_ASSERT(get_tree(v) == tColorTraits::black()
                        || get_tree(v) == tColorTraits::white());
                    return v;
                }
            }
        }

        /**
         * adds v as an active vertex, but only if its not in the list already
         */
        inline void add_active_node(vertex_descriptor v)
        {
            BOOST_ASSERT(get_tree(v) != tColorTraits::gray());
            if (get(m_in_active_list_map, v))
            {
                if (m_last_grow_vertex == v)
                {
                    m_last_grow_vertex = graph_traits< Graph >::null_vertex();
                }
                return;
            }
            else
            {
                put(m_in_active_list_map, v, true);
                m_active_nodes.push(v);
            }
        }

        /**
         * finish_node removes a node from the front of the active queue (its
         * called in grow phase, if no more paths can be found using this node)
         */
        inline void finish_node(vertex_descriptor v)
        {
            BOOST_ASSERT(m_active_nodes.front() == v);
            m_active_nodes.pop();
            put(m_in_active_list_map, v, false);
            m_last_grow_vertex = graph_traits< Graph >::null_vertex();
        }

        /**
         * removes a vertex from the queue of active nodes (actually this does
         * nothing, but checks if this node has no parent edge, as this is the
         * criteria for being no more active)
         */
        inline void remove_active_node(vertex_descriptor v)
        {
            BOOST_ASSERT(!has_parent(v));
        }

        /**
         * returns the search tree of v; tColorValue::black() for source tree,
         * white() for sink tree, gray() for no tree
         */
        inline tColorValue get_tree(vertex_descriptor v) const
        {
            return get(m_tree_map, v);
        }

        /**
         * sets search tree of v; tColorValue::black() for source tree, white()
         * for sink tree, gray() for no tree
         */
        inline void set_tree(vertex_descriptor v, tColorValue t)
        {
            put(m_tree_map, v, t);
        }

        /**
         * returns edge to parent vertex of v;
         */
        inline edge_descriptor get_edge_to_parent(vertex_descriptor v) const
        {
            return get(m_pre_map, v);
        }

        /**
         * returns true if the edge stored in m_pre_map[v] is a valid entry
         */
        inline bool has_parent(vertex_descriptor v) const
        {
            return get(m_has_parent_map, v);
        }

        /**
         * sets edge to parent vertex of v;
         */
        inline void set_edge_to_parent(
            vertex_descriptor v, edge_descriptor f_edge_to_parent)
        {
            BOOST_ASSERT(get(m_res_cap_map, f_edge_to_parent) > 0);
            put(m_pre_map, v, f_edge_to_parent);
            put(m_has_parent_map, v, true);
        }

        /**
         * removes the edge to parent of v (this is done by invalidating the
         * entry an additional map)
         */
        inline void set_no_parent(vertex_descriptor v)
        {
            put(m_has_parent_map, v, false);
        }

        /**
         * checks if vertex v has a connect to the sink-vertex (@var m_sink)
         * @param v the vertex which is checked
         * @return true if a path to the sink was found, false if not
         */
        inline bool has_sink_connect(vertex_descriptor v)
        {
            tDistanceVal current_distance = 0;
            vertex_descriptor current_vertex = v;
            while (true)
            {
                if (get(m_time_map, current_vertex) == m_time)
                {
                    // we found a node which was already checked this round. use
                    // it for distance calculations
                    current_distance += get(m_dist_map, current_vertex);
                    break;
                }
                if (current_vertex == m_sink)
                {
                    put(m_time_map, m_sink, m_time);
                    break;
                }
                if (has_parent(current_vertex))
                {
                    // it has a parent, so get it
                    current_vertex
                        = target(get_edge_to_parent(current_vertex), m_g);
                    ++current_distance;
                }
                else
                {
                    // no path found
                    return false;
                }
            }
            current_vertex = v;
            while (get(m_time_map, current_vertex) != m_time)
            {
                put(m_dist_map, current_vertex, current_distance);
                --current_distance;
                put(m_time_map, current_vertex, m_time);
                current_vertex
                    = target(get_edge_to_parent(current_vertex), m_g);
            }
            return true;
        }

        /**
         * checks if vertex v has a connect to the source-vertex (@var m_source)
         * @param v the vertex which is checked
         * @return true if a path to the source was found, false if not
         */
        inline bool has_source_connect(vertex_descriptor v)
        {
            tDistanceVal current_distance = 0;
            vertex_descriptor current_vertex = v;
            while (true)
            {
                if (get(m_time_map, current_vertex) == m_time)
                {
                    // we found a node which was already checked this round. use
                    // it for distance calculations
                    current_distance += get(m_dist_map, current_vertex);
                    break;
                }
                if (current_vertex == m_source)
                {
                    put(m_time_map, m_source, m_time);
                    break;
                }
                if (has_parent(current_vertex))
                {
                    // it has a parent, so get it
                    current_vertex
                        = source(get_edge_to_parent(current_vertex), m_g);
                    ++current_distance;
                }
                else
                {
                    // no path found
                    return false;
                }
            }
            current_vertex = v;
            while (get(m_time_map, current_vertex) != m_time)
            {
                put(m_dist_map, current_vertex, current_distance);
                --current_distance;
                put(m_time_map, current_vertex, m_time);
                current_vertex
                    = source(get_edge_to_parent(current_vertex), m_g);
            }
            return true;
        }

        /**
         * returns true, if p is closer to a terminal than q
         */
        inline bool is_closer_to_terminal(
            vertex_descriptor p, vertex_descriptor q)
        {
            // checks the timestamps first, to build no cycles, and after that
            // the real distance
            return (get(m_time_map, q) <= get(m_time_map, p)
                && get(m_dist_map, q) > get(m_dist_map, p) + 1);
        }

        ////////
        // member vars
        ////////
        Graph& m_g;
        IndexMap m_index_map;
        EdgeCapacityMap m_cap_map;
        ResidualCapacityEdgeMap m_res_cap_map;
        ReverseEdgeMap m_rev_edge_map;
        PredecessorMap m_pre_map; // stores paths found in the growth stage
        ColorMap m_tree_map; // maps each vertex into one of the two search tree
                             // or none (gray())
        DistanceMap m_dist_map; // stores distance to source/sink nodes
        vertex_descriptor m_source;
        vertex_descriptor m_sink;

        tQueue m_active_nodes;
        std::vector< bool > m_in_active_list_vec;
        iterator_property_map< std::vector< bool >::iterator, IndexMap >
            m_in_active_list_map;

        std::list< vertex_descriptor > m_orphans;
        tQueue m_child_orphans; // we use a second queuqe for child orphans, as
                                // they are FIFO processed

        std::vector< bool > m_has_parent_vec;
        iterator_property_map< std::vector< bool >::iterator, IndexMap >
            m_has_parent_map;

        std::vector< long > m_time_vec; // timestamp of each node, used for
                                        // sink/source-path calculations
        iterator_property_map< std::vector< long >::iterator, IndexMap >
            m_time_map;
        tEdgeVal m_flow;
        long m_time;
        vertex_descriptor m_last_grow_vertex;
        out_edge_iterator m_last_grow_edge_it;
        out_edge_iterator m_last_grow_edge_end;
    };

} // namespace boost::detail

/**
 * non-named-parameter version, given everything
 * this is the catch all version
 */
template < class Graph, class CapacityEdgeMap, class ResidualCapacityEdgeMap,
    class ReverseEdgeMap, class PredecessorMap, class ColorMap,
    class DistanceMap, class IndexMap >
typename property_traits< CapacityEdgeMap >::value_type
boykov_kolmogorov_max_flow(Graph& g, CapacityEdgeMap cap,
    ResidualCapacityEdgeMap res_cap, ReverseEdgeMap rev_map,
    PredecessorMap pre_map, ColorMap color, DistanceMap dist, IndexMap idx,
    typename graph_traits< Graph >::vertex_descriptor src,
    typename graph_traits< Graph >::vertex_descriptor sink)
{
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_descriptor;
    typedef typename graph_traits< Graph >::edge_descriptor edge_descriptor;

    // as this method is the last one before we instantiate the solver, we do
    // the concept checks here
    BOOST_CONCEPT_ASSERT(
        (VertexListGraphConcept< Graph >)); // to have vertices(),
                                            // num_vertices(),
    BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< Graph >)); // to have edges()
    BOOST_CONCEPT_ASSERT(
        (IncidenceGraphConcept< Graph >)); // to have source(), target() and
                                           // out_edges()
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< CapacityEdgeMap,
        edge_descriptor >)); // read flow-values from edges
    BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept< ResidualCapacityEdgeMap,
        edge_descriptor >)); // write flow-values to residuals
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< ReverseEdgeMap,
        edge_descriptor >)); // read out reverse edges
    BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept< PredecessorMap,
        vertex_descriptor >)); // store predecessor there
    BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept< ColorMap,
        vertex_descriptor >)); // write corresponding tree
    BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept< DistanceMap,
        vertex_descriptor >)); // write distance to source/sink
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< IndexMap,
        vertex_descriptor >)); // get index 0...|V|-1
    BOOST_ASSERT(num_vertices(g) >= 2 && src != sink);

    detail::bk_max_flow< Graph, CapacityEdgeMap, ResidualCapacityEdgeMap,
        ReverseEdgeMap, PredecessorMap, ColorMap, DistanceMap, IndexMap >
        algo(g, cap, res_cap, rev_map, pre_map, color, dist, idx, src, sink);

    return algo.max_flow();
}

/**
 * non-named-parameter version, given capacity, residucal_capacity,
 * reverse_edges, and an index map.
 */
template < class Graph, class CapacityEdgeMap, class ResidualCapacityEdgeMap,
    class ReverseEdgeMap, class IndexMap >
typename property_traits< CapacityEdgeMap >::value_type
boykov_kolmogorov_max_flow(Graph& g, CapacityEdgeMap cap,
    ResidualCapacityEdgeMap res_cap, ReverseEdgeMap rev, IndexMap idx,
    typename graph_traits< Graph >::vertex_descriptor src,
    typename graph_traits< Graph >::vertex_descriptor sink)
{
    typename graph_traits< Graph >::vertices_size_type n_verts
        = num_vertices(g);
    std::vector< typename graph_traits< Graph >::edge_descriptor >
        predecessor_vec(n_verts);
    std::vector< default_color_type > color_vec(n_verts);
    std::vector< typename graph_traits< Graph >::vertices_size_type >
        distance_vec(n_verts);
    return boykov_kolmogorov_max_flow(g, cap, res_cap, rev,
        make_iterator_property_map(predecessor_vec.begin(), idx),
        make_iterator_property_map(color_vec.begin(), idx),
        make_iterator_property_map(distance_vec.begin(), idx), idx, src, sink);
}

/**
 * non-named-parameter version, some given: capacity, residual_capacity,
 * reverse_edges, color_map and an index map. Use this if you are interested in
 * the minimum cut, as the color map provides that info.
 */
template < class Graph, class CapacityEdgeMap, class ResidualCapacityEdgeMap,
    class ReverseEdgeMap, class ColorMap, class IndexMap >
typename property_traits< CapacityEdgeMap >::value_type
boykov_kolmogorov_max_flow(Graph& g, CapacityEdgeMap cap,
    ResidualCapacityEdgeMap res_cap, ReverseEdgeMap rev, ColorMap color,
    IndexMap idx, typename graph_traits< Graph >::vertex_descriptor src,
    typename graph_traits< Graph >::vertex_descriptor sink)
{
    typename graph_traits< Graph >::vertices_size_type n_verts
        = num_vertices(g);
    std::vector< typename graph_traits< Graph >::edge_descriptor >
        predecessor_vec(n_verts);
    std::vector< typename graph_traits< Graph >::vertices_size_type >
        distance_vec(n_verts);
    return boykov_kolmogorov_max_flow(g, cap, res_cap, rev,
        make_iterator_property_map(predecessor_vec.begin(), idx), color,
        make_iterator_property_map(distance_vec.begin(), idx), idx, src, sink);
}

/**
 * named-parameter version, some given
 */
template < class Graph, class P, class T, class R >
typename property_traits<
    typename property_map< Graph, edge_capacity_t >::const_type >::value_type
boykov_kolmogorov_max_flow(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor src,
    typename graph_traits< Graph >::vertex_descriptor sink,
    const bgl_named_params< P, T, R >& params)
{
    return boykov_kolmogorov_max_flow(g,
        choose_const_pmap(get_param(params, edge_capacity), g, edge_capacity),
        choose_pmap(get_param(params, edge_residual_capacity), g,
            edge_residual_capacity),
        choose_const_pmap(get_param(params, edge_reverse), g, edge_reverse),
        choose_pmap(
            get_param(params, vertex_predecessor), g, vertex_predecessor),
        choose_pmap(get_param(params, vertex_color), g, vertex_color),
        choose_pmap(get_param(params, vertex_distance), g, vertex_distance),
        choose_const_pmap(get_param(params, vertex_index), g, vertex_index),
        src, sink);
}

/**
 * named-parameter version, none given
 */
template < class Graph >
typename property_traits<
    typename property_map< Graph, edge_capacity_t >::const_type >::value_type
boykov_kolmogorov_max_flow(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor src,
    typename graph_traits< Graph >::vertex_descriptor sink)
{
    bgl_named_params< int, buffer_param_t > params(0); // bogus empty param
    return boykov_kolmogorov_max_flow(g, src, sink, params);
}

} // namespace boost

#endif // BOOST_BOYKOV_KOLMOGOROV_MAX_FLOW_HPP

/* boykov_kolmogorov_max_flow.hpp
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
*/