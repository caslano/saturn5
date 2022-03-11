// r_c_shortest_paths.hpp header file

// Copyright Michael Drexl 2005, 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_R_C_SHORTEST_PATHS_HPP
#define BOOST_GRAPH_R_C_SHORTEST_PATHS_HPP

#include <map>
#include <queue>
#include <vector>
#include <list>

#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost
{

// r_c_shortest_paths_label struct
template < class Graph, class Resource_Container >
struct r_c_shortest_paths_label
: public boost::enable_shared_from_this<
      r_c_shortest_paths_label< Graph, Resource_Container > >
{
    r_c_shortest_paths_label(const unsigned long n,
        const Resource_Container& rc = Resource_Container(),
        const boost::shared_ptr<
            r_c_shortest_paths_label< Graph, Resource_Container > >
            pl
        = boost::shared_ptr<
            r_c_shortest_paths_label< Graph, Resource_Container > >(),
        const typename graph_traits< Graph >::edge_descriptor& ed
        = graph_traits< Graph >::edge_descriptor(),
        const typename graph_traits< Graph >::vertex_descriptor& vd
        = graph_traits< Graph >::vertex_descriptor())
    : num(n)
    , cumulated_resource_consumption(rc)
    , p_pred_label(pl)
    , pred_edge(ed)
    , resident_vertex(vd)
    , b_is_dominated(false)
    , b_is_processed(false)
    {
    }

    r_c_shortest_paths_label& operator=(const r_c_shortest_paths_label& other)
    {
        if (this == &other)
            return *this;
        this->~r_c_shortest_paths_label();
        new (this) r_c_shortest_paths_label(other);
        return *this;
    }
    const unsigned long num;
    Resource_Container cumulated_resource_consumption;
    const boost::shared_ptr<
        r_c_shortest_paths_label< Graph, Resource_Container > >
        p_pred_label;
    const typename graph_traits< Graph >::edge_descriptor pred_edge;
    const typename graph_traits< Graph >::vertex_descriptor resident_vertex;
    bool b_is_dominated;
    bool b_is_processed;
}; // r_c_shortest_paths_label

template < class Graph, class Resource_Container >
inline bool operator==(
    const r_c_shortest_paths_label< Graph, Resource_Container >& l1,
    const r_c_shortest_paths_label< Graph, Resource_Container >& l2)
{
    return l1.cumulated_resource_consumption
        == l2.cumulated_resource_consumption;
}

template < class Graph, class Resource_Container >
inline bool operator!=(
    const r_c_shortest_paths_label< Graph, Resource_Container >& l1,
    const r_c_shortest_paths_label< Graph, Resource_Container >& l2)
{
    return !(l1 == l2);
}

template < class Graph, class Resource_Container >
inline bool operator<(
    const r_c_shortest_paths_label< Graph, Resource_Container >& l1,
    const r_c_shortest_paths_label< Graph, Resource_Container >& l2)
{
    return l1.cumulated_resource_consumption
        < l2.cumulated_resource_consumption;
}

template < class Graph, class Resource_Container >
inline bool operator>(
    const r_c_shortest_paths_label< Graph, Resource_Container >& l1,
    const r_c_shortest_paths_label< Graph, Resource_Container >& l2)
{
    return l2.cumulated_resource_consumption
        < l1.cumulated_resource_consumption;
}

template < class Graph, class Resource_Container >
inline bool operator<=(
    const r_c_shortest_paths_label< Graph, Resource_Container >& l1,
    const r_c_shortest_paths_label< Graph, Resource_Container >& l2)
{
    return l1 < l2 || l1 == l2;
}

template < class Graph, class Resource_Container >
inline bool operator>=(
    const r_c_shortest_paths_label< Graph, Resource_Container >& l1,
    const r_c_shortest_paths_label< Graph, Resource_Container >& l2)
{
    return l2 < l1 || l1 == l2;
}

template < typename Graph, typename Resource_Container >
inline bool operator<(
    const boost::shared_ptr<
        r_c_shortest_paths_label< Graph, Resource_Container > >& t,
    const boost::shared_ptr<
        r_c_shortest_paths_label< Graph, Resource_Container > >& u)
{
    return *t < *u;
}

template < typename Graph, typename Resource_Container >
inline bool operator<=(
    const boost::shared_ptr<
        r_c_shortest_paths_label< Graph, Resource_Container > >& t,
    const boost::shared_ptr<
        r_c_shortest_paths_label< Graph, Resource_Container > >& u)
{
    return *t <= *u;
}

template < typename Graph, typename Resource_Container >
inline bool operator>(
    const boost::shared_ptr<
        r_c_shortest_paths_label< Graph, Resource_Container > >& t,
    const boost::shared_ptr<
        r_c_shortest_paths_label< Graph, Resource_Container > >& u)
{
    return *t > *u;
}

template < typename Graph, typename Resource_Container >
inline bool operator>=(
    const boost::shared_ptr<
        r_c_shortest_paths_label< Graph, Resource_Container > >& t,
    const boost::shared_ptr<
        r_c_shortest_paths_label< Graph, Resource_Container > >& u)
{
    return *t >= *u;
}

namespace detail
{

    // r_c_shortest_paths_dispatch function (body/implementation)
    template < class Graph, class VertexIndexMap, class EdgeIndexMap,
        class Resource_Container, class Resource_Extension_Function,
        class Dominance_Function, class Label_Allocator, class Visitor >
    void r_c_shortest_paths_dispatch(const Graph& g,
        const VertexIndexMap& vertex_index_map,
        const EdgeIndexMap& /*edge_index_map*/,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t,
        // each inner vector corresponds to a pareto-optimal path
        std::vector<
            std::vector< typename graph_traits< Graph >::edge_descriptor > >&
            pareto_optimal_solutions,
        std::vector< Resource_Container >& pareto_optimal_resource_containers,
        bool b_all_pareto_optimal_solutions,
        // to initialize the first label/resource container
        // and to carry the type information
        const Resource_Container& rc, Resource_Extension_Function& ref,
        Dominance_Function& dominance,
        // to specify the memory management strategy for the labels
        Label_Allocator /*la*/, Visitor vis)
    {
        pareto_optimal_resource_containers.clear();
        pareto_optimal_solutions.clear();

        size_t i_label_num = 0;
#if defined(BOOST_NO_CXX11_ALLOCATOR)
        typedef typename Label_Allocator::template rebind<
            r_c_shortest_paths_label< Graph, Resource_Container > >::other
            LAlloc;
#else
        typedef typename std::allocator_traits< Label_Allocator >::
            template rebind_alloc<
                r_c_shortest_paths_label< Graph, Resource_Container > >
                LAlloc;
        typedef std::allocator_traits< LAlloc > LTraits;
#endif
        LAlloc l_alloc;
        typedef boost::shared_ptr<
            r_c_shortest_paths_label< Graph, Resource_Container > >
            Splabel;
        std::priority_queue< Splabel, std::vector< Splabel >,
            std::greater< Splabel > >
            unprocessed_labels;

        bool b_feasible = true;
        Splabel splabel_first_label = boost::allocate_shared<
            r_c_shortest_paths_label< Graph, Resource_Container > >(l_alloc,
            i_label_num++, rc,
            boost::shared_ptr<
                r_c_shortest_paths_label< Graph, Resource_Container > >(),
            typename graph_traits< Graph >::edge_descriptor(), s);

        unprocessed_labels.push(splabel_first_label);
        std::vector< std::list< Splabel > > vec_vertex_labels_data(
            num_vertices(g));
        iterator_property_map<
            typename std::vector< std::list< Splabel > >::iterator,
            VertexIndexMap >
            vec_vertex_labels(vec_vertex_labels_data.begin(), vertex_index_map);
        vec_vertex_labels[s].push_back(splabel_first_label);
        typedef std::vector< typename std::list< Splabel >::iterator >
            vec_last_valid_positions_for_dominance_data_type;
        vec_last_valid_positions_for_dominance_data_type
            vec_last_valid_positions_for_dominance_data(num_vertices(g));
        iterator_property_map<
            typename vec_last_valid_positions_for_dominance_data_type::iterator,
            VertexIndexMap >
            vec_last_valid_positions_for_dominance(
                vec_last_valid_positions_for_dominance_data.begin(),
                vertex_index_map);
        BGL_FORALL_VERTICES_T(v, g, Graph)
        {
            put(vec_last_valid_positions_for_dominance, v,
                vec_vertex_labels[v].begin());
        }
        std::vector< size_t > vec_last_valid_index_for_dominance_data(
            num_vertices(g), 0);
        iterator_property_map< std::vector< size_t >::iterator, VertexIndexMap >
            vec_last_valid_index_for_dominance(
                vec_last_valid_index_for_dominance_data.begin(),
                vertex_index_map);
        std::vector< bool > b_vec_vertex_already_checked_for_dominance_data(
            num_vertices(g), false);
        iterator_property_map< std::vector< bool >::iterator, VertexIndexMap >
            b_vec_vertex_already_checked_for_dominance(
                b_vec_vertex_already_checked_for_dominance_data.begin(),
                vertex_index_map);

        while (!unprocessed_labels.empty()
            && vis.on_enter_loop(unprocessed_labels, g))
        {
            Splabel cur_label = unprocessed_labels.top();
            unprocessed_labels.pop();
            vis.on_label_popped(*cur_label, g);
            // an Splabel object in unprocessed_labels and the respective
            // Splabel object in the respective list<Splabel> of
            // vec_vertex_labels share their embedded r_c_shortest_paths_label
            // object to avoid memory leaks, dominated r_c_shortest_paths_label
            // objects are marked and deleted when popped from
            // unprocessed_labels, as they can no longer be deleted at the end
            // of the function; only the Splabel object in unprocessed_labels
            // still references the r_c_shortest_paths_label object this is also
            // for efficiency, because the else branch is executed only if there
            // is a chance that extending the label leads to new undominated
            // labels, which in turn is possible only if the label to be
            // extended is undominated
            if (!cur_label->b_is_dominated)
            {
                typename boost::graph_traits< Graph >::vertex_descriptor
                    i_cur_resident_vertex
                    = cur_label->resident_vertex;
                std::list< Splabel >& list_labels_cur_vertex
                    = get(vec_vertex_labels, i_cur_resident_vertex);
                if (list_labels_cur_vertex.size() >= 2
                    && vec_last_valid_index_for_dominance[i_cur_resident_vertex]
                        < list_labels_cur_vertex.size())
                {
                    typename std::list< Splabel >::iterator outer_iter
                        = list_labels_cur_vertex.begin();
                    bool b_outer_iter_at_or_beyond_last_valid_pos_for_dominance
                        = false;
                    while (outer_iter != list_labels_cur_vertex.end())
                    {
                        Splabel cur_outer_splabel = *outer_iter;
                        typename std::list< Splabel >::iterator inner_iter
                            = outer_iter;
                        if (!b_outer_iter_at_or_beyond_last_valid_pos_for_dominance
                            && outer_iter
                                == get(vec_last_valid_positions_for_dominance,
                                    i_cur_resident_vertex))
                            b_outer_iter_at_or_beyond_last_valid_pos_for_dominance
                                = true;
                        if (!get(b_vec_vertex_already_checked_for_dominance,
                                i_cur_resident_vertex)
                            || b_outer_iter_at_or_beyond_last_valid_pos_for_dominance)
                        {
                            ++inner_iter;
                        }
                        else
                        {
                            inner_iter
                                = get(vec_last_valid_positions_for_dominance,
                                    i_cur_resident_vertex);
                            ++inner_iter;
                        }
                        bool b_outer_iter_erased = false;
                        while (inner_iter != list_labels_cur_vertex.end())
                        {
                            Splabel cur_inner_splabel = *inner_iter;
                            if (dominance(cur_outer_splabel
                                              ->cumulated_resource_consumption,
                                    cur_inner_splabel
                                        ->cumulated_resource_consumption))
                            {
                                typename std::list< Splabel >::iterator buf
                                    = inner_iter;
                                ++inner_iter;
                                list_labels_cur_vertex.erase(buf);
                                if (cur_inner_splabel->b_is_processed)
                                {
                                    cur_inner_splabel.reset();
                                }
                                else
                                    cur_inner_splabel->b_is_dominated = true;
                                continue;
                            }
                            else
                                ++inner_iter;
                            if (dominance(cur_inner_splabel
                                              ->cumulated_resource_consumption,
                                    cur_outer_splabel
                                        ->cumulated_resource_consumption))
                            {
                                typename std::list< Splabel >::iterator buf
                                    = outer_iter;
                                ++outer_iter;
                                list_labels_cur_vertex.erase(buf);
                                b_outer_iter_erased = true;
                                if (cur_outer_splabel->b_is_processed)
                                {
                                    cur_outer_splabel.reset();
                                }
                                else
                                    cur_outer_splabel->b_is_dominated = true;
                                break;
                            }
                        }
                        if (!b_outer_iter_erased)
                            ++outer_iter;
                    }
                    if (list_labels_cur_vertex.size() > 1)
                        put(vec_last_valid_positions_for_dominance,
                            i_cur_resident_vertex,
                            (--(list_labels_cur_vertex.end())));
                    else
                        put(vec_last_valid_positions_for_dominance,
                            i_cur_resident_vertex,
                            list_labels_cur_vertex.begin());
                    put(b_vec_vertex_already_checked_for_dominance,
                        i_cur_resident_vertex, true);
                    put(vec_last_valid_index_for_dominance,
                        i_cur_resident_vertex,
                        list_labels_cur_vertex.size() - 1);
                }
            }
            if (!b_all_pareto_optimal_solutions
                && cur_label->resident_vertex == t)
            {
                // the devil don't sleep
                if (cur_label->b_is_dominated)
                {
                    cur_label.reset();
                }
                while (unprocessed_labels.size())
                {
                    Splabel l = unprocessed_labels.top();
                    unprocessed_labels.pop();
                    // delete only dominated labels, because nondominated labels
                    // are deleted at the end of the function
                    if (l->b_is_dominated)
                    {
                        l.reset();
                    }
                }
                break;
            }
            if (!cur_label->b_is_dominated)
            {
                cur_label->b_is_processed = true;
                vis.on_label_not_dominated(*cur_label, g);
                typename graph_traits< Graph >::vertex_descriptor cur_vertex
                    = cur_label->resident_vertex;
                typename graph_traits< Graph >::out_edge_iterator oei, oei_end;
                for (boost::tie(oei, oei_end) = out_edges(cur_vertex, g);
                     oei != oei_end; ++oei)
                {
                    b_feasible = true;
                    Splabel new_label = boost::allocate_shared<
                        r_c_shortest_paths_label< Graph, Resource_Container > >(
                        l_alloc, i_label_num++,
                        cur_label->cumulated_resource_consumption, cur_label,
                        *oei, target(*oei, g));
                    b_feasible = ref(g,
                        new_label->cumulated_resource_consumption,
                        new_label->p_pred_label->cumulated_resource_consumption,
                        new_label->pred_edge);

                    if (!b_feasible)
                    {
                        vis.on_label_not_feasible(*new_label, g);
                        new_label.reset();
                    }
                    else
                    {
                        vis.on_label_feasible(*new_label, g);
                        vec_vertex_labels[new_label->resident_vertex].push_back(
                            new_label);
                        unprocessed_labels.push(new_label);
                    }
                }
            }
            else
            {
                vis.on_label_dominated(*cur_label, g);
                cur_label.reset();
            }
        }
        std::list< Splabel > dsplabels = get(vec_vertex_labels, t);
        typename std::list< Splabel >::const_iterator csi = dsplabels.begin();
        typename std::list< Splabel >::const_iterator csi_end = dsplabels.end();
        // if d could be reached from o
        if (!dsplabels.empty())
        {
            for (; csi != csi_end; ++csi)
            {
                std::vector< typename graph_traits< Graph >::edge_descriptor >
                    cur_pareto_optimal_path;
                boost::shared_ptr<
                    r_c_shortest_paths_label< Graph, Resource_Container > >
                    p_cur_label = *csi;
                pareto_optimal_resource_containers.push_back(
                    p_cur_label->cumulated_resource_consumption);
                while (p_cur_label->num != 0)
                {
                    cur_pareto_optimal_path.push_back(p_cur_label->pred_edge);
                    p_cur_label = p_cur_label->p_pred_label;

                    // assertion b_is_valid beyond this point is not correct if
                    // the domination function requires resource levels to be
                    // strictly greater than existing values
                    //
                    // Example
                    // Customers
                    // id   min_arrival   max_departure
                    //  2             0             974
                    //  3             0             972
                    //  4             0             964
                    //  5           678             801
                    //
                    // Path A: 2-3-4-5 (times: 0-16-49-84-678)
                    // Path B: 3-2-4-5 (times: 0-18-51-62-678)
                    // The partial path 3-2-4 dominates the other partial path
                    // 2-3-4, though the path 3-2-4-5 does not strictly dominate
                    // the path 2-3-4-5
                }
                pareto_optimal_solutions.push_back(cur_pareto_optimal_path);
                if (!b_all_pareto_optimal_solutions)
                    break;
            }
        }

        BGL_FORALL_VERTICES_T(i, g, Graph)
        {
            std::list< Splabel >& list_labels_cur_vertex = vec_vertex_labels[i];
            typename std::list< Splabel >::iterator si
                = list_labels_cur_vertex.begin();
            const typename std::list< Splabel >::iterator si_end
                = list_labels_cur_vertex.end();
            for (; si != si_end; ++si)
            {
                (*si).reset();
            }
        }
    } // r_c_shortest_paths_dispatch

} // detail

// default_r_c_shortest_paths_visitor struct
struct default_r_c_shortest_paths_visitor
{
    template < class Label, class Graph >
    void on_label_popped(const Label&, const Graph&)
    {
    }
    template < class Label, class Graph >
    void on_label_feasible(const Label&, const Graph&)
    {
    }
    template < class Label, class Graph >
    void on_label_not_feasible(const Label&, const Graph&)
    {
    }
    template < class Label, class Graph >
    void on_label_dominated(const Label&, const Graph&)
    {
    }
    template < class Label, class Graph >
    void on_label_not_dominated(const Label&, const Graph&)
    {
    }
    template < class Queue, class Graph >
    bool on_enter_loop(const Queue& queue, const Graph& graph)
    {
        return true;
    }
}; // default_r_c_shortest_paths_visitor

// default_r_c_shortest_paths_allocator
typedef std::allocator< int > default_r_c_shortest_paths_allocator;
// default_r_c_shortest_paths_allocator

// r_c_shortest_paths functions (handle/interface)
// first overload:
// - return all pareto-optimal solutions
// - specify Label_Allocator and Visitor arguments
template < class Graph, class VertexIndexMap, class EdgeIndexMap,
    class Resource_Container, class Resource_Extension_Function,
    class Dominance_Function, class Label_Allocator, class Visitor >
void r_c_shortest_paths(const Graph& g, const VertexIndexMap& vertex_index_map,
    const EdgeIndexMap& edge_index_map,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor t,
    // each inner vector corresponds to a pareto-optimal path
    std::vector<
        std::vector< typename graph_traits< Graph >::edge_descriptor > >&
        pareto_optimal_solutions,
    std::vector< Resource_Container >& pareto_optimal_resource_containers,
    // to initialize the first label/resource container
    // and to carry the type information
    const Resource_Container& rc, const Resource_Extension_Function& ref,
    const Dominance_Function& dominance,
    // to specify the memory management strategy for the labels
    Label_Allocator la, Visitor vis)
{
    r_c_shortest_paths_dispatch(g, vertex_index_map, edge_index_map, s, t,
        pareto_optimal_solutions, pareto_optimal_resource_containers, true, rc,
        ref, dominance, la, vis);
}

// second overload:
// - return only one pareto-optimal solution
// - specify Label_Allocator and Visitor arguments
template < class Graph, class VertexIndexMap, class EdgeIndexMap,
    class Resource_Container, class Resource_Extension_Function,
    class Dominance_Function, class Label_Allocator, class Visitor >
void r_c_shortest_paths(const Graph& g, const VertexIndexMap& vertex_index_map,
    const EdgeIndexMap& edge_index_map,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor t,
    std::vector< typename graph_traits< Graph >::edge_descriptor >&
        pareto_optimal_solution,
    Resource_Container& pareto_optimal_resource_container,
    // to initialize the first label/resource container
    // and to carry the type information
    const Resource_Container& rc, const Resource_Extension_Function& ref,
    const Dominance_Function& dominance,
    // to specify the memory management strategy for the labels
    Label_Allocator la, Visitor vis)
{
    // each inner vector corresponds to a pareto-optimal path
    std::vector<
        std::vector< typename graph_traits< Graph >::edge_descriptor > >
        pareto_optimal_solutions;
    std::vector< Resource_Container > pareto_optimal_resource_containers;
    r_c_shortest_paths_dispatch(g, vertex_index_map, edge_index_map, s, t,
        pareto_optimal_solutions, pareto_optimal_resource_containers, false, rc,
        ref, dominance, la, vis);
    if (!pareto_optimal_solutions.empty())
    {
        pareto_optimal_solution = pareto_optimal_solutions[0];
        pareto_optimal_resource_container
            = pareto_optimal_resource_containers[0];
    }
}

// third overload:
// - return all pareto-optimal solutions
// - use default Label_Allocator and Visitor
template < class Graph, class VertexIndexMap, class EdgeIndexMap,
    class Resource_Container, class Resource_Extension_Function,
    class Dominance_Function >
void r_c_shortest_paths(const Graph& g, const VertexIndexMap& vertex_index_map,
    const EdgeIndexMap& edge_index_map,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor t,
    // each inner vector corresponds to a pareto-optimal path
    std::vector<
        std::vector< typename graph_traits< Graph >::edge_descriptor > >&
        pareto_optimal_solutions,
    std::vector< Resource_Container >& pareto_optimal_resource_containers,
    // to initialize the first label/resource container
    // and to carry the type information
    const Resource_Container& rc, const Resource_Extension_Function& ref,
    const Dominance_Function& dominance)
{
    r_c_shortest_paths_dispatch(g, vertex_index_map, edge_index_map, s, t,
        pareto_optimal_solutions, pareto_optimal_resource_containers, true, rc,
        ref, dominance, default_r_c_shortest_paths_allocator(),
        default_r_c_shortest_paths_visitor());
}

// fourth overload:
// - return only one pareto-optimal solution
// - use default Label_Allocator and Visitor
template < class Graph, class VertexIndexMap, class EdgeIndexMap,
    class Resource_Container, class Resource_Extension_Function,
    class Dominance_Function >
void r_c_shortest_paths(const Graph& g, const VertexIndexMap& vertex_index_map,
    const EdgeIndexMap& edge_index_map,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor t,
    std::vector< typename graph_traits< Graph >::edge_descriptor >&
        pareto_optimal_solution,
    Resource_Container& pareto_optimal_resource_container,
    // to initialize the first label/resource container
    // and to carry the type information
    const Resource_Container& rc, const Resource_Extension_Function& ref,
    const Dominance_Function& dominance)
{
    // each inner vector corresponds to a pareto-optimal path
    std::vector<
        std::vector< typename graph_traits< Graph >::edge_descriptor > >
        pareto_optimal_solutions;
    std::vector< Resource_Container > pareto_optimal_resource_containers;
    r_c_shortest_paths_dispatch(g, vertex_index_map, edge_index_map, s, t,
        pareto_optimal_solutions, pareto_optimal_resource_containers, false, rc,
        ref, dominance, default_r_c_shortest_paths_allocator(),
        default_r_c_shortest_paths_visitor());
    if (!pareto_optimal_solutions.empty())
    {
        pareto_optimal_solution = pareto_optimal_solutions[0];
        pareto_optimal_resource_container
            = pareto_optimal_resource_containers[0];
    }
}
// r_c_shortest_paths

// check_r_c_path function
template < class Graph, class Resource_Container,
    class Resource_Extension_Function >
void check_r_c_path(const Graph& g,
    const std::vector< typename graph_traits< Graph >::edge_descriptor >&
        ed_vec_path,
    const Resource_Container& initial_resource_levels,
    // if true, computed accumulated final resource levels must
    // be equal to desired_final_resource_levels
    // if false, computed accumulated final resource levels must
    // be less than or equal to desired_final_resource_levels
    bool b_result_must_be_equal_to_desired_final_resource_levels,
    const Resource_Container& desired_final_resource_levels,
    Resource_Container& actual_final_resource_levels,
    const Resource_Extension_Function& ref, bool& b_is_a_path_at_all,
    bool& b_feasible, bool& b_correctly_extended,
    typename graph_traits< Graph >::edge_descriptor& ed_last_extended_arc)
{
    size_t i_size_ed_vec_path = ed_vec_path.size();
    std::vector< typename graph_traits< Graph >::edge_descriptor > buf_path;
    if (i_size_ed_vec_path == 0)
        b_feasible = true;
    else
    {
        if (i_size_ed_vec_path == 1
            || target(ed_vec_path[0], g) == source(ed_vec_path[1], g))
            buf_path = ed_vec_path;
        else
            for (size_t i = i_size_ed_vec_path; i > 0; --i)
                buf_path.push_back(ed_vec_path[i - 1]);
        for (size_t i = 0; i < i_size_ed_vec_path - 1; ++i)
        {
            if (target(buf_path[i], g) != source(buf_path[i + 1], g))
            {
                b_is_a_path_at_all = false;
                b_feasible = false;
                b_correctly_extended = false;
                return;
            }
        }
    }
    b_is_a_path_at_all = true;
    b_feasible = true;
    b_correctly_extended = false;
    Resource_Container current_resource_levels = initial_resource_levels;
    actual_final_resource_levels = current_resource_levels;
    for (size_t i = 0; i < i_size_ed_vec_path; ++i)
    {
        ed_last_extended_arc = buf_path[i];
        b_feasible = ref(g, actual_final_resource_levels,
            current_resource_levels, buf_path[i]);
        current_resource_levels = actual_final_resource_levels;
        if (!b_feasible)
            return;
    }
    if (b_result_must_be_equal_to_desired_final_resource_levels)
        b_correctly_extended
            = actual_final_resource_levels == desired_final_resource_levels
            ? true
            : false;
    else
    {
        if (actual_final_resource_levels < desired_final_resource_levels
            || actual_final_resource_levels == desired_final_resource_levels)
            b_correctly_extended = true;
    }
} // check_path

} // namespace

