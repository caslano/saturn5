// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2018, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_COMPLEMENT_GRAPH_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_COMPLEMENT_GRAPH_HPP

#include <cstddef>

#include <set>
#include <stack>
#include <utility>
#include <vector>

#include <boost/core/addressof.hpp>

#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/policies/compare.hpp>


namespace boost { namespace geometry
{

namespace detail { namespace is_valid
{


template <typename TurnPoint, typename CSTag>
class complement_graph_vertex
{
public:
    complement_graph_vertex(std::size_t id)
        : m_id(id)
        , m_turn_point(NULL)
    {}

    complement_graph_vertex(TurnPoint const* turn_point,
                            std::size_t expected_id)
        : m_id(expected_id)
        , m_turn_point(turn_point)
    {}

    inline std::size_t id() const { return m_id; }

    inline bool operator<(complement_graph_vertex const& other) const
    {
        if ( m_turn_point != NULL && other.m_turn_point != NULL )
        {
            return geometry::less
                <
                    TurnPoint, -1, CSTag
                >()(*m_turn_point, *other.m_turn_point);
        }
        if ( m_turn_point == NULL && other.m_turn_point == NULL )
        {
            return m_id < other.m_id;
        }
        return m_turn_point == NULL;
    }

private:
    // the value of m_turn_point determines the type of the vertex
    // non-NULL: vertex corresponds to an IP
    // NULL    : vertex corresponds to a hole or outer space, and the id
    //           is the ring id of the corresponding ring of the polygon
    std::size_t m_id;
    TurnPoint const* m_turn_point;
};




template <typename TurnPoint, typename CSTag>
class complement_graph
{
private:
    typedef complement_graph_vertex<TurnPoint, CSTag> vertex;
    typedef std::set<vertex> vertex_container;

public:
    typedef typename vertex_container::const_iterator vertex_handle;

private:
    struct vertex_handle_less
    {
        inline bool operator()(vertex_handle v1, vertex_handle v2) const
        {
            return v1->id() < v2->id();
        }
    };

    typedef std::set<vertex_handle, vertex_handle_less> neighbor_container;

    class has_cycles_dfs_data
    {
    public:
        has_cycles_dfs_data(std::size_t num_nodes)
            : m_visited(num_nodes, false)
            , m_parent_id(num_nodes, -1)
        {}

        inline signed_size_type parent_id(vertex_handle v) const
        {
            return m_parent_id[v->id()];
        }

        inline void set_parent_id(vertex_handle v, signed_size_type id)
        {
            m_parent_id[v->id()] = id;
        }

        inline bool visited(vertex_handle v) const
        {
            return m_visited[v->id()];
        }

        inline void set_visited(vertex_handle v, bool value)
        {
            m_visited[v->id()] = value;
        }
    private:
        std::vector<bool> m_visited;
        std::vector<signed_size_type> m_parent_id;
    };


    inline bool has_cycles(vertex_handle start_vertex,
                           has_cycles_dfs_data& data) const
    {
        std::stack<vertex_handle> stack;
        stack.push(start_vertex);

        while ( !stack.empty() )
        {
            vertex_handle v = stack.top();
            stack.pop();

            data.set_visited(v, true);
            for (typename neighbor_container::const_iterator nit
                     = m_neighbors[v->id()].begin();
                 nit != m_neighbors[v->id()].end(); ++nit)
            {
                if ( static_cast<signed_size_type>((*nit)->id()) != data.parent_id(v) )
                {
                    if ( data.visited(*nit) )
                    {
                        return true;
                    }
                    else
                    {
                        data.set_parent_id(*nit, static_cast<signed_size_type>(v->id()));
                        stack.push(*nit);
                    }
                }
            }
        }
        return false;
    }

public:
    // num_rings: total number of rings, including the exterior ring
    complement_graph(std::size_t num_rings)
        : m_num_rings(num_rings)
        , m_num_turns(0)
        , m_vertices()
        , m_neighbors(num_rings)
    {}

    // inserts a ring vertex in the graph and returns its handle
    // ring id's are zero-based (so the first interior ring has id 1)
    inline vertex_handle add_vertex(signed_size_type id)
    {
        return m_vertices.insert(vertex(static_cast<std::size_t>(id))).first;
    }

    // inserts an IP in the graph and returns its id
    inline vertex_handle add_vertex(TurnPoint const& turn_point)
    {
        std::pair<vertex_handle, bool> res
            = m_vertices.insert(vertex(boost::addressof(turn_point),
                                       m_num_rings + m_num_turns)
                                );

        if ( res.second )
        {
            // a new element is inserted
            m_neighbors.push_back(neighbor_container());
            ++m_num_turns;
        }
        return res.first;
    }

    inline void add_edge(vertex_handle v1, vertex_handle v2)
    {
        BOOST_GEOMETRY_ASSERT( v1 != m_vertices.end() );
        BOOST_GEOMETRY_ASSERT( v2 != m_vertices.end() );
        m_neighbors[v1->id()].insert(v2);
        m_neighbors[v2->id()].insert(v1);
    }

    inline bool has_cycles() const
    {
        // initialize all vertices as non-visited and with no parent set
        // this is done by the constructor of has_cycles_dfs_data
        has_cycles_dfs_data data(m_num_rings + m_num_turns);

        // for each non-visited vertex, start a DFS from that vertex
        for (vertex_handle it = m_vertices.begin();
             it != m_vertices.end(); ++it)
        {
            if ( !data.visited(it) && has_cycles(it, data) )
            {
                return true;
            }
        }
        return false;
    }

#ifdef BOOST_GEOMETRY_TEST_DEBUG
    template <typename OStream, typename TP>
    friend inline
    void debug_print_complement_graph(OStream&, complement_graph<TP> const&);
#endif // BOOST_GEOMETRY_TEST_DEBUG

private:
    std::size_t m_num_rings, m_num_turns;
    vertex_container m_vertices;
    std::vector<neighbor_container> m_neighbors;
};


}} // namespace detail::is_valid

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_COMPLEMENT_GRAPH_HPP

/* complement_graph.hpp
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
*/