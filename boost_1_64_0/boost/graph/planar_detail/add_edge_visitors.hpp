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
4tyIpeKWBhwR/pDjOZSIpgYE4eKWjgw6u5PRqPswiXj0P0/u1QDFZa28vn9CkxybZEKNudaxx/sf2dLT9UmSzZA/5+uftZyPKR/U+V0xSqWjt8FgH+UYhmVIvQ0SmWnGCoiMkLsKkk0A6EEvwXyukOhJe3ZZQKTfyIaAxwH1CScx4m08zDZ/urU0fgjoAbWKc5ZZvuvcDC773LYztN+DEEuisM1KRmYjk+tk+x1k51fMSLmWaQCiNSMsgf7a57/B/VxZqMjOA0UT0r6jB06feUWsUY1xBaPaBLp6eJ9cgKG4cydbgPJfPoGchLHFGyZCQoM+g+VeVqlSwlHUiaMJFdoWl9vGS7cYT5TH3FSTv4vy0QCa20W5GSa+CpdhG4+WGlYHwTk4Q8DWMt5BMbLXTWyBzlazChRN8j1zF7n44Svk1U8Uco78QgvfNkVyRX1EbsY9Onq5GFrgt108ZH7qwu6etMw2gB+FxIaBBMh6XJaLoQwCc4ZDkH4dF7Sc3ZXCus7l5A7wVm9Z1cY/VVSpUoN4jHTHWxknk2SPnkw7HelWwcQhTqyWjM3F+g==
*/