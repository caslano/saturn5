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
x+Detm6StR8CsP2AwXMRRF4reK8Ekdex5zho3VRLt+eQ3GyHH/X8uj0GZUOHvIH/Xkb0PCe7l/O+G+q5Erasich69xiTSzhK1tTvPhvD/fXg69y+1kyu4UX24FwmTeQ6772F/1l7W3MrNoSZW7GDvNtJnf0+MNqQn69ZnKH4J9yt3CJzK/KLivJ6D86j0BQXVlpnh46U+RFl9rmwonuOkajWEh8UewfXEcOj50uYMvdBzafQbvqKm1HY/yr2zq4vjRjrzFbsRcUTDHuOxR7R6e5ymab4k6P9OcsRzsz8yTOK9dmM7/jvzRVrusTNUO2mgz1fRJ0d6zw7FB19Hui6CMOpmzeltEyPx+4UvV4ut+nW7jMD3G8IdJ8/S59D+ZboDXJ5zQjtvkuA+2dxn6jGQk3mCMgKcMf9dg/Q31wlvClEiK3bL0B3K7qh5pWUofu56LVzfW5EBZ01ncBf2W+JL+K+a01fnVEwY4Lsj9ErIQn6fndv9elcbKZRq++kJvs7ubud2dqYxHr1VNEzRe8Z0RtjNiasHvSKqTNo5XxVXz9jJWk72zfWOf/ySJc3wh0bFdvC90c1dOz8UlE53XEuZHO5v8bY1dmMjjNjE2BLuV7Pf16+Cmc14XyQ7AvnVQ5xvSC2J4GkRNtnMjJGKvqnYa+m7A9gCvBwFwa7/vt0Za8PE41cib/HGvFPpHo3qPv4WOJ5q9nSuJF4SozPiTj2eY/dI6zzHj0Jadt8buMZI+yYZY0bHpHnMpoyai46h7f47RVMjrDOFl6GH5Rj/CEvY18RYY3vSTkV2UpkcaKjyiGyNVrPKmcJlA9rDFCVI2QbtEyVF2TPOmWUgRRkm5E1FpkjXyPfqnUl/+rzj8lnyCSfyRjibMk3dDPV9NuXKvvrtdT54aqeO+A15DfLRT2p+BdfnbxN13P5lZXTSwtmVBar6k7yzXTJV7zj7Xyl3AzQddcksbdxfRG+vlNu+un5MCViz2QHDHfY+q5YdNq79hqpqr6z/MkOW9+Nk+vdKLM1dX3X0C87Vn2Hjl0nlBvh67sxone26xsj3q7vAtzPMsLXd4NF7xyXx4y167sA9/OM49d3Tv0rsIeqnza+7dfIsOqniPGh0rlF167js/iHTFW17mog7meZDRkle4fcdIC6q655ljExoO46W/RyzQa8u86g7vLVJTnRsp+R1Fle1/y5sc1iWx2vvrpH/KkXtr5ayXVdX6kwhsda9dWmY9ZXnbB7j1lfYZKtOSAnVm8VSBq8YrZi5t1xzqmWemjFO8F1VXNkzrqqfFuVukqfWT1d6iHKoZKNhoH11XgjuL4qgYH1VbkRXF/NgoH11TwjuL66wghVX3klfy2Tdr9dNx3dVrVuinm7at2Upeom4lt+F3OxGRwHn/O1wSRu5rHr1dQ83ywNLoWrk5RuO72fy1ti72/69BNFv6gsr2KSqo8s/dP0flNvir2Lmaj1fcXE58LQ86VeE51epm57ib2Vnq+GGylaFcpNqdZJF/sU7JvFnmOGKt/VrXaH6LQ0q7TH3rHL+zIVDyMl3ipmFFxg79WzT/Q6mI76QJ8lvkOuNTA9lFGrPtotsv2MW0b4973C9sC7PtloJEnUtDHI0dXy6VpezZ57qOvnGNEZKNc6SurO1PPPXpVrdXW97BJ7jj2n2HF2/jCuR8r1Mkf7TN6FuvydI9czDBf/+eqDQxTwkhrkI1+d4+7i9UR73fNWeD0eia+xCS54SbwY/3nzys0S3Mz1uYkboeuNS5VOqtLZaPkbPT/R6+6Mp8f2c5/lZ7X5DYP8xO7B/iMPsYeEiVDnne/lb1890j18PaLKb3B9MMtHkUk+l7I6T8vsvCxlWJdrlV8=
*/