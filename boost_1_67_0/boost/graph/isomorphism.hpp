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