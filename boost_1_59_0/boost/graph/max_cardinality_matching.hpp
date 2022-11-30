//=======================================================================
// Copyright (c) 2005 Aaron Windsor
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//=======================================================================

#ifndef BOOST_GRAPH_MAXIMUM_CARDINALITY_MATCHING_HPP
#define BOOST_GRAPH_MAXIMUM_CARDINALITY_MATCHING_HPP

#include <vector>
#include <list>
#include <deque>
#include <algorithm> // for std::sort and std::stable_sort
#include <utility> // for std::pair
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/pending/disjoint_sets.hpp>
#include <boost/assert.hpp>

namespace boost
{
namespace graph
{
    namespace detail
    {
        enum VERTEX_STATE
        {
            V_EVEN,
            V_ODD,
            V_UNREACHED
        };
    }
} // end namespace graph::detail

template < typename Graph, typename MateMap, typename VertexIndexMap >
typename graph_traits< Graph >::vertices_size_type matching_size(
    const Graph& g, MateMap mate, VertexIndexMap vm)
{
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator_t;
    typedef
        typename graph_traits< Graph >::vertex_descriptor vertex_descriptor_t;
    typedef typename graph_traits< Graph >::vertices_size_type v_size_t;

    v_size_t size_of_matching = 0;
    vertex_iterator_t vi, vi_end;

    for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
    {
        vertex_descriptor_t v = *vi;
        if (get(mate, v) != graph_traits< Graph >::null_vertex()
            && get(vm, v) < get(vm, get(mate, v)))
            ++size_of_matching;
    }
    return size_of_matching;
}

template < typename Graph, typename MateMap >
inline typename graph_traits< Graph >::vertices_size_type matching_size(
    const Graph& g, MateMap mate)
{
    return matching_size(g, mate, get(vertex_index, g));
}

template < typename Graph, typename MateMap, typename VertexIndexMap >
bool is_a_matching(const Graph& g, MateMap mate, VertexIndexMap)
{
    typedef
        typename graph_traits< Graph >::vertex_descriptor vertex_descriptor_t;
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator_t;

    vertex_iterator_t vi, vi_end;
    for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
    {
        vertex_descriptor_t v = *vi;
        if (get(mate, v) != graph_traits< Graph >::null_vertex()
            && v != get(mate, get(mate, v)))
            return false;
    }
    return true;
}

template < typename Graph, typename MateMap >
inline bool is_a_matching(const Graph& g, MateMap mate)
{
    return is_a_matching(g, mate, get(vertex_index, g));
}

//***************************************************************************
//***************************************************************************
//               Maximum Cardinality Matching Functors
//***************************************************************************
//***************************************************************************

template < typename Graph, typename MateMap,
    typename VertexIndexMap = dummy_property_map >
struct no_augmenting_path_finder
{
    no_augmenting_path_finder(const Graph&, MateMap, VertexIndexMap) {}

    inline bool augment_matching() { return false; }

    template < typename PropertyMap > void get_current_matching(PropertyMap) {}
};

template < typename Graph, typename MateMap, typename VertexIndexMap >
class edmonds_augmenting_path_finder
{
    // This implementation of Edmonds' matching algorithm closely
    // follows Tarjan's description of the algorithm in "Data
    // Structures and Network Algorithms."

public:
    // generates the type of an iterator property map from vertices to type X
    template < typename X > struct map_vertex_to_
    {
        typedef boost::iterator_property_map<
            typename std::vector< X >::iterator, VertexIndexMap >
            type;
    };

