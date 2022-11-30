//=======================================================================
// Copyright 2007 Aaron Windsor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef __IS_KURATOWSKI_SUBGRAPH_HPP__
#define __IS_KURATOWSKI_SUBGRAPH_HPP__

#include <boost/config.hpp>
#include <boost/tuple/tuple.hpp> //for tie
#include <boost/property_map/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/isomorphism.hpp>
#include <boost/graph/adjacency_list.hpp>

#include <algorithm>
#include <vector>
#include <set>

namespace boost
{

namespace detail
{

    template < typename Graph > Graph make_K_5()
    {
        typename graph_traits< Graph >::vertex_iterator vi, vi_end, inner_vi;
        Graph K_5(5);
        for (boost::tie(vi, vi_end) = vertices(K_5); vi != vi_end; ++vi)
            for (inner_vi = next(vi); inner_vi != vi_end; ++inner_vi)
                add_edge(*vi, *inner_vi, K_5);
        return K_5;
    }

    template < typename Graph > Graph make_K_3_3()
    {
        typename graph_traits< Graph >::vertex_iterator vi, vi_end,
            bipartition_start, inner_vi;
        Graph K_3_3(6);
        bipartition_start = next(next(next(vertices(K_3_3).first)));
        for (boost::tie(vi, vi_end) = vertices(K_3_3); vi != bipartition_start;
             ++vi)
            for (inner_vi = bipartition_start; inner_vi != vi_end; ++inner_vi)
                add_edge(*vi, *inner_vi, K_3_3);
        return K_3_3;
    }

    template < typename AdjacencyList, typename Vertex >
    void contract_edge(AdjacencyList& neighbors, Vertex u, Vertex v)
    {
        // Remove u from v's neighbor list
        neighbors[v].erase(
            std::remove(neighbors[v].begin(), neighbors[v].end(), u),
            neighbors[v].end());

        // Replace any references to u with references to v
        typedef
            typename AdjacencyList::value_type::iterator adjacency_iterator_t;

        adjacency_iterator_t u_neighbor_end = neighbors[u].end();
        for (adjacency_iterator_t u_neighbor_itr = neighbors[u].begin();
             u_neighbor_itr != u_neighbor_end; ++u_neighbor_itr)
        {
            Vertex u_neighbor(*u_neighbor_itr);
            std::replace(neighbors[u_neighbor].begin(),
                neighbors[u_neighbor].end(), u, v);
        }

        // Remove v from u's neighbor list
        neighbors[u].erase(
            std::remove(neighbors[u].begin(), neighbors[u].end(), v),
            neighbors[u].end());

        // Add everything in u's neighbor list to v's neighbor list
        std::copy(neighbors[u].begin(), neighbors[u].end(),
            std::back_inserter(neighbors[v]));

        // Clear u's neighbor list
        neighbors[u].clear();
    }

