// Copyright Louis Dionne 2013

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_HAWICK_CIRCUITS_HPP
#define BOOST_GRAPH_HAWICK_CIRCUITS_HPP

#include <algorithm>
#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/one_bit_color_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/move/utility.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/tuple/tuple.hpp> // for boost::tie
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/result_of.hpp>
#include <set>
#include <utility> // for std::pair
#include <vector>

namespace boost
{
namespace hawick_circuits_detail
{
    //! @internal Functor returning all the vertices adjacent to a vertex.
    struct get_all_adjacent_vertices
    {
        template < typename Sig > struct result;

        template < typename This, typename Vertex, typename Graph >
        struct result< This(Vertex, Graph) >
        {
        private:
            typedef typename remove_reference< Graph >::type RawGraph;
            typedef graph_traits< RawGraph > Traits;
            typedef typename Traits::adjacency_iterator AdjacencyIterator;

        public:
            typedef std::pair< AdjacencyIterator, AdjacencyIterator > type;
        };

        template < typename Vertex, typename Graph >
        typename result< get_all_adjacent_vertices(
            BOOST_FWD_REF(Vertex), BOOST_FWD_REF(Graph)) >::type
        operator()(BOOST_FWD_REF(Vertex) v, BOOST_FWD_REF(Graph) g) const
        {
            return adjacent_vertices(
                boost::forward< Vertex >(v), boost::forward< Graph >(g));
        }
    };

    //! @internal Functor returning a set of the vertices adjacent to a vertex.
    struct get_unique_adjacent_vertices
    {
        template < typename Sig > struct result;

        template < typename This, typename Vertex, typename Graph >
        struct result< This(Vertex, Graph) >
        {
            typedef std::set< typename remove_reference< Vertex >::type > type;
        };

        template < typename Vertex, typename Graph >
        typename result< get_unique_adjacent_vertices(
            Vertex, Graph const&) >::type
        operator()(Vertex v, Graph const& g) const
        {
            typedef typename result< get_unique_adjacent_vertices(
                Vertex, Graph const&) >::type Set;
            return Set(
                adjacent_vertices(v, g).first, adjacent_vertices(v, g).second);
        }
    };

    //! @internal
    //! Return whether a container contains a given value.
    //! This is not meant as a general purpose membership testing function; it
    //! would have to be more clever about possible optimizations.
    template < typename Container, typename Value >
    bool contains(Container const& c, Value const& v)
    {
        return std::find(boost::begin(c), boost::end(c), v) != boost::end(c);
    }

    /*!
     * @internal
     * Algorithm finding all the cycles starting from a given vertex.
     *
     * The search is only done in the subgraph induced by the starting vertex
     * and the vertices with an index higher than the starting vertex.
     */
    template < typename Graph, typename Visitor, typename VertexIndexMap,
        typename Stack, typename ClosedMatrix, typename GetAdjacentVertices >
    struct hawick_circuits_from
    {
    private:
        typedef graph_traits< Graph > Traits;
        typedef typename Traits::vertex_descriptor Vertex;
        typedef typename Traits::edge_descriptor Edge;
        typedef typename Traits::vertices_size_type VerticesSize;
        typedef
            typename property_traits< VertexIndexMap >::value_type VertexIndex;

        typedef typename result_of< GetAdjacentVertices(
            Vertex, Graph const&) >::type AdjacentVertices;
        typedef typename range_iterator< AdjacentVertices const >::type
            AdjacencyIterator;

        // The one_bit_color_map starts all white, i.e. not blocked.
        // Since we make that assumption (I looked at the implementation, but
        // I can't find anything that documents this behavior), we're gonna
        // assert it in the constructor.
        typedef one_bit_color_map< VertexIndexMap > BlockedMap;
        typedef typename property_traits< BlockedMap >::value_type BlockedColor;

        static BlockedColor blocked_false_color()
        {
            return color_traits< BlockedColor >::white();
        }

        static BlockedColor blocked_true_color()
        {
            return color_traits< BlockedColor >::black();
        }

        // This is used by the constructor to secure the assumption
        // documented above.
        bool blocked_map_starts_all_unblocked() const
        {
            BOOST_FOREACH (Vertex v, vertices(graph_))
                if (is_blocked(v))
                    return false;
            return true;
        }

        // This is only used in the constructor to make sure the optimization of
        // sharing data structures between iterations does not break the code.
        bool all_closed_rows_are_empty() const
        {
            BOOST_FOREACH (typename ClosedMatrix::reference row, closed_)
                if (!row.empty())
                    return false;
            return true;
        }

