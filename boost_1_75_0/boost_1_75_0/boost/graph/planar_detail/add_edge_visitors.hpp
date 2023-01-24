//=======================================================================
// Copyright 2007 Aaron Windsor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef __ADD_EDGE_VISITORS_HPP__
#define __ADD_EDGE_VISITORS_HPP__

#include <boost/property_map/property_map.hpp>

namespace boost
{

struct default_add_edge_visitor
{

    template < typename Graph, typename Vertex >
    void visit_vertex_pair(Vertex u, Vertex v, Graph& g)
    {
        add_edge(u, v, g);
    }
};

template < typename EdgeIndexMap > struct edge_index_update_visitor
{

    typedef
        typename property_traits< EdgeIndexMap >::value_type edge_index_value_t;

    edge_index_update_visitor(
        EdgeIndexMap em, edge_index_value_t next_index_available)
    : m_em(em), m_next_index(next_index_available)
    {
    }

    template < typename Graph, typename Vertex >
    void visit_vertex_pair(Vertex u, Vertex v, Graph& g)
    {
        typedef typename graph_traits< Graph >::edge_descriptor edge_t;
        std::pair< edge_t, bool > return_value = add_edge(u, v, g);
        if (return_value.second)
            put(m_em, return_value.first, m_next_index++);
    }

private:
    EdgeIndexMap m_em;
    edge_index_value_t m_next_index;
};

} // namespace boost

#endif //__ADD_EDGE_VISITORS_HPP__

/* add_edge_visitors.hpp
Qyim2OwfKgoJIXS6fc8LNQVqpy1LOVEnq/7KjjD9PuEzpklRi+gGwNUbYy/0Orm2So7uH3ln6nAlKItd/5Yx13PyQnI2TsC7udmatY0p0kWD7nrWOQD0D4erME9H+9W96sodJmMqxeUmsh05Nu1PvGMP8Z3CIifryV1vEjTan1viFJ3JHGGPJ55ru9XlK3t3Ih6DCb/pA7TL6dUofY/FcCtISo7jJEOd9DxndztOobFU00eRmD6ZKnC3cLA+7ZQ5HyMRiuio/9jgp5uFxtbKK60vV1OX4tbU2bd/pqrd3re9B8Sei5h/738ub2Cf8omwMOQMes6vtJpTpI3JaHIZPhyK0inXtmocVEV4ghyGxWx/tGU1Cb3QZIWYZC/sNF27Dm96sNy9vZZv92TNw1IBHXay1rySVZirIWzW6/ccwrRaAA1EJxQnqQ7j8SVMC72RtHvxcOvJRIpZ15Spk9X/oKiqrgQ9ELghlQBmTuHa29tb/2pY0XN7b0bTWWL9i8nqAm9FxJb6ESf6z2cCoQwVJJLCAHHbZ0h9t8VbtgetZ6EHDN2Nwzznx97zy2xCmnuMnzztd46LL/keo8oGTgMppQdWuR74CTdqElMyOT8Tlb/k1eYBVoXqHSkR4W/8ZkkE1S+L+3c45Rz6AiZVywcbKG3i2ka8lvpdYnFWC9A3vD6mY+F8m23icjDVr1bNLW0N1WKexFMlgVqjt9Aq
*/