    enum target_graph_t
    {
        tg_k_3_3,
        tg_k_5
    };

} // namespace detail

template < typename Graph, typename ForwardIterator, typename VertexIndexMap >
bool is_kuratowski_subgraph(const Graph& g, ForwardIterator begin,
    ForwardIterator end, VertexIndexMap vm)
{

    typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator_t;
    typedef typename graph_traits< Graph >::edge_descriptor edge_t;
    typedef typename graph_traits< Graph >::edges_size_type e_size_t;
    typedef typename graph_traits< Graph >::vertices_size_type v_size_t;
    typedef typename std::vector< vertex_t > v_list_t;
    typedef typename v_list_t::iterator v_list_iterator_t;
    typedef iterator_property_map< typename std::vector< v_list_t >::iterator,
        VertexIndexMap >
        vertex_to_v_list_map_t;

    typedef adjacency_list< vecS, vecS, undirectedS > small_graph_t;

    detail::target_graph_t target_graph
        = detail::tg_k_3_3; // unless we decide otherwise later

    static small_graph_t K_5(detail::make_K_5< small_graph_t >());

    static small_graph_t K_3_3(detail::make_K_3_3< small_graph_t >());

    v_size_t n_vertices(num_vertices(g));
    v_size_t max_num_edges(3 * n_vertices - 5);

    std::vector< v_list_t > neighbors_vector(n_vertices);
    vertex_to_v_list_map_t neighbors(neighbors_vector.begin(), vm);

    e_size_t count = 0;
    for (ForwardIterator itr = begin; itr != end; ++itr)
    {

        if (count++ > max_num_edges)
            return false;

        edge_t e(*itr);
        vertex_t u(source(e, g));
        vertex_t v(target(e, g));

        neighbors[u].push_back(v);
        neighbors[v].push_back(u);
    }

    for (v_size_t max_size = 2; max_size < 5; ++max_size)
    {

        vertex_iterator_t vi, vi_end;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
        {
            vertex_t v(*vi);

            // a hack to make sure we don't contract the middle edge of a path
            // of four degree-3 vertices
            if (max_size == 4 && neighbors[v].size() == 3)
            {
                if (neighbors[neighbors[v][0]].size()
                        + neighbors[neighbors[v][1]].size()
                        + neighbors[neighbors[v][2]].size()
                    < 11 // so, it has two degree-3 neighbors
                )
                    continue;
            }

            while (neighbors[v].size() > 0 && neighbors[v].size() < max_size)
            {
                // Find one of v's neighbors u such that v and u
                // have no neighbors in common. We'll look for such a
                // neighbor with a naive cubic-time algorithm since the
                // max size of any of the neighbor sets we'll consider
                // merging is 3

                bool neighbor_sets_intersect = false;

                vertex_t min_u = graph_traits< Graph >::null_vertex();
                vertex_t u;
                v_list_iterator_t v_neighbor_end = neighbors[v].end();
                for (v_list_iterator_t v_neighbor_itr = neighbors[v].begin();
                     v_neighbor_itr != v_neighbor_end; ++v_neighbor_itr)
                {
                    neighbor_sets_intersect = false;
                    u = *v_neighbor_itr;
                    v_list_iterator_t u_neighbor_end = neighbors[u].end();
                    for (v_list_iterator_t u_neighbor_itr
                         = neighbors[u].begin();
                         u_neighbor_itr != u_neighbor_end
                         && !neighbor_sets_intersect;
                         ++u_neighbor_itr)
                    {
                        for (v_list_iterator_t inner_v_neighbor_itr
                             = neighbors[v].begin();
                             inner_v_neighbor_itr != v_neighbor_end;
                             ++inner_v_neighbor_itr)
                        {
                            if (*u_neighbor_itr == *inner_v_neighbor_itr)
                            {
                                neighbor_sets_intersect = true;
                                break;
                            }
                        }
                    }
                    if (!neighbor_sets_intersect
                        && (min_u == graph_traits< Graph >::null_vertex()
                            || neighbors[u].size() < neighbors[min_u].size()))
                    {
                        min_u = u;
                    }
                }

                if (min_u == graph_traits< Graph >::null_vertex())
                    // Exited the loop without finding an appropriate neighbor
                    // of v, so v must be a lost cause. Move on to other
                    // vertices.
                    break;
                else
                    u = min_u;

                detail::contract_edge(neighbors, u, v);

            } // end iteration over v's neighbors

        } // end iteration through vertices v

        if (max_size == 3)
        {
            // check to see whether we should go on to find a K_5
            for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
                if (neighbors[*vi].size() == 4)
                {
                    target_graph = detail::tg_k_5;
                    break;
                }

            if (target_graph == detail::tg_k_3_3)
                break;
        }

    } // end iteration through max degree 2,3, and 4

    // Now, there should only be 5 or 6 vertices with any neighbors. Find them.

    v_list_t main_vertices;
    vertex_iterator_t vi, vi_end;

    for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
    {
        if (!neighbors[*vi].empty())
            main_vertices.push_back(*vi);
    }

    // create a graph isomorphic to the contracted graph to test
    // against K_5 and K_3_3
    small_graph_t contracted_graph(main_vertices.size());
    std::map< vertex_t,
        typename graph_traits< small_graph_t >::vertex_descriptor >
        contracted_vertex_map;

    typename v_list_t::iterator itr, itr_end;
    itr_end = main_vertices.end();
    typename graph_traits< small_graph_t >::vertex_iterator si
        = vertices(contracted_graph).first;

    for (itr = main_vertices.begin(); itr != itr_end; ++itr, ++si)
    {
        contracted_vertex_map[*itr] = *si;
    }

    typename v_list_t::iterator jtr, jtr_end;
    for (itr = main_vertices.begin(); itr != itr_end; ++itr)
    {
        jtr_end = neighbors[*itr].end();
        for (jtr = neighbors[*itr].begin(); jtr != jtr_end; ++jtr)
        {
            if (get(vm, *itr) < get(vm, *jtr))
            {
                add_edge(contracted_vertex_map[*itr],
                    contracted_vertex_map[*jtr], contracted_graph);
            }
        }
    }

    if (target_graph == detail::tg_k_5)
    {
        return boost::isomorphism(K_5, contracted_graph);
    }
    else // target_graph == tg_k_3_3
    {
        return boost::isomorphism(K_3_3, contracted_graph);
    }
}

template < typename Graph, typename ForwardIterator >
bool is_kuratowski_subgraph(
    const Graph& g, ForwardIterator begin, ForwardIterator end)
{
    return is_kuratowski_subgraph(g, begin, end, get(vertex_index, g));
}

}

#endif //__IS_KURATOWSKI_SUBGRAPH_HPP__

/* is_kuratowski_subgraph.hpp
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
*/