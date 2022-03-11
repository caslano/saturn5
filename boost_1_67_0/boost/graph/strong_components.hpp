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

#include BOOST_GRAPH_MPI_INCLUDE(< boost / graph / distributed / strong_components.hpp >)

#endif // BOOST_GRAPH_STRONG_COMPONENTS_HPP

/* strong_components.hpp
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
*/