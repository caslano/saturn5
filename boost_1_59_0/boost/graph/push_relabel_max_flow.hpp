//=======================================================================
// Copyright 2000 University of Notre Dame.
// Authors: Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_PUSH_RELABEL_MAX_FLOW_HPP
#define BOOST_PUSH_RELABEL_MAX_FLOW_HPP

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <vector>
#include <list>
#include <iosfwd>
#include <algorithm> // for std::min and std::max

#include <boost/pending/queue.hpp>
#include <boost/limits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/named_function_params.hpp>

namespace boost
{

namespace detail
{

    // This implementation is based on Goldberg's
    // "On Implementing Push-Relabel Method for the Maximum Flow Problem"
    // by B.V. Cherkassky and A.V. Goldberg, IPCO '95, pp. 157--171
    // and on the h_prf.c and hi_pr.c code written by the above authors.

    // This implements the highest-label version of the push-relabel method
    // with the global relabeling and gap relabeling heuristics.

    // The terms "rank", "distance", "height" are synonyms in
    // Goldberg's implementation, paper and in the CLR.  A "layer" is a
    // group of vertices with the same distance. The vertices in each
    // layer are categorized as active or inactive.  An active vertex
    // has positive excess flow and its distance is less than n (it is
    // not blocked).

    template < class Vertex > struct preflow_layer
    {
        std::list< Vertex > active_vertices;
        std::list< Vertex > inactive_vertices;
    };

    template < class Graph,
        class EdgeCapacityMap, // integer value type
        class ResidualCapacityEdgeMap, class ReverseEdgeMap,
        class VertexIndexMap, // vertex_descriptor -> integer
        class FlowValue >
    class push_relabel
    {
    public:
        typedef graph_traits< Graph > Traits;
        typedef typename Traits::vertex_descriptor vertex_descriptor;
        typedef typename Traits::edge_descriptor edge_descriptor;
        typedef typename Traits::vertex_iterator vertex_iterator;
        typedef typename Traits::out_edge_iterator out_edge_iterator;
        typedef typename Traits::vertices_size_type vertices_size_type;
        typedef typename Traits::edges_size_type edges_size_type;

        typedef preflow_layer< vertex_descriptor > Layer;
        typedef std::vector< Layer > LayerArray;
        typedef typename LayerArray::iterator layer_iterator;
        typedef typename LayerArray::size_type distance_size_type;

        typedef color_traits< default_color_type > ColorTraits;

        //=======================================================================
        // Some helper predicates

        inline bool is_admissible(vertex_descriptor u, vertex_descriptor v)
        {
            return get(distance, u) == get(distance, v) + 1;
        }
        inline bool is_residual_edge(edge_descriptor a)
        {
            return 0 < get(residual_capacity, a);
        }
        inline bool is_saturated(edge_descriptor a)
        {
            return get(residual_capacity, a) == 0;
        }

        //=======================================================================
        // Layer List Management Functions

        typedef typename std::list< vertex_descriptor >::iterator list_iterator;

        void add_to_active_list(vertex_descriptor u, Layer& layer)
        {
            BOOST_USING_STD_MIN();
            BOOST_USING_STD_MAX();
            layer.active_vertices.push_front(u);
            max_active = max BOOST_PREVENT_MACRO_SUBSTITUTION(
                get(distance, u), max_active);
            min_active = min BOOST_PREVENT_MACRO_SUBSTITUTION(
                get(distance, u), min_active);
            layer_list_ptr[u] = layer.active_vertices.begin();
        }
        void remove_from_active_list(vertex_descriptor u)
        {
            layers[get(distance, u)].active_vertices.erase(layer_list_ptr[u]);
        }

        void add_to_inactive_list(vertex_descriptor u, Layer& layer)
        {
            layer.inactive_vertices.push_front(u);
            layer_list_ptr[u] = layer.inactive_vertices.begin();
        }
        void remove_from_inactive_list(vertex_descriptor u)
        {
            layers[get(distance, u)].inactive_vertices.erase(layer_list_ptr[u]);
        }

