//=======================================================================
// Copyright (C) 2012 Flavio De Lorenzi (fdlorenzi@gmail.com)
// Copyright (C) 2013 Jakob Lykke Andersen, University of Southern Denmark
// (jlandersen@imada.sdu.dk)
//
// The algorithm implemented here is derived from original ideas by
// Pasquale Foggia and colaborators. For further information see
// e.g. Cordella et al. 2001, 2004.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

// Revision History:
//   8 April 2013: Fixed a typo in vf2_print_callback. (Flavio De Lorenzi)

#ifndef BOOST_VF2_SUB_GRAPH_ISO_HPP
#define BOOST_VF2_SUB_GRAPH_ISO_HPP

#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>
#include <utility>

#include <boost/assert.hpp>
#include <boost/concept/assert.hpp>
#include <boost/concept_check.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/mcgregor_common_subgraphs.hpp> // for always_equivalent
#include <boost/graph/named_function_params.hpp>
#include <boost/type_traits/has_less.hpp>
#include <boost/mpl/int.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/enable_if.hpp>

#ifndef BOOST_GRAPH_ITERATION_MACROS_HPP
#define BOOST_ISO_INCLUDED_ITER_MACROS // local macro, see bottom of file
#include <boost/graph/iteration_macros.hpp>
#endif

namespace boost
{

// Default print_callback
template < typename Graph1, typename Graph2 > struct vf2_print_callback
{

    vf2_print_callback(const Graph1& graph1, const Graph2& graph2)
    : graph1_(graph1), graph2_(graph2)
    {
    }

    template < typename CorrespondenceMap1To2, typename CorrespondenceMap2To1 >
    bool operator()(CorrespondenceMap1To2 f, CorrespondenceMap2To1) const
    {

        // Print (sub)graph isomorphism map
        BGL_FORALL_VERTICES_T(v, graph1_, Graph1)
        std::cout << '(' << get(vertex_index_t(), graph1_, v) << ", "
                  << get(vertex_index_t(), graph2_, get(f, v)) << ") ";

        std::cout << std::endl;

        return true;
    }

private:
    const Graph1& graph1_;
    const Graph2& graph2_;
};

namespace detail
{

    // State associated with a single graph (graph_this)
    template < typename GraphThis, typename GraphOther, typename IndexMapThis,
        typename IndexMapOther >
    class base_state
    {

        typedef typename graph_traits< GraphThis >::vertex_descriptor
            vertex_this_type;
        typedef typename graph_traits< GraphOther >::vertex_descriptor
            vertex_other_type;

        typedef
            typename graph_traits< GraphThis >::vertices_size_type size_type;

        const GraphThis& graph_this_;
        const GraphOther& graph_other_;

        IndexMapThis index_map_this_;
        IndexMapOther index_map_other_;

        std::vector< vertex_other_type > core_vec_;
        typedef iterator_property_map<
            typename std::vector< vertex_other_type >::iterator, IndexMapThis,
            vertex_other_type, vertex_other_type& >
            core_map_type;
        core_map_type core_;

        std::vector< size_type > in_vec_, out_vec_;
        typedef iterator_property_map<
            typename std::vector< size_type >::iterator, IndexMapThis,
            size_type, size_type& >
            in_out_map_type;
        in_out_map_type in_, out_;

        size_type term_in_count_, term_out_count_, term_both_count_,
            core_count_;

        // Forbidden
        base_state(const base_state&);
        base_state& operator=(const base_state&);

    public:
        base_state(const GraphThis& graph_this, const GraphOther& graph_other,
            IndexMapThis index_map_this, IndexMapOther index_map_other)
        : graph_this_(graph_this)
        , graph_other_(graph_other)
        , index_map_this_(index_map_this)
        , index_map_other_(index_map_other)
        , core_vec_(num_vertices(graph_this_),
              graph_traits< GraphOther >::null_vertex())
        , core_(core_vec_.begin(), index_map_this_)
        , in_vec_(num_vertices(graph_this_), 0)
        , out_vec_(num_vertices(graph_this_), 0)
        , in_(in_vec_.begin(), index_map_this_)
        , out_(out_vec_.begin(), index_map_this_)
        , term_in_count_(0)
        , term_out_count_(0)
        , term_both_count_(0)
        , core_count_(0)
        {
        }

        // Adds a vertex pair to the state of graph graph_this
        void push(
            const vertex_this_type& v_this, const vertex_other_type& v_other)
        {

            ++core_count_;

            put(core_, v_this, v_other);

            if (!get(in_, v_this))
            {
                put(in_, v_this, core_count_);
                ++term_in_count_;
                if (get(out_, v_this))
                    ++term_both_count_;
            }

            if (!get(out_, v_this))
            {
                put(out_, v_this, core_count_);
                ++term_out_count_;
                if (get(in_, v_this))
                    ++term_both_count_;
            }

            BGL_FORALL_INEDGES_T(v_this, e, graph_this_, GraphThis)
            {
                vertex_this_type w = source(e, graph_this_);
                if (!get(in_, w))
                {
                    put(in_, w, core_count_);
                    ++term_in_count_;
                    if (get(out_, w))
                        ++term_both_count_;
                }
            }

            BGL_FORALL_OUTEDGES_T(v_this, e, graph_this_, GraphThis)
            {
                vertex_this_type w = target(e, graph_this_);
                if (!get(out_, w))
                {
                    put(out_, w, core_count_);
                    ++term_out_count_;
                    if (get(in_, w))
                        ++term_both_count_;
                }
            }
        }

