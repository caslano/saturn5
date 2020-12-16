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
PoDGYX0F1s/2FRi/8L4C4xdw7dKHp6YnY4p/FP7V9yHM4Nmxsxkn2zqoZLvQUeoEw7X6QflGd77AtCpjY4uoTbbvwNg0V/GmL6C5uGc5R1RdxljUk3BfN9bhWK9b2T4FE66lhEvH3VLcM5xDKlq159TG2+9QT59XUpJbWJYjX1+037vqLvY/qFZqh/Fz1CLxe1ZFqft83xfU4XJyS0qKSnB432sW2zjnbpXqPmsTfuBN4qd686wdjW06B/gb8x2PceZ7GIs4lhlNuI9LcN3DY10tNd+74OHzR5+Np8jveO4s664TG8nf/mfS72+0z6Tu2ET7DCrnwY5NJI/xkzyWZ1A7F6Sukm2U6R86FSZQJirkd8q9tcvJr5MSqp6nEU7Irqv9ZuQT4v6dcTvq7rWyX8I3kL4j7xuwqdhvFvv3nRTnAvfc2zg72m+yKonjN7izuT89UfpugnE6rnlMR/C+x5dhw55ix/8+Ju53na7OddjgR3xrJL4zfPGU2XjiTHl7ScI9y0jWOyTcGBv3YHGnSzzesdWReKaXFJR6ZbhojYzFl/HK3KNzRKE4HJlfUYw73tab0ryic3NC6bBhEsPCSN676WYTc5Me+ork9+6oLn32u4vQ9j+96palgFsHJb5Sbhm8OTKy/zFH3PZcnqzCvwE/TvdDie0RJ2zsrtSlSyVdbRxxe2XCVwcL583JmVcoX+TMnWH70D6WcNcZt3fevN84x/bZ/VZ+vwnHImkz9dqbPxIvYRupZmpUbLsg90M8nwdj9Te0lk6ODpbw0a0av7kl9gXYR2j7hkvfDv9uVryxWYXNVm1Tb2lxdLDRUd8bm4Y7QbnfO1oX5/aX5eFxh/k7P4EjQnM5F+nGr4S/ZyfI38htawrE7elhbCvw3x77U/rf6sSuW3t0vxV127QPXr8V9RU/t77G4zcFP8odfrbeiX+e9ffXo1gp33XE360XzfBbYNsnX3k345s7uelSk9x5GrYPe+PxSratXNhPFLp92HvFvty9Irtd2NX2YetIvrlF2wbtdckNm2r7WTvdrN1Jdvz9n8X+CWeYetO1wfXtrdqv2I5B/6O4S2vsF+c3bHsxCncb+Y3J9luhgUrt/toZyG/cRs2JEztHfSm/XRaIUt87Xh0hD3NmFJ1bWFA01XxfPhHfQRJnlwi3fbX95rYdO0f2Dw/GBW6x7YKb7nnYECb0jfWpZXly3kzaW0jaTnAS1Kf6t6Q8dJC4kiPC25Nmpl88IPsnRFwU+Lm6JxhQXwcnyLE2xvfiSrc9baB60mdyorQTjU0/fjNzTuZK+EucTqqVk4HluU5A8vZBSeP84jnyW27ejRLbxhEPkXs7ApepqcERks6+2IyQfW0ivLwjbFkRhTZ3hr+PPk7sMiP8+SCl3TdPoK6ku6vTXn1u30V0lXADI6qbH/mm2P/MlqvF4s6p8p1o8ysSn/QNSXyJpCPUrodaQmXn4ZlrDJtbl/CXeuuFse2n7EtRVb8VzW9JPa0rv5UbYa7nbKVlRSW5du5iPdk/zpd3/nrqva9pJnapEf7jMqVIfmsrPr3Epk9ETd9cXSl5E2nb6KvF3dPcG4TKzHjuFPvL8W8y5YBIbBz7xSaKMMwBrMszYzRtjm6DY5eNCG+nQzZ9sYlwbfrVZDPRs+kYbvMg7lNwj/V//9CnwzFVGe37vuBZcdhX862+O2KrfoOuCBYj8TOcC0tQqc99gfkOYy5ait8luGcluJqE3zIdr7kuFP+Ee8+C27z3MptuOfqbSNd6fj1Cfld5ft1DfpPxC/8mUgvPr0/Ib9/N1q9XyG+P52d/d6fnd1rI79een03Lg56fTcvZlSG/7vZ3B3l+vUPvg6R9910=
*/