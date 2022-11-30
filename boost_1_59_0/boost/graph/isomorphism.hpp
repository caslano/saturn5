// Copyright (C) 2001 Jeremy Siek, Douglas Gregor, Brian Osman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_GRAPH_ISOMORPHISM_HPP
#define BOOST_GRAPH_ISOMORPHISM_HPP

#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/detail/algorithm.hpp>
#include <boost/pending/indirect_cmp.hpp> // for make_indirect_pmap
#include <boost/concept/assert.hpp>

#ifndef BOOST_GRAPH_ITERATION_MACROS_HPP
#define BOOST_ISO_INCLUDED_ITER_MACROS // local macro, see bottom of file
#include <boost/graph/iteration_macros.hpp>
#endif

namespace boost
{

namespace detail
{

    template < typename Graph1, typename Graph2, typename IsoMapping,
        typename Invariant1, typename Invariant2, typename IndexMap1,
        typename IndexMap2 >
    class isomorphism_algo
    {
        typedef typename graph_traits< Graph1 >::vertex_descriptor vertex1_t;
        typedef typename graph_traits< Graph2 >::vertex_descriptor vertex2_t;
        typedef typename graph_traits< Graph1 >::edge_descriptor edge1_t;
        typedef typename graph_traits< Graph1 >::vertices_size_type size_type;
        typedef typename Invariant1::result_type invar1_value;
        typedef typename Invariant2::result_type invar2_value;

        const Graph1& G1;
        const Graph2& G2;
        IsoMapping f;
        Invariant1 invariant1;
        Invariant2 invariant2;
        std::size_t max_invariant;
        IndexMap1 index_map1;
        IndexMap2 index_map2;

        std::vector< vertex1_t > dfs_vertices;
        typedef typename std::vector< vertex1_t >::iterator vertex_iter;
        std::vector< int > dfs_num_vec;
        typedef safe_iterator_property_map<
            typename std::vector< int >::iterator, IndexMap1
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
            ,
            int, int&
#endif /* BOOST_NO_STD_ITERATOR_TRAITS */
            >
            DFSNumMap;
        DFSNumMap dfs_num;
        std::vector< edge1_t > ordered_edges;
        typedef typename std::vector< edge1_t >::iterator edge_iter;

        std::vector< char > in_S_vec;
        typedef safe_iterator_property_map<
            typename std::vector< char >::iterator, IndexMap2
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
            ,
            char, char&
#endif /* BOOST_NO_STD_ITERATOR_TRAITS */
            >
            InSMap;
        InSMap in_S;

        int num_edges_on_k;

        friend struct compare_multiplicity;
        struct compare_multiplicity
        {
            compare_multiplicity(Invariant1 invariant1, size_type* multiplicity)
            : invariant1(invariant1), multiplicity(multiplicity)
            {
            }
            bool operator()(const vertex1_t& x, const vertex1_t& y) const
            {
                return multiplicity[invariant1(x)]
                    < multiplicity[invariant1(y)];
            }
            Invariant1 invariant1;
            size_type* multiplicity;
        };

        struct record_dfs_order : default_dfs_visitor
        {
            record_dfs_order(
                std::vector< vertex1_t >& v, std::vector< edge1_t >& e)
            : vertices(v), edges(e)
            {
            }

            void discover_vertex(vertex1_t v, const Graph1&) const
            {
                vertices.push_back(v);
            }
            void examine_edge(edge1_t e, const Graph1&) const
            {
                edges.push_back(e);
            }
            std::vector< vertex1_t >& vertices;
            std::vector< edge1_t >& edges;
        };

        struct edge_cmp
        {
            edge_cmp(const Graph1& G1, DFSNumMap dfs_num)
            : G1(G1), dfs_num(dfs_num)
            {
            }
            bool operator()(const edge1_t& e1, const edge1_t& e2) const
            {
                using namespace std;
                int u1 = dfs_num[source(e1, G1)], v1 = dfs_num[target(e1, G1)];
                int u2 = dfs_num[source(e2, G1)], v2 = dfs_num[target(e2, G1)];
                int m1 = (max)(u1, v1);
                int m2 = (max)(u2, v2);
                // lexicographical comparison
                return std::make_pair(m1, std::make_pair(u1, v1))
                    < std::make_pair(m2, std::make_pair(u2, v2));
            }
            const Graph1& G1;
            DFSNumMap dfs_num;
        };