        // Removes vertex pair from state of graph_this
        void pop(const vertex_this_type& v_this, const vertex_other_type&)
        {

            if (!core_count_)
                return;

            if (get(in_, v_this) == core_count_)
            {
                put(in_, v_this, 0);
                --term_in_count_;
                if (get(out_, v_this))
                    --term_both_count_;
            }

            BGL_FORALL_INEDGES_T(v_this, e, graph_this_, GraphThis)
            {
                vertex_this_type w = source(e, graph_this_);
                if (get(in_, w) == core_count_)
                {
                    put(in_, w, 0);
                    --term_in_count_;
                    if (get(out_, w))
                        --term_both_count_;
                }
            }

            if (get(out_, v_this) == core_count_)
            {
                put(out_, v_this, 0);
                --term_out_count_;
                if (get(in_, v_this))
                    --term_both_count_;
            }

            BGL_FORALL_OUTEDGES_T(v_this, e, graph_this_, GraphThis)
            {
                vertex_this_type w = target(e, graph_this_);
                if (get(out_, w) == core_count_)
                {
                    put(out_, w, 0);
                    --term_out_count_;
                    if (get(in_, w))
                        --term_both_count_;
                }
            }
            put(core_, v_this, graph_traits< GraphOther >::null_vertex());

            --core_count_;
        }

        // Returns true if the in-terminal set is not empty
        bool term_in() const { return core_count_ < term_in_count_; }

        // Returns true if vertex belongs to the in-terminal set
        bool term_in(const vertex_this_type& v) const
        {
            return (get(in_, v) > 0)
                && (get(core_, v) == graph_traits< GraphOther >::null_vertex());
        }

        // Returns true if the out-terminal set is not empty
        bool term_out() const { return core_count_ < term_out_count_; }

        // Returns true if vertex belongs to the out-terminal set
        bool term_out(const vertex_this_type& v) const
        {
            return (get(out_, v) > 0)
                && (get(core_, v) == graph_traits< GraphOther >::null_vertex());
        }

        // Returns true of both (in- and out-terminal) sets are not empty
        bool term_both() const { return core_count_ < term_both_count_; }

        // Returns true if vertex belongs to both (in- and out-terminal) sets
        bool term_both(const vertex_this_type& v) const
        {
            return (get(in_, v) > 0) && (get(out_, v) > 0)
                && (get(core_, v) == graph_traits< GraphOther >::null_vertex());
        }

        // Returns true if vertex belongs to the core map, i.e. it is in the
        // present mapping
        bool in_core(const vertex_this_type& v) const
        {
            return get(core_, v) != graph_traits< GraphOther >::null_vertex();
        }

        // Returns the number of vertices in the mapping
        size_type count() const { return core_count_; }

        // Returns the image (in graph_other) of vertex v (in graph_this)
        vertex_other_type core(const vertex_this_type& v) const
        {
            return get(core_, v);
        }

        // Returns the mapping
        core_map_type get_map() const { return core_; }

        // Returns the "time" (or depth) when vertex was added to the
        // in-terminal set
        size_type in_depth(const vertex_this_type& v) const
        {
            return get(in_, v);
        }

        // Returns the "time" (or depth) when vertex was added to the
        // out-terminal set
        size_type out_depth(const vertex_this_type& v) const
        {
            return get(out_, v);
        }

        // Returns the terminal set counts
        boost::tuple< size_type, size_type, size_type > term_set() const
        {
            return boost::make_tuple(
                term_in_count_, term_out_count_, term_both_count_);
        }
    };

    // Function object that checks whether a valid edge
    // exists. For multi-graphs matched edges are excluded
    template < typename Graph, typename Enable = void >
    struct equivalent_edge_exists
    {
        typedef
            typename boost::graph_traits< Graph >::edge_descriptor edge_type;

        BOOST_CONCEPT_ASSERT((LessThanComparable< edge_type >));

        template < typename EdgePredicate >
        bool operator()(typename graph_traits< Graph >::vertex_descriptor s,
            typename graph_traits< Graph >::vertex_descriptor t,
            EdgePredicate is_valid_edge, const Graph& g)
        {

            BGL_FORALL_OUTEDGES_T(s, e, g, Graph)
            {
                if ((target(e, g) == t) && is_valid_edge(e)
                    && (matched_edges_.find(e) == matched_edges_.end()))
                {
                    matched_edges_.insert(e);
                    return true;
                }
            }

            return false;
        }

    private:
        std::set< edge_type > matched_edges_;
    };

    template < typename Graph >
    struct equivalent_edge_exists< Graph,
        typename boost::disable_if< is_multigraph< Graph > >::type >
    {
        template < typename EdgePredicate >
        bool operator()(typename graph_traits< Graph >::vertex_descriptor s,
            typename graph_traits< Graph >::vertex_descriptor t,
            EdgePredicate is_valid_edge, const Graph& g)
        {

            typename graph_traits< Graph >::edge_descriptor e;
            bool found;
            boost::tie(e, found) = edge(s, t, g);
            if (!found)
                return false;
            else if (is_valid_edge(e))
                return true;

            return false;
        }
    };

    // Generates a predicate for edge e1 given  a binary predicate and a
    // fixed edge e2
    template < typename Graph1, typename Graph2,
        typename EdgeEquivalencePredicate >
    struct edge1_predicate
    {

        edge1_predicate(EdgeEquivalencePredicate edge_comp,
            typename graph_traits< Graph2 >::edge_descriptor e2)
        : edge_comp_(edge_comp), e2_(e2)
        {
        }

        bool operator()(typename graph_traits< Graph1 >::edge_descriptor e1)
        {
            return edge_comp_(e1, e2_);
        }

        EdgeEquivalencePredicate edge_comp_;
        typename graph_traits< Graph2 >::edge_descriptor e2_;
    };

    // Generates a predicate for edge e2 given given a binary predicate and a
    // fixed edge e1
    template < typename Graph1, typename Graph2,
        typename EdgeEquivalencePredicate >
    struct edge2_predicate
    {

