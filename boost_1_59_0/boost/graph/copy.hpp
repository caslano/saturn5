//
//=======================================================================
// Copyright 1997-2001 University of Notre Dame.
// Authors: Jeremy G. Siek, Lie-Quan Lee, Andrew Lumsdaine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

/*
  This file implements the following functions:


  template <typename VertexListGraph, typename MutableGraph>
  void copy_graph(const VertexListGraph& g_in, MutableGraph& g_out)

  template <typename VertexListGraph, typename MutableGraph,
    class P, class T, class R>
  void copy_graph(const VertexListGraph& g_in, MutableGraph& g_out,
                  const bgl_named_params<P, T, R>& params)


  template <typename IncidenceGraph, typename MutableGraph>
  typename graph_traits<MutableGraph>::vertex_descriptor
  copy_component(IncidenceGraph& g_in,
                 typename graph_traits<IncidenceGraph>::vertex_descriptor src,
                 MutableGraph& g_out)

  template <typename IncidenceGraph, typename MutableGraph,
           typename P, typename T, typename R>
  typename graph_traits<MutableGraph>::vertex_descriptor
  copy_component(IncidenceGraph& g_in,
                 typename graph_traits<IncidenceGraph>::vertex_descriptor src,
                 MutableGraph& g_out,
                 const bgl_named_params<P, T, R>& params)
 */

#ifndef BOOST_GRAPH_COPY_HPP
#define BOOST_GRAPH_COPY_HPP

#include <boost/config.hpp>
#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/reverse_graph.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/type_traits/conversion_traits.hpp>

namespace boost
{

namespace detail
{

    // Hack to make transpose_graph work with the same interface as before
    template < typename Graph, typename Desc >
    struct remove_reverse_edge_descriptor
    {
        typedef Desc type;
        static Desc convert(const Desc& d, const Graph&) { return d; }
    };

    template < typename Graph, typename Desc >
    struct remove_reverse_edge_descriptor< Graph,
        reverse_graph_edge_descriptor< Desc > >
    {
        typedef Desc type;
        static Desc convert(
            const reverse_graph_edge_descriptor< Desc >& d, const Graph& g)
        {
            return get(edge_underlying, g, d);
        }
    };

    // Add a reverse_graph_edge_descriptor wrapper if the Graph is a
    // reverse_graph but the edge descriptor is from the original graph (this
    // case comes from the fact that transpose_graph uses reverse_graph
    // internally but doesn't expose the different edge descriptor type to the
    // user).
    template < typename Desc, typename Graph >
    struct add_reverse_edge_descriptor
    {
        typedef Desc type;
        static Desc convert(const Desc& d) { return d; }
    };

    template < typename Desc, typename G, typename GR >
    struct add_reverse_edge_descriptor< Desc, boost::reverse_graph< G, GR > >
    {
        typedef reverse_graph_edge_descriptor< Desc > type;
        static reverse_graph_edge_descriptor< Desc > convert(const Desc& d)
        {
            return reverse_graph_edge_descriptor< Desc >(d);
        }
    };

    template < typename Desc, typename G, typename GR >
    struct add_reverse_edge_descriptor< reverse_graph_edge_descriptor< Desc >,
        boost::reverse_graph< G, GR > >
    {
        typedef reverse_graph_edge_descriptor< Desc > type;
        static reverse_graph_edge_descriptor< Desc > convert(
            const reverse_graph_edge_descriptor< Desc >& d)
        {
            return d;
        }
    };

    // Default edge and vertex property copiers

    template < typename Graph1, typename Graph2 > struct edge_copier
    {
        edge_copier(const Graph1& g1, Graph2& g2)
        : edge_all_map1(get(edge_all, g1)), edge_all_map2(get(edge_all, g2))
        {
        }

        template < typename Edge1, typename Edge2 >
        void operator()(const Edge1& e1, Edge2& e2) const
        {
            put(edge_all_map2, e2,
                get(edge_all_map1,
                    add_reverse_edge_descriptor< Edge1, Graph1 >::convert(e1)));
        }
        typename property_map< Graph1, edge_all_t >::const_type edge_all_map1;
        mutable typename property_map< Graph2, edge_all_t >::type edge_all_map2;
    };
    template < typename Graph1, typename Graph2 >
    inline edge_copier< Graph1, Graph2 > make_edge_copier(
        const Graph1& g1, Graph2& g2)
    {
        return edge_copier< Graph1, Graph2 >(g1, g2);
    }

