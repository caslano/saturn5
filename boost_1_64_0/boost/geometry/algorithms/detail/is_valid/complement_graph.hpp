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
GSiNqZD8ZHCn4HsCTgMq4/ZzPmORzYMTzetwfdMQ3eXzvcyRdchr0QKf4nLquCinwy+wOHnRHF/FFT19kPGma1QXMidao/owY9EaVSwjtnd/9zdzpJ74Du0lhDsPy+Xto/Rdt+XDieoW38xnu63Xkshuh9lu5T16Lo+jw1tGRk1vL+6nnScx9vFd3MtlXJry8Tr8TIyRepQ+nzn83hOvLUQc6hAF54pIlhwj6Bz2sVkXnws44VskXwgwuVbF+roSHF7rpfRlfV8KHN4WAfKecPKJOHnaaufxqyM8fMfraxEe3oXz9SzObmjTPJAbyvj1EU4um9/bDj/VfKymhH28Jg2r58cmi9G+0d9gzjPVQ66nUhpHHDU8X8b4JsboXY9HsH+prqwv7TxCe+f9bNs25Unr4ERc22tb033xXHZZlX0D2ZG4uKj5vqgbm3HZv+C392Iu2gFP7/t9DyqPBuYurZtVjtuWxDK/G/MSTeb3VV4o8wcah2XyHk3Lm+6L7xX9MWPqvaLXLnN4fDfoTzhu07tBb1c57Kvr6eh3g341yks014zyKPdcKfuP7lB54RnpX2gc5Yz0nRqPh/D0viI4fz4EczxmvtbuNXrQhi0WYf+yYatMWNv7j/ASY9SeX6t+5x4mndu13tKE3KPz72DeRF48QHajc8Jz3P+ROM/5R/d5/Ffn0fYh7gOgEJ1HrxTR5NaSSLbOJReI63mv/7F3JfBxFlU8IKIiIpQSpGqtlbZQaJqkaZr0gKbJtl2bJjGbpq1G1s3uJlmy+XbZbzdNwYJ44X3feB+oeCuoiHgr3veteKPiDeKt6Jvvzcx7883bJIv+1J+2v19IeP//HN+bN2/uGSFumgOnPBxbl4dZqM7RmsJdZK65W6aqdLV2AR3Ugsi7w+zlQvpqQ30x3nFS+jS/atO+q8fz5+0N93iP68/dG+7dPK4/f9+yGC6bb109L59sdO28dkAmA7qgdV5xrQhbuEgHi+DhjC7Z1T3EfNKcbgvFKfPKoKaCf//dCVK8NMdLeZV5fJ7Xck/0uP46hOHeS+Ty+d4Fvw06ZGTe5A/ksqW5XcrvSSJPnt892ecW+JvIp/g4OG/S46kebuasIZ4pSJHthTjN54ZQl721ydPr8KCLl+e8MyQe+Sar5/vW4WkV2zO8a+fnU6EsIm79AK55CIHuFBL57v2vMkeumw+QuDTeoPVjiUfrLPPzeF1fBC9e11cKXKrrxDtT4tH4zPJWeTx5rWSNyMNB8vxxoWnwNM8WeFLdO0fm8bpH944uob28pnQxd9QXWddFHMQoT+sNRvNxaPvQn6uwOxxaLW9GxQAd3QubDNZuMIPwNyniGBSZs3+o0x/34LiN8PFaoWgqgZHfH+S2saX4YI4D5aCx4gRe3JWLp4cNX6YGtwIXYdsFnSPkOOYE9czlmA8+42bDLiMOZIr039nF5Po7DLaJY9E2VNJ5N8ew4Oj9GYspj0btDX2ng5ehXJ25wS0UPl9UxyEyoTNe3mbxqZJ6r8XXT4G/Awv5Ibmu6RZbasJgNjGc9/2QQ10cyz0Meh4TtH/fKxPchIw3T4Byq2i3xGGdIp72+SZ+U+1F/VEHSc432JjOd7OnC3QBJkwPyFVJZqZBRxGBvdOrMfjJlRGkd3oRI5vTG4WMHnYBzsKpOLQ9UHkmgYOW0p7j5bzHyDFKK9+r5fD50bwUlT/Kjdcy8sEu/b44pmy/+SEg1x0ntDR+DphhYRb3Ktl33jnG9LQf5RgXIPQtuB+JOl8QRpSrQOwcM8RXsJrL4RkQ+lZ6Uxe/15bJQyEc67yh+vjZw04HDyFVer8LMDVyTcPouziecdbCL+iKxrp9SZjxGhpMDuA=
*/