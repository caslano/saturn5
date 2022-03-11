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

#include <boost/config.hpp>
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