    public:
        isomorphism_algo(const Graph1& G1, const Graph2& G2, IsoMapping f,
            Invariant1 invariant1, Invariant2 invariant2,
            std::size_t max_invariant, IndexMap1 index_map1,
            IndexMap2 index_map2)
        : G1(G1)
        , G2(G2)
        , f(f)
        , invariant1(invariant1)
        , invariant2(invariant2)
        , max_invariant(max_invariant)
        , index_map1(index_map1)
        , index_map2(index_map2)
        {
            in_S_vec.resize(num_vertices(G1));
            in_S = make_safe_iterator_property_map(
                in_S_vec.begin(), in_S_vec.size(), index_map2
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
                ,
                in_S_vec.front()
#endif /* BOOST_NO_STD_ITERATOR_TRAITS */
            );
        }

        bool test_isomorphism()
        {
            // reset isomapping
            BGL_FORALL_VERTICES_T(v, G1, Graph1)
            f[v] = graph_traits< Graph2 >::null_vertex();

            {
                std::vector< invar1_value > invar1_array;
                BGL_FORALL_VERTICES_T(v, G1, Graph1)
                invar1_array.push_back(invariant1(v));
                sort(invar1_array);

                std::vector< invar2_value > invar2_array;
                BGL_FORALL_VERTICES_T(v, G2, Graph2)
                invar2_array.push_back(invariant2(v));
                sort(invar2_array);
                if (!equal(invar1_array, invar2_array))
                    return false;
            }

            std::vector< vertex1_t > V_mult;
            BGL_FORALL_VERTICES_T(v, G1, Graph1)
            V_mult.push_back(v);
            {
                std::vector< size_type > multiplicity(max_invariant, 0);
                BGL_FORALL_VERTICES_T(v, G1, Graph1)
                ++multiplicity.at(invariant1(v));
                sort(
                    V_mult, compare_multiplicity(invariant1, &multiplicity[0]));
            }

            std::vector< default_color_type > color_vec(num_vertices(G1));
            safe_iterator_property_map<
                std::vector< default_color_type >::iterator, IndexMap1
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
                ,
                default_color_type, default_color_type&
#endif /* BOOST_NO_STD_ITERATOR_TRAITS */
                >
                color_map(color_vec.begin(), color_vec.size(), index_map1);
            record_dfs_order dfs_visitor(dfs_vertices, ordered_edges);
            typedef color_traits< default_color_type > Color;
            for (vertex_iter u = V_mult.begin(); u != V_mult.end(); ++u)
            {
                if (color_map[*u] == Color::white())
                {
                    dfs_visitor.start_vertex(*u, G1);
                    depth_first_visit(G1, *u, dfs_visitor, color_map);
                }
            }
            // Create the dfs_num array and dfs_num_map
            dfs_num_vec.resize(num_vertices(G1));
            dfs_num = make_safe_iterator_property_map(
                dfs_num_vec.begin(), dfs_num_vec.size(), index_map1
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
                ,
                dfs_num_vec.front()
#endif /* BOOST_NO_STD_ITERATOR_TRAITS */
            );
            size_type n = 0;
            for (vertex_iter v = dfs_vertices.begin(); v != dfs_vertices.end();
                 ++v)
                dfs_num[*v] = n++;

            sort(ordered_edges, edge_cmp(G1, dfs_num));

            int dfs_num_k = -1;
            return this->match(ordered_edges.begin(), dfs_num_k);
        }

    private:
        struct match_continuation
        {
            enum
            {
                pos_G2_vertex_loop,
                pos_fi_adj_loop,
                pos_dfs_num
            } position;
            typedef typename graph_traits< Graph2 >::vertex_iterator
                vertex_iterator;
            std::pair< vertex_iterator, vertex_iterator > G2_verts;
            typedef typename graph_traits< Graph2 >::adjacency_iterator
                adjacency_iterator;
            std::pair< adjacency_iterator, adjacency_iterator > fi_adj;
            edge_iter iter;
            int dfs_num_k;
        };

