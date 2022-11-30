//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

#ifndef BOOST_GRAPH_STRONG_COMPONENTS_HPP
#define BOOST_GRAPH_STRONG_COMPONENTS_HPP

#include <stack>
#include <boost/config.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/type_traits/conversion_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/graph/detail/mpi_include.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{

//==========================================================================
// This is Tarjan's algorithm for strongly connected components
// from his paper "Depth first search and linear graph algorithms".
// It calculates the components in a single application of DFS.
// We implement the algorithm as a dfs-visitor.

namespace detail
{

    template < typename ComponentMap, typename RootMap, typename DiscoverTime,
        typename Stack >
    class tarjan_scc_visitor : public dfs_visitor<>
    {
        typedef typename property_traits< ComponentMap >::value_type comp_type;
        typedef typename property_traits< DiscoverTime >::value_type time_type;

    public:
        tarjan_scc_visitor(ComponentMap comp_map, RootMap r, DiscoverTime d,
            comp_type& c_, Stack& s_)
        : c(c_)
        , comp(comp_map)
        , root(r)
        , discover_time(d)
        , dfs_time(time_type())
        , s(s_)
        {
        }

        template < typename Graph >
        void discover_vertex(
            typename graph_traits< Graph >::vertex_descriptor v, const Graph&)
        {
            put(root, v, v);
            put(comp, v, (std::numeric_limits< comp_type >::max)());
            put(discover_time, v, dfs_time++);
            s.push(v);
        }
        template < typename Graph >
        void finish_vertex(
            typename graph_traits< Graph >::vertex_descriptor v, const Graph& g)
        {
            typename graph_traits< Graph >::vertex_descriptor w;
            typename graph_traits< Graph >::out_edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end) = out_edges(v, g); ei != ei_end; ++ei)
            {
                w = target(*ei, g);
                if (get(comp, w) == (std::numeric_limits< comp_type >::max)())
                    put(root, v,
                        this->min_discover_time(get(root, v), get(root, w)));
            }
            if (get(root, v) == v)
            {
                do
                {
                    w = s.top();
                    s.pop();
                    put(comp, w, c);
                    put(root, w, v);
                } while (w != v);
                ++c;
            }
        }

    private:
        template < typename Vertex >
        Vertex min_discover_time(Vertex u, Vertex v)
        {
            return get(discover_time, u) < get(discover_time, v) ? u : v;
        }

        comp_type& c;
        ComponentMap comp;
        RootMap root;
        DiscoverTime discover_time;
        time_type dfs_time;
        Stack& s;
    };

    template < class Graph, class ComponentMap, class RootMap,
        class DiscoverTime, class P, class T, class R >
    typename property_traits< ComponentMap >::value_type strong_components_impl(
        const Graph& g, // Input
        ComponentMap comp, // Output
        // Internal record keeping
        RootMap root, DiscoverTime discover_time,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
        BOOST_CONCEPT_ASSERT(
            (ReadWritePropertyMapConcept< ComponentMap, Vertex >));
        BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept< RootMap, Vertex >));
        typedef typename property_traits< RootMap >::value_type RootV;
        BOOST_CONCEPT_ASSERT((ConvertibleConcept< RootV, Vertex >));
        BOOST_CONCEPT_ASSERT(
            (ReadWritePropertyMapConcept< DiscoverTime, Vertex >));

        typename property_traits< ComponentMap >::value_type total = 0;

        std::stack< Vertex > s;
        detail::tarjan_scc_visitor< ComponentMap, RootMap, DiscoverTime,
            std::stack< Vertex > >
            vis(comp, root, discover_time, total, s);
        depth_first_search(g, params.visitor(vis));
        return total;
    }

    //-------------------------------------------------------------------------
    // The dispatch functions handle the defaults for the rank and discover
    // time property maps.
    // dispatch with class specialization to avoid VC++ bug

    template < class DiscoverTimeMap > struct strong_comp_dispatch2
    {
        template < class Graph, class ComponentMap, class RootMap, class P,
            class T, class R >
        inline static typename property_traits< ComponentMap >::value_type
        apply(const Graph& g, ComponentMap comp, RootMap r_map,
            const bgl_named_params< P, T, R >& params, DiscoverTimeMap time_map)
        {
            return strong_components_impl(g, comp, r_map, time_map, params);
        }
    };

    template <> struct strong_comp_dispatch2< param_not_found >
    {
        template < class Graph, class ComponentMap, class RootMap, class P,
            class T, class R >
        inline static typename property_traits< ComponentMap >::value_type
        apply(const Graph& g, ComponentMap comp, RootMap r_map,
            const bgl_named_params< P, T, R >& params, param_not_found)
        {
            typedef
                typename graph_traits< Graph >::vertices_size_type size_type;
            size_type n = num_vertices(g) > 0 ? num_vertices(g) : 1;
            std::vector< size_type > time_vec(n);
            return strong_components_impl(g, comp, r_map,
                make_iterator_property_map(time_vec.begin(),
                    choose_const_pmap(
                        get_param(params, vertex_index), g, vertex_index),
                    time_vec[0]),
                params);
        }
    };

    template < class Graph, class ComponentMap, class RootMap, class P, class T,
        class R, class DiscoverTimeMap >
    inline typename property_traits< ComponentMap >::value_type scc_helper2(
        const Graph& g, ComponentMap comp, RootMap r_map,
        const bgl_named_params< P, T, R >& params, DiscoverTimeMap time_map)
    {
        return strong_comp_dispatch2< DiscoverTimeMap >::apply(
            g, comp, r_map, params, time_map);
    }

    template < class RootMap > struct strong_comp_dispatch1
    {

        template < class Graph, class ComponentMap, class P, class T, class R >
        inline static typename property_traits< ComponentMap >::value_type
        apply(const Graph& g, ComponentMap comp,
            const bgl_named_params< P, T, R >& params, RootMap r_map)
        {
            return scc_helper2(g, comp, r_map, params,
                get_param(params, vertex_discover_time));
        }
    };
    template <> struct strong_comp_dispatch1< param_not_found >
    {

        template < class Graph, class ComponentMap, class P, class T, class R >
        inline static typename property_traits< ComponentMap >::value_type
        apply(const Graph& g, ComponentMap comp,
            const bgl_named_params< P, T, R >& params, param_not_found)
        {
            typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
            typename std::vector< Vertex >::size_type n
                = num_vertices(g) > 0 ? num_vertices(g) : 1;
            std::vector< Vertex > root_vec(n);
            return scc_helper2(g, comp,
                make_iterator_property_map(root_vec.begin(),
                    choose_const_pmap(
                        get_param(params, vertex_index), g, vertex_index),
                    root_vec[0]),
                params, get_param(params, vertex_discover_time));
        }
    };

    template < class Graph, class ComponentMap, class RootMap, class P, class T,
        class R >
    inline typename property_traits< ComponentMap >::value_type scc_helper1(
        const Graph& g, ComponentMap comp,
        const bgl_named_params< P, T, R >& params, RootMap r_map)
    {
        return detail::strong_comp_dispatch1< RootMap >::apply(
            g, comp, params, r_map);
    }

} // namespace detail