        //=======================================================================
        // initialization
        push_relabel(Graph& g_, EdgeCapacityMap cap,
            ResidualCapacityEdgeMap res, ReverseEdgeMap rev,
            vertex_descriptor src_, vertex_descriptor sink_, VertexIndexMap idx)
        : g(g_)
        , n(num_vertices(g_))
        , capacity(cap)
        , src(src_)
        , sink(sink_)
        , index(idx)
        , excess_flow_data(num_vertices(g_))
        , excess_flow(excess_flow_data.begin(), idx)
        , current_data(num_vertices(g_), out_edges(*vertices(g_).first, g_))
        , current(current_data.begin(), idx)
        , distance_data(num_vertices(g_))
        , distance(distance_data.begin(), idx)
        , color_data(num_vertices(g_))
        , color(color_data.begin(), idx)
        , reverse_edge(rev)
        , residual_capacity(res)
        , layers(num_vertices(g_))
        , layer_list_ptr_data(
              num_vertices(g_), layers.front().inactive_vertices.end())
        , layer_list_ptr(layer_list_ptr_data.begin(), idx)
        , push_count(0)
        , update_count(0)
        , relabel_count(0)
        , gap_count(0)
        , gap_node_count(0)
        , work_since_last_update(0)
        {
            vertex_iterator u_iter, u_end;
            // Don't count the reverse edges
            edges_size_type m = num_edges(g) / 2;
            nm = alpha() * n + m;

            // Initialize flow to zero which means initializing
            // the residual capacity to equal the capacity.
            out_edge_iterator ei, e_end;
            for (boost::tie(u_iter, u_end) = vertices(g); u_iter != u_end;
                 ++u_iter)
                for (boost::tie(ei, e_end) = out_edges(*u_iter, g); ei != e_end;
                     ++ei)
                {
                    put(residual_capacity, *ei, get(capacity, *ei));
                }

            for (boost::tie(u_iter, u_end) = vertices(g); u_iter != u_end;
                 ++u_iter)
            {
                vertex_descriptor u = *u_iter;
                put(excess_flow, u, 0);
                current[u] = out_edges(u, g);
            }

            bool overflow_detected = false;
            FlowValue test_excess = 0;

            out_edge_iterator a_iter, a_end;
            for (boost::tie(a_iter, a_end) = out_edges(src, g); a_iter != a_end;
                 ++a_iter)
                if (target(*a_iter, g) != src)
                    test_excess += get(residual_capacity, *a_iter);
            if (test_excess > (std::numeric_limits< FlowValue >::max)())
                overflow_detected = true;

            if (overflow_detected)
                put(excess_flow, src,
                    (std::numeric_limits< FlowValue >::max)());
            else
            {
                put(excess_flow, src, 0);
                for (boost::tie(a_iter, a_end) = out_edges(src, g);
                     a_iter != a_end; ++a_iter)
                {
                    edge_descriptor a = *a_iter;
                    vertex_descriptor tgt = target(a, g);
                    if (tgt != src)
                    {
                        ++push_count;
                        FlowValue delta = get(residual_capacity, a);
                        put(residual_capacity, a,
                            get(residual_capacity, a) - delta);
                        edge_descriptor rev = get(reverse_edge, a);
                        put(residual_capacity, rev,
                            get(residual_capacity, rev) + delta);
                        put(excess_flow, tgt, get(excess_flow, tgt) + delta);
                    }
                }
            }
            max_distance = num_vertices(g) - 1;
            max_active = 0;
            min_active = n;

            for (boost::tie(u_iter, u_end) = vertices(g); u_iter != u_end;
                 ++u_iter)
            {
                vertex_descriptor u = *u_iter;
                if (u == sink)
                {
                    put(distance, u, 0);
                    continue;
                }
                else if (u == src && !overflow_detected)
                    put(distance, u, n);
                else
                    put(distance, u, 1);

                if (get(excess_flow, u) > 0)
                    add_to_active_list(u, layers[1]);
                else if (get(distance, u) < n)
                    add_to_inactive_list(u, layers[1]);
            }

        } // push_relabel constructor