        bool match(edge_iter iter, int dfs_num_k)
        {
            std::vector< match_continuation > k;
            typedef typename graph_traits< Graph2 >::vertex_iterator
                vertex_iterator;
            std::pair< vertex_iterator, vertex_iterator > G2_verts(
                vertices(G2));
            typedef typename graph_traits< Graph2 >::adjacency_iterator
                adjacency_iterator;
            std::pair< adjacency_iterator, adjacency_iterator > fi_adj;
            vertex1_t i, j;

        recur:
            if (iter != ordered_edges.end())
            {
                i = source(*iter, G1);
                j = target(*iter, G1);
                if (dfs_num[i] > dfs_num_k)
                {
                    G2_verts = vertices(G2);
                    while (G2_verts.first != G2_verts.second)
                    {
                        {
                            vertex2_t u = *G2_verts.first;
                            vertex1_t kp1 = dfs_vertices[dfs_num_k + 1];
                            if (invariant1(kp1) == invariant2(u)
                                && in_S[u] == false)
                            {
                                {
                                    f[kp1] = u;
                                    in_S[u] = true;
                                    num_edges_on_k = 0;

                                    match_continuation new_k;
                                    new_k.position = match_continuation::
                                        pos_G2_vertex_loop;
                                    new_k.G2_verts = G2_verts;
                                    new_k.iter = iter;
                                    new_k.dfs_num_k = dfs_num_k;
                                    k.push_back(new_k);
                                    ++dfs_num_k;
                                    goto recur;
                                }
                            }
                        }
                    G2_loop_k:
                        ++G2_verts.first;
                    }
                }
                else if (dfs_num[j] > dfs_num_k)
                {
                    {
                        vertex1_t vk = dfs_vertices[dfs_num_k];
                        num_edges_on_k -= count_if(adjacent_vertices(f[vk], G2),
                            make_indirect_pmap(in_S));

                        for (int jj = 0; jj < dfs_num_k; ++jj)
                        {
                            vertex1_t j = dfs_vertices[jj];
                            num_edges_on_k
                                -= count(adjacent_vertices(f[j], G2), f[vk]);
                        }
                    }

                    if (num_edges_on_k != 0)
                        goto return_point_false;
                    fi_adj = adjacent_vertices(f[i], G2);
                    while (fi_adj.first != fi_adj.second)
                    {
                        {
                            vertex2_t v = *fi_adj.first;
                            if (invariant2(v) == invariant1(j)
                                && in_S[v] == false)
                            {
                                f[j] = v;
                                in_S[v] = true;
                                num_edges_on_k = 1;
                                BOOST_USING_STD_MAX();
                                int next_k
                                    = max BOOST_PREVENT_MACRO_SUBSTITUTION(
                                        dfs_num_k,
                                        max BOOST_PREVENT_MACRO_SUBSTITUTION(
                                            dfs_num[i], dfs_num[j]));
                                match_continuation new_k;
                                new_k.position
                                    = match_continuation::pos_fi_adj_loop;
                                new_k.fi_adj = fi_adj;
                                new_k.iter = iter;
                                new_k.dfs_num_k = dfs_num_k;
                                ++iter;
                                dfs_num_k = next_k;
                                k.push_back(new_k);
                                goto recur;
                            }
                        }
                    fi_adj_loop_k:
                        ++fi_adj.first;
                    }
                }
                else
                {
                    if (container_contains(adjacent_vertices(f[i], G2), f[j]))
                    {
                        ++num_edges_on_k;
                        match_continuation new_k;
                        new_k.position = match_continuation::pos_dfs_num;
                        k.push_back(new_k);
                        ++iter;
                        goto recur;
                    }
                }
            }
            else
                goto return_point_true;
            goto return_point_false;

            {
            return_point_true:
                return true;

            return_point_false:
                if (k.empty())
                    return false;
                const match_continuation& this_k = k.back();
                switch (this_k.position)
                {
                case match_continuation::pos_G2_vertex_loop:
                {
                    G2_verts = this_k.G2_verts;
                    iter = this_k.iter;
                    dfs_num_k = this_k.dfs_num_k;
                    k.pop_back();
                    in_S[*G2_verts.first] = false;
                    i = source(*iter, G1);
                    j = target(*iter, G1);
                    goto G2_loop_k;
                }
                case match_continuation::pos_fi_adj_loop:
                {
                    fi_adj = this_k.fi_adj;
                    iter = this_k.iter;
                    dfs_num_k = this_k.dfs_num_k;
                    k.pop_back();
                    in_S[*fi_adj.first] = false;
                    i = source(*iter, G1);
                    j = target(*iter, G1);
                    goto fi_adj_loop_k;
                }
                case match_continuation::pos_dfs_num:
                {
                    k.pop_back();
                    goto return_point_false;
                }
                default:
                {
                    BOOST_ASSERT(!"Bad position");
#ifdef UNDER_CE
                    exit(-1);
#else
                    abort();
#endif
                }
                }
            }
        }
    };

