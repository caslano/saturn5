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
9I035SAMKt/6cpP9hQ4Hw9PumMzQwEcO3bGz2d7sUKH2fq698rP/N7BYaq2H/dHFaT9X+1fjVxmYczM16jTYsPmOCkdCVT3v2VvJyL1ty3I2PtdbLv1Q27norRDT5WoRvKAbw7hIh079JxQljykbMDr1Y5CkOZM83wf4yhm474d4VdsvA753CP52z8/7eKmeNsMKvH2tpy2BUR3PlBucyELiLKMkIG82dG3Lj7dmUMXB6J315j4I/YR0l/4MLwpFoQCn2gqjeOFhDgsYShDF7YaTHw8vznrFQ01CDeynbe71yTxK/EIZOdzcc3H9hqqMkKjd1DYRkMbfKbE1Y09FM/OT/Bg1rOVsEE3cqnRC1mpRPZZ0cjc74v0N5luMWb8Y4gtzPvY2yMkJr80zC2vbgoBPSO4uggQjf9HInhSr2FgTIO3zdrtIzhClUt5VYgNRohR0luFtKK/nND5kH9rLk7LypBXPi0WtQmbuDrECsawJH9cnV55czyZ1bihgaJvZ07Yz8shU3GUU+v6Uj1Z9ykSMEJtEMZ53ZAOQFMAal2olKaYD+omfPuPsMA5wLV6VGLYPEJFFtMKLimbO5T1yXJXFNAiXK921SfNSxaG6IpmyBqRmyVfFiqkkKrkm9S5YT+mUcYRmYXmYnwUP
*/