        //=======================================================================
        // This is a breadth-first search over the residual graph
        // (well, actually the reverse of the residual graph).
        // Would be cool to have a graph view adaptor for hiding certain
        // edges, like the saturated (non-residual) edges in this case.
        // Goldberg's implementation abused "distance" for the coloring.
        void global_distance_update()
        {
            BOOST_USING_STD_MAX();
            ++update_count;
            vertex_iterator u_iter, u_end;
            for (boost::tie(u_iter, u_end) = vertices(g); u_iter != u_end;
                 ++u_iter)
            {
                put(color, *u_iter, ColorTraits::white());
                put(distance, *u_iter, n);
            }
            put(color, sink, ColorTraits::gray());
            put(distance, sink, 0);

            for (distance_size_type l = 0; l <= max_distance; ++l)
            {
                layers[l].active_vertices.clear();
                layers[l].inactive_vertices.clear();
            }

            max_distance = max_active = 0;
            min_active = n;

            Q.push(sink);
            while (!Q.empty())
            {
                vertex_descriptor u = Q.top();
                Q.pop();
                distance_size_type d_v = get(distance, u) + 1;

                out_edge_iterator ai, a_end;
                for (boost::tie(ai, a_end) = out_edges(u, g); ai != a_end; ++ai)
                {
                    edge_descriptor a = *ai;
                    vertex_descriptor v = target(a, g);
                    if (get(color, v) == ColorTraits::white()
                        && is_residual_edge(get(reverse_edge, a)))
                    {
                        put(distance, v, d_v);
                        put(color, v, ColorTraits::gray());
                        current[v] = out_edges(v, g);
                        max_distance = max BOOST_PREVENT_MACRO_SUBSTITUTION(
                            d_v, max_distance);

                        if (get(excess_flow, v) > 0)
                            add_to_active_list(v, layers[d_v]);
                        else
                            add_to_inactive_list(v, layers[d_v]);

                        Q.push(v);
                    }
                }
            }
        } // global_distance_update()

        //=======================================================================
        // This function is called "push" in Goldberg's h_prf implementation,
        // but it is called "discharge" in the paper and in hi_pr.c.
        void discharge(vertex_descriptor u)
        {
            BOOST_ASSERT(get(excess_flow, u) > 0);
            while (1)
            {
                out_edge_iterator ai, ai_end;
                for (boost::tie(ai, ai_end) = current[u]; ai != ai_end; ++ai)
                {
                    edge_descriptor a = *ai;
                    if (is_residual_edge(a))
                    {
                        vertex_descriptor v = target(a, g);
                        if (is_admissible(u, v))
                        {
                            ++push_count;
                            if (v != sink && get(excess_flow, v) == 0)
                            {
                                remove_from_inactive_list(v);
                                add_to_active_list(v, layers[get(distance, v)]);
                            }
                            push_flow(a);
                            if (get(excess_flow, u) == 0)
                                break;
                        }
                    }
                } // for out_edges of i starting from current

                Layer& layer = layers[get(distance, u)];
                distance_size_type du = get(distance, u);

                if (ai == ai_end)
                { // i must be relabeled
                    relabel_distance(u);
                    if (layer.active_vertices.empty()
                        && layer.inactive_vertices.empty())
                        gap(du);
                    if (get(distance, u) == n)
                        break;
                }
                else
                { // i is no longer active
                    current[u].first = ai;
                    add_to_inactive_list(u, layer);
                    break;
                }
            } // while (1)
        } // discharge()

