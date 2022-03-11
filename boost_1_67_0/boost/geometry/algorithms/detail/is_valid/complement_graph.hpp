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