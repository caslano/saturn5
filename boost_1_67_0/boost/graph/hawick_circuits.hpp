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