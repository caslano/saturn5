//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2004, 2005 Trustees of Indiana University
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek,
//          Doug Gregor, D. Kevin McGrath
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================//
#ifndef BOOST_GRAPH_KING_HPP
#define BOOST_GRAPH_KING_HPP

#include <deque>
#include <vector>
#include <algorithm>
#include <boost/config.hpp>
#include <boost/bind/bind.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/detail/sparse_ordering.hpp>
#include <boost/graph/graph_utility.hpp>

/*
  King Algorithm for matrix reordering
*/

namespace boost
{
namespace detail
{
    template < typename OutputIterator, typename Buffer, typename Compare,
        typename PseudoDegreeMap, typename VecMap, typename VertexIndexMap >
    class bfs_king_visitor : public default_bfs_visitor
    {
    public:
        bfs_king_visitor(OutputIterator* iter, Buffer* b, Compare compare,
            PseudoDegreeMap deg, std::vector< int > loc, VecMap color,
            VertexIndexMap vertices)
        : permutation(iter)
        , Qptr(b)
        , degree(deg)
        , comp(compare)
        , Qlocation(loc)
        , colors(color)
        , vertex_map(vertices)
        {
        }

        template < typename Vertex, typename Graph >
        void finish_vertex(Vertex, Graph& g)
        {
            using namespace boost::placeholders;

            typename graph_traits< Graph >::out_edge_iterator ei, ei_end;
            Vertex v, w;

            typedef typename std::deque< Vertex >::reverse_iterator
                reverse_iterator;

            reverse_iterator rend = Qptr->rend() - index_begin;
            reverse_iterator rbegin = Qptr->rbegin();

            // heap the vertices already there
            std::make_heap(rbegin, rend, boost::bind< bool >(comp, _2, _1));

            unsigned i = 0;

            for (i = index_begin; i != Qptr->size(); ++i)
            {
                colors[get(vertex_map, (*Qptr)[i])] = 1;
                Qlocation[get(vertex_map, (*Qptr)[i])] = i;
            }

            i = 0;

            for (; rbegin != rend; rend--)
            {
                percolate_down< Vertex >(i);
                w = (*Qptr)[index_begin + i];
                for (boost::tie(ei, ei_end) = out_edges(w, g); ei != ei_end;
                     ++ei)
                {
                    v = target(*ei, g);
                    put(degree, v, get(degree, v) - 1);

                    if (colors[get(vertex_map, v)] == 1)
                    {
                        percolate_up< Vertex >(get(vertex_map, v), i);
                    }
                }

                colors[get(vertex_map, w)] = 0;
                i++;
            }
        }

        template < typename Vertex, typename Graph >
        void examine_vertex(Vertex u, const Graph&)
        {

            *(*permutation)++ = u;
            index_begin = Qptr->size();
        }

    protected:
        // this function replaces pop_heap, and tracks state information
        template < typename Vertex > void percolate_down(int offset)
        {
            int heap_last = index_begin + offset;
            int heap_first = Qptr->size() - 1;

            // pop_heap functionality:
            // swap first, last
            std::swap((*Qptr)[heap_last], (*Qptr)[heap_first]);

            // swap in the location queue
            std::swap(Qlocation[heap_first], Qlocation[heap_last]);

            // set drifter, children
            int drifter = heap_first;
            int drifter_heap = Qptr->size() - drifter;

            int right_child_heap = drifter_heap * 2 + 1;
            int right_child = Qptr->size() - right_child_heap;

            int left_child_heap = drifter_heap * 2;
            int left_child = Qptr->size() - left_child_heap;

            // check that we are staying in the heap
            bool valid = (right_child < heap_last) ? false : true;

            // pick smallest child of drifter, and keep in mind there might only
            // be left child
            int smallest_child = (valid
                                     && get(degree, (*Qptr)[left_child])
                                         > get(degree, (*Qptr)[right_child]))
                ? right_child
                : left_child;

            while (valid && smallest_child < heap_last
                && comp((*Qptr)[drifter], (*Qptr)[smallest_child]))
            {

                // if smallest child smaller than drifter, swap them
                std::swap((*Qptr)[smallest_child], (*Qptr)[drifter]);
                std::swap(Qlocation[drifter], Qlocation[smallest_child]);

                // update the values, run again, as necessary
                drifter = smallest_child;
                drifter_heap = Qptr->size() - drifter;

                right_child_heap = drifter_heap * 2 + 1;
                right_child = Qptr->size() - right_child_heap;

                left_child_heap = drifter_heap * 2;
                left_child = Qptr->size() - left_child_heap;

                valid = (right_child < heap_last) ? false : true;

                smallest_child = (valid
                                     && get(degree, (*Qptr)[left_child])
                                         > get(degree, (*Qptr)[right_child]))
                    ? right_child
                    : left_child;
            }
        }

        // this is like percolate down, but we always compare against the
        // parent, as there is only a single choice
        template < typename Vertex > void percolate_up(int vertex, int offset)
        {

            int child_location = Qlocation[vertex];
            int heap_child_location = Qptr->size() - child_location;
            int heap_parent_location = (int)(heap_child_location / 2);
            unsigned parent_location = Qptr->size() - heap_parent_location;

            bool valid = (heap_parent_location != 0
                && child_location > index_begin + offset
                && parent_location < Qptr->size());

            while (valid
                && comp((*Qptr)[child_location], (*Qptr)[parent_location]))
            {

                // swap in the heap
                std::swap((*Qptr)[child_location], (*Qptr)[parent_location]);

                // swap in the location queue
                std::swap(
                    Qlocation[child_location], Qlocation[parent_location]);

                child_location = parent_location;
                heap_child_location = heap_parent_location;
                heap_parent_location = (int)(heap_child_location / 2);
                parent_location = Qptr->size() - heap_parent_location;
                valid = (heap_parent_location != 0
                    && child_location > index_begin + offset);
            }
        }