template < class Graph, class ComponentMap, class P, class T, class R >
inline typename property_traits< ComponentMap >::value_type strong_components(
    const Graph& g, ComponentMap comp,
    const bgl_named_params< P, T, R >& params BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        Graph, vertex_list_graph_tag))
{
    typedef typename graph_traits< Graph >::directed_category DirCat;
    BOOST_STATIC_ASSERT(
        (is_convertible< DirCat*, directed_tag* >::value == true));
    return detail::scc_helper1(
        g, comp, params, get_param(params, vertex_root_t()));
}

template < class Graph, class ComponentMap >
inline typename property_traits< ComponentMap >::value_type strong_components(
    const Graph& g,
    ComponentMap comp BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        Graph, vertex_list_graph_tag))
{
    typedef typename graph_traits< Graph >::directed_category DirCat;
    BOOST_STATIC_ASSERT(
        (is_convertible< DirCat*, directed_tag* >::value == true));
    bgl_named_params< int, int > params(0);
    return strong_components(g, comp, params);
}

template < typename Graph, typename ComponentMap, typename ComponentLists >
void build_component_lists(const Graph& g,
    typename graph_traits< Graph >::vertices_size_type num_scc,
    ComponentMap component_number, ComponentLists& components)
{
    components.resize(num_scc);
    typename graph_traits< Graph >::vertex_iterator vi, vi_end;
    for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
        components[component_number[*vi]].push_back(*vi);
}

} // namespace boost

#include <queue>
#include <vector>
#include <boost/graph/transpose_graph.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/graph/connected_components.hpp> // for components_recorder

namespace boost
{

//==========================================================================
// This is the version of strongly connected components from
// "Intro. to Algorithms" by Cormen, Leiserson, Rivest, which was
// adapted from "Data Structure and Algorithms" by Aho, Hopcroft,
// and Ullman, who credit the algorithm to S.R. Kosaraju and M. Sharir.
// The algorithm is based on computing DFS forests the graph
// and its transpose.

// This algorithm is slower than Tarjan's by a constant factor, uses
// more memory, and puts more requirements on the graph type.

template < class Graph, class DFSVisitor, class ComponentsMap,
    class DiscoverTime, class FinishTime, class ColorMap >
typename property_traits< ComponentsMap >::value_type
kosaraju_strong_components(
    Graph& G, ComponentsMap c, FinishTime finish_time, ColorMap color)
{
    BOOST_CONCEPT_ASSERT((MutableGraphConcept< Graph >));
    // ...

    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename property_traits< ColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;
    typename property_traits< FinishTime >::value_type time = 0;
    depth_first_search(G,
        make_dfs_visitor(stamp_times(finish_time, time, on_finish_vertex())),
        color);

    Graph G_T(num_vertices(G));
    transpose_graph(G, G_T);

    typedef typename property_traits< ComponentsMap >::value_type count_type;

    count_type c_count(0);
    detail::components_recorder< ComponentsMap > vis(c, c_count);

    // initialize G_T
    typename graph_traits< Graph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(G_T); ui != ui_end; ++ui)
        put(color, *ui, Color::white());

    typedef typename property_traits< FinishTime >::value_type D;
    typedef indirect_cmp< FinishTime, std::less< D > > Compare;

    Compare fl(finish_time);
    std::priority_queue< Vertex, std::vector< Vertex >, Compare > Q(fl);

    typename graph_traits< Graph >::vertex_iterator i, j, iend, jend;
    boost::tie(i, iend) = vertices(G_T);
    boost::tie(j, jend) = vertices(G);
    for (; i != iend; ++i, ++j)
    {
        put(finish_time, *i, get(finish_time, *j));
        Q.push(*i);
    }

    while (!Q.empty())
    {
        Vertex u = Q.top();
        Q.pop();
        if (get(color, u) == Color::white())
        {
            depth_first_visit(G_T, u, vis, color);
            ++c_count;
        }
    }
    return c_count;
}

} // namespace boost

#include BOOST_GRAPH_MPI_INCLUDE(<boost/graph/distributed/strong_components.hpp>)

#endif // BOOST_GRAPH_STRONG_COMPONENTS_HPP

/* strong_components.hpp
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
*/