    public:
        hawick_circuits_from(Graph const& graph, Visitor& visitor,
            VertexIndexMap const& vim, Stack& stack, ClosedMatrix& closed,
            VerticesSize n_vertices)
        : graph_(graph)
        , visitor_(visitor)
        , vim_(vim)
        , stack_(stack)
        , closed_(closed)
        , blocked_(n_vertices, vim_)
        {
            BOOST_ASSERT(blocked_map_starts_all_unblocked());

            // Since sharing the data structures between iterations is
            // just an optimization, it must always be equivalent to
            // constructing new ones in this constructor.
            BOOST_ASSERT(stack_.empty());
            BOOST_ASSERT(closed_.size() == n_vertices);
            BOOST_ASSERT(all_closed_rows_are_empty());
        }

    private:
        //! @internal Return the index of a given vertex.
        VertexIndex index_of(Vertex v) const { return get(vim_, v); }

        //! @internal Return whether a vertex `v` is closed to a vertex `u`.
        bool is_closed_to(Vertex u, Vertex v) const
        {
            typedef typename ClosedMatrix::const_reference VertexList;
            VertexList closed_to_u = closed_[index_of(u)];
            return contains(closed_to_u, v);
        }

        //! @internal Close a vertex `v` to a vertex `u`.
        void close_to(Vertex u, Vertex v)
        {
            BOOST_ASSERT(!is_closed_to(u, v));
            closed_[index_of(u)].push_back(v);
        }

        //! @internal Return whether a given vertex is blocked.
        bool is_blocked(Vertex v) const
        {
            return get(blocked_, v) == blocked_true_color();
        }

        //! @internal Block a given vertex.
        void block(Vertex v) { put(blocked_, v, blocked_true_color()); }

        //! @internal Unblock a given vertex.
        void unblock(Vertex u)
        {
            typedef typename ClosedMatrix::reference VertexList;

            put(blocked_, u, blocked_false_color());
            VertexList closed_to_u = closed_[index_of(u)];

            while (!closed_to_u.empty())
            {
                Vertex const w = closed_to_u.back();
                closed_to_u.pop_back();
                if (is_blocked(w))
                    unblock(w);
            }
            BOOST_ASSERT(closed_to_u.empty());
        }

        //! @internal Main procedure as described in the paper.
        bool circuit(Vertex start, Vertex v)
        {
            bool found_circuit = false;
            stack_.push_back(v);
            block(v);

            // Cache some values that are used more than once in the function.
            VertexIndex const index_of_start = index_of(start);
            AdjacentVertices const adj_vertices
                = GetAdjacentVertices()(v, graph_);
            AdjacencyIterator const w_end = boost::end(adj_vertices);

            for (AdjacencyIterator w_it = boost::begin(adj_vertices);
                 w_it != w_end; ++w_it)
            {
                Vertex const w = *w_it;
                // Since we're only looking in the subgraph induced by `start`
                // and the vertices with an index higher than `start`, we skip
                // any vertex that does not satisfy that.
                if (index_of(w) < index_of_start)
                    continue;

                // If the last vertex is equal to `start`, we have a circuit.
                else if (w == start)
                {
                    // const_cast to ensure the visitor does not modify the
                    // stack
                    visitor_.cycle(const_cast< Stack const& >(stack_), graph_);
                    found_circuit = true;
                }

                // If `w` is not blocked, we continue searching further down the
                // same path for a cycle with `w` in it.
                else if (!is_blocked(w) && circuit(start, w))
                    found_circuit = true;
            }

            if (found_circuit)
                unblock(v);
            else
                for (AdjacencyIterator w_it = boost::begin(adj_vertices);
                     w_it != w_end; ++w_it)
                {
                    Vertex const w = *w_it;
                    // Like above, we skip vertices that are not in the subgraph
                    // we're considering.
                    if (index_of(w) < index_of_start)
                        continue;

                    // If `v` is not closed to `w`, we make it so.
                    if (!is_closed_to(w, v))
                        close_to(w, v);
                }

            BOOST_ASSERT(v == stack_.back());
            stack_.pop_back();
            return found_circuit;
        }

    public:
        void operator()(Vertex start) { circuit(start, start); }

    private:
        Graph const& graph_;
        Visitor& visitor_;
        VertexIndexMap const& vim_;
        Stack& stack_;
        ClosedMatrix& closed_;
        BlockedMap blocked_;
    };