    template < typename Graph1, typename Graph2 > struct vertex_copier
    {
        vertex_copier(const Graph1& g1, Graph2& g2)
        : vertex_all_map1(get(vertex_all, g1))
        , vertex_all_map2(get(vertex_all, g2))
        {
        }

        template < typename Vertex1, typename Vertex2 >
        void operator()(const Vertex1& v1, Vertex2& v2) const
        {
            put(vertex_all_map2, v2, get(vertex_all_map1, v1));
        }
        typename property_map< Graph1, vertex_all_t >::const_type
            vertex_all_map1;
        mutable
            typename property_map< Graph2, vertex_all_t >::type vertex_all_map2;
    };
    template < typename Graph1, typename Graph2 >
    inline vertex_copier< Graph1, Graph2 > make_vertex_copier(
        const Graph1& g1, Graph2& g2)
    {
        return vertex_copier< Graph1, Graph2 >(g1, g2);
    }

    // Copy all the vertices and edges of graph g_in into graph g_out.
    // The copy_vertex and copy_edge function objects control how vertex
    // and edge properties are copied.

    template < int Version > struct copy_graph_impl
    {
    };

    template <> struct copy_graph_impl< 0 >
    {
        template < typename Graph, typename MutableGraph, typename CopyVertex,
            typename CopyEdge, typename IndexMap,
            typename Orig2CopyVertexIndexMap >
        static void apply(const Graph& g_in, MutableGraph& g_out,
            CopyVertex copy_vertex, CopyEdge copy_edge,
            Orig2CopyVertexIndexMap orig2copy, IndexMap)
        {
            typedef remove_reverse_edge_descriptor< Graph,
                typename graph_traits< Graph >::edge_descriptor >
                cvt;
            typename graph_traits< Graph >::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end) = vertices(g_in); vi != vi_end; ++vi)
            {
                typename graph_traits< MutableGraph >::vertex_descriptor new_v
                    = add_vertex(g_out);
                put(orig2copy, *vi, new_v);
                copy_vertex(*vi, new_v);
            }
            typename graph_traits< Graph >::edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end) = edges(g_in); ei != ei_end; ++ei)
            {
                typename graph_traits< MutableGraph >::edge_descriptor new_e;
                bool inserted;
                boost::tie(new_e, inserted)
                    = add_edge(get(orig2copy, source(*ei, g_in)),
                        get(orig2copy, target(*ei, g_in)), g_out);
                copy_edge(cvt::convert(*ei, g_in), new_e);
            }
        }
    };

    // for directed graphs
    template <> struct copy_graph_impl< 1 >
    {
        template < typename Graph, typename MutableGraph, typename CopyVertex,
            typename CopyEdge, typename IndexMap,
            typename Orig2CopyVertexIndexMap >
        static void apply(const Graph& g_in, MutableGraph& g_out,
            CopyVertex copy_vertex, CopyEdge copy_edge,
            Orig2CopyVertexIndexMap orig2copy, IndexMap)
        {
            typedef remove_reverse_edge_descriptor< Graph,
                typename graph_traits< Graph >::edge_descriptor >
                cvt;
            typename graph_traits< Graph >::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end) = vertices(g_in); vi != vi_end; ++vi)
            {
                typename graph_traits< MutableGraph >::vertex_descriptor new_v
                    = add_vertex(g_out);
                put(orig2copy, *vi, new_v);
                copy_vertex(*vi, new_v);
            }
            for (boost::tie(vi, vi_end) = vertices(g_in); vi != vi_end; ++vi)
            {
                typename graph_traits< Graph >::out_edge_iterator ei, ei_end;
                for (boost::tie(ei, ei_end) = out_edges(*vi, g_in);
                     ei != ei_end; ++ei)
                {
                    typename graph_traits< MutableGraph >::edge_descriptor
                        new_e;
                    bool inserted;
                    boost::tie(new_e, inserted)
                        = add_edge(get(orig2copy, source(*ei, g_in)),
                            get(orig2copy, target(*ei, g_in)), g_out);
                    copy_edge(cvt::convert(*ei, g_in), new_e);
                }
            }
        }
    };

    // for undirected graphs
    template <> struct copy_graph_impl< 2 >
    {
        template < typename Graph, typename MutableGraph, typename CopyVertex,
            typename CopyEdge, typename IndexMap,
            typename Orig2CopyVertexIndexMap >
        static void apply(const Graph& g_in, MutableGraph& g_out,
            CopyVertex copy_vertex, CopyEdge copy_edge,
            Orig2CopyVertexIndexMap orig2copy, IndexMap index_map)
        {
            typedef remove_reverse_edge_descriptor< Graph,
                typename graph_traits< Graph >::edge_descriptor >
                cvt;
            typedef color_traits< default_color_type > Color;
            std::vector< default_color_type > color(
                num_vertices(g_in), Color::white());
            typename graph_traits< Graph >::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end) = vertices(g_in); vi != vi_end; ++vi)
            {
                typename graph_traits< MutableGraph >::vertex_descriptor new_v
                    = add_vertex(g_out);
                put(orig2copy, *vi, new_v);
                copy_vertex(*vi, new_v);
            }
            for (boost::tie(vi, vi_end) = vertices(g_in); vi != vi_end; ++vi)
            {
                typename graph_traits< Graph >::out_edge_iterator ei, ei_end;
                for (boost::tie(ei, ei_end) = out_edges(*vi, g_in);
                     ei != ei_end; ++ei)
                {
                    typename graph_traits< MutableGraph >::edge_descriptor
                        new_e;
                    bool inserted;
                    if (color[get(index_map, target(*ei, g_in))]
                        == Color::white())
                    {
                        boost::tie(new_e, inserted)
                            = add_edge(get(orig2copy, source(*ei, g_in)),
                                get(orig2copy, target(*ei, g_in)), g_out);
                        copy_edge(cvt::convert(*ei, g_in), new_e);
                    }
                }
                color[get(index_map, *vi)] = Color::black();
            }
        }
    };

    template < class Graph > struct choose_graph_copy
    {
        typedef typename graph_traits< Graph >::traversal_category Trv;
        typedef typename graph_traits< Graph >::directed_category Dr;
        enum
        {
            algo = (is_convertible< Trv, vertex_list_graph_tag >::value
                       && is_convertible< Trv, edge_list_graph_tag >::value)
                ? 0
                : is_convertible< Dr, directed_tag >::value ? 1 : 2
        };
        typedef copy_graph_impl< algo > type;
    };

    //-------------------------------------------------------------------------
    struct choose_copier_parameter
    {
        template < class P, class G1, class G2 > struct bind_
        {
            typedef const P& result_type;
            static result_type apply(const P& p, const G1&, G2&) { return p; }
        };
    };
    struct choose_default_edge_copier
    {
        template < class P, class G1, class G2 > struct bind_
        {
            typedef edge_copier< G1, G2 > result_type;
            static result_type apply(const P&, const G1& g1, G2& g2)
            {
                return result_type(g1, g2);
            }
        };
    };
    template < class Param > struct choose_edge_copy
    {
        typedef choose_copier_parameter type;
    };
    template <> struct choose_edge_copy< param_not_found >
    {
        typedef choose_default_edge_copier type;
    };
    template < class Param, class G1, class G2 >
    struct choose_edge_copier_helper
    {
        typedef typename choose_edge_copy< Param >::type Selector;
        typedef typename Selector::template bind_< Param, G1, G2 > Bind;
        typedef Bind type;
        typedef typename Bind::result_type result_type;
    };
    template < typename Param, typename G1, typename G2 >
    typename detail::choose_edge_copier_helper< Param, G1, G2 >::result_type
    choose_edge_copier(const Param& params, const G1& g_in, G2& g_out)
    {
        typedef
            typename detail::choose_edge_copier_helper< Param, G1, G2 >::type
                Choice;
        return Choice::apply(params, g_in, g_out);
    }

    struct choose_default_vertex_copier
    {
        template < class P, class G1, class G2 > struct bind_
        {
            typedef vertex_copier< G1, G2 > result_type;
            static result_type apply(const P&, const G1& g1, G2& g2)
            {
                return result_type(g1, g2);
            }
        };
    };
    template < class Param > struct choose_vertex_copy
    {
        typedef choose_copier_parameter type;
    };
    template <> struct choose_vertex_copy< param_not_found >
    {
        typedef choose_default_vertex_copier type;
    };
    template < class Param, class G1, class G2 >
    struct choose_vertex_copier_helper
    {
        typedef typename choose_vertex_copy< Param >::type Selector;
        typedef typename Selector::template bind_< Param, G1, G2 > Bind;
        typedef Bind type;
        typedef typename Bind::result_type result_type;
    };
    template < typename Param, typename G1, typename G2 >
    typename detail::choose_vertex_copier_helper< Param, G1, G2 >::result_type
    choose_vertex_copier(const Param& params, const G1& g_in, G2& g_out)
    {
        typedef
            typename detail::choose_vertex_copier_helper< Param, G1, G2 >::type
                Choice;
        return Choice::apply(params, g_in, g_out);
    }

} // namespace detail