    template < typename Graph, typename InDegreeMap >
    void compute_in_degree(const Graph& g, InDegreeMap in_degree_map)
    {
        BGL_FORALL_VERTICES_T(v, g, Graph)
        put(in_degree_map, v, 0);

        BGL_FORALL_VERTICES_T(u, g, Graph)
        BGL_FORALL_ADJ_T(u, v, g, Graph)
        put(in_degree_map, v, get(in_degree_map, v) + 1);
    }

} // namespace detail

template < typename InDegreeMap, typename Graph > class degree_vertex_invariant
{
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
    typedef typename graph_traits< Graph >::degree_size_type size_type;

public:
    typedef vertex_t argument_type;
    typedef size_type result_type;

    degree_vertex_invariant(const InDegreeMap& in_degree_map, const Graph& g)
    : m_in_degree_map(in_degree_map)
    , m_max_vertex_in_degree(0)
    , m_max_vertex_out_degree(0)
    , m_g(g)
    {
        BGL_FORALL_VERTICES_T(v, g, Graph)
        {
            m_max_vertex_in_degree
                = (std::max)(m_max_vertex_in_degree, get(m_in_degree_map, v));
            m_max_vertex_out_degree
                = (std::max)(m_max_vertex_out_degree, out_degree(v, g));
        }
    }

    size_type operator()(vertex_t v) const
    {
        return (m_max_vertex_in_degree + 1) * out_degree(v, m_g)
            + get(m_in_degree_map, v);
    }
    // The largest possible vertex invariant number
    size_type max BOOST_PREVENT_MACRO_SUBSTITUTION() const
    {
        return (m_max_vertex_in_degree + 1) * (m_max_vertex_out_degree + 1);
    }

private:
    InDegreeMap m_in_degree_map;
    size_type m_max_vertex_in_degree;
    size_type m_max_vertex_out_degree;
    const Graph& m_g;
};

// Count actual number of vertices, even in filtered graphs.
template < typename Graph > size_t count_vertices(const Graph& g)
{
    size_t n = 0;
    BGL_FORALL_VERTICES_T(v, g, Graph)
    {
        (void)v;
        ++n;
    }
    return n;
}

template < typename Graph1, typename Graph2, typename IsoMapping,
    typename Invariant1, typename Invariant2, typename IndexMap1,
    typename IndexMap2 >
bool isomorphism(const Graph1& G1, const Graph2& G2, IsoMapping f,
    Invariant1 invariant1, Invariant2 invariant2, std::size_t max_invariant,
    IndexMap1 index_map1, IndexMap2 index_map2)

{
    // Graph requirements
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph1 >));
    BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< Graph1 >));
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph2 >));
    // BOOST_CONCEPT_ASSERT(( BidirectionalGraphConcept<Graph2> ));

    typedef typename graph_traits< Graph1 >::vertex_descriptor vertex1_t;
    typedef typename graph_traits< Graph2 >::vertex_descriptor vertex2_t;
    typedef typename graph_traits< Graph1 >::vertices_size_type size_type;

    // Vertex invariant requirement
    BOOST_CONCEPT_ASSERT(
        (AdaptableUnaryFunctionConcept< Invariant1, size_type, vertex1_t >));
    BOOST_CONCEPT_ASSERT(
        (AdaptableUnaryFunctionConcept< Invariant2, size_type, vertex2_t >));

    // Property map requirements
    BOOST_CONCEPT_ASSERT(
        (ReadWritePropertyMapConcept< IsoMapping, vertex1_t >));
    typedef typename property_traits< IsoMapping >::value_type IsoMappingValue;
    BOOST_STATIC_ASSERT((is_convertible< IsoMappingValue, vertex2_t >::value));

    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< IndexMap1, vertex1_t >));
    typedef typename property_traits< IndexMap1 >::value_type IndexMap1Value;
    BOOST_STATIC_ASSERT((is_convertible< IndexMap1Value, size_type >::value));

    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< IndexMap2, vertex2_t >));
    typedef typename property_traits< IndexMap2 >::value_type IndexMap2Value;
    BOOST_STATIC_ASSERT((is_convertible< IndexMap2Value, size_type >::value));

    if (count_vertices(G1) != count_vertices(G2))
        return false;
    if (count_vertices(G1) == 0 && count_vertices(G2) == 0)
        return true;

    detail::isomorphism_algo< Graph1, Graph2, IsoMapping, Invariant1,
        Invariant2, IndexMap1, IndexMap2 >
        algo(G1, G2, f, invariant1, invariant2, max_invariant, index_map1,
            index_map2);
    return algo.test_isomorphism();
}

