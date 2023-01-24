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
#ifndef BOOST_GRAPH_DETAIL_ADJ_LIST_EDGE_ITERATOR_HPP
#define BOOST_GRAPH_DETAIL_ADJ_LIST_EDGE_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__IBMCPP__, <= 600)
#define BOOST_GRAPH_NO_OPTIONAL
#endif

#ifdef BOOST_GRAPH_NO_OPTIONAL
#define BOOST_GRAPH_MEMBER .
#else
#define BOOST_GRAPH_MEMBER ->
#include <boost/optional.hpp>
#endif // ndef BOOST_GRAPH_NO_OPTIONAL

namespace boost
{

namespace detail
{

    template < class VertexIterator, class OutEdgeIterator, class Graph >
    class adj_list_edge_iterator
    {
        typedef adj_list_edge_iterator self;

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef typename OutEdgeIterator::value_type value_type;
        typedef typename OutEdgeIterator::reference reference;
        typedef typename OutEdgeIterator::pointer pointer;
        typedef typename OutEdgeIterator::difference_type difference_type;
        typedef difference_type distance_type;

        inline adj_list_edge_iterator() {}

        inline adj_list_edge_iterator(const self& x)
        : vBegin(x.vBegin)
        , vCurr(x.vCurr)
        , vEnd(x.vEnd)
        , edges(x.edges)
        , m_g(x.m_g)
        {
        }

        template < class G >
        inline adj_list_edge_iterator(
            VertexIterator b, VertexIterator c, VertexIterator e, const G& g)
        : vBegin(b), vCurr(c), vEnd(e), m_g(&g)
        {
            if (vCurr != vEnd)
            {
                while (vCurr != vEnd && out_degree(*vCurr, *m_g) == 0)
                    ++vCurr;
                if (vCurr != vEnd)
                    edges = out_edges(*vCurr, *m_g);
            }
        }

        /*Note:
          In the directed graph cases, it is fine.
          For undirected graphs, one edge go through twice.
        */
        inline self& operator++()
        {
            ++edges BOOST_GRAPH_MEMBER first;
            if (edges BOOST_GRAPH_MEMBER first
                == edges BOOST_GRAPH_MEMBER second)
            {
                ++vCurr;
                while (vCurr != vEnd && out_degree(*vCurr, *m_g) == 0)
                    ++vCurr;
                if (vCurr != vEnd)
                    edges = out_edges(*vCurr, *m_g);
            }
            return *this;
        }
        inline self operator++(int)
        {
            self tmp = *this;
            ++(*this);
            return tmp;
        }
        inline value_type operator*() const
        {
            return *edges BOOST_GRAPH_MEMBER first;
        }
        inline bool operator==(const self& x) const
        {
            return vCurr == x.vCurr
                && (vCurr == vEnd
                    || edges BOOST_GRAPH_MEMBER first
                        == x.edges BOOST_GRAPH_MEMBER first);
        }
        inline bool operator!=(const self& x) const
        {
            return vCurr != x.vCurr
                || (vCurr != vEnd
                    && edges BOOST_GRAPH_MEMBER first
                        != x.edges BOOST_GRAPH_MEMBER first);
        }

    protected:
        VertexIterator vBegin;
        VertexIterator vCurr;
        VertexIterator vEnd;

#ifdef BOOST_GRAPH_NO_OPTIONAL
        std::pair< OutEdgeIterator, OutEdgeIterator > edges;
#else
        boost::optional< std::pair< OutEdgeIterator, OutEdgeIterator > > edges;
#endif // ndef BOOST_GRAPH_NO_OPTIONAL
        const Graph* m_g;
    };

} // namespace detail

}

#undef BOOST_GRAPH_MEMBER

#endif // BOOST_GRAPH_DETAIL_ADJ_LIST_EDGE_ITERATOR_HPP

/* adj_list_edge_iterator.hpp
a9q4oA7HQOeVVFyxwl++EfsFh34LFcdy/Y8D6/dsc7rmQOtl08P3+Te9gXXOy6YOFcLO+2dovn0Aln5EeFHfvtLuH/SxglnUGeKl1vobMcMRZjRqPsts3BxpBI23g2w3Ysj9q6nhblJQGHKw7a5Qr8I7osFrwsf7wRk/5XfByP0aO0JX/CdI0O3wwiusgwgQ5k3JTa6v3ruMgcSB6/dQzp9cKCObZo+XoaDr3RWoFPKnP0kq1uXlWaRFtB6Df6n53dxa/pv4WIMIyoYlyz2hd2xu+ZdSp4g0Z6cJRQ78j5afIkZVONcOWusYC1mca4aFqlsnaA3C5W6CP54adlZAQgfLnAWyakChtC5aVu+zNaPDTor9W0IydshpKybQz4t+fiawD/+lZOCL1LQyBnwD30eVoaAFqUlFzWslhB2QvCMg7nt7NtVsheoRxymy+/g2v6xcvRdZq7x0+DlqAjCJXqZZAddDPL8ZnszF9hi0UPWbfc9+D34pEzRslotsNvZTlHbMQKjISM8e1PmWbqNkjPW2oHVJZ8pec1FTWlRimxe/a4ovpb5MQEK60fgNnEyxsSCHau5zDeY2Y6yiR3gwKmrMAckfBoJoMfsSmiRLD6XceA9ZzFDXGhUuTlZxp3cGwwYnvKaxVlfh/i3jssjjgssU96dlWHQDpZkeYWSKAZkkcvPxWgnJv4ZU6ILIcxBJxDFkV5EqcHQSSzEF
*/