        //=======================================================================
        // This corresponds to the "push" update operation of the paper,
        // not the "push" function in Goldberg's h_prf.c implementation.
        // The idea is to push the excess flow from from vertex u to v.
        void push_flow(edge_descriptor u_v)
        {
            vertex_descriptor u = source(u_v, g), v = target(u_v, g);

            BOOST_USING_STD_MIN();
            FlowValue flow_delta = min BOOST_PREVENT_MACRO_SUBSTITUTION(
                get(excess_flow, u), get(residual_capacity, u_v));

            put(residual_capacity, u_v,
                get(residual_capacity, u_v) - flow_delta);
            edge_descriptor rev = get(reverse_edge, u_v);
            put(residual_capacity, rev,
                get(residual_capacity, rev) + flow_delta);

            put(excess_flow, u, get(excess_flow, u) - flow_delta);
            put(excess_flow, v, get(excess_flow, v) + flow_delta);
        } // push_flow()

        //=======================================================================
        // The main purpose of this routine is to set distance[v]
        // to the smallest value allowed by the valid labeling constraints,
        // which are:
        // distance[t] = 0
        // distance[u] <= distance[v] + 1   for every residual edge (u,v)
        //
        distance_size_type relabel_distance(vertex_descriptor u)
        {
            BOOST_USING_STD_MAX();
            ++relabel_count;
            work_since_last_update += beta();

            distance_size_type min_distance = num_vertices(g);
            put(distance, u, min_distance);

            // Examine the residual out-edges of vertex i, choosing the
            // edge whose target vertex has the minimal distance.
            out_edge_iterator ai, a_end, min_edge_iter;
            for (boost::tie(ai, a_end) = out_edges(u, g); ai != a_end; ++ai)
            {
                ++work_since_last_update;
                edge_descriptor a = *ai;
                vertex_descriptor v = target(a, g);
                if (is_residual_edge(a) && get(distance, v) < min_distance)
                {
                    min_distance = get(distance, v);
                    min_edge_iter = ai;
                }
            }
            ++min_distance;
            if (min_distance < n)
            {
                put(distance, u, min_distance); // this is the main action
                current[u].first = min_edge_iter;
                max_distance = max BOOST_PREVENT_MACRO_SUBSTITUTION(
                    min_distance, max_distance);
            }
            return min_distance;
        } // relabel_distance()

        //=======================================================================
        // cleanup beyond the gap
        void gap(distance_size_type empty_distance)
        {
            ++gap_count;

            distance_size_type r; // distance of layer before the current layer
            r = empty_distance - 1;

            // Set the distance for the vertices beyond the gap to "infinity".
            for (layer_iterator l = layers.begin() + empty_distance + 1;
                 l < layers.begin() + max_distance; ++l)
            {
                list_iterator i;
                for (i = l->inactive_vertices.begin();
                     i != l->inactive_vertices.end(); ++i)
                {
                    put(distance, *i, n);
                    ++gap_node_count;
                }
                l->inactive_vertices.clear();
            }
            max_distance = r;
            max_active = r;
        }

        //=======================================================================
        // This is the core part of the algorithm, "phase one".
        FlowValue maximum_preflow()
        {
            work_since_last_update = 0;

            while (max_active >= min_active)
            { // "main" loop

                Layer& layer = layers[max_active];
                list_iterator u_iter = layer.active_vertices.begin();

                if (u_iter == layer.active_vertices.end())
                    --max_active;
                else
                {
                    vertex_descriptor u = *u_iter;
                    remove_from_active_list(u);

                    discharge(u);

                    if (work_since_last_update * global_update_frequency() > nm)
                    {
                        global_distance_update();
                        work_since_last_update = 0;
                    }
                }
            } // while (max_active >= min_active)

            return get(excess_flow, sink);
        } // maximum_preflow()