namespace detail
{

    template < typename Graph1, typename Graph2, typename IsoMapping,
        typename IndexMap1, typename IndexMap2, typename P, typename T,
        typename R >
    bool isomorphism_impl(const Graph1& G1, const Graph2& G2, IsoMapping f,
        IndexMap1 index_map1, IndexMap2 index_map2,
        const bgl_named_params< P, T, R >& params)
    {
        std::vector< std::size_t > in_degree1_vec(num_vertices(G1));
        typedef safe_iterator_property_map<
            std::vector< std::size_t >::iterator, IndexMap1
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
            ,
            std::size_t, std::size_t&
#endif /* BOOST_NO_STD_ITERATOR_TRAITS */
            >
            InDeg1;
        InDeg1 in_degree1(
            in_degree1_vec.begin(), in_degree1_vec.size(), index_map1);
        compute_in_degree(G1, in_degree1);

        std::vector< std::size_t > in_degree2_vec(num_vertices(G2));
        typedef safe_iterator_property_map<
            std::vector< std::size_t >::iterator, IndexMap2
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
            ,
            std::size_t, std::size_t&
#endif /* BOOST_NO_STD_ITERATOR_TRAITS */
            >
            InDeg2;
        InDeg2 in_degree2(
            in_degree2_vec.begin(), in_degree2_vec.size(), index_map2);
        compute_in_degree(G2, in_degree2);

        degree_vertex_invariant< InDeg1, Graph1 > invariant1(in_degree1, G1);
        degree_vertex_invariant< InDeg2, Graph2 > invariant2(in_degree2, G2);

        return isomorphism(G1, G2, f,
            choose_param(get_param(params, vertex_invariant1_t()), invariant1),
            choose_param(get_param(params, vertex_invariant2_t()), invariant2),
            choose_param(get_param(params, vertex_max_invariant_t()),
                (invariant2.max)()),
            index_map1, index_map2);
    }

    template < typename G, typename Index > struct make_degree_invariant
    {
        const G& g;
        const Index& index;
        make_degree_invariant(const G& g, const Index& index)
        : g(g), index(index)
        {
        }
        typedef typename boost::graph_traits< G >::degree_size_type
            degree_size_type;
        typedef shared_array_property_map< degree_size_type, Index >
            prop_map_type;
        typedef degree_vertex_invariant< prop_map_type, G > result_type;
        result_type operator()() const
        {
            prop_map_type pm = make_shared_array_property_map(
                num_vertices(g), degree_size_type(), index);
            compute_in_degree(g, pm);
            return result_type(pm, g);
        }
    };

} // namespace detail