template < typename VertexListGraph, typename MutableGraph >
void copy_graph(const VertexListGraph& g_in, MutableGraph& g_out)
{
    if (num_vertices(g_in) == 0)
        return;
    typedef typename graph_traits< MutableGraph >::vertex_descriptor vertex_t;
    std::vector< vertex_t > orig2copy(num_vertices(g_in));
    typedef
        typename detail::choose_graph_copy< VertexListGraph >::type copy_impl;
    copy_impl::apply(g_in, g_out, detail::make_vertex_copier(g_in, g_out),
        detail::make_edge_copier(g_in, g_out),
        make_iterator_property_map(
            orig2copy.begin(), get(vertex_index, g_in), orig2copy[0]),
        get(vertex_index, g_in));
}

template < typename VertexListGraph, typename MutableGraph, class P, class T,
    class R >
void copy_graph(const VertexListGraph& g_in, MutableGraph& g_out,
    const bgl_named_params< P, T, R >& params)
{
    typename std::vector< T >::size_type n;
    n = is_default_param(get_param(params, orig_to_copy_t()))
        ? num_vertices(g_in)
        : 1;
    if (n == 0)
        return;
    std::vector<
        BOOST_DEDUCED_TYPENAME graph_traits< MutableGraph >::vertex_descriptor >
        orig2copy(n);

    typedef
        typename detail::choose_graph_copy< VertexListGraph >::type copy_impl;
    copy_impl::apply(g_in, g_out,
        detail::choose_vertex_copier(
            get_param(params, vertex_copy_t()), g_in, g_out),
        detail::choose_edge_copier(
            get_param(params, edge_copy_t()), g_in, g_out),
        choose_param(get_param(params, orig_to_copy_t()),
            make_iterator_property_map(orig2copy.begin(),
                choose_const_pmap(
                    get_param(params, vertex_index), g_in, vertex_index),
                orig2copy[0])),
        choose_const_pmap(get_param(params, vertex_index), g_in, vertex_index));
}