#endif // BOOST_GRAPH_R_C_SHORTEST_PATHS_HPP

/* r_c_shortest_paths.hpp
p6ATkF5usNjBGpMMjcZ71rJJDmDe0Ym+PNJsPQ2cuMUEHQJuTBw6El5+aDWt3g5GvYoHln4OOibBuaSCvamSuGdGu+4vGIZ07EoAPCyX9m91Xtbl0xDFf8VvZb6TMVF72t4nIlkBPDRXZgNHDdevBjfljLmD666IWm5g/FXMLAqSePHCMMiVgHJAikmgWVdF1TGbnkbpGdpi0bGRMfLyxMIDO4r4HthH/VRh2m+FBU1tpmVBJDJMTlQjPtn1JCDcw08eLNnxfrpxtNqvpF9p7EbdFoKN4Rp9ETUM4DrAtKI1FireyL1+zWYGdJrqsLCo9rDkKT9JAwNDD8WKYK/8gbqN5E1V6ZtsoB7m4MtdM45Fx0HGyuTTtKR88XCUk2MN3A0jHBZNZNbgVoRnuGRPLXt/9GvdrCLUVD7s6Lv+jLRx/GVdESshofgr0xvdNS8VqYJYfKTw7/ZTjQ5SCn+jrO2rO46W1icPNqNo2kBDz16zyXAr1XAfCnUPGwd2TaXiN1PlPgpHkrIJNlaaKVUgPxPCWvLJT2j1Dk/Q6oH8tOYiyhzwRHqU2qjuUh0v7iKj0XKX2bzugVOPiKlNWX4o0TaKbVb7Y1kbt5yXsLVBUbROQTp5uZ98hbFCYFnNv6LpazVBPlb+fPm3mcbDmVfTM6jps6fpk2N++feWG1xBs2/qSK+WDS7Lc8GVO7Bt0c2Z42TtdHRshlajTYyQ48A8bUt78PbWgI3NXYbWx7k2fMFz6OPLmCJ5RW/xfXXxsou5l4W5FSVjZrtg5a/JSyCeBeq/xceDkveoj3Irw/tE/+vvonXCUw5pY59IZJ5e6JljDyWz0h40dRNqfN7nYTCE3rNqxDr0DY2QEpA4mtdRa3wCeNwDdl7Aum/XQwu5V5OTCgKDWcu3H7bjQFIxcJlxOm/UW4yguSXabXD53xIJvWBqvPQPrflgI9y82V0se6ey7z/mbXJMb2XOqeK4PHvdMynFXI2DcRN3fdyTJHW/ORL4F3CgUhND1J8Jn3i8oSY7VXweWGvNBMcpmB19XOlOVGrh6bovLoOjlBUL17DxzleKikxMjg1xdNAvYteZ+Tpkngu7J2v3PvXvG9jfYibVoZk/PDrhlN4BuKMxPoMndRRT0HJxP3Jzxbl40aIN8RveFNjvTGPdFFHb/zHWXbo7SvFY+PymqmvqDoGakkzMp3tnRcBPYfnIzSoLeS0qN8FHUA3g0BbjhW1/pz26QD06ayQWzyX8H+hzySnao/HzcPgECLzSpjzS+F4ZOJ+A0gHqA8WdstdsRy9xh7qyuK9XsDFov9w+70cTnLIhxxrE1zavc8iBD0VfcfDAfwKpM/V75HVPoYsXce+B2l8ZvC/meQ9lXrWMHD2IeRHcL8zhTNIe+bMhmHBLQsMWwWQfvW4C+r1/vY8VFsTywPDuAwP4NQ8RMVERL28RL1LLRlHkfph6KJbNHYbcZwEBIqZctkc/gFsRS873wNNA9y//2/FdZB1HvhRT9od0dCp+A83f9+feOcmwswcDjQ777rJ0EkluRqfpN/HnboilX8/QvVSHIloa5njGpdG5iSZoUopPl0OpqPbyFbvpacHu679OyO55ZVrKCxadolBzzcniOf6ksnI9rThuD/5xhI5tKwn/HDs9Br1NaKLFIKu6T0roEPae5Z5sn4jAKqaWmjmWBfDdO+6lC7IJItMRgEsxJZJRPkiEkNNChwfp8I9W4RcIpvyqzXD/ttP1gDhe9GxAvGwv90aYm0GDxxqycJyYEl+scxsPux2fs2h1xN5k9rwNg5UDlL8QlPTfoO6cSOUbRMHaMumaDe9trJlgnx3AO9kXVNtUrWqNbg68qT8v60unvecS2yaL7dxinJjj/E3yiXlGFdJSKDA/YHG3P7Atedu2xWMsloDI8ZH71hVIDc2XaSormj5/Get5pni6zIMNEEo8kDVfuktXRaw5sj34VNvYThKDxIqUvixD4uqgD8+ZDTcdMwFoEdM2IobF3kiX1G4LTTc/7xeooKwkbryW6skWJ1Ymvq2BBrXgC7B0vymslC2GWTLx3G9fQQE+hSinm3q6s1+ybe5LVtdwkLhaWObd9B7FKzblrIhPr9PTYmJNvKpS3u7nzRtpspcHu1aFWbRfMH5040+9cGXERZFwCaEQMN1Cz9Ugn3AfWWlyvaanOmvTz9cgY4QE4z7VyPwZlVHSXqSxec63Cc5NveUVMnbg12pGd0x7vgN1rcRjN9PzMHKWNRautJ9h2Vo3W3gKbwgxdQGXSouxMwt6GRbrr4mjO7rCXTFnA7bwaQsB8wQaci+Oy07cLHi2Gbrl9L8s6VgEtblVjaoPyXuSEUXEcsxxupMWvNZjSsTYINMJe8zuV5RDgJ9bopyae49629laF3ZS6y8ye9Muk0Z75J/2Fo4I4MnVwCivjbcUO0J3E3YGhEfR5knFSu1Utgfd1HKzb88VwBh6PmSir4KRAAHiw/QOftEOfvwvQJ0HQNAefVzrCq8msXZxM4a8s04vJFWWfoJSPPDUjz5cIZ9L1+R/jSVfUlEuSaMC80eeQ4mO1dA+c3x1ZmYV6KD26SO1q1iWQCHCyhGTELbLs1k2/CPIPBXduyXE0SwbYeEnYfDzH/D7arj6dp0efRV3DUJrYhFLFGYYbJlL58iVnm1QFjkHu7yydFBnDfXMcQqlB0Hy7+gbq/bX5NJCg4WPJ9dX7lhYOQlMdfbrfygJgnvuHuI1o9mVSltlQYR60zWI5MznDIJGdzGsOM8vaHR6Wh6uyu91Afo59V1WCGcSE9k9C0afincnCKodsTP7g07KkqvfpHNgJwZCSTQFK0Xs+WoXrP66nuwfVfhvrwhJL+lfeyahhbMf9YbmPJS5L5bDDcB76nyKr+83ZqxhDDUG0M8G5Q9arlpVt6jbX+RSFqbvzny3NAB3valT3qnTjSLhXXxDj3oRyWsCwBWeSI5x8BQhGs+y3V3djA/79q8KhrKetgsQCylHp9g6/7JffAsck47rpPLhM3/fxizxv8rpo5XniyxLb4iclmolOnrPxsorkXhDum17z6OnrT95+29IA8X7lpzpbFZLgNXY5tHcob6zCxv+OndpNHLtVGkkUxMCrp8lCjhdNcl5Op8vp229u9+qSXtpesoCV+vfUy9wZyMwqM1BqanmaxmRIJ0iQK/mQT87Ideij12vYyN43dqyuroQePojKH5V3YHDnswO5UzZK/N+Ffhjhq6nQq4lh64nQL7OxQyEuvjtTpl3hnyPhViOW5zv+dD47IF6WYvjPOceF53TvbXFEq8cAOndK4Q3c0SoR4Ia0vVFmf1ji82UXmmJKLznovQXDgO98Q/u7lGjTGs7/8JXhGYdwAJl9tXoyJSJD9yPSXL2UXy7j4+pN3fw3J/cc1h2s/9/MQsrM1i9LKFTsYipH6Mh53ro1YFzzNujhOuYt805kz+HtXWX3ts1EwzRY5SA+D4vm3jXLX8AFpjsva+WUbvCIgfNBnDw9Yf3Tz0EdDSUAQ0+kHkN/w7SYaJ1ASsoJpHH1nvt6e9Ek1QNcLv0SyMmV6SbTTaJMXOWLuHIbkPHXuLalgAeS4WWbiymPFrEOV8HlqB+bbki3TTnMPpKJF8dkzvXLWUgf8+5s2+n8JB9ZdDZYL1jlJsRxteW2yb93F/m8VQcNc9TvV0C0MvvHiecGUNdsX0oSII8w4WysN+t7A2wJ+jKm0Z726/PriTBFBjx4M9bvcK00m+2Q5aO2vG+pALrv04CrdE8byH8L3ritrFvmC/yo574LelnO7ZWXPh7deZuGMrcONsbh43bYdOkgjCyquC6/i6BczdYH+9zgKOxPNSYYsolAgOn5lqy07PUn7CFpNpvB75yDITHdMDNK3CqcX2Tf+s2WYTNeAUNiU8Gnyv+ENFq0goFxsa9Uu4FP9vj+Vy2IfTuvr8b5iyYf4buqvsOElc2iWMJz5PxnO1PFWIO+pHnO9qTq5c30qSIYADamytNJE18T4Hs615eBPAqjlvwZm3nbINjnYptA6O7AqOlvzKGCGU0itYKRInapobEfNUnXvSfF2QXXya/RKfO+OiB0ubsp5Qnyh0SfoTC2d3Xq1IweGgydxtphKRx2JpTg+VmyTI6qGK+cjxIXomC6T/jAtB8/vTfZehlF/eyfL22FhP8xPQWnruyH3wx0ZvXaRl3ZMJ+KdYJDaJUzdGDO75t6jWEbhOVZPwNiv9y1nnuSVRsCZRpyZQhp9pd5aTirUBVOKt8ZwlueZT0dtrlWMG4pT+4s4radiOnrLOc3Fi7fArAMGlkui93rSN54QO/v5E4Yuc+h7lRk+eSOBva1D7rkqDcV+g13CGtm9vTcuBbiXQOsJVwyxJOgyRIeKjlI+3vDzX2yohN/9e9nw8l5XmNC2InSJizJWU7ooLnI92/fwHPNLqCWSRaUHLDIHjIWIVyIRK1ZhN3OmpsYabdCbx3IEBbh3l+Rni+RLj39nTVE0vCmiIYt6fxohLGpDGBMlIfrY0sIWCX+plXnugJA+uXLLSkFxnIGQKex9hWW9dJeZvIuYeVGLNZ5XONN6vtLrSXq2ii8e/cnCm79OPtJtFdm+Ouyu0g8Ox9nF05xS2huewNSO0qGtddad5/POxR7Qrc7loMzC09T5L+wDTtAO2S4qM5Zl08Sxv/BHEGK+q3J/f68xQct7or2I5+TpVsbj4Bs4j1lQ1dqAbr3HqHq7u+I7vt51hw9yYdrk49SMXK8EUCLcT/uOg6q5o3/qE0bFsXuKsPmduHwMaX5iKi11gzNWldfOtXZ/WX2TFucWnVxBrv3a+6OXCc0lTaKvZ44GObOl+w1p38Vtcuzjwn1LIm5q2jEuCz/jfblnt17jnBRUeD3oh2h+mquZv9jttqz3XNyZtjRmxEqYKRBWdKaVMP28RzkfI/U8kyofoPtgj99sgod99+HLBNq0wXIMnD5UwZL5z1GAAALP/TvpiWCLo2//9FP099/Rebi6tlw9gk74DmLnpMoIyKq4iVaBZCqNw9feSpn6cJxY0fbmhzCxxkDhmEds4+Jk0YR40g8Q2P3oC5e3dJsgsotxEotzAeJdWN+hstrTQjTV18NYsqmwOULqZdxHEkbYB/PnkXpvu6y68+qahLLcA7jOd0nVVgpD7qFzva8R3fkv6UDdgdLo2XfgAaW4F+MGO5uq7dJUYDmhvxcrPdAXOm7WGVIj6ptHl3zLeVlX9N1zaIDLqyGK5557PBaNoN/qGD6c8GbQvmfX42BwjtNGMA1uHy68bDikF7N/112/RJcXVBoXXef6AVFK0LmILWCz3yjrkuTO0iucPPh3WN+ccspx6RuXwveo0MOcZNDBtxsa1G0+5Yg+qY/yPwtal6LpNtMZltzpVt0Zbt30scTHPBvPVYvmTwiUvsVi/LV9PeLIVhP/k5+M0r8A3XiIA9bbb1eWXYVaJpZ5R1fOyZWrwlTe8B/jePa9mNK+r5yBBfMVdr4Kst21riuOPGSzsuS2nD3Pinuh/o13rDAU0XVCWW2ajSLkZOsDm8Y8ZO+aT96SqdNP0TBwLPTp3R787sVW7ZroXtGcnu0QOO3NXSNHoG7llL6mPnnpkDnhkq6EX/o64T75xRBDGFIQfhP/VbSIpVXTe5sSI/764F/N/s81mS111hC16ZfHfdW4YmIqYFZP9uUC9hYe9Mq4+W+xd4o+tOsvpx+yCkXICM5v0kM6wqT6Ph1dgYDKiueqSG7oq6H8bTL2tqdY3dZqlH/h/S99Uf4K9dEV9tPxv/71wRR4/JxzdbFzb0dx6DdCtyvr8+ibxzI6eL9zOmoDWzTTuNAx07MO+3/+gQTueNMsjmjlm3iVSnnYhcIZuf7pj33CkynUyT/HeKKUe9gN8/wQTi8+Xhf6vrOzXh2O+98ONEGqsdUubmkx4E3LIHcPjqzhuCl0d/3WPobqBvvD93XIlzPxgXwiKHm3o8Hf8qyI+24lYn5P1+ad+glvWP3FuogjMlMlYz5oCNCBvkTtvD61vTHEVNJUpmXx9kmaA5rs2A2D4daKKHYYjmogUkhJyGPFjAu+tPw7xfwbxXlUUF41eo14SKJTeqorP0DZ1y5e0F74RfVCwkW8LgzddZXSvXCdkq0/a6Fc/UJ9SsyVpGpWuShVAP60Db5oQuGxOXz2kYociBy9KgHvggKjU34lAt2Z424jDTeoKMTjxhDPDTFvcWJVXtNerKlOoIlurYzrF36gRUlol7mGEvWrLrOY+WJK0PyDID5Wjm3WwuJUan5lQ5XYxPUIxWP0jMKvJpuE+U4l/BuiQ5EBH8njHlijFQKMGepTIzjar0GatFWxVUnStfJe4wAcfzrB66rwre6f7bm+p0h+Z0p8Iu8dcRsOHsu4XR5dIuute1kn6TNTuvJVjbUr9QxeBae53L0TwxDscAC6s31ROA1qPJMy94plddQqAmxc+S3DA3O4YPssoA2HatMj0M6QrZrI730QNzobhSf9I8zf8hk/7QP8onEIN7NxwS2Yb4Boy9uRjL2Xu1IrN3QKHHYm47FAneUUh7Oh7Z19jBrfAQi7XimHcs/zltTbcrPm/tmM+pTDZBzQcAaFUb4n9/xVUjapr5vJIICrYT1wdkN7Xshyo3D3sP0KzJ/A8iiV6LS083y4+5y1fZaFfZzdb250FvVIvuR1ZTar47iq/3KRE/snCM2w/kLJ1dThg6B+NHSJQPS60aNpyz1Sjm8RbSxV7lsGzSdNh5+IF36Gug7WmF+v7TNm5uiddJD9Y6051GehEkehkHYxgHnAKDPosBrOjhPOM4MoyWvZjgQyznNdzTmN9em0/k+XFDv0vG40M4Nl2eRlyt6OAc3sh2ldv6qBQjb5xZ5ISOcHaY+j/Gjl7+6gDtXaPucImMYiIVyHRA46mRJK+4IZXw4gedtaFIPEoFfTCdtrDe2ycx6dRIoqCrkQbj22YIVUHdn7+d/lr+rSUYU9jouZQsUdz4ZTQ1yZ3R2cpIxih3vnav8Nfu1++bBK2SPjqClypsOaqo6vLOVlUh861Pg7WWLMy332lm0i55BkaYUPj7/LRoO+85zxCueJy5I/5PKSbSiXW5UfL20ez65CxS+5O6r28RX8WwV/Q6/3czpdFsvFryVSyliIXNI2J932GCWQbXQjRPm0fwWxvCt7NhpE3gqpZgqsVPzsaftxBWN3WFZTs5HJNHIaT0JbnOLdSv+AXKsrQHYM9IQFgMSKauojXtPnrzSNo3t6KqPRzZZT+Thq2ap3UwnHsqRoOnf/trnkhX/8p9CoDf18/BQjhJv2b4Z/bT+59z/zF79ELIpYRCUuseDVVbPN+UfIJEUbYZ6DfajRHk3RDVlWlKey/BQBo1iYg5ceXlRTSwKYWEveFcU3U9vbeZ1t/KCGD/XT1q0DUOB+gdTZyS4goNkMNzOQ2eQ4+hbeJkDIupgSjR0clwX7zpmcWvt+IpJT09beO3SwGsatoPWisW9NH2cBoIjWJeaWyVoVaytWZhbMRU7O/qnDiAggGa4ZGQ6aPQhgEcMCM9O0v3TyUx2C4UGpwYH5QoOT+6b3Dn7KaISvpcI2TIMt5deK/KBLmepxECuYJ5s4TK/yqWVHCREnuOQY4m4qQSe6hvXCfq2TpySdR7HWmQSP9sGsAUHACO1SIJC4Bxb3BzwMwMD9wQzw4+7J47lS7eiwKo+WS4homdr5etQpz9yhKu2WOIPfWB+cH2IOMI0sXKTcI9sZ9teZCwYSbYlXOrHSviKf4SZYzuLX6C64o9+WNdyXNzn0Fz2cP8Ov73LlFiy2r/AwWuinIfliDVIL0+mLFNCMOyMAAthmCQqTdVP3hXqv7zQGOVybq25f4vwUye51SR3JY12IwrJoVdyJzVKeS0ncscXA9ZQxZLlVIp1AGNNdx3CtYnTRmzoJsSM4ZlkKOJbwJiBNYKvOki1olcZqd+TG6/nKA1JfnyhlL6RMYeXMsNXAtdWAKEiMThwogzHwqVgzCh5tGHEOoUYDExWWeP4A+Gu2mHHReBwO2fUFgs180KeqFXnHA3T/qBSZCWmhJgORZesiFjWIJzaB8jngGu7zPeaL/eln0wx49/OO3sc6mIlgAg1opbzVXMckVKG4OZCB7Fy6tv5Qh/Ucwhk9vJypB3l0xcXCVVTzmkj6eih4WcVk0Jok4JLi6MjmTo82WUHLwInMkuHn8GOR9Az1xmRnBkU1kRrcg9Ukw34mcPWkKG7gHaN4n951p2iJuisfINFPpX8UoivLIE+GQJCciUwYKy7kR5IgzbvVhoE2MxXYidiGDBaY5yDN0Fn58d/EJEwWnFTWxy9G2/jL99FqJCH7xAhkNuXGI0EA44Q1ZLio/KI8WDGLPP7+JXed4rm/jHZsphfUGuFLMEUhK+U4ct6vnUF9FIdM+cIk47DjodymZlUIZNnQN5cgVyMHS60rsIBtIDUMcuoE30Oukzu0/Xdq5LHvK/bLyfMpvyviBntggDR2pqm6jGXsK901nCDt1sB+uDvTzbDDWFzq2k3AYE1vWjlgpTPbwCexZqn6BUlxYTfjumeOmGLDH6lKnH3pcjGWzLX3lg0C7Pw79di8A5Uw787hLv8W6h9zwjms1dfas6wR398P/eenhfmzM1mq0bKn3DnGV6dISjyIxdlkkKqnm4N0M7lEGHyQ4q5Ca95xHZkeb4lvV28kJV4/4mq3GhNTQbJdZ2asLgw++YNA7inCkNm/dqK5y2PnwIrSHPwkbTXpmZBHDA/74MKU3XWWDMEbUBtn33ZHylozsxEsia76pau6sYMKcBkKwpYT4yV/jF8BXfy4DG+Jr31Zv12XtFt+JJ0Eddw7Lh9tc3uiHr5mL1q+KMq+JENtqIXWQnoL8/uS2mHdZ/kFi6VPW+gpAvVum2gQq80nVARJVu3ZmJL7piCXdGubfj/45KO750bmViUWGAlgkeZB0ltrEFa+cN2MK3zt1QPzs0EiVoXZOVTOTjy+DjC7A63UYPLeqYzT2J78RxN9LKzsD15aQQvLMcmQzPOmaEBUPwNpnl29ez9akNWfbhd/RD2n2LzxfC8M/xo6peo4BX5oeZdZM4jGWWubVPyNZz8HmfBBy/DfNxTvpyeg3Ycdaq6Rp37yTp1WLMOPv6fundVJoNGujvDsSCW0URHhqssfE1bNvzBnidMDL6VbP6WbMqWyUD/wdaLAE+Qhs=
*/