        edge2_predicate(EdgeEquivalencePredicate edge_comp,
            typename graph_traits< Graph1 >::edge_descriptor e1)
        : edge_comp_(edge_comp), e1_(e1)
        {
        }

        bool operator()(typename graph_traits< Graph2 >::edge_descriptor e2)
        {
            return edge_comp_(e1_, e2);
        }

        EdgeEquivalencePredicate edge_comp_;
        typename graph_traits< Graph1 >::edge_descriptor e1_;
    };

    enum problem_selector
    {
        subgraph_mono,
        subgraph_iso,
        isomorphism
    };

    // The actual state associated with both graphs
    template < typename Graph1, typename Graph2, typename IndexMap1,
        typename IndexMap2, typename EdgeEquivalencePredicate,
        typename VertexEquivalencePredicate, typename SubGraphIsoMapCallback,
        problem_selector problem_selection >
    class state
    {

        typedef typename graph_traits< Graph1 >::vertex_descriptor vertex1_type;
        typedef typename graph_traits< Graph2 >::vertex_descriptor vertex2_type;

        typedef typename graph_traits< Graph1 >::edge_descriptor edge1_type;
        typedef typename graph_traits< Graph2 >::edge_descriptor edge2_type;

        typedef typename graph_traits< Graph1 >::vertices_size_type
            graph1_size_type;
        typedef typename graph_traits< Graph2 >::vertices_size_type
            graph2_size_type;

        const Graph1& graph1_;
        const Graph2& graph2_;

        IndexMap1 index_map1_;

        EdgeEquivalencePredicate edge_comp_;
        VertexEquivalencePredicate vertex_comp_;

        base_state< Graph1, Graph2, IndexMap1, IndexMap2 > state1_;
        base_state< Graph2, Graph1, IndexMap2, IndexMap1 > state2_;

        // Three helper functions used in Feasibility and Valid functions to
        // test terminal set counts when testing for:
        // - graph sub-graph monomorphism, or
        inline bool comp_term_sets(graph1_size_type a, graph2_size_type b,
            boost::mpl::int_< subgraph_mono >) const
        {
            return a <= b;
        }

        // - graph sub-graph isomorphism, or
        inline bool comp_term_sets(graph1_size_type a, graph2_size_type b,
            boost::mpl::int_< subgraph_iso >) const
        {
            return a <= b;
        }

        // - graph isomorphism
        inline bool comp_term_sets(graph1_size_type a, graph2_size_type b,
            boost::mpl::int_< isomorphism >) const
        {
            return a == b;
        }

        // Forbidden
        state(const state&);
        state& operator=(const state&);

    public:
        state(const Graph1& graph1, const Graph2& graph2, IndexMap1 index_map1,
            IndexMap2 index_map2, EdgeEquivalencePredicate edge_comp,
            VertexEquivalencePredicate vertex_comp)
        : graph1_(graph1)
        , graph2_(graph2)
        , index_map1_(index_map1)
        , edge_comp_(edge_comp)
        , vertex_comp_(vertex_comp)
        , state1_(graph1, graph2, index_map1, index_map2)
        , state2_(graph2, graph1, index_map2, index_map1)
        {
        }

        // Add vertex pair to the state
        void push(const vertex1_type& v, const vertex2_type& w)
        {
            state1_.push(v, w);
            state2_.push(w, v);
        }

        // Remove vertex pair from state
        void pop(const vertex1_type& v, const vertex2_type&)
        {
            vertex2_type w = state1_.core(v);
            state1_.pop(v, w);
            state2_.pop(w, v);
        }

