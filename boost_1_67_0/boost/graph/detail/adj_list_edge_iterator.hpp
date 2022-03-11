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