        OutputIterator* permutation;
        int index_begin;
        Buffer* Qptr;
        PseudoDegreeMap degree;
        Compare comp;
        std::vector< int > Qlocation;
        VecMap colors;
        VertexIndexMap vertex_map;
    };

} // namespace detail

template < class Graph, class OutputIterator, class ColorMap, class DegreeMap,
    typename VertexIndexMap >
OutputIterator king_ordering(const Graph& g,
    std::deque< typename graph_traits< Graph >::vertex_descriptor >
        vertex_queue,
    OutputIterator permutation, ColorMap color, DegreeMap degree,
    VertexIndexMap index_map)
{
    typedef typename property_traits< DegreeMap >::value_type ds_type;
    typedef typename property_traits< ColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef iterator_property_map< typename std::vector< ds_type >::iterator,
        VertexIndexMap, ds_type, ds_type& >
        PseudoDegreeMap;
    typedef indirect_cmp< PseudoDegreeMap, std::less< ds_type > > Compare;
    typedef typename boost::sparse::sparse_ordering_queue< Vertex > queue;
    typedef typename detail::bfs_king_visitor< OutputIterator, queue, Compare,
        PseudoDegreeMap, std::vector< int >, VertexIndexMap >
        Visitor;
    typedef
        typename graph_traits< Graph >::vertices_size_type vertices_size_type;
    std::vector< ds_type > pseudo_degree_vec(num_vertices(g));
    PseudoDegreeMap pseudo_degree(pseudo_degree_vec.begin(), index_map);

    typename graph_traits< Graph >::vertex_iterator ui, ui_end;
    queue Q;
    // Copy degree to pseudo_degree
    // initialize the color map
    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
    {
        put(pseudo_degree, *ui, get(degree, *ui));
        put(color, *ui, Color::white());
    }

    Compare comp(pseudo_degree);
    std::vector< int > colors(num_vertices(g));

    for (vertices_size_type i = 0; i < num_vertices(g); i++)
        colors[i] = 0;

    std::vector< int > loc(num_vertices(g));

    // create the visitor
    Visitor vis(&permutation, &Q, comp, pseudo_degree, loc, colors, index_map);

    while (!vertex_queue.empty())
    {
        Vertex s = vertex_queue.front();
        vertex_queue.pop_front();

        // call BFS with visitor
        breadth_first_visit(g, s, Q, vis, color);
    }

    return permutation;
}

// This is the case where only a single starting vertex is supplied.
template < class Graph, class OutputIterator, class ColorMap, class DegreeMap,
    typename VertexIndexMap >
OutputIterator king_ordering(const Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    OutputIterator permutation, ColorMap color, DegreeMap degree,
    VertexIndexMap index_map)
{

    std::deque< typename graph_traits< Graph >::vertex_descriptor >
        vertex_queue;
    vertex_queue.push_front(s);
    return king_ordering(
        g, vertex_queue, permutation, color, degree, index_map);
}

template < class Graph, class OutputIterator, class ColorMap, class DegreeMap,
    class VertexIndexMap >
OutputIterator king_ordering(const Graph& G, OutputIterator permutation,
    ColorMap color, DegreeMap degree, VertexIndexMap index_map)
{
    if (has_no_vertices(G))
        return permutation;

    typedef typename boost::graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename property_traits< ColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;

    std::deque< Vertex > vertex_queue;

    // Mark everything white
    BGL_FORALL_VERTICES_T(v, G, Graph) put(color, v, Color::white());

    // Find one vertex from each connected component
    BGL_FORALL_VERTICES_T(v, G, Graph)
    {
        if (get(color, v) == Color::white())
        {
            depth_first_visit(G, v, dfs_visitor<>(), color);
            vertex_queue.push_back(v);
        }
    }

    // Find starting nodes for all vertices
    // TBD: How to do this with a directed graph?
    for (typename std::deque< Vertex >::iterator i = vertex_queue.begin();
         i != vertex_queue.end(); ++i)
        *i = find_starting_node(G, *i, color, degree);

    return king_ordering(
        G, vertex_queue, permutation, color, degree, index_map);
}

template < typename Graph, typename OutputIterator, typename VertexIndexMap >
OutputIterator king_ordering(
    const Graph& G, OutputIterator permutation, VertexIndexMap index_map)
{
    if (has_no_vertices(G))
        return permutation;

    std::vector< default_color_type > colors(num_vertices(G));
    return king_ordering(G, permutation,
        make_iterator_property_map(&colors[0], index_map, colors[0]),
        make_out_degree_map(G), index_map);
}

template < typename Graph, typename OutputIterator >
inline OutputIterator king_ordering(const Graph& G, OutputIterator permutation)
{
    return king_ordering(G, permutation, get(vertex_index, G));
}

} // namespace boost

#endif // BOOST_GRAPH_KING_HPP

/* king_ordering.hpp
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
*/