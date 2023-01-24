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
a48jIs1ZS2DZEAGKEdzl1w1pQluqty93W/ugs6KferRGMFW/2fDb6pNgUbxNu5X2vGf8MgtfhnuXmX3VBk/XH48F+X9P4RfWZ9Zpmw244wDZ5XBUzEnl5d+ULrjlJC5Uh8q/5MtDge3QQd8nwetOtY2OTZTxVVeOzHFXraPLO2XXF8yd2CTXKI1bzTaB8iva90gUJWjJUiEItciIEqG7V/bYN69+GTDdboL75CUqBpgJ+Hn2dlo711H5KkCgc+EF0tcgu7wvgGEM9V4W6Yzc3rsrPCNaJ4J5wRgIJkgYswiRvo7m6lBw0P6W7p8BSSe1Lil+KbbVvE5bfIcBLGPw4AoU1t8hLjD8eZzn7xDn+L/Tdb5P/0rX+f49XRfGcyJZ/bHJwAkJfoEWvDfzXhCHAKelhvQNizjEf2iAbpaODvqZRbo7hG/DRltAJOYvmfAPIHn9enVyLua0UpVjNTfL7nGtVdjTabRLp4bBGxYlE5iLO5UI6ShdlYbdKE+G3HQn3P7Bz6JFl6woLYq96vrkV9bt8fKzIfjcn9fxsAaoc3UG9LF/lvhsKPyK6dJ/CS/G+ZcKvXLaZ5LiJ3/+HLfqZgl5VAMkAYdUt13TmVrM1dLWUPq70hGTvkJHaGOwE+vOx4GDAUyjsNNRNdIDbVhqQDryoiIlkb7xc9grxmOHge/+HzJ569ASTuCTZPkNtdDfjpGH8fq6j08AftT7
*/