        //=======================================================================
        // remove excess flow, the "second phase"
        // This does a DFS on the reverse flow graph of nodes with excess flow.
        // If a cycle is found, cancel it.
        // Return the nodes with excess flow in topological order.
        //
        // Unlike the prefl_to_flow() implementation, we use
        //   "color" instead of "distance" for the DFS labels
        //   "parent" instead of nl_prev for the DFS tree
        //   "topo_next" instead of nl_next for the topological ordering
        void convert_preflow_to_flow()
        {
            vertex_iterator u_iter, u_end;
            out_edge_iterator ai, a_end;

            vertex_descriptor r, restart, u;

            std::vector< vertex_descriptor > parent(n);
            std::vector< vertex_descriptor > topo_next(n);

            vertex_descriptor tos(parent[0]),
                bos(parent[0]); // bogus initialization, just to avoid warning
            bool bos_null = true;

            // handle self-loops
            for (boost::tie(u_iter, u_end) = vertices(g); u_iter != u_end;
                 ++u_iter)
                for (boost::tie(ai, a_end) = out_edges(*u_iter, g); ai != a_end;
                     ++ai)
                    if (target(*ai, g) == *u_iter)
                        put(residual_capacity, *ai, get(capacity, *ai));

            // initialize
            for (boost::tie(u_iter, u_end) = vertices(g); u_iter != u_end;
                 ++u_iter)
            {
                u = *u_iter;
                put(color, u, ColorTraits::white());
                parent[get(index, u)] = u;
                current[u] = out_edges(u, g);
            }
            // eliminate flow cycles and topologically order the vertices
            for (boost::tie(u_iter, u_end) = vertices(g); u_iter != u_end;
                 ++u_iter)
            {
                u = *u_iter;
                if (get(color, u) == ColorTraits::white()
                    && get(excess_flow, u) > 0 && u != src && u != sink)
                {
                    r = u;
                    put(color, r, ColorTraits::gray());
                    while (1)
                    {
                        for (; current[u].first != current[u].second;
                             ++current[u].first)
                        {
                            edge_descriptor a = *current[u].first;
                            if (get(capacity, a) == 0 && is_residual_edge(a))
                            {
                                vertex_descriptor v = target(a, g);
                                if (get(color, v) == ColorTraits::white())
                                {
                                    put(color, v, ColorTraits::gray());
                                    parent[get(index, v)] = u;
                                    u = v;
                                    break;
                                }
                                else if (get(color, v) == ColorTraits::gray())
                                {
                                    // find minimum flow on the cycle
                                    FlowValue delta = get(residual_capacity, a);
                                    while (1)
                                    {
                                        BOOST_USING_STD_MIN();
                                        delta = min
                                            BOOST_PREVENT_MACRO_SUBSTITUTION(
                                                delta,
                                                get(residual_capacity,
                                                    *current[v].first));
                                        if (v == u)
                                            break;
                                        else
                                            v = target(*current[v].first, g);
                                    }
                                    // remove delta flow units
                                    v = u;
                                    while (1)
                                    {
                                        a = *current[v].first;
                                        put(residual_capacity, a,
                                            get(residual_capacity, a) - delta);
                                        edge_descriptor rev
                                            = get(reverse_edge, a);
                                        put(residual_capacity, rev,
                                            get(residual_capacity, rev)
                                                + delta);
                                        v = target(a, g);
                                        if (v == u)
                                            break;
                                    }

                                    // back-out of DFS to the first saturated
                                    // edge
                                    restart = u;
                                    for (v = target(*current[u].first, g);
                                         v != u; v = target(a, g))
                                    {
                                        a = *current[v].first;
                                        if (get(color, v)
                                                == ColorTraits::white()
                                            || is_saturated(a))
                                        {
                                            put(color,
                                                target(*current[v].first, g),
                                                ColorTraits::white());
                                            if (get(color, v)
                                                != ColorTraits::white())
                                                restart = v;
                                        }
                                    }
                                    if (restart != u)
                                    {
                                        u = restart;
                                        ++current[u].first;
                                        break;
                                    }
                                } // else if (color[v] == ColorTraits::gray())
                            } // if (get(capacity, a) == 0 ...
                        } // for out_edges(u, g)  (though "u" changes during
                          // loop)

                        if (current[u].first == current[u].second)
                        {
                            // scan of i is complete
                            put(color, u, ColorTraits::black());
                            if (u != src)
                            {
                                if (bos_null)
                                {
                                    bos = u;
                                    bos_null = false;
                                    tos = u;
                                }
                                else
                                {
                                    topo_next[get(index, u)] = tos;
                                    tos = u;
                                }
                            }
                            if (u != r)
                            {
                                u = parent[get(index, u)];
                                ++current[u].first;
                            }
                            else
                                break;
                        }
                    } // while (1)
                } // if (color[u] == white && excess_flow[u] > 0 & ...)
            } // for all vertices in g

            // return excess flows
            // note that the sink is not on the stack
            if (!bos_null)
            {
                for (u = tos; u != bos; u = topo_next[get(index, u)])
                {
                    boost::tie(ai, a_end) = out_edges(u, g);
                    while (get(excess_flow, u) > 0 && ai != a_end)
                    {
                        if (get(capacity, *ai) == 0 && is_residual_edge(*ai))
                            push_flow(*ai);
                        ++ai;
                    }
                }
                // do the bottom
                u = bos;
                boost::tie(ai, a_end) = out_edges(u, g);
                while (get(excess_flow, u) > 0 && ai != a_end)
                {
                    if (get(capacity, *ai) == 0 && is_residual_edge(*ai))
                        push_flow(*ai);
                    ++ai;
                }
            }

        } // convert_preflow_to_flow()