        // Checks the feasibility of a new vertex pair
        bool feasible(const vertex1_type& v_new, const vertex2_type& w_new)
        {

            if (!vertex_comp_(v_new, w_new))
                return false;

            // graph1
            graph1_size_type term_in1_count = 0, term_out1_count = 0,
                             rest1_count = 0;

            {
                equivalent_edge_exists< Graph2 > edge2_exists;

                BGL_FORALL_INEDGES_T(v_new, e1, graph1_, Graph1)
                {
                    vertex1_type v = source(e1, graph1_);

                    if (state1_.in_core(v) || (v == v_new))
                    {
                        vertex2_type w = w_new;
                        if (v != v_new)
                            w = state1_.core(v);
                        if (!edge2_exists(w, w_new,
                                edge2_predicate< Graph1, Graph2,
                                    EdgeEquivalencePredicate >(edge_comp_, e1),
                                graph2_))
                            return false;
                    }
                    else
                    {
                        if (0 < state1_.in_depth(v))
                            ++term_in1_count;
                        if (0 < state1_.out_depth(v))
                            ++term_out1_count;
                        if ((state1_.in_depth(v) == 0)
                            && (state1_.out_depth(v) == 0))
                            ++rest1_count;
                    }
                }
            }

            {
                equivalent_edge_exists< Graph2 > edge2_exists;

                BGL_FORALL_OUTEDGES_T(v_new, e1, graph1_, Graph1)
                {
                    vertex1_type v = target(e1, graph1_);
                    if (state1_.in_core(v) || (v == v_new))
                    {
                        vertex2_type w = w_new;
                        if (v != v_new)
                            w = state1_.core(v);

                        if (!edge2_exists(w_new, w,
                                edge2_predicate< Graph1, Graph2,
                                    EdgeEquivalencePredicate >(edge_comp_, e1),
                                graph2_))
                            return false;
                    }
                    else
                    {
                        if (0 < state1_.in_depth(v))
                            ++term_in1_count;
                        if (0 < state1_.out_depth(v))
                            ++term_out1_count;
                        if ((state1_.in_depth(v) == 0)
                            && (state1_.out_depth(v) == 0))
                            ++rest1_count;
                    }
                }
            }

            // graph2
            graph2_size_type term_out2_count = 0, term_in2_count = 0,
                             rest2_count = 0;

            {
                equivalent_edge_exists< Graph1 > edge1_exists;

                BGL_FORALL_INEDGES_T(w_new, e2, graph2_, Graph2)
                {
                    vertex2_type w = source(e2, graph2_);
                    if (state2_.in_core(w) || (w == w_new))
                    {
                        if (problem_selection != subgraph_mono)
                        {
                            vertex1_type v = v_new;
                            if (w != w_new)
                                v = state2_.core(w);

                            if (!edge1_exists(v, v_new,
                                    edge1_predicate< Graph1, Graph2,
                                        EdgeEquivalencePredicate >(
                                        edge_comp_, e2),
                                    graph1_))
                                return false;
                        }
                    }
                    else
                    {
                        if (0 < state2_.in_depth(w))
                            ++term_in2_count;
                        if (0 < state2_.out_depth(w))
                            ++term_out2_count;
                        if ((state2_.in_depth(w) == 0)
                            && (state2_.out_depth(w) == 0))
                            ++rest2_count;
                    }
                }
            }

            {
                equivalent_edge_exists< Graph1 > edge1_exists;

                BGL_FORALL_OUTEDGES_T(w_new, e2, graph2_, Graph2)
                {
                    vertex2_type w = target(e2, graph2_);
                    if (state2_.in_core(w) || (w == w_new))
                    {
                        if (problem_selection != subgraph_mono)
                        {
                            vertex1_type v = v_new;
                            if (w != w_new)
                                v = state2_.core(w);

                            if (!edge1_exists(v_new, v,
                                    edge1_predicate< Graph1, Graph2,
                                        EdgeEquivalencePredicate >(
                                        edge_comp_, e2),
                                    graph1_))
                                return false;
                        }
                    }
                    else
                    {
                        if (0 < state2_.in_depth(w))
                            ++term_in2_count;
                        if (0 < state2_.out_depth(w))
                            ++term_out2_count;
                        if ((state2_.in_depth(w) == 0)
                            && (state2_.out_depth(w) == 0))
                            ++rest2_count;
                    }
                }
            }

            if (problem_selection != subgraph_mono)
            { // subgraph_iso and isomorphism
                return comp_term_sets(term_in1_count, term_in2_count,
                           boost::mpl::int_< problem_selection >())
                    && comp_term_sets(term_out1_count, term_out2_count,
                        boost::mpl::int_< problem_selection >())
                    && comp_term_sets(rest1_count, rest2_count,
                        boost::mpl::int_< problem_selection >());
            }
            else
            { // subgraph_mono
                return comp_term_sets(term_in1_count, term_in2_count,
                           boost::mpl::int_< problem_selection >())
                    && comp_term_sets(term_out1_count, term_out2_count,
                        boost::mpl::int_< problem_selection >())
                    && comp_term_sets(
                        term_in1_count + term_out1_count + rest1_count,
                        term_in2_count + term_out2_count + rest2_count,
                        boost::mpl::int_< problem_selection >());
            }
        }

        // Returns true if vertex v in graph1 is a possible candidate to
        // be added to the current state
        bool possible_candidate1(const vertex1_type& v) const
        {
            if (state1_.term_both() && state2_.term_both())
                return state1_.term_both(v);
            else if (state1_.term_out() && state2_.term_out())
                return state1_.term_out(v);
            else if (state1_.term_in() && state2_.term_in())
                return state1_.term_in(v);
            else
                return !state1_.in_core(v);
        }

        // Returns true if vertex w in graph2 is a possible candidate to
        // be added to the current state
        bool possible_candidate2(const vertex2_type& w) const
        {
            if (state1_.term_both() && state2_.term_both())
                return state2_.term_both(w);
            else if (state1_.term_out() && state2_.term_out())
                return state2_.term_out(w);
            else if (state1_.term_in() && state2_.term_in())
                return state2_.term_in(w);
            else
                return !state2_.in_core(w);
        }

        // Returns true if a mapping was found
        bool success() const
        {
            return state1_.count() == num_vertices(graph1_);
        }

        // Returns true if a state is valid
        bool valid() const
        {
            boost::tuple< graph1_size_type, graph1_size_type, graph1_size_type >
                term1;
            boost::tuple< graph2_size_type, graph2_size_type, graph2_size_type >
                term2;

            term1 = state1_.term_set();
            term2 = state2_.term_set();

            return comp_term_sets(boost::get< 0 >(term1),
                       boost::get< 0 >(term2),
                       boost::mpl::int_< problem_selection >())
                && comp_term_sets(boost::get< 1 >(term1),
                    boost::get< 1 >(term2),
                    boost::mpl::int_< problem_selection >())
                && comp_term_sets(boost::get< 2 >(term1),
                    boost::get< 2 >(term2),
                    boost::mpl::int_< problem_selection >());
        }

        // Calls the user_callback with a graph (sub)graph mapping
        bool call_back(SubGraphIsoMapCallback user_callback) const
        {
            return user_callback(state1_.get_map(), state2_.get_map());
        }
    };

    // Data structure to keep info used for back tracking during
    // matching process
    template < typename Graph1, typename Graph2, typename VertexOrder1 >
    struct vf2_match_continuation
    {
        typename VertexOrder1::const_iterator graph1_verts_iter;
        typename graph_traits< Graph2 >::vertex_iterator graph2_verts_iter;
    };