namespace detail
{

    template < class NewGraph, class Copy2OrigIndexMap, class CopyVertex,
        class CopyEdge >
    struct graph_copy_visitor : public bfs_visitor<>
    {
        graph_copy_visitor(
            NewGraph& graph, Copy2OrigIndexMap c, CopyVertex cv, CopyEdge ce)
        : g_out(graph), orig2copy(c), copy_vertex(cv), copy_edge(ce)
        {
        }

        template < class Vertex >
        typename graph_traits< NewGraph >::vertex_descriptor copy_one_vertex(
            Vertex u) const
        {
            typename graph_traits< NewGraph >::vertex_descriptor new_u
                = add_vertex(g_out);
            put(orig2copy, u, new_u);
            copy_vertex(u, new_u);
            return new_u;
        }

        template < class Edge, class Graph >
        void tree_edge(Edge e, const Graph& g_in) const
        {
            // For a tree edge, the target vertex has not been copied yet.
            typename graph_traits< NewGraph >::edge_descriptor new_e;
            bool inserted;
            boost::tie(new_e, inserted)
                = add_edge(get(orig2copy, source(e, g_in)),
                    this->copy_one_vertex(target(e, g_in)), g_out);
            copy_edge(e, new_e);
        }

        template < class Edge, class Graph >
        void non_tree_edge(Edge e, const Graph& g_in) const
        {
            // For a non-tree edge, the target vertex has already been copied.
            typename graph_traits< NewGraph >::edge_descriptor new_e;
            bool inserted;
            boost::tie(new_e, inserted)
                = add_edge(get(orig2copy, source(e, g_in)),
                    get(orig2copy, target(e, g_in)), g_out);
            copy_edge(e, new_e);
        }

