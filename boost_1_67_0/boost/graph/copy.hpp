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