    // Non-recursive method that explores state space using a depth-first
    // search strategy.  At each depth possible pairs candidate are compute
    // and tested for feasibility to extend the mapping. If a complete
    // mapping is found, the mapping is output to user_callback in the form
    // of a correspondence map (graph1 to graph2). Returning false from the
    // user_callback will terminate the search. Function match will return
    // true if the entire search space was explored.
    template < typename Graph1, typename Graph2, typename IndexMap1,
        typename IndexMap2, typename VertexOrder1,
        typename EdgeEquivalencePredicate, typename VertexEquivalencePredicate,
        typename SubGraphIsoMapCallback, problem_selector problem_selection >
    bool match(const Graph1& graph1, const Graph2& graph2,
        SubGraphIsoMapCallback user_callback, const VertexOrder1& vertex_order1,
        state< Graph1, Graph2, IndexMap1, IndexMap2, EdgeEquivalencePredicate,
            VertexEquivalencePredicate, SubGraphIsoMapCallback,
            problem_selection >& s)
    {

        typename VertexOrder1::const_iterator graph1_verts_iter;

        typedef typename graph_traits< Graph2 >::vertex_iterator
            vertex2_iterator_type;
        vertex2_iterator_type graph2_verts_iter, graph2_verts_iter_end;

        typedef vf2_match_continuation< Graph1, Graph2, VertexOrder1 >
            match_continuation_type;
        std::vector< match_continuation_type > k;
        bool found_match = false;

    recur:
        if (s.success())
        {
            if (!s.call_back(user_callback))
                return true;
            found_match = true;

            goto back_track;
        }

        if (!s.valid())
            goto back_track;

        graph1_verts_iter = vertex_order1.begin();
        while (graph1_verts_iter != vertex_order1.end()
            && !s.possible_candidate1(*graph1_verts_iter))
        {
            ++graph1_verts_iter;
        }

        boost::tie(graph2_verts_iter, graph2_verts_iter_end) = vertices(graph2);
        while (graph2_verts_iter != graph2_verts_iter_end)
        {
            if (s.possible_candidate2(*graph2_verts_iter))
            {
                if (s.feasible(*graph1_verts_iter, *graph2_verts_iter))
                {
                    match_continuation_type kk;
                    kk.graph1_verts_iter = graph1_verts_iter;
                    kk.graph2_verts_iter = graph2_verts_iter;
                    k.push_back(kk);

                    s.push(*graph1_verts_iter, *graph2_verts_iter);
                    goto recur;
                }
            }
        graph2_loop:
            ++graph2_verts_iter;
        }

    back_track:
        if (k.empty())
            return found_match;

        const match_continuation_type kk = k.back();
        graph1_verts_iter = kk.graph1_verts_iter;
        graph2_verts_iter = kk.graph2_verts_iter;
        k.pop_back();

        s.pop(*graph1_verts_iter, *graph2_verts_iter);

        goto graph2_loop;
    }

    // Used to sort nodes by in/out degrees
    template < typename Graph > struct vertex_in_out_degree_cmp
    {
        typedef typename graph_traits< Graph >::vertex_descriptor vertex_type;

        vertex_in_out_degree_cmp(const Graph& graph) : graph_(graph) {}

        bool operator()(const vertex_type& v, const vertex_type& w) const
        {
            // lexicographical comparison
            return std::make_pair(in_degree(v, graph_), out_degree(v, graph_))
                < std::make_pair(in_degree(w, graph_), out_degree(w, graph_));
        }

        const Graph& graph_;
    };

    // Used to sort nodes by multiplicity of in/out degrees
    template < typename Graph, typename FrequencyMap >
    struct vertex_frequency_degree_cmp
    {
        typedef typename graph_traits< Graph >::vertex_descriptor vertex_type;

        vertex_frequency_degree_cmp(const Graph& graph, FrequencyMap freq)
        : graph_(graph), freq_(freq)
        {
        }

        bool operator()(const vertex_type& v, const vertex_type& w) const
        {
            // lexicographical comparison
            return std::make_pair(
                       freq_[v], in_degree(v, graph_) + out_degree(v, graph_))
                < std::make_pair(
                    freq_[w], in_degree(w, graph_) + out_degree(w, graph_));
        }

        const Graph& graph_;
        FrequencyMap freq_;
    };

    // Sorts vertices of a graph by multiplicity of in/out degrees
    template < typename Graph, typename IndexMap, typename VertexOrder >
    void sort_vertices(
        const Graph& graph, IndexMap index_map, VertexOrder& order)
    {
        typedef typename graph_traits< Graph >::vertices_size_type size_type;

        boost::range::sort(order, vertex_in_out_degree_cmp< Graph >(graph));

        std::vector< size_type > freq_vec(num_vertices(graph), 0);
        typedef iterator_property_map<
            typename std::vector< size_type >::iterator, IndexMap, size_type,
            size_type& >
            frequency_map_type;

        frequency_map_type freq
            = make_iterator_property_map(freq_vec.begin(), index_map);

        typedef typename VertexOrder::iterator order_iterator;

        for (order_iterator order_iter = order.begin();
             order_iter != order.end();)
        {
            size_type count = 0;
            for (order_iterator count_iter = order_iter;
                 (count_iter != order.end())
                 && (in_degree(*order_iter, graph)
                     == in_degree(*count_iter, graph))
                 && (out_degree(*order_iter, graph)
                     == out_degree(*count_iter, graph));
                 ++count_iter)
                ++count;

            for (size_type i = 0; i < count; ++i)
            {
                freq[*order_iter] = count;
                ++order_iter;
            }
        }

        boost::range::sort(order,
            vertex_frequency_degree_cmp< Graph, frequency_map_type >(
                graph, freq));
    }

