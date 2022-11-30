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
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
*/