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
HUCrXGJWF8qywF4uWhaR/wpon92evLE7du9fM0M/L6cbSX57LWouo4QOTUSLOXwLm+3UwprXHpne8pX2TniW8gEcCR6yGdikphuJGdaxYPc0c6ZAL7dG1ug+ERxO7ZbdugiWrwkXCtNsyql9gcdJRrS7qA65PniSxG6V1+gaVOt5h2Y4NO1U2KA2JQmOhp1DpzjmxuvRla6mTupKjvJX4u5xosV83OsplKrBIrqbWRK6EqFAfxBnaK8iak+Y7hkq/j1nv8IjeivlaZhV4Qr9UtzIC0kaMMJL/jhtQpj7a4762xau8AdbzqEAeyK3jN9kJ6E+zaM28jAsAT08RxfCucyPyRKl8ToeY39HF25K3IM/uIHI/AqPA/aOtvO/4tbKuFtMShN3pYwNKFPphO9rQHBJvb5bpUnfl6VIXSLA/uq9JIzxJ1JIRouSkZaPdreFfN1ntz3BTw+BxOChfvd62ucgq9D4byXwIEa3J2csB33PLiKpxPpOewqcwdTCNsHcnlIMx+5/SqQn+Xqh3cW3Wc3F8FzXf+/qN2ZZgPLnzCgmr6HOQK5wOUvPz9IpZodGzsDjjp7SivlcmyC2rge6YlmS2Pot+JWOiK0/x3ej2Poc3iLtdyplZ6gvvEEFXY8Ox/3fKbYj5FR7KvTyq83j2bLY/CTGowjbjlAHafPFjj5x9/7AR0lvGEKfmI4OqJXzzvDGIvnP0FXT4ZzTJKzY+pWyg9K4GDiEJZh+ha2/eVkC0+prvj/Bl9V+nbj7gNhxFCp6FyuGuo79Vdy9et6Z4EnZXAJ55DOknJfKOTm9wKEN/13Xkz+OFO0PKcHUT/ZJkYbEd3C2MMKQWRF2wKYO+I8AkPR9DZsppM3E2oAGOg6EzpvE3ZWzzgRP+ay9SQm0pZNDyZibvkuRTQKmsSJD6AvP3y/5D4pPLUM4X8yrAjoaqlsIvXL/PaY7bEUSjPKr40/r/t6gq6dpNBIyP8y1YyfxxOHruhpIoIedFel9Ou4iDhg0xghpv3t6OpdG13sJ1UhCdx4ZOac9OVFc66oJ6YIs6CZL58+jeR8AMWct0tN4+RW2DeOj9ttzjK2N5FZNiMGQgbpClAeB7sNhti2kjnS1sK2f6aaeAboQbxuVqgiVzwX8/Qm+xRh22oWEUvaJCpW7D8iMwd+jqPKMqRcVb1xoAI9HVkMPhhekU/67xN2cpAqSUnZEsg3IyUVDv2b8UTt3X16KLzVvli+pWPqicWSIl74Qn2mnwavPwD5Bg8PgaXkFsQ3fi3SzGLie+qM9Tm031aUJbvt6Q4X2l4+mj2qIbgsgxEaxC/KwPprzGH+BfJF9wW360An85xntX16gtOFtMvY5plRaFVHk2AScF6CIuDvjvl7uvoR2Q96XfWvybvCtov5wm5aTXvTFKlSgN1zg1IDcUmwDUdcgUyvH+MvUktg1AiBzQC0bBEbvCGSK5wAYJEVRLXe0LeO+YuCGA5dT5DSY8Vk05Nr5HyK0Hpp18fSNp1v+OkadEaYoVQPQw/O+ST1k2YhiJGXHgSE+1xnHZjP1Gyl99zleGOC9R3ta636x9SXKwfG+GwIRiw9aFPBatWsE9uaQ0GX5Hfwkdh2Bt+bxJXJGe7mheXyzL7F5fK0sQl6U3NFMgV6juHu+k0w7WORAaNzULhhgV7ae9N2+Q9zpF8SOH9uhrmLTJch9rcytJ+UPGNY0UqOndRTOTdFjSNujcLoVL2zbza3dLIxXYBwHMD41gF1sALvYAHbhAHR8mfdVmS/WFXeb71si39BebMjb7OPypka0Kz4isxNVGOKd3Ec7OZuN6DY2oGY2IKCbzNfKO2NAeLHnw1Ab4Xikh5n6hVPjOxAfX/f/T+O7A11PsuGJOw97TaFisfP/Mcq++Ci9VHd7T9iH0emuHufV8ZaYX86Qn7m3zDkqhcSXr4yGOs2+pLMNkLz69LPMcIsHaCxHMBTb9y7qoFcMIpYhT++AHOSnz+QzAFjBrlktbu33/6nbUaQrT+NXlElQg8NOLBH6mDONzKBB0PnJdP9WANjgRG9KrZ7iAhh1Ct2JrE9A/YI1/0npC9oIAK0CFB65qMl77rMmJh6JYP3VvN7NBYFup8PORqXNHtPlPxjDJ0ozXK1CA5N9NyBQ353qdizkoPFmGOpZAFMaiDjrZgW6/z00wJm24Sj3wlNi+m9nWWA14vo023EunZQ0cldWkH5SvFatTDdUACh1xDRqAmdiGjVKcSUQlLcAib7WhEpZTrtHe/QnpoRebmEKs94sMlSvZST0TOP/mDzWapguj9WB0SKUGJlRwx9N9ShRMA+TtmHnPHY1OAwgTnv9f5hvcYeguDPIfNIDY52hD7XZ0BJFBFU3LyY5pKj0yWaGNT0VahDDitq1jh+bElQVnz2OXQ99IlpUlbawa4wx4FZg3J4I/HEU0kR5I3kOP5LCxeiwu/uPgchXG6rEjrbXf4G28urP4CdcnIFiQPVtWkvW/zBVF9b637ey1iGPZSpPwow8J6fy8FN5zoxOz/P21mk+Y3V64BextOgN0Iv74O9b8Pco/CWYYv8ZTCaj6ar/Zn6foq+V9GYpwUMu++aQaHtSXqYvJS/Zx0ivkfYkPeY18HvJ4u59StkEEEfU5G2v9gMW1bAaVR6NbSKLP8EZfEk53TU6N0HCvdSLe77pGBCSc3c0j2ciIkmWeUyENfy0ednNsiEfmViDdGTTV9tXRuN55qzsNQLF2jBEL1AZgX9kU0rzE9GbZa63MJowlX4N+1cPiZCncTMxGzHFFnGQvbHtvfRCDGy0Po9AYAOHEKDBToq5Ul9Bqe/mUjG4yEgtVNan2LW3mXuZGsbyxS2i1qesT9AeGL/GN7dA/BG8X31DdwPG6x5RsMXDsQ3fq5NpcKJ++QYTk0+vRe3EM+6GmQ5+wWADXs5/BQa33uDUPro03dYGiHOac90XTKDQT0pKc0tWyy40nqZenABCIaSy2IfmErTPmq6GYqnQftw/TQ3FLgZvx8NYUpqzH2FJiT3G0wFDFy0pJUUU1KTpoIYC1CE+BmtIw2rCs/lU0oidxoIqReUYgFClvq+W+uaXypX6zK5jLn1g2EMFsRlNisTTvorcVGzmfAsR9N1ARwNDsWvf36kbb1ONHPkJ3HAp0qwN/zbLIi98xQc/9xRy8rz2WTI+rkyUU17ZRBPNvptRp8WzmhlMkgWOCu1HI9Mcm9wBVUVLVndVQvZ3sPnsI+x+OsMopcs3Bs5zqBk8ztV/Cnyogio6E3FxDL8rFSmk/t/Msuwg10P2pYFPOBbTJ3CJqx+mMvxMXX6f3p5vvKfACOepHBdeWbMoVo+L79r3m3jrMf/bV7fvpuU8i+OGejyxSPMO/gowePA7cHLbZx2B53tKOTHoxtd5ffhqTxSDJfTrUfrVLAYpX7MJ73xn11TDQTFRMnqC1tpuztvguyfP7rs773HfTXllvi/lfdvH5xWJQSN1dDcRLqHgMN4JTLBcmcBPJUw/rxkxjbJ0UpNJWX1C8OCijXUacKX6ii5vn0eX1M3Jue3z6JK6E+Wvtc+ja+o2y19Gs/7ypICW1JwLJFdBqYNc0FLGdY5x4rwd2ifXKa7hsZ5MMfgmjRFVVFpQIQb/iWoCck4xuINpEtnVHy6C8bh3Jfx+lkV7fmSGazQ8GfQzUDC4h386yj4XLVFKULaSFC5agiKJlq3Acc1OqJvVxUzoJs57sGjREnQuxGgHIByyHNr8vwDhULQsJpkQg3dgsAsxM2bo/5ZeHLmhlnFb+fJi+S7o7hp5cXNTYrn8leYmc6WcSZxLSdGyWvtLyZb1WRV2poSBXm9vnTxfkaSXLJKzoGSpvABKFsjpULJCntNy7n4YoVKSoVynNxk4l6+4Bn1zAlszolS/KbeAE1s72Q0BhiN9ZxTISYUyTmSONFsMDiLF+vgIF7CN0p3uH+Hqz7VjPJB7UsRgL7VTSoeBA7P4jd/SqG0V6stTc0zeD5ekU9B822csYB49h7cBgifHtO98Go1S+6VM7Z8+jRtcyXd2mdjMwNYZS8r33YDmE7YIEFzH/y3GDenVxvYhasnQK/31CcVuJNsqtBeOMUcU6RipMiYc+nc38FRPtSPZhua1AT6fRM4LsI7vaDBwciK7L2xL5ymPPDJkwns662xptnwrcaXjaQ9xCjzAaf+vXNugGPwBbISut/VVrECZL84rT1blEydq6K5aSpzLVGG/6ms/A5z1xR60wRdbB/Cyp9OdRtbw0oG6LFI2HNwvtt2JTvz3446l+E8RvUqgFfbb+ccTIfvO8gzizjCVp5uOwk5XbOnBo75vADABAnZE3L3cGG2f3X2OM+5AEh/Yx7bZ0J7UU58yZks3+LgCQElQRuqpO4hxWjo3YVhN342kJFPsbN6Wj/X3BgaS2puXwCxkGqhiDt9uTWm+tMQniLuPNu/CehN8NxHxYgjNgeTraFfzZ3YVykVL+PN76GUfikFbxp2eFcvl7zRv5irlmubNiaXyA61HN8/q6tAn7Us0yIzgIEcq6H5h51ObmOElKwIECRxI8jQ9nKWc9nd2cL1A0reISCaeX8HhQViOjT1BG/PRxr6vm1Wzau3s2L88o/J/Rmpn+rF/JV55ysUkrBzYfadV3Om0VIid3bX51xsS7FpqgKIovQdAUZwPmxD7F4rBDiQDNhvg6XX6ZFzLotxcqyvWGV2xxLuCoy3gtLc/j0a9SDr8lPavkKd49GWWmqbPRz7DrgpLtehjKbDQ1HpMJeVpXtM++DjHq5RbA+9lXuyHl/liZ8kcr7SvKVHcExoyvCB2rrF6lZI5YmfxfK8UemGrCdIh0QKJVi/gQ6+pGJ9nfIQZKLFACQsmNuqJaZAoxBJpTphIDLmhlKThDawbSrlTSElWAKmlJ6knEZjgVVCRO8VBZ7hC+00LdZKJkywV8761ONX0eN1EivLV0mjofKL6LGmFscJL4KOFusvmZOPQjejjtS90KVFt/QnqyMBHaj507FyyBRYL0BfNq+9ZSIG9c5434gYqXFFZJgZR+Rg2UYEYPEafEoFuwt0O5xeyyrO6OvXdW3MZ+xigB6izXBB3wujLgXpKCkVM4s59SnEGi1a4aVZXl15k8WW0c5+ArRSieAJWJBPAJ7Bo2t8O4eVD+hS6SIC80D102lLCx+kHoWIGEus7P30L/fnS9KOSz2k//pR9LskIdjfNp8I2QFw6fD3/0iVUMtn8NZQDxCYpFElUlz+9KGjxzaMudwDBI6fgVQhO15Ax2QLLkNBYAQgvt2ip/FWyahnVpFbt+ZR+W59l1zIOXYH5vo5ULaBPUsRAYne+Ak8l6arQrhiIJ0NxcEMbcUds5lBvvygvtygfLUOXTxG0HBC0WRVa6M9Y9fKpqk8hJVCUx8G2IKuWA6pQuW6Va1EsAIaBuI0W5Q9dF0cgP3mV6dEw7EHElo+A77q/ZX8zHShNVEQaT1VsfQUqPt84jkGyqb/InKh0UWxNQfbB7CQvISmD9z+vRnUNAOrJTQr7Muzawf+CxO3NzInuwlcZObub0qTAmjs1gXVDaapU/BO5TaWblpJie6BxGWeQryerl+Hd0flfogtGO3Z2+XUCcyw1kR8IIwaVikvrDuVEoQx0oPuXzMi+aWmC0mTHcLBNyzbdRUSo41+xDk96hZNds2rP/VIn6uhA85GICGfR+pbWHQo05SeQpuUxVfG7SBJU/m0ssSbdEavB+Q9ryK87RNzLYGxLMEvxcntO1Kk0LdNuot2zBJo2QPdotNqmWr175iu6N/Yv/6jyDVB5cS305xhk0WUk4WLqC0V7CLVAdiOrggh9NwpYEmKDsMXo6+ugYz/9FzZRWzkDa1C2khIBKm36F31TXDnN27Cyuh6yHWuHDrv0jFQGQ/2B6FwqINPFgabSBN9XgJ25GdmZL+nLr/1iMCbJSYHziGxVsV2X2lwlP+PJj6g3qoqlit1CFOroudR6dTjCWH67BUMEjnnIZiuQA3loAsrk7yp3V59GhLB00nddPUeQydlgkL6o+xtGdwaoWl2110uWh7l13nz9FX5C1TP9zTOBXjKNlkc2WHKOFngUF4/u4b7YlKFy86GFvL3SYd990AIQS6rdIJ2o+xuRJ3L2Syfq7yDCMS+pPMZ5C8XOHsXGB8ajm1CTDJgQ6t0R2qUQDTLt5YZOAmATO9HmRTfRulpeOM3eFTiLk+RNnCs4lV2Dv0L73+OKX1P8/Yr/jOIfUPyDypOC9ghG8QnvwfZ8+bmbOVmiOjy+pe3JzeNrfGLz+A98Kc3jK1Aw8ai8AIoAOm1PyFvjSw3bBn72iWjJ+wHQ/bYBDkBtlwDtaLMnqV7eTVhbBlM6mAclCn1c3rfk1MAqwRi2nXkVSnYNY/Zzf6fZF2L2G1j2ue18637frObxch/fPP59n0mxDXZFgNnR3v5fZe7PGcs5SpbP6w8vnzcccwc0XXqmQLrqM6NjxcAlS91xYP3mhm39z0KnwrZh3PrUASIpegRjKrrt2s93IhWmIZAqSseoo9MCHPGP64KpkZzTU/Hal/+8nzT+fBhaBiL0uFSX7uN6zZnFHrtby9pKb1+Cp32JgcsmeR4Nmik25y3JlLlebslX86Vw3eemi0WBy1xdJ96J9ZrhzGnUVvafH4vH4/XoNhB4aUQ9IJBOXG9t4yX0h4RHA07uey8hxYRI3pEz5lQ6MVnbiYk/bWNOjjvxo/YzTCqx2uEd07VnXtLBmtJg1bbiiycTMjeka3X48vQztHqlIVP71kt4fJcptPF4iE49/gN1Ie4hXfjNYdeeD2BFi0LnzIo7nZQsvtiPekXFGUAScQA2Qh+Za5TyrKut86fOG4amzEQdLL1SUoxXAdexNc4g5fw/ihdvQk8Gd7NY5oFPE3w55b7ZNVA0iQE0nXZYs9i0ZpEUQucPPGqjfj063UUBcQqBnszQJbPU4zs7M0YS8zfEQiZQECV2PoVUj2ITdKfo6Ey1wCIG+pnOLM8Cxw4ZSknFMjfge3Vpu+cd5DBVf/+FfyW2QTQrtSirVpOyEbHzCLGNwmI47UpRpfbDV2LCtdKa6kAkqeEr0axgfmeypbeo2jB0PfxrGpoL/3JDs3YhfQ6PRq/ifFDcY9PEPWXDYqfrnLKqVil6BKOur8rC9XAuChdRnTZckaJMsspOv6UTJ3RgQi1Kp5kyYoNbaYbPsKJci+4i7ArPfB0dyZY/wN9f4K9H/4397etg8bsxdCZskd/RXXsayIhqWEMbsC8rfItX+OavoPY2YQMVx9gFIIAQztMkqgqdLygFU0mGGbmuigCs44O2VqpcKigppLmNuY5XDLF4GjbBXlsL7J32g8arfCxTef6OmfrVNmtcfqME0RhE+eMG1IsO+nQN5C68z3xnEXL5J8gN0vViEPXg0U1qiEPQE+HqtfZkFBOgx1jSkEllZ9qRCAI52SnucQuKexHyoHtKBYf6HKqe12ZBdRXRedorwAsyBXXIUEsLXjwfv0kRg4eQo1qTuYtR8j+ipKmZ/Bz7hi2hiE3zspbKxD3FaUrxYsgu7nGkVbB6aUt21hKaKqqY6KilBdWpluQFABp0fuEpyuOqOBeBWz8LGx76VbKF2UNTSHn2u7oq+zycF4HOSwxewvTI6TOmZhgVrsRW3MAkTReFrZoSheW/QiVhxYny3e2zqCSs3CxnNzclJajFSQBsgT7CmXFrH2nxM0x7sVbvBXQbratUunR2h0qXjZzVPoo5VvDdTp6jNj70SwXWpj17RWWpscqARZ8p1tEeiDvgKiZzyV1MoPPsGSDPWIvrM7VevGxSN9BFLICu3q3pYRj02v/dq9fO+hZzmPC89yoFdro/X7hyf2K8GSpebMhUghtYAI4/1uJOpRWyXSuN+ATyPJU7PkebmS3No5NdrU+2g5OdutzRkSiX6nJHh1m+l3iycgt5sVVIorbgrVwSFSIGQtNlkVrzoB4Rng2q/zv6oJKcrxnEoB/Xt3MZzJzyNjbfhTBw11qcw+ulG8RgiX5keujWoEfGeI+BiQpVutUcta/mowcvdziJCltqMrX//jUVbdHxoQb1XjH4XTPej9J21mQqP6LjfRlf1ReRWoYTekH5Oc6NNtIfmxoqkjSjzXmYTh8K+YdSqD4Pzaqvi76Ce8n1bq2ImfhNlf8sEfpPS1uKA5POuj8ROkyVbq0KvKHNx85Cn1oo+xPrM9VcT0TpYSb07Q38prln9Ow5/LomC+MwezKVwgyoY11NuCArSnuGufQZ9z7CZnxdTdcbU1eFdj11l4igqhQn/PMp+mWBlC4G8V5el+H3Uhm+1m65Zz5zOIJyfDesw6/wOd94T7GRiZPHkmBDfI2jYLbCMV1mVXrqiqk5zjFBTlxsVXyWzkRsbhLsSkHpeuDtOTbR6y127a+72WQV2GMzlUmtrjkUHFvIczjRMAtGS1eyRR/od789faDL6EDZ+NIM1x7f2LTxfTJtfGfp+Dh5Pszk76dm0qw3cNWI3VduhnOm6SPO57RRNmIvoLKZMqzT8Q/m2AcmxuqJf+BjH5gk6zfxDymwZ7zEnuI12c0wP17FLtCU0hQvau6XpgVEns1eXGur6Fv6EAxSYuQ3eIXyEcOUurDaEYNqgf4rhiTCkBhs6/oAYdsGHbZ98oGe8TGWsfUjlAtQ6AO9JLMZKgKu86ZnIeVtLEaxDD3RMSG1k2kUav/9B0qBKsYZi/4s1kjrpzW67RXavnoMS5wF73ZtM/UMaMGc69EfsGiMD7fyYTbce50rvmljdjRjSUa6rr+bWtevPfwP1rXpgysmAWUeM3Zy42l9m1r0RVrJlvWRWLo1ls5WdTVLR7WDgvTAniXwKVEM0sAaMxb5vTP6IrcgdUlqMsXON+nTCQa8vaQXybH9OUe9gMBuG6PnxuAziZ0HvH1aoZcBfvgmD3oD46ZNSe8gozOUyhD4sQGxc5+XhBSV5pJGGoy+u0z7vQrBNgIid8WumfVQHJXGKIBrZxys0eebXTudQKnhFrx2OsggBp35N6dm/i09v077kK8jEaKULoKGxD2Fgp0RI5RCcURP4L6hxFEFo4M+owtvjS2P/ANWTZpSuphVkPaPK6DkzX8M6AaR8lIEvwyovMNG2IY0DgAYpG0C+2Ig1qR3mAoO18Uszf67Ooao4/fzAvrUQdXl2jxYVmfsXj7vFzNcUqJSIukFtjSxiweco5Q=
*/