    typedef
        typename graph_traits< Graph >::vertex_descriptor vertex_descriptor_t;
    typedef typename std::pair< vertex_descriptor_t, vertex_descriptor_t >
        vertex_pair_t;
    typedef typename graph_traits< Graph >::edge_descriptor edge_descriptor_t;
    typedef typename graph_traits< Graph >::vertices_size_type v_size_t;
    typedef typename graph_traits< Graph >::edges_size_type e_size_t;
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator_t;
    typedef
        typename graph_traits< Graph >::out_edge_iterator out_edge_iterator_t;
    typedef typename std::deque< vertex_descriptor_t > vertex_list_t;
    typedef typename std::vector< edge_descriptor_t > edge_list_t;
    typedef typename map_vertex_to_< vertex_descriptor_t >::type
        vertex_to_vertex_map_t;
    typedef typename map_vertex_to_< int >::type vertex_to_int_map_t;
    typedef typename map_vertex_to_< vertex_pair_t >::type
        vertex_to_vertex_pair_map_t;
    typedef typename map_vertex_to_< v_size_t >::type vertex_to_vsize_map_t;
    typedef typename map_vertex_to_< e_size_t >::type vertex_to_esize_map_t;

    edmonds_augmenting_path_finder(
        const Graph& arg_g, MateMap arg_mate, VertexIndexMap arg_vm)
    : g(arg_g)
    , vm(arg_vm)
    , n_vertices(num_vertices(arg_g))
    ,

        mate_vector(n_vertices)
    , ancestor_of_v_vector(n_vertices)
    , ancestor_of_w_vector(n_vertices)
    , vertex_state_vector(n_vertices)
    , origin_vector(n_vertices)
    , pred_vector(n_vertices)
    , bridge_vector(n_vertices)
    , ds_parent_vector(n_vertices)
    , ds_rank_vector(n_vertices)
    ,

        mate(mate_vector.begin(), vm)
    , ancestor_of_v(ancestor_of_v_vector.begin(), vm)
    , ancestor_of_w(ancestor_of_w_vector.begin(), vm)
    , vertex_state(vertex_state_vector.begin(), vm)
    , origin(origin_vector.begin(), vm)
    , pred(pred_vector.begin(), vm)
    , bridge(bridge_vector.begin(), vm)
    , ds_parent_map(ds_parent_vector.begin(), vm)
    , ds_rank_map(ds_rank_vector.begin(), vm)
    ,

        ds(ds_rank_map, ds_parent_map)
    {
        vertex_iterator_t vi, vi_end;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
            mate[*vi] = get(arg_mate, *vi);
    }

