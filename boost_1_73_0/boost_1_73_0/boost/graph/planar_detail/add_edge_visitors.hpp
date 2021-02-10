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
wBqiF5qP0MM/9+eT+aIh2c0gtCrVtC1FJI0OT+pRtS8/szJpmjJBYrYiVqJGy4Iax7ZOLxcMEryY1itPOkDCv+CT2c7cBL392AbXefo4fbrdyhfTPObqtDe65LirB2pWq10qa7dXloMfk5cVeog9KCcOXN+hlbuwUqO8InvUkDAULV5COvqcBsYc7l67lJ4Ejb94BxFNGh2FWCMD/E+LgI05dCdoo2IflkN4IRoc3NjcPdwsRGcDf2mOAR4j8m3/aa5erwgJoW1+99fL3rB7+nBtvObwzH334jXdsn1wRiIOQ2wwtX+kQaXw4+a3cKsWEURbHme42dswFKeK7veg/F/kAi3282t4QYswTSPLBpPOBeX849866XIMHjTpyOfXGffetsf/QVOvpnObT72fvvHUw1VEIgkC+87P7jXjKon+nzfviqPwNeZdEWZh3nEodCH9zc/CiLvLkt849Nw+S3WOySzfcZX3IjcVb1xzMOy9ei93+Rh5rM6VqvGrOgzHPTV07vwC++oMayuUM+MEVUFP4eMuRoFHX26yqgyfw9NzN/HtMX7fNfbou5ybiQaKfpLQ9PPfhrJDv9nihGAwdGvD4wOUOkH3XScBeZrmedtkCBO+q5HHiw95+hBzE/QEA6DYeFNU1AymzNs/
*/