    // Enumerates all graph sub-graph mono-/iso-morphism mappings between graphs
    // graph_small and graph_large. Continues until user_callback returns true
    // or the search space has been fully explored.
    template < problem_selector problem_selection, typename GraphSmall,
        typename GraphLarge, typename IndexMapSmall, typename IndexMapLarge,
        typename VertexOrderSmall, typename EdgeEquivalencePredicate,
        typename VertexEquivalencePredicate, typename SubGraphIsoMapCallback >
    bool vf2_subgraph_morphism(const GraphSmall& graph_small,
        const GraphLarge& graph_large, SubGraphIsoMapCallback user_callback,
        IndexMapSmall index_map_small, IndexMapLarge index_map_large,
        const VertexOrderSmall& vertex_order_small,
        EdgeEquivalencePredicate edge_comp,
        VertexEquivalencePredicate vertex_comp)
    {

        // Graph requirements
        BOOST_CONCEPT_ASSERT((BidirectionalGraphConcept< GraphSmall >));
        BOOST_CONCEPT_ASSERT((VertexListGraphConcept< GraphSmall >));
        BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< GraphSmall >));
        BOOST_CONCEPT_ASSERT((AdjacencyMatrixConcept< GraphSmall >));

        BOOST_CONCEPT_ASSERT((BidirectionalGraphConcept< GraphLarge >));
        BOOST_CONCEPT_ASSERT((VertexListGraphConcept< GraphLarge >));
        BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< GraphLarge >));
        BOOST_CONCEPT_ASSERT((AdjacencyMatrixConcept< GraphLarge >));

        typedef typename graph_traits< GraphSmall >::vertex_descriptor
            vertex_small_type;
        typedef typename graph_traits< GraphLarge >::vertex_descriptor
            vertex_large_type;

        typedef typename graph_traits< GraphSmall >::vertices_size_type
            size_type_small;
        typedef typename graph_traits< GraphLarge >::vertices_size_type
            size_type_large;

        // Property map requirements
        BOOST_CONCEPT_ASSERT(
            (ReadablePropertyMapConcept< IndexMapSmall, vertex_small_type >));
        typedef typename property_traits< IndexMapSmall >::value_type
            IndexMapSmallValue;
        BOOST_STATIC_ASSERT(
            (is_convertible< IndexMapSmallValue, size_type_small >::value));

        BOOST_CONCEPT_ASSERT(
            (ReadablePropertyMapConcept< IndexMapLarge, vertex_large_type >));
        typedef typename property_traits< IndexMapLarge >::value_type
            IndexMapLargeValue;
        BOOST_STATIC_ASSERT(
            (is_convertible< IndexMapLargeValue, size_type_large >::value));

        // Edge & vertex requirements
        typedef typename graph_traits< GraphSmall >::edge_descriptor
            edge_small_type;
        typedef typename graph_traits< GraphLarge >::edge_descriptor
            edge_large_type;

        BOOST_CONCEPT_ASSERT((BinaryPredicateConcept< EdgeEquivalencePredicate,
            edge_small_type, edge_large_type >));

        BOOST_CONCEPT_ASSERT(
            (BinaryPredicateConcept< VertexEquivalencePredicate,
                vertex_small_type, vertex_large_type >));

        // Vertex order requirements
        BOOST_CONCEPT_ASSERT((ContainerConcept< VertexOrderSmall >));
        typedef typename VertexOrderSmall::value_type order_value_type;
        BOOST_STATIC_ASSERT(
            (is_same< vertex_small_type, order_value_type >::value));
        BOOST_ASSERT(num_vertices(graph_small) == vertex_order_small.size());

        if (num_vertices(graph_small) > num_vertices(graph_large))
            return false;

        typename graph_traits< GraphSmall >::edges_size_type num_edges_small
            = num_edges(graph_small);
        typename graph_traits< GraphLarge >::edges_size_type num_edges_large
            = num_edges(graph_large);

        // Double the number of edges for undirected graphs: each edge counts as
        // in-edge and out-edge
        if (is_undirected(graph_small))
            num_edges_small *= 2;
        if (is_undirected(graph_large))
            num_edges_large *= 2;
        if (num_edges_small > num_edges_large)
            return false;

        detail::state< GraphSmall, GraphLarge, IndexMapSmall, IndexMapLarge,
            EdgeEquivalencePredicate, VertexEquivalencePredicate,
            SubGraphIsoMapCallback, problem_selection >
            s(graph_small, graph_large, index_map_small, index_map_large,
                edge_comp, vertex_comp);

        return detail::match(
            graph_small, graph_large, user_callback, vertex_order_small, s);
    }

} // namespace detail

// Returns vertex order (vertices sorted by multiplicity of in/out degrees)
template < typename Graph >
std::vector< typename graph_traits< Graph >::vertex_descriptor >
vertex_order_by_mult(const Graph& graph)
{

    std::vector< typename graph_traits< Graph >::vertex_descriptor >
        vertex_order;
    std::copy(vertices(graph).first, vertices(graph).second,
        std::back_inserter(vertex_order));

    detail::sort_vertices(graph, get(vertex_index, graph), vertex_order);
    return vertex_order;
}

// Enumerates all graph sub-graph monomorphism mappings between graphs
// graph_small and graph_large. Continues until user_callback returns true or
// the search space has been fully explored.
template < typename GraphSmall, typename GraphLarge, typename IndexMapSmall,
    typename IndexMapLarge, typename VertexOrderSmall,
    typename EdgeEquivalencePredicate, typename VertexEquivalencePredicate,
    typename SubGraphIsoMapCallback >
bool vf2_subgraph_mono(const GraphSmall& graph_small,
    const GraphLarge& graph_large, SubGraphIsoMapCallback user_callback,
    IndexMapSmall index_map_small, IndexMapLarge index_map_large,
    const VertexOrderSmall& vertex_order_small,
    EdgeEquivalencePredicate edge_comp, VertexEquivalencePredicate vertex_comp)
{
    return detail::vf2_subgraph_morphism< detail::subgraph_mono >(graph_small,
        graph_large, user_callback, index_map_small, index_map_large,
        vertex_order_small, edge_comp, vertex_comp);
}