    bool augment_matching()
    {
        // As an optimization, some of these values can be saved from one
        // iteration to the next instead of being re-initialized each
        // iteration, allowing for "lazy blossom expansion." This is not
        // currently implemented.

        e_size_t timestamp = 0;
        even_edges.clear();

        vertex_iterator_t vi, vi_end;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
        {
            vertex_descriptor_t u = *vi;

            origin[u] = u;
            pred[u] = u;
            ancestor_of_v[u] = 0;
            ancestor_of_w[u] = 0;
            ds.make_set(u);

            if (mate[u] == graph_traits< Graph >::null_vertex())
            {
                vertex_state[u] = graph::detail::V_EVEN;
                out_edge_iterator_t ei, ei_end;
                for (boost::tie(ei, ei_end) = out_edges(u, g); ei != ei_end;
                     ++ei)
                {
                    if (target(*ei, g) != u)
                    {
                        even_edges.push_back(*ei);
                    }
                }
            }
            else
                vertex_state[u] = graph::detail::V_UNREACHED;
        }

        // end initializations

        vertex_descriptor_t v, w, w_free_ancestor, v_free_ancestor;
        w_free_ancestor = graph_traits< Graph >::null_vertex();
        v_free_ancestor = graph_traits< Graph >::null_vertex();
        bool found_alternating_path = false;

        while (!even_edges.empty() && !found_alternating_path)
        {
            // since we push even edges onto the back of the list as
            // they're discovered, taking them off the back will search
            // for augmenting paths depth-first.
            edge_descriptor_t current_edge = even_edges.back();
            even_edges.pop_back();

            v = source(current_edge, g);
            w = target(current_edge, g);

            vertex_descriptor_t v_prime = origin[ds.find_set(v)];
            vertex_descriptor_t w_prime = origin[ds.find_set(w)];

            // because of the way we put all of the edges on the queue,
            // v_prime should be labeled V_EVEN; the following is a
            // little paranoid but it could happen...
            if (vertex_state[v_prime] != graph::detail::V_EVEN)
            {
                std::swap(v_prime, w_prime);
                std::swap(v, w);
            }

            if (vertex_state[w_prime] == graph::detail::V_UNREACHED)
            {
                vertex_state[w_prime] = graph::detail::V_ODD;
                vertex_descriptor_t w_prime_mate = mate[w_prime];
                vertex_state[w_prime_mate] = graph::detail::V_EVEN;
                out_edge_iterator_t ei, ei_end;
                for (boost::tie(ei, ei_end) = out_edges(w_prime_mate, g);
                     ei != ei_end; ++ei)
                {
                    if (target(*ei, g) != w_prime_mate)
                    {
                        even_edges.push_back(*ei);
                    }
                }
                pred[w_prime] = v;
            }

            // w_prime == v_prime can happen below if we get an edge that has
            // been shrunk into a blossom
            else if (vertex_state[w_prime] == graph::detail::V_EVEN
                && w_prime != v_prime)
            {
                vertex_descriptor_t w_up = w_prime;
                vertex_descriptor_t v_up = v_prime;
                vertex_descriptor_t nearest_common_ancestor
                    = graph_traits< Graph >::null_vertex();
                w_free_ancestor = graph_traits< Graph >::null_vertex();
                v_free_ancestor = graph_traits< Graph >::null_vertex();

                // We now need to distinguish between the case that
                // w_prime and v_prime share an ancestor under the
                // "parent" relation, in which case we've found a
                // blossom and should shrink it, or the case that
                // w_prime and v_prime both have distinct ancestors that
                // are free, in which case we've found an alternating
                // path between those two ancestors.

                ++timestamp;

                while (nearest_common_ancestor
                        == graph_traits< Graph >::null_vertex()
                    && (v_free_ancestor == graph_traits< Graph >::null_vertex()
                        || w_free_ancestor
                            == graph_traits< Graph >::null_vertex()))
                {
                    ancestor_of_w[w_up] = timestamp;
                    ancestor_of_v[v_up] = timestamp;

                    if (w_free_ancestor == graph_traits< Graph >::null_vertex())
                        w_up = parent(w_up);
                    if (v_free_ancestor == graph_traits< Graph >::null_vertex())
                        v_up = parent(v_up);

                    if (mate[v_up] == graph_traits< Graph >::null_vertex())
                        v_free_ancestor = v_up;
                    if (mate[w_up] == graph_traits< Graph >::null_vertex())
                        w_free_ancestor = w_up;

                    if (ancestor_of_w[v_up] == timestamp)
                        nearest_common_ancestor = v_up;
                    else if (ancestor_of_v[w_up] == timestamp)
                        nearest_common_ancestor = w_up;
                    else if (v_free_ancestor == w_free_ancestor
                        && v_free_ancestor
                            != graph_traits< Graph >::null_vertex())
                        nearest_common_ancestor = v_up;
                }

                if (nearest_common_ancestor
                    == graph_traits< Graph >::null_vertex())
                    found_alternating_path = true; // to break out of the loop
                else
                {
                    // shrink the blossom
                    link_and_set_bridges(
                        w_prime, nearest_common_ancestor, std::make_pair(w, v));
                    link_and_set_bridges(
                        v_prime, nearest_common_ancestor, std::make_pair(v, w));
                }
            }
        }

        if (!found_alternating_path)
            return false;

        // retrieve the augmenting path and put it in aug_path
        reversed_retrieve_augmenting_path(v, v_free_ancestor);
        retrieve_augmenting_path(w, w_free_ancestor);

        // augment the matching along aug_path
        vertex_descriptor_t a, b;
        while (!aug_path.empty())
        {
            a = aug_path.front();
            aug_path.pop_front();
            b = aug_path.front();
            aug_path.pop_front();
            mate[a] = b;
            mate[b] = a;
        }

        return true;
    }

    template < typename PropertyMap > void get_current_matching(PropertyMap pm)
    {
        vertex_iterator_t vi, vi_end;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
            put(pm, *vi, mate[*vi]);
    }