namespace graph
{
    namespace detail
    {
        template < typename Graph1, typename Graph2 > struct isomorphism_impl
        {
            typedef bool result_type;
            typedef result_type type;
            template < typename ArgPack >
            bool operator()(const Graph1& g1, const Graph2& g2,
                const ArgPack& arg_pack) const
            {
                using namespace boost::graph::keywords;
                typedef typename boost::detail::override_const_property_result<
                    ArgPack, tag::vertex_index1_map, boost::vertex_index_t,
                    Graph1 >::type index1_map_type;
                typedef typename boost::detail::override_const_property_result<
                    ArgPack, tag::vertex_index2_map, boost::vertex_index_t,
                    Graph2 >::type index2_map_type;
                index1_map_type index1_map
                    = boost::detail::override_const_property(
                        arg_pack, _vertex_index1_map, g1, boost::vertex_index);
                index2_map_type index2_map
                    = boost::detail::override_const_property(
                        arg_pack, _vertex_index2_map, g2, boost::vertex_index);
                typedef typename graph_traits< Graph2 >::vertex_descriptor
                    vertex2_t;
                typename std::vector< vertex2_t >::size_type n
                    = (typename std::vector< vertex2_t >::size_type)
                        num_vertices(g1);
                std::vector< vertex2_t > f(n);
                typename boost::parameter::lazy_binding< ArgPack,
                    tag::vertex_invariant1,
                    boost::detail::make_degree_invariant< Graph1,
                        index1_map_type > >::type invariant1
                    = arg_pack[_vertex_invariant1
                        || boost::detail::make_degree_invariant< Graph1,
                            index1_map_type >(g1, index1_map)];
                typename boost::parameter::lazy_binding< ArgPack,
                    tag::vertex_invariant2,
                    boost::detail::make_degree_invariant< Graph2,
                        index2_map_type > >::type invariant2
                    = arg_pack[_vertex_invariant2
                        || boost::detail::make_degree_invariant< Graph2,
                            index2_map_type >(g2, index2_map)];
                return boost::isomorphism(g1, g2,
                    choose_param(
                        arg_pack[_isomorphism_map | boost::param_not_found()],
                        make_shared_array_property_map(
                            num_vertices(g1), vertex2_t(), index1_map)),
                    invariant1, invariant2,
                    arg_pack[_vertex_max_invariant | (invariant2.max)()],
                    index1_map, index2_map);
            }
        };
    }
    BOOST_GRAPH_MAKE_FORWARDING_FUNCTION(isomorphism, 2, 6)
}

// Named parameter interface
BOOST_GRAPH_MAKE_OLD_STYLE_PARAMETER_FUNCTION(isomorphism, 2)

// Verify that the given mapping iso_map from the vertices of g1 to the
// vertices of g2 describes an isomorphism.
// Note: this could be made much faster by specializing based on the graph
// concepts modeled, but since we're verifying an O(n^(lg n)) algorithm,
// O(n^4) won't hurt us.
template < typename Graph1, typename Graph2, typename IsoMap >
inline bool verify_isomorphism(
    const Graph1& g1, const Graph2& g2, IsoMap iso_map)
{
#if 0
    // problematic for filtered_graph!
    if (num_vertices(g1) != num_vertices(g2) || num_edges(g1) != num_edges(g2))
      return false;
#endif

    BGL_FORALL_EDGES_T(e1, g1, Graph1)
    {
        bool found_edge = false;
        BGL_FORALL_EDGES_T(e2, g2, Graph2)
        {
            if (source(e2, g2) == get(iso_map, source(e1, g1))
                && target(e2, g2) == get(iso_map, target(e1, g1)))
            {
                found_edge = true;
            }
        }

        if (!found_edge)
            return false;
    }

    return true;
}

} // namespace boost

#ifdef BOOST_ISO_INCLUDED_ITER_MACROS
#undef BOOST_ISO_INCLUDED_ITER_MACROS
#include <boost/graph/iteration_macros_undef.hpp>
#endif

#endif // BOOST_GRAPH_ISOMORPHISM_HPP

/* isomorphism.hpp
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
*/