// All default interface for vf2_subgraph_iso
template < typename GraphSmall, typename GraphLarge,
    typename SubGraphIsoMapCallback >
bool vf2_subgraph_mono(const GraphSmall& graph_small,
    const GraphLarge& graph_large, SubGraphIsoMapCallback user_callback)
{
    return vf2_subgraph_mono(graph_small, graph_large, user_callback,
        get(vertex_index, graph_small), get(vertex_index, graph_large),
        vertex_order_by_mult(graph_small), always_equivalent(),
        always_equivalent());
}

// Named parameter interface of vf2_subgraph_iso
template < typename GraphSmall, typename GraphLarge, typename VertexOrderSmall,
    typename SubGraphIsoMapCallback, typename Param, typename Tag,
    typename Rest >
bool vf2_subgraph_mono(const GraphSmall& graph_small,
    const GraphLarge& graph_large, SubGraphIsoMapCallback user_callback,
    const VertexOrderSmall& vertex_order_small,
    const bgl_named_params< Param, Tag, Rest >& params)
{
    return vf2_subgraph_mono(graph_small, graph_large, user_callback,
        choose_const_pmap(
            get_param(params, vertex_index1), graph_small, vertex_index),
        choose_const_pmap(
            get_param(params, vertex_index2), graph_large, vertex_index),
        vertex_order_small,
        choose_param(
            get_param(params, edges_equivalent_t()), always_equivalent()),
        choose_param(
            get_param(params, vertices_equivalent_t()), always_equivalent()));
}

// Enumerates all graph sub-graph isomorphism mappings between graphs
// graph_small and graph_large. Continues until user_callback returns true or
// the search space has been fully explored.
template < typename GraphSmall, typename GraphLarge, typename IndexMapSmall,
    typename IndexMapLarge, typename VertexOrderSmall,
    typename EdgeEquivalencePredicate, typename VertexEquivalencePredicate,
    typename SubGraphIsoMapCallback >
bool vf2_subgraph_iso(const GraphSmall& graph_small,
    const GraphLarge& graph_large, SubGraphIsoMapCallback user_callback,
    IndexMapSmall index_map_small, IndexMapLarge index_map_large,
    const VertexOrderSmall& vertex_order_small,
    EdgeEquivalencePredicate edge_comp, VertexEquivalencePredicate vertex_comp)
{
    return detail::vf2_subgraph_morphism< detail::subgraph_iso >(graph_small,
        graph_large, user_callback, index_map_small, index_map_large,
        vertex_order_small, edge_comp, vertex_comp);
}

// All default interface for vf2_subgraph_iso
template < typename GraphSmall, typename GraphLarge,
    typename SubGraphIsoMapCallback >
bool vf2_subgraph_iso(const GraphSmall& graph_small,
    const GraphLarge& graph_large, SubGraphIsoMapCallback user_callback)
{

    return vf2_subgraph_iso(graph_small, graph_large, user_callback,
        get(vertex_index, graph_small), get(vertex_index, graph_large),
        vertex_order_by_mult(graph_small), always_equivalent(),
        always_equivalent());
}

// Named parameter interface of vf2_subgraph_iso
template < typename GraphSmall, typename GraphLarge, typename VertexOrderSmall,
    typename SubGraphIsoMapCallback, typename Param, typename Tag,
    typename Rest >
bool vf2_subgraph_iso(const GraphSmall& graph_small,
    const GraphLarge& graph_large, SubGraphIsoMapCallback user_callback,
    const VertexOrderSmall& vertex_order_small,
    const bgl_named_params< Param, Tag, Rest >& params)
{

    return vf2_subgraph_iso(graph_small, graph_large, user_callback,
        choose_const_pmap(
            get_param(params, vertex_index1), graph_small, vertex_index),
        choose_const_pmap(
            get_param(params, vertex_index2), graph_large, vertex_index),
        vertex_order_small,
        choose_param(
            get_param(params, edges_equivalent_t()), always_equivalent()),
        choose_param(
            get_param(params, vertices_equivalent_t()), always_equivalent()));
}

// Enumerates all isomorphism mappings between graphs graph1_ and graph2_.
// Continues until user_callback returns true or the search space has been
// fully explored.
template < typename Graph1, typename Graph2, typename IndexMap1,
    typename IndexMap2, typename VertexOrder1,
    typename EdgeEquivalencePredicate, typename VertexEquivalencePredicate,
    typename GraphIsoMapCallback >