    template < typename PropertyMap > void get_vertex_state_map(PropertyMap pm)
    {
        vertex_iterator_t vi, vi_end;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
            put(pm, *vi, vertex_state[origin[ds.find_set(*vi)]]);
    }

private:
    vertex_descriptor_t parent(vertex_descriptor_t x)
    {
        if (vertex_state[x] == graph::detail::V_EVEN
            && mate[x] != graph_traits< Graph >::null_vertex())
            return mate[x];
        else if (vertex_state[x] == graph::detail::V_ODD)
            return origin[ds.find_set(pred[x])];
        else
            return x;
    }

    void link_and_set_bridges(vertex_descriptor_t x,
        vertex_descriptor_t stop_vertex, vertex_pair_t the_bridge)
    {
        for (vertex_descriptor_t v = x; v != stop_vertex; v = parent(v))
        {
            ds.union_set(v, stop_vertex);
            origin[ds.find_set(stop_vertex)] = stop_vertex;

            if (vertex_state[v] == graph::detail::V_ODD)
            {
                bridge[v] = the_bridge;
                out_edge_iterator_t oei, oei_end;
                for (boost::tie(oei, oei_end) = out_edges(v, g); oei != oei_end;
                     ++oei)
                {
                    if (target(*oei, g) != v)
                    {
                        even_edges.push_back(*oei);
                    }
                }
            }
        }
    }

    // Since none of the STL containers support both constant-time
    // concatenation and reversal, the process of expanding an
    // augmenting path once we know one exists is a little more
    // complicated than it has to be. If we know the path is from v to
    // w, then the augmenting path is recursively defined as:
    //
    // path(v,w) = [v], if v = w
    //           = concat([v, mate[v]], path(pred[mate[v]], w),
    //                if v != w and vertex_state[v] == graph::detail::V_EVEN
    //           = concat([v], reverse(path(x,mate[v])), path(y,w)),
    //                if v != w, vertex_state[v] == graph::detail::V_ODD, and
    //                bridge[v] = (x,y)
    //
    // These next two mutually recursive functions implement this definition.

    void retrieve_augmenting_path(vertex_descriptor_t v, vertex_descriptor_t w)
    {
        if (v == w)
            aug_path.push_back(v);
        else if (vertex_state[v] == graph::detail::V_EVEN)
        {
            aug_path.push_back(v);
            aug_path.push_back(mate[v]);
            retrieve_augmenting_path(pred[mate[v]], w);
        }
        else // vertex_state[v] == graph::detail::V_ODD
        {
            aug_path.push_back(v);
            reversed_retrieve_augmenting_path(bridge[v].first, mate[v]);
            retrieve_augmenting_path(bridge[v].second, w);
        }
    }

    void reversed_retrieve_augmenting_path(
        vertex_descriptor_t v, vertex_descriptor_t w)
    {

        if (v == w)
            aug_path.push_back(v);
        else if (vertex_state[v] == graph::detail::V_EVEN)
        {
            reversed_retrieve_augmenting_path(pred[mate[v]], w);
            aug_path.push_back(mate[v]);
            aug_path.push_back(v);
        }
        else // vertex_state[v] == graph::detail::V_ODD
        {
            reversed_retrieve_augmenting_path(bridge[v].second, w);
            retrieve_augmenting_path(bridge[v].first, mate[v]);
            aug_path.push_back(v);
        }
    }

    // private data members

    const Graph& g;
    VertexIndexMap vm;
    v_size_t n_vertices;

    // storage for the property maps below
    std::vector< vertex_descriptor_t > mate_vector;
    std::vector< e_size_t > ancestor_of_v_vector;
    std::vector< e_size_t > ancestor_of_w_vector;
    std::vector< int > vertex_state_vector;
    std::vector< vertex_descriptor_t > origin_vector;
    std::vector< vertex_descriptor_t > pred_vector;
    std::vector< vertex_pair_t > bridge_vector;
    std::vector< vertex_descriptor_t > ds_parent_vector;
    std::vector< v_size_t > ds_rank_vector;