    template < typename GetAdjacentVertices, typename Graph, typename Visitor,
        typename VertexIndexMap >
    void call_hawick_circuits(Graph const& graph,
        Visitor /* by value */ visitor, VertexIndexMap const& vertex_index_map)
    {
        typedef graph_traits< Graph > Traits;
        typedef typename Traits::vertex_descriptor Vertex;
        typedef typename Traits::vertices_size_type VerticesSize;
        typedef typename Traits::vertex_iterator VertexIterator;

        typedef std::vector< Vertex > Stack;
        typedef std::vector< std::vector< Vertex > > ClosedMatrix;

        typedef hawick_circuits_from< Graph, Visitor, VertexIndexMap, Stack,
            ClosedMatrix, GetAdjacentVertices >
            SubAlgorithm;

        VerticesSize const n_vertices = num_vertices(graph);
        Stack stack;
        stack.reserve(n_vertices);
        ClosedMatrix closed(n_vertices);

        VertexIterator start, last;
        for (boost::tie(start, last) = vertices(graph); start != last; ++start)
        {
            // Note1: The sub algorithm may NOT be reused once it has been
            // called.

            // Note2: We reuse the Stack and the ClosedMatrix (after clearing
            // them) in each iteration to avoid redundant destruction and
            // construction. It would be strictly equivalent to have these as
            // member variables of the sub algorithm.
            SubAlgorithm sub_algo(
                graph, visitor, vertex_index_map, stack, closed, n_vertices);
            sub_algo(*start);
            stack.clear();
            typename ClosedMatrix::iterator row, last_row = closed.end();
            for (row = closed.begin(); row != last_row; ++row)
                row->clear();
        }
    }

    template < typename GetAdjacentVertices, typename Graph, typename Visitor >
    void call_hawick_circuits(
        Graph const& graph, BOOST_FWD_REF(Visitor) visitor)
    {
        call_hawick_circuits< GetAdjacentVertices >(graph,
            boost::forward< Visitor >(visitor), get(vertex_index, graph));
    }
} // end namespace hawick_circuits_detail

//! Enumerate all the elementary circuits in a directed multigraph.
template < typename Graph, typename Visitor, typename VertexIndexMap >
void hawick_circuits(BOOST_FWD_REF(Graph) graph, BOOST_FWD_REF(Visitor) visitor,
    BOOST_FWD_REF(VertexIndexMap) vertex_index_map)
{
    hawick_circuits_detail::call_hawick_circuits<
        hawick_circuits_detail::get_all_adjacent_vertices >(
        boost::forward< Graph >(graph), boost::forward< Visitor >(visitor),
        boost::forward< VertexIndexMap >(vertex_index_map));
}

template < typename Graph, typename Visitor >
void hawick_circuits(BOOST_FWD_REF(Graph) graph, BOOST_FWD_REF(Visitor) visitor)
{
    hawick_circuits_detail::call_hawick_circuits<
        hawick_circuits_detail::get_all_adjacent_vertices >(
        boost::forward< Graph >(graph), boost::forward< Visitor >(visitor));
}

/*!
 * Same as `boost::hawick_circuits`, but duplicate circuits caused by parallel
 * edges will not be considered. Each circuit will be considered only once.
 */
template < typename Graph, typename Visitor, typename VertexIndexMap >
void hawick_unique_circuits(BOOST_FWD_REF(Graph) graph,
    BOOST_FWD_REF(Visitor) visitor,
    BOOST_FWD_REF(VertexIndexMap) vertex_index_map)
{
    hawick_circuits_detail::call_hawick_circuits<
        hawick_circuits_detail::get_unique_adjacent_vertices >(
        boost::forward< Graph >(graph), boost::forward< Visitor >(visitor),
        boost::forward< VertexIndexMap >(vertex_index_map));
}

template < typename Graph, typename Visitor >
void hawick_unique_circuits(
    BOOST_FWD_REF(Graph) graph, BOOST_FWD_REF(Visitor) visitor)
{
    hawick_circuits_detail::call_hawick_circuits<
        hawick_circuits_detail::get_unique_adjacent_vertices >(
        boost::forward< Graph >(graph), boost::forward< Visitor >(visitor));
}
} // end namespace boost

#endif // !BOOST_GRAPH_HAWICK_CIRCUITS_HPP

/* hawick_circuits.hpp
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
*/