bool vf2_graph_iso(const Graph1& graph1, const Graph2& graph2,
    GraphIsoMapCallback user_callback, IndexMap1 index_map1,
    IndexMap2 index_map2, const VertexOrder1& vertex_order1,
    EdgeEquivalencePredicate edge_comp, VertexEquivalencePredicate vertex_comp)
{

    // Graph requirements
    BOOST_CONCEPT_ASSERT((BidirectionalGraphConcept< Graph1 >));
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph1 >));
    BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< Graph1 >));
    BOOST_CONCEPT_ASSERT((AdjacencyMatrixConcept< Graph1 >));

    BOOST_CONCEPT_ASSERT((BidirectionalGraphConcept< Graph2 >));
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph2 >));
    BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< Graph2 >));
    BOOST_CONCEPT_ASSERT((AdjacencyMatrixConcept< Graph2 >));

    typedef typename graph_traits< Graph1 >::vertex_descriptor vertex1_type;
    typedef typename graph_traits< Graph2 >::vertex_descriptor vertex2_type;

    typedef typename graph_traits< Graph1 >::vertices_size_type size_type1;
    typedef typename graph_traits< Graph2 >::vertices_size_type size_type2;

    // Property map requirements
    BOOST_CONCEPT_ASSERT(
        (ReadablePropertyMapConcept< IndexMap1, vertex1_type >));
    typedef typename property_traits< IndexMap1 >::value_type IndexMap1Value;
    BOOST_STATIC_ASSERT((is_convertible< IndexMap1Value, size_type1 >::value));

    BOOST_CONCEPT_ASSERT(
        (ReadablePropertyMapConcept< IndexMap2, vertex2_type >));
    typedef typename property_traits< IndexMap2 >::value_type IndexMap2Value;
    BOOST_STATIC_ASSERT((is_convertible< IndexMap2Value, size_type2 >::value));

    // Edge & vertex requirements
    typedef typename graph_traits< Graph1 >::edge_descriptor edge1_type;
    typedef typename graph_traits< Graph2 >::edge_descriptor edge2_type;

    BOOST_CONCEPT_ASSERT((BinaryPredicateConcept< EdgeEquivalencePredicate,
        edge1_type, edge2_type >));

    BOOST_CONCEPT_ASSERT((BinaryPredicateConcept< VertexEquivalencePredicate,
        vertex1_type, vertex2_type >));

    // Vertex order requirements
    BOOST_CONCEPT_ASSERT((ContainerConcept< VertexOrder1 >));
    typedef typename VertexOrder1::value_type order_value_type;
    BOOST_STATIC_ASSERT((is_same< vertex1_type, order_value_type >::value));
    BOOST_ASSERT(num_vertices(graph1) == vertex_order1.size());

    if (num_vertices(graph1) != num_vertices(graph2))
        return false;

    typename graph_traits< Graph1 >::edges_size_type num_edges1
        = num_edges(graph1);
    typename graph_traits< Graph2 >::edges_size_type num_edges2
        = num_edges(graph2);

    // Double the number of edges for undirected graphs: each edge counts as
    // in-edge and out-edge
    if (is_undirected(graph1))
        num_edges1 *= 2;
    if (is_undirected(graph2))
        num_edges2 *= 2;
    if (num_edges1 != num_edges2)
        return false;

    detail::state< Graph1, Graph2, IndexMap1, IndexMap2,
        EdgeEquivalencePredicate, VertexEquivalencePredicate,
        GraphIsoMapCallback, detail::isomorphism >
        s(graph1, graph2, index_map1, index_map2, edge_comp, vertex_comp);

    return detail::match(graph1, graph2, user_callback, vertex_order1, s);
}

// All default interface for vf2_graph_iso
template < typename Graph1, typename Graph2, typename GraphIsoMapCallback >
bool vf2_graph_iso(const Graph1& graph1, const Graph2& graph2,
    GraphIsoMapCallback user_callback)
{

    return vf2_graph_iso(graph1, graph2, user_callback,
        get(vertex_index, graph1), get(vertex_index, graph2),
        vertex_order_by_mult(graph1), always_equivalent(), always_equivalent());
}

// Named parameter interface of vf2_graph_iso
template < typename Graph1, typename Graph2, typename VertexOrder1,
    typename GraphIsoMapCallback, typename Param, typename Tag, typename Rest >
bool vf2_graph_iso(const Graph1& graph1, const Graph2& graph2,
    GraphIsoMapCallback user_callback, const VertexOrder1& vertex_order1,
    const bgl_named_params< Param, Tag, Rest >& params)
{

    return vf2_graph_iso(graph1, graph2, user_callback,
        choose_const_pmap(
            get_param(params, vertex_index1), graph1, vertex_index),
        choose_const_pmap(
            get_param(params, vertex_index2), graph2, vertex_index),
        vertex_order1,
        choose_param(
            get_param(params, edges_equivalent_t()), always_equivalent()),
        choose_param(
            get_param(params, vertices_equivalent_t()), always_equivalent()));
}

// Verifies a graph (sub)graph isomorphism map
template < typename Graph1, typename Graph2, typename CorresponenceMap1To2,
    typename EdgeEquivalencePredicate, typename VertexEquivalencePredicate >
inline bool verify_vf2_subgraph_iso(const Graph1& graph1, const Graph2& graph2,
    const CorresponenceMap1To2 f, EdgeEquivalencePredicate edge_comp,
    VertexEquivalencePredicate vertex_comp)
{

    BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< Graph1 >));
    BOOST_CONCEPT_ASSERT((AdjacencyMatrixConcept< Graph2 >));

    detail::equivalent_edge_exists< Graph2 > edge2_exists;

    BGL_FORALL_EDGES_T(e1, graph1, Graph1)
    {
        typename graph_traits< Graph1 >::vertex_descriptor s1, t1;
        typename graph_traits< Graph2 >::vertex_descriptor s2, t2;

        s1 = source(e1, graph1);
        t1 = target(e1, graph1);
        s2 = get(f, s1);
        t2 = get(f, t1);

        if (!vertex_comp(s1, s2) || !vertex_comp(t1, t2))
            return false;

        typename graph_traits< Graph2 >::edge_descriptor e2;

        if (!edge2_exists(s2, t2,
                detail::edge2_predicate< Graph1, Graph2,
                    EdgeEquivalencePredicate >(edge_comp, e1),
                graph2))
            return false;
    }

    return true;
}

// Variant of verify_subgraph_iso with all default parameters
template < typename Graph1, typename Graph2, typename CorresponenceMap1To2 >
inline bool verify_vf2_subgraph_iso(
    const Graph1& graph1, const Graph2& graph2, const CorresponenceMap1To2 f)
{
    return verify_vf2_subgraph_iso(
        graph1, graph2, f, always_equivalent(), always_equivalent());
}

} // namespace boost

#ifdef BOOST_ISO_INCLUDED_ITER_MACROS
#undef BOOST_ISO_INCLUDED_ITER_MACROS
#include <boost/graph/iteration_macros_undef.hpp>
#endif

#endif // BOOST_VF2_SUB_GRAPH_ISO_HPP

/* vf2_sub_graph_iso.hpp
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
*/