    // iterator property maps
    vertex_to_vertex_map_t mate;
    vertex_to_esize_map_t ancestor_of_v;
    vertex_to_esize_map_t ancestor_of_w;
    vertex_to_int_map_t vertex_state;
    vertex_to_vertex_map_t origin;
    vertex_to_vertex_map_t pred;
    vertex_to_vertex_pair_map_t bridge;
    vertex_to_vertex_map_t ds_parent_map;
    vertex_to_vsize_map_t ds_rank_map;

    vertex_list_t aug_path;
    edge_list_t even_edges;
    disjoint_sets< vertex_to_vsize_map_t, vertex_to_vertex_map_t > ds;
};

//***************************************************************************
//***************************************************************************
//               Initial Matching Functors
//***************************************************************************
//***************************************************************************

template < typename Graph, typename MateMap > struct greedy_matching
{
    typedef
        typename graph_traits< Graph >::vertex_descriptor vertex_descriptor_t;
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator_t;
    typedef typename graph_traits< Graph >::edge_descriptor edge_descriptor_t;
    typedef typename graph_traits< Graph >::edge_iterator edge_iterator_t;

    static void find_matching(const Graph& g, MateMap mate)
    {
        vertex_iterator_t vi, vi_end;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
            put(mate, *vi, graph_traits< Graph >::null_vertex());

        edge_iterator_t ei, ei_end;
        for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        {
            edge_descriptor_t e = *ei;
            vertex_descriptor_t u = source(e, g);
            vertex_descriptor_t v = target(e, g);

            if (u != v && get(mate, u) == get(mate, v))
            // only way equality can hold is if
            //   mate[u] == mate[v] == null_vertex
            {
                put(mate, u, v);
                put(mate, v, u);
            }
        }
    }
};

template < typename Graph, typename MateMap > struct extra_greedy_matching
{
    // The "extra greedy matching" is formed by repeating the
    // following procedure as many times as possible: Choose the
    // unmatched vertex v of minimum non-zero degree.  Choose the
    // neighbor w of v which is unmatched and has minimum degree over
    // all of v's neighbors. Add (u,v) to the matching. Ties for
    // either choice are broken arbitrarily. This procedure takes time
    // O(m log n), where m is the number of edges in the graph and n
    // is the number of vertices.

    typedef
        typename graph_traits< Graph >::vertex_descriptor vertex_descriptor_t;
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator_t;
    typedef typename graph_traits< Graph >::edge_descriptor edge_descriptor_t;
    typedef typename graph_traits< Graph >::edge_iterator edge_iterator_t;
    typedef std::pair< vertex_descriptor_t, vertex_descriptor_t > vertex_pair_t;

    struct select_first
    {
        inline static vertex_descriptor_t select_vertex(const vertex_pair_t p)
        {
            return p.first;
        }
    };

    struct select_second
    {
        inline static vertex_descriptor_t select_vertex(const vertex_pair_t p)
        {
            return p.second;
        }
    };

    template < class PairSelector > class less_than_by_degree
    {
    public:
        less_than_by_degree(const Graph& g) : m_g(g) {}
        bool operator()(const vertex_pair_t x, const vertex_pair_t y)
        {
            return out_degree(PairSelector::select_vertex(x), m_g)
                < out_degree(PairSelector::select_vertex(y), m_g);
        }

    private:
        const Graph& m_g;
    };

    static void find_matching(const Graph& g, MateMap mate)
    {
        typedef std::vector<
            std::pair< vertex_descriptor_t, vertex_descriptor_t > >
            directed_edges_vector_t;

        directed_edges_vector_t edge_list;
        vertex_iterator_t vi, vi_end;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
            put(mate, *vi, graph_traits< Graph >::null_vertex());

        edge_iterator_t ei, ei_end;
        for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        {
            edge_descriptor_t e = *ei;
            vertex_descriptor_t u = source(e, g);
            vertex_descriptor_t v = target(e, g);
            if (u == v)
                continue;
            edge_list.push_back(std::make_pair(u, v));
            edge_list.push_back(std::make_pair(v, u));
        }

        // sort the edges by the degree of the target, then (using a
        // stable sort) by degree of the source
        std::sort(edge_list.begin(), edge_list.end(),
            less_than_by_degree< select_second >(g));
        std::stable_sort(edge_list.begin(), edge_list.end(),
            less_than_by_degree< select_first >(g));

        // construct the extra greedy matching
        for (typename directed_edges_vector_t::const_iterator itr
             = edge_list.begin();
             itr != edge_list.end(); ++itr)
        {
            if (get(mate, itr->first) == get(mate, itr->second))
            // only way equality can hold is if mate[itr->first] ==
            // mate[itr->second] == null_vertex
            {
                put(mate, itr->first, itr->second);
                put(mate, itr->second, itr->first);
            }
        }
    }
};

template < typename Graph, typename MateMap > struct empty_matching
{
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator_t;

    static void find_matching(const Graph& g, MateMap mate)
    {
        vertex_iterator_t vi, vi_end;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
            put(mate, *vi, graph_traits< Graph >::null_vertex());
    }
};

//***************************************************************************
//***************************************************************************
//               Matching Verifiers
//***************************************************************************
//***************************************************************************

namespace detail
{