    private:
        NewGraph& g_out;
        Copy2OrigIndexMap orig2copy;
        CopyVertex copy_vertex;
        CopyEdge copy_edge;
    };

    template < typename Graph, typename MutableGraph, typename CopyVertex,
        typename CopyEdge, typename Orig2CopyVertexIndexMap, typename Params >
    typename graph_traits< MutableGraph >::vertex_descriptor
    copy_component_impl(const Graph& g_in,
        typename graph_traits< Graph >::vertex_descriptor src,
        MutableGraph& g_out, CopyVertex copy_vertex, CopyEdge copy_edge,
        Orig2CopyVertexIndexMap orig2copy, const Params& params)
    {
        graph_copy_visitor< MutableGraph, Orig2CopyVertexIndexMap, CopyVertex,
            CopyEdge >
            vis(g_out, orig2copy, copy_vertex, copy_edge);
        typename graph_traits< MutableGraph >::vertex_descriptor src_copy
            = vis.copy_one_vertex(src);
        breadth_first_search(g_in, src, params.visitor(vis));
        return src_copy;
    }

} // namespace detail

// Copy all the vertices and edges of graph g_in that are reachable
// from the source vertex into graph g_out. Return the vertex
// in g_out that matches the source vertex of g_in.
template < typename IncidenceGraph, typename MutableGraph, typename P,
    typename T, typename R >
typename graph_traits< MutableGraph >::vertex_descriptor copy_component(
    IncidenceGraph& g_in,
    typename graph_traits< IncidenceGraph >::vertex_descriptor src,
    MutableGraph& g_out, const bgl_named_params< P, T, R >& params)
{
    typename std::vector< T >::size_type n;
    n = is_default_param(get_param(params, orig_to_copy_t()))
        ? num_vertices(g_in)
        : 1;
    std::vector< typename graph_traits< IncidenceGraph >::vertex_descriptor >
        orig2copy(n);

    return detail::copy_component_impl(g_in, src, g_out,
        detail::choose_vertex_copier(
            get_param(params, vertex_copy_t()), g_in, g_out),
        detail::choose_edge_copier(
            get_param(params, edge_copy_t()), g_in, g_out),
        choose_param(get_param(params, orig_to_copy_t()),
            make_iterator_property_map(orig2copy.begin(),
                choose_pmap(
                    get_param(params, vertex_index), g_in, vertex_index),
                orig2copy[0])),
        params);
}

template < typename IncidenceGraph, typename MutableGraph >
typename graph_traits< MutableGraph >::vertex_descriptor copy_component(
    IncidenceGraph& g_in,
    typename graph_traits< IncidenceGraph >::vertex_descriptor src,
    MutableGraph& g_out)
{
    std::vector< typename graph_traits< IncidenceGraph >::vertex_descriptor >
        orig2copy(num_vertices(g_in));

    return detail::copy_component_impl(g_in, src, g_out,
        make_vertex_copier(g_in, g_out), make_edge_copier(g_in, g_out),
        make_iterator_property_map(
            orig2copy.begin(), get(vertex_index, g_in), orig2copy[0]),
        bgl_named_params< char, char >('x') // dummy param object
    );
}

} // namespace boost

#endif // BOOST_GRAPH_COPY_HPP

/* copy.hpp
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
*/