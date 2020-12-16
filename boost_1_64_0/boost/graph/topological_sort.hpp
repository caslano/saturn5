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
#ifndef BOOST_GRAPH_TOPOLOGICAL_SORT_HPP
#define BOOST_GRAPH_TOPOLOGICAL_SORT_HPP

#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/exception.hpp>
#include <boost/throw_exception.hpp>

namespace boost
{

// Topological sort visitor
//
// This visitor merely writes the linear ordering into an
// OutputIterator. The OutputIterator could be something like an
// ostream_iterator, or it could be a back/front_insert_iterator.
// Note that if it is a back_insert_iterator, the recorded order is
// the reverse topological order. On the other hand, if it is a
// front_insert_iterator, the recorded order is the topological
// order.
//
template < typename OutputIterator >
struct topo_sort_visitor : public dfs_visitor<>
{
    topo_sort_visitor(OutputIterator _iter) : m_iter(_iter) {}

    template < typename Edge, typename Graph >
    void back_edge(const Edge&, Graph&)
    {
        BOOST_THROW_EXCEPTION(not_a_dag());
    }

    template < typename Vertex, typename Graph >
    void finish_vertex(const Vertex& u, Graph&)
    {
        *m_iter++ = u;
    }

    OutputIterator m_iter;
};

// Topological Sort
//
// The topological sort algorithm creates a linear ordering
// of the vertices such that if edge (u,v) appears in the graph,
// then u comes before v in the ordering. The graph must
// be a directed acyclic graph (DAG). The implementation
// consists mainly of a call to depth-first search.
//

template < typename VertexListGraph, typename OutputIterator, typename P,
    typename T, typename R >
void topological_sort(VertexListGraph& g, OutputIterator result,
    const bgl_named_params< P, T, R >& params)
{
    typedef topo_sort_visitor< OutputIterator > TopoVisitor;
    depth_first_search(g, params.visitor(TopoVisitor(result)));
}

template < typename VertexListGraph, typename OutputIterator >
void topological_sort(VertexListGraph& g, OutputIterator result)
{
    topological_sort(
        g, result, bgl_named_params< int, buffer_param_t >(0)); // bogus
}

} // namespace boost

#endif /*BOOST_GRAPH_TOPOLOGICAL_SORT_H*/

/* topological_sort.hpp
jVmnPsQovW5+xjZInZW6TvN+Sjpga5195d6ptdkXlMl0DXtfwOfSS+rZ0t76nUtT3ae9nS2fv0dN1Ui1V5/Y6riUqTkuHV13ug81n5H0kn25zjVX+fDNg586xojLjmcPJ2T+ne4+6g138zrYvG5aIfvIeXxnFRQXZuYXWta9fHDV+75/ybSLfAcxn/xY+cw3RPSvky3HRV/5TUBOVmGucYmalVlSUmp/PqLrm5Zu/567sd6P9Uj7Rs5jDTroY8Uxf25uJu2zMGu8sTPbUDYDT0rZ4A6PhXqqnDB39RAvfu3X1FOl8NLdmObLasyN+NRyHztx9CR9OeprzM++niv7enx7y3GSW1oq/+uSuc0fZDm3OZlpm5wbAvU2kKOv8/itm719UeYVqTfDeo1SpHtLKdOOMu9KmT763Kqvz6veh8ryzTrku9BMvghS5ndw3WTZ8z0yGE3C8Rw+Yaz9XBN8033f3KC76t4n1+pbmbdSlt/aso7jnect3d4eHSbtzbzn/Vaml9v4Nb1N31fpa3N/XYZfzsn0I7amPPdiWfJ7gEOyrHBrP6wfKTmXFZBEGaYcbTVMptO4Bmgr++wKZb6Wehpajo1S2U8jzWee+ljW58yhxvktzZhnQfAU91zeeZ+j0x37ZUTDN23t6/8ecreNNsxirf376kCjTvcA/Qyg1HmPMkLO3+tdt9q4ZpQ0573/GtsmufeX+x2jPmmjAZbrMjrZ8kn0NM7j4OgAo8zTqptKM4+tFQOcz1RmGe+Plm0/aGmr+YXGFbz8xkI/322bKNeAzFPffMZbImmFPGGNVEN0fasoO17qm6vbn/N6UTdA2a/0zdWvsyiRNT6/YJLUs5DUGnLM/2Q9t5VllZRxvDv//7s2rEsg1pK2cafHIFXXlmdL5R3ohxlzfYm63/WsGu22TbV2r2EzljtftsnZj+rDVpZpjB8ZK+u+oX3VY1sOMCmTTJkFUmY0bcXc7+YxnSXPAjzMZ2d7Yozpd9y7qzx3x3XKGCmTo8vo8xxvb37L1qdGqJTR52POwsb52N+ju1rtOZb3NAZa7+/NY6qp7p+TcuR3ae7zlLc6QD9Sm6Oks83bLc69LmWq98kLwgY33eQR0Ppl/YyruVyHJP/FdYiv9XnVaPu+6mqM3yv7oZ3z2KP95Zbn8097mR6UOSJlwixljIuT0ZMcZVpR5rSUqSPnXvNzLrPv73Abk9IOrlmuJ0ZnFRSMysoel1maXTpRtaBcJalNpNzhiIL619UzIbXVxyHcGeLaBldrv9f2VZvRjlKD9bW544FqbuGY/ELnfcxiOf4u6/O849jzCnzJ1qH2Ob8QF7leMN6lLsv6R0SAnIscdXI/WarMumrFG2XS//JzlvMEZQ7IMdyiQ4i0parntJwiedqr+wHqlf7mVdd09axSLpNtIdWfT8jzJj/3VUGXgoz6Nxm/SZD6G3dw7v9848wrH5KUwUuy/2taj9fxOQW5ZWU8iVO63GF0lW3+JUJfh5jXmvrUqUL0drdNNcrNcutpa6ketCWo713KbKE3XTdtZV09WNfHbI5zx1rm7SXL2BLhW/WYVwH6WcGjcuz0U/VUmPkca6+k1azy7KtQvnrT9xjoJcv9l77/1+fEas+eK+QeNtrsJ3tYrp/q8Zl3kf20U9rybyGWexDdp61CL7ON5ZrfjV036tXn8Es26ukp9USEmNdDlp8wFuaO4fMx++8YmTdLhapwmT+P9Vgi8w+3HA/89GNiVkF+TlaZ/D5Hn8Mnpci5RJ/THW15ot9Ltgpfx7PrjVJXTMTEBi/XfoHraOs+zB9TmJlbNFrJZ0PKBCk7U9q8TdabnZwpzzDNfdgxwyjTyL6uTM+See4=
*/