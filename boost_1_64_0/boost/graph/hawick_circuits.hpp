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
CCv/qLo/dv8f+6X/o7yw84/a+UNY+Tdofsm/UTCBIe1hXkZ/7Lw0dIfrtT92Xh16JK9Omz92Xk+Gw/Xo8DoBGB5H4hQBEFYeBsbDfEsR+H8jL9GfPz+EAv6f1+3/eRv+9/I2/DrONxX+9jptfDgPEKIRLiKkvokhK0JdhIEI2xBuI5QMxD7PGPHTEL5CiLoF+G/kX4Lf//6B5/naYb8EY68/eMj6oxuMvf7gH+ZbDcbO60XwV/J6Qb/k9UIFYOcHSwtG2gkh0S/Xf4WQGIn3Bv8hDy7Wc4ciBGn/kF/yg4X8fx37/zr2v7eO/bP5Bf/u+6bGL/nPwpDvwTDs7zU7xF+Mxv5O8ULipmXY3ylpSLw6DPv9tAHxB8Ow3/tHEd+lDDuPHSocWW9+i53HizX838/PZ3PQ/+HY76dHD/Olhf3lvH3T4X/5/bQajZ0XDf8w/99H/L/4/Ugfgax/pvhYedUVkbhFBHZ+bRfEj0P4m8Pv7j/E8bGOb4iAsPKicR628+F9w/Cx8m6/QvyVCAjr/XEb8dHnMb+fPFx3byPXR+J8SJznNoS1vvIe1guJWyDkORxXiE+fjp0/bPs7PtZ3MevhdzFyvGQ4PlZ+cDQSb0coisR7b2N/dwsh8bXbEFZee7nD51gk8lxHKHFYL8S3Q8h0OP4RPy0SO498CeK/Qnj6sP0RfzMSO+8/6g7SLncgrO8JScS3uANh52lD/LQ7EFY+qhLEJ9LFx/o7TBsSR0X9MZ+s9kH9EZ/+T94j4PUNiRO1/TGvj+xBOZC4F0K2w35B/NFO7Od/NRKXfIKs44ffMUicNBr5PjucF4ivi1Ds8HmO+HEIqQ6/wxF/eg37u21tDTv/H/theZDjXRIw8eOH/YLEJY3++P0qe3AdJL5miP13AfoYZH2LwM5T2ID4kjEQVv48RcS3Q3jq8O8jiJ+GUOCwHxH/FULBw+9+xN9ESICsM6hY5H4ICZE4D+Lj62N/31MgvjryOzVSX2PED0TIcvgdj/htsdh58HsR3w+Zj9KH60Mc9veozC/fo+rI75KH/Yv4EXHY+fHT4rD/riX7Dz73fv2NFvXf/e+NGWu/zeDPn6fvvjuVDhbb36Vh8gELsv6xvrh/Uu9/5J3gb/4DE/U7EEU6BE/OIKDdhxAqDlCECowrEFcENAQSyoFgLh8D/ZMDwcQHA8oU2BSAEUBRDRDMWSDHTAgmJQ0YZ8BmBZQEYnoMrgl4jg4cA87VBVSgB2M9G8QBjRlAeUDcApD5OJgbB+cC1gDp5kKoNkA5RlDOUnA8YCMj5vg2wBAmcD44Pg4wgxncC8TRgI3MmPu2AQqfAM+JXHAuYBSQZDoE0xq0sXo6BNOSDYxVYLsANgGpZ0Mw1dhBPBuCaQXkDmwXQPLfYMpJAagJRJ8JwdTiBM/wTAjmZSB1YLsAGnCB43NBHQFDuDBliwNc4sLUaw2QhRsTZwX8xI3plzXAEzyYY1gBdRBbF/AmYgcC5vNgzq0GXALqzQLnAtLzgr7IhWDmA0XkQjDrgNC5EMxWoIaDdgZ0OAnm4EE7ACqB8ZiUBe4FaM8HXx9+wHDzY2whQBegpEwIpjRY5AoyIZjngRqArQsoLgTiOaD9AT2A0AdlBuwFepQDwbwgDNonB4LZDDSRA8F8DbSWA8HkPw3WuVwI5nMgplwI5hSQUC4E86IIWJMP2hlwShTTR9OAJmKYsWQBmCKGKQMa8JQEqEMWqAsgC1jkRg/GHmCZDOinHNCegCby4P0YxC0AKxXAfbNAHFBdEXNNXcBSoJBsCGaSEljfsiGYZUAVwK4GXAbqrYZgypwB8ygXgqkF5HJwHcBgoNEsCGYW0GIWBFNOGfR1FgQ=
*/