    template < typename SizeType >
    class odd_components_counter : public dfs_visitor<>
    // This depth-first search visitor will count the number of connected
    // components with an odd number of vertices. It's used by
    // maximum_matching_verifier.
    {
    public:
        odd_components_counter(SizeType& c_count) : m_count(c_count)
        {
            m_count = 0;
        }

        template < class Vertex, class Graph > void start_vertex(Vertex, Graph&)
        {
            m_parity = false;
        }

        template < class Vertex, class Graph >
        void discover_vertex(Vertex, Graph&)
        {
            m_parity = !m_parity;
            m_parity ? ++m_count : --m_count;
        }

    protected:
        SizeType& m_count;

    private:
        bool m_parity;
    };

} // namespace detail

template < typename Graph, typename MateMap,
    typename VertexIndexMap = dummy_property_map >
struct no_matching_verifier
{
    inline static bool verify_matching(const Graph&, MateMap, VertexIndexMap)
    {
        return true;
    }
};

template < typename Graph, typename MateMap, typename VertexIndexMap >
struct maximum_cardinality_matching_verifier
{

    template < typename X > struct map_vertex_to_
    {
        typedef boost::iterator_property_map<
            typename std::vector< X >::iterator, VertexIndexMap >
            type;
    };

    typedef
        typename graph_traits< Graph >::vertex_descriptor vertex_descriptor_t;
    typedef typename graph_traits< Graph >::vertices_size_type v_size_t;
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator_t;
    typedef typename map_vertex_to_< int >::type vertex_to_int_map_t;
    typedef typename map_vertex_to_< vertex_descriptor_t >::type
        vertex_to_vertex_map_t;

    template < typename VertexStateMap > struct non_odd_vertex
    {
        // this predicate is used to create a filtered graph that
        // excludes vertices labeled "graph::detail::V_ODD"
        non_odd_vertex() : vertex_state(0) {}

        non_odd_vertex(VertexStateMap* arg_vertex_state)
        : vertex_state(arg_vertex_state)
        {
        }

        template < typename Vertex > bool operator()(const Vertex& v) const
        {
            BOOST_ASSERT(vertex_state);
            return get(*vertex_state, v) != graph::detail::V_ODD;
        }

        VertexStateMap* vertex_state;
    };

