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