        //=======================================================================
        inline bool is_flow()
        {
            vertex_iterator u_iter, u_end;
            out_edge_iterator ai, a_end;

            // check edge flow values
            for (boost::tie(u_iter, u_end) = vertices(g); u_iter != u_end;
                 ++u_iter)
            {
                for (boost::tie(ai, a_end) = out_edges(*u_iter, g); ai != a_end;
                     ++ai)
                {
                    edge_descriptor a = *ai;
                    if (get(capacity, a) > 0)
                        if ((get(residual_capacity, a)
                                    + get(
                                        residual_capacity, get(reverse_edge, a))
                                != get(capacity, a)
                                    + get(capacity, get(reverse_edge, a)))
                            || (get(residual_capacity, a) < 0)
                            || (get(residual_capacity, get(reverse_edge, a))
                                < 0))
                            return false;
                }
            }

            // check conservation
            FlowValue sum;
            for (boost::tie(u_iter, u_end) = vertices(g); u_iter != u_end;
                 ++u_iter)
            {
                vertex_descriptor u = *u_iter;
                if (u != src && u != sink)
                {
                    if (get(excess_flow, u) != 0)
                        return false;
                    sum = 0;
                    for (boost::tie(ai, a_end) = out_edges(u, g); ai != a_end;
                         ++ai)
                        if (get(capacity, *ai) > 0)
                            sum -= get(capacity, *ai)
                                - get(residual_capacity, *ai);
                        else
                            sum += get(residual_capacity, *ai);

                    if (get(excess_flow, u) != sum)
                        return false;
                }
            }

            return true;
        } // is_flow()

        bool is_optimal()
        {
            // check if mincut is saturated...
            global_distance_update();
            return get(distance, src) >= n;
        }

        void print_statistics(std::ostream& os) const
        {
            os << "pushes:     " << push_count << std::endl
               << "relabels:   " << relabel_count << std::endl
               << "updates:    " << update_count << std::endl
               << "gaps:       " << gap_count << std::endl
               << "gap nodes:  " << gap_node_count << std::endl
               << std::endl;
        }

        void print_flow_values(std::ostream& os) const
        {
            os << "flow values" << std::endl;
            vertex_iterator u_iter, u_end;
            out_edge_iterator ei, e_end;
            for (boost::tie(u_iter, u_end) = vertices(g); u_iter != u_end;
                 ++u_iter)
                for (boost::tie(ei, e_end) = out_edges(*u_iter, g); ei != e_end;
                     ++ei)
                    if (get(capacity, *ei) > 0)
                        os << *u_iter << " " << target(*ei, g) << " "
                           << (get(capacity, *ei) - get(residual_capacity, *ei))
                           << std::endl;
            os << std::endl;
        }

        //=======================================================================

        Graph& g;
        vertices_size_type n;
        vertices_size_type nm;
        EdgeCapacityMap capacity;
        vertex_descriptor src;
        vertex_descriptor sink;
        VertexIndexMap index;

