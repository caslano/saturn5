//=======================================================================
// Copyright 2007 Aaron Windsor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef __MAKE_CONNECTED_HPP__
#define __MAKE_CONNECTED_HPP__

#include <boost/config.hpp>
#include <boost/next_prior.hpp>
#include <boost/tuple/tuple.hpp> //for tie
#include <boost/graph/connected_components.hpp>
#include <boost/property_map/property_map.hpp>
#include <vector>

#include <boost/graph/planar_detail/add_edge_visitors.hpp>
#include <boost/graph/planar_detail/bucket_sort.hpp>

namespace boost
{

template < typename Graph, typename VertexIndexMap, typename AddEdgeVisitor >
void make_connected(Graph& g, VertexIndexMap vm, AddEdgeVisitor& vis)
{
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator_t;
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
    typedef typename graph_traits< Graph >::vertices_size_type v_size_t;
    typedef iterator_property_map< typename std::vector< v_size_t >::iterator,
        VertexIndexMap >
        vertex_to_v_size_map_t;

    std::vector< v_size_t > component_vector(num_vertices(g));
    vertex_to_v_size_map_t component(component_vector.begin(), vm);
    std::vector< vertex_t > vertices_by_component(num_vertices(g));

    v_size_t num_components = connected_components(g, component);

    if (num_components < 2)
        return;

    vertex_iterator_t vi, vi_end;
    boost::tie(vi, vi_end) = vertices(g);
    std::copy(vi, vi_end, vertices_by_component.begin());

    bucket_sort(vertices_by_component.begin(), vertices_by_component.end(),
        component, num_components);

    typedef typename std::vector< vertex_t >::iterator vec_of_vertices_itr_t;

    vec_of_vertices_itr_t ci_end = vertices_by_component.end();
    vec_of_vertices_itr_t ci_prev = vertices_by_component.begin();
    if (ci_prev == ci_end)
        return;

    for (vec_of_vertices_itr_t ci = boost::next(ci_prev); ci != ci_end;
         ci_prev = ci, ++ci)
    {
        if (component[*ci_prev] != component[*ci])
            vis.visit_vertex_pair(*ci_prev, *ci, g);
    }
}

template < typename Graph, typename VertexIndexMap >
inline void make_connected(Graph& g, VertexIndexMap vm)
{
    default_add_edge_visitor vis;
    make_connected(g, vm, vis);
}

template < typename Graph > inline void make_connected(Graph& g)
{
    make_connected(g, get(vertex_index, g));
}

} // namespace boost

#endif //__MAKE_CONNECTED_HPP__

/* make_connected.hpp
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
*/