    static bool verify_matching(const Graph& g, MateMap mate, VertexIndexMap vm)
    {
        // For any graph G, let o(G) be the number of connected
        // components in G of odd size. For a subset S of G's vertex set
        // V(G), let (G - S) represent the subgraph of G induced by
        // removing all vertices in S from G. Let M(G) be the size of the
        // maximum cardinality matching in G. Then the Tutte-Berge
        // formula guarantees that
        //
        //           2 * M(G) = min ( |V(G)| + |U| + o(G - U) )
        //
        // where the minimum is taken over all subsets U of
        // V(G). Edmonds' algorithm finds a set U that achieves the
        // minimum in the above formula, namely the vertices labeled
        //"ODD." This function runs one iteration of Edmonds' algorithm
        // to find U, then verifies that the size of the matching given
        // by mate satisfies the Tutte-Berge formula.

        // first, make sure it's a valid matching
        if (!is_a_matching(g, mate, vm))
            return false;

        // We'll try to augment the matching once. This serves two
        // purposes: first, if we find some augmenting path, the matching
        // is obviously non-maximum. Second, running edmonds' algorithm
        // on a graph with no augmenting path will create the
        // Edmonds-Gallai decomposition that we need as a certificate of
        // maximality - we can get it by looking at the vertex_state map
        // that results.
        edmonds_augmenting_path_finder< Graph, MateMap, VertexIndexMap >
            augmentor(g, mate, vm);
        if (augmentor.augment_matching())
            return false;

        std::vector< int > vertex_state_vector(num_vertices(g));
        vertex_to_int_map_t vertex_state(vertex_state_vector.begin(), vm);
        augmentor.get_vertex_state_map(vertex_state);

        // count the number of graph::detail::V_ODD vertices
        v_size_t num_odd_vertices = 0;
        vertex_iterator_t vi, vi_end;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
            if (vertex_state[*vi] == graph::detail::V_ODD)
                ++num_odd_vertices;

        // count the number of connected components with odd cardinality
        // in the graph without graph::detail::V_ODD vertices
        non_odd_vertex< vertex_to_int_map_t > filter(&vertex_state);
        filtered_graph< Graph, keep_all, non_odd_vertex< vertex_to_int_map_t > >
            fg(g, keep_all(), filter);

        v_size_t num_odd_components;
        detail::odd_components_counter< v_size_t > occ(num_odd_components);
        depth_first_search(fg, visitor(occ).vertex_index_map(vm));

        if (2 * matching_size(g, mate, vm)
            == num_vertices(g) + num_odd_vertices - num_odd_components)
            return true;
        else
            return false;
    }
};

template < typename Graph, typename MateMap, typename VertexIndexMap,
    template < typename, typename, typename > class AugmentingPathFinder,
    template < typename, typename > class InitialMatchingFinder,
    template < typename, typename, typename > class MatchingVerifier >
bool matching(const Graph& g, MateMap mate, VertexIndexMap vm)
{

    InitialMatchingFinder< Graph, MateMap >::find_matching(g, mate);

    AugmentingPathFinder< Graph, MateMap, VertexIndexMap > augmentor(
        g, mate, vm);
    bool not_maximum_yet = true;
    while (not_maximum_yet)
    {
        not_maximum_yet = augmentor.augment_matching();
    }
    augmentor.get_current_matching(mate);

    return MatchingVerifier< Graph, MateMap, VertexIndexMap >::verify_matching(
        g, mate, vm);
}

template < typename Graph, typename MateMap, typename VertexIndexMap >
inline bool checked_edmonds_maximum_cardinality_matching(
    const Graph& g, MateMap mate, VertexIndexMap vm)
{
    return matching< Graph, MateMap, VertexIndexMap,
        edmonds_augmenting_path_finder, extra_greedy_matching,
        maximum_cardinality_matching_verifier >(g, mate, vm);
}

template < typename Graph, typename MateMap >
inline bool checked_edmonds_maximum_cardinality_matching(
    const Graph& g, MateMap mate)
{
    return checked_edmonds_maximum_cardinality_matching(
        g, mate, get(vertex_index, g));
}

template < typename Graph, typename MateMap, typename VertexIndexMap >
inline void edmonds_maximum_cardinality_matching(
    const Graph& g, MateMap mate, VertexIndexMap vm)
{
    matching< Graph, MateMap, VertexIndexMap, edmonds_augmenting_path_finder,
        extra_greedy_matching, no_matching_verifier >(g, mate, vm);
}

template < typename Graph, typename MateMap >
inline void edmonds_maximum_cardinality_matching(const Graph& g, MateMap mate)
{
    edmonds_maximum_cardinality_matching(g, mate, get(vertex_index, g));
}

} // namespace boost

#endif // BOOST_GRAPH_MAXIMUM_CARDINALITY_MATCHING_HPP

/* max_cardinality_matching.hpp
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
*/