        // will need to use random_access_property_map with these
        std::vector< FlowValue > excess_flow_data;
        iterator_property_map< typename std::vector< FlowValue >::iterator,
            VertexIndexMap >
            excess_flow;
        std::vector< std::pair< out_edge_iterator, out_edge_iterator > >
            current_data;
        iterator_property_map<
            typename std::vector<
                std::pair< out_edge_iterator, out_edge_iterator > >::iterator,
            VertexIndexMap >
            current;
        std::vector< distance_size_type > distance_data;
        iterator_property_map<
            typename std::vector< distance_size_type >::iterator,
            VertexIndexMap >
            distance;
        std::vector< default_color_type > color_data;
        iterator_property_map< std::vector< default_color_type >::iterator,
            VertexIndexMap >
            color;

        // Edge Property Maps that must be interior to the graph
        ReverseEdgeMap reverse_edge;
        ResidualCapacityEdgeMap residual_capacity;

        LayerArray layers;
        std::vector< list_iterator > layer_list_ptr_data;
        iterator_property_map< typename std::vector< list_iterator >::iterator,
            VertexIndexMap >
            layer_list_ptr;
        distance_size_type max_distance; // maximal distance
        distance_size_type max_active; // maximal distance with active node
        distance_size_type min_active; // minimal distance with active node
        boost::queue< vertex_descriptor > Q;

        // Statistics counters
        long push_count;
        long update_count;
        long relabel_count;
        long gap_count;
        long gap_node_count;

        inline double global_update_frequency() { return 0.5; }
        inline vertices_size_type alpha() { return 6; }
        inline long beta() { return 12; }

        long work_since_last_update;
    };

} // namespace detail

template < class Graph, class CapacityEdgeMap, class ResidualCapacityEdgeMap,
    class ReverseEdgeMap, class VertexIndexMap >
typename property_traits< CapacityEdgeMap >::value_type push_relabel_max_flow(
    Graph& g, typename graph_traits< Graph >::vertex_descriptor src,
    typename graph_traits< Graph >::vertex_descriptor sink, CapacityEdgeMap cap,
    ResidualCapacityEdgeMap res, ReverseEdgeMap rev, VertexIndexMap index_map)
{
    typedef typename property_traits< CapacityEdgeMap >::value_type FlowValue;

    detail::push_relabel< Graph, CapacityEdgeMap, ResidualCapacityEdgeMap,
        ReverseEdgeMap, VertexIndexMap, FlowValue >
        algo(g, cap, res, rev, src, sink, index_map);

    FlowValue flow = algo.maximum_preflow();

    algo.convert_preflow_to_flow();

    BOOST_ASSERT(algo.is_flow());
    BOOST_ASSERT(algo.is_optimal());

    return flow;
} // push_relabel_max_flow()

template < class Graph, class P, class T, class R >
typename detail::edge_capacity_value< Graph, P, T, R >::type
push_relabel_max_flow(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor src,
    typename graph_traits< Graph >::vertex_descriptor sink,
    const bgl_named_params< P, T, R >& params)
{
    return push_relabel_max_flow(g, src, sink,
        choose_const_pmap(get_param(params, edge_capacity), g, edge_capacity),
        choose_pmap(get_param(params, edge_residual_capacity), g,
            edge_residual_capacity),
        choose_const_pmap(get_param(params, edge_reverse), g, edge_reverse),
        choose_const_pmap(get_param(params, vertex_index), g, vertex_index));
}

template < class Graph >
typename property_traits<
    typename property_map< Graph, edge_capacity_t >::const_type >::value_type
push_relabel_max_flow(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor src,
    typename graph_traits< Graph >::vertex_descriptor sink)
{
    bgl_named_params< int, buffer_param_t > params(0); // bogus empty param
    return push_relabel_max_flow(g, src, sink, params);
}

} // namespace boost

#endif // BOOST_PUSH_RELABEL_MAX_FLOW_HPP

/* push_relabel_max_flow.hpp
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
*/