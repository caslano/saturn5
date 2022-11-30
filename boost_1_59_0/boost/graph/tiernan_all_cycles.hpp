// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_CYCLE_HPP
#define BOOST_GRAPH_CYCLE_HPP

#include <vector>

#include <boost/config.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/concept/assert.hpp>

#include <boost/concept/detail/concept_def.hpp>
namespace boost
{
namespace concepts
{
    BOOST_concept(CycleVisitor, (Visitor)(Path)(Graph))
    {
        BOOST_CONCEPT_USAGE(CycleVisitor) { vis.cycle(p, g); }

    private:
        Visitor vis;
        Graph g;
        Path p;
    };
} /* namespace concepts */
using concepts::CycleVisitorConcept;
} /* namespace boost */
#include <boost/concept/detail/concept_undef.hpp>

namespace boost
{

// The implementation of this algorithm is a reproduction of the Teirnan
// approach for directed graphs: bibtex follows
//
//     @article{362819,
//         author = {James C. Tiernan},
//         title = {An efficient search algorithm to find the elementary
//         circuits of a graph}, journal = {Commun. ACM}, volume = {13}, number
//         = {12}, year = {1970}, issn = {0001-0782}, pages = {722--726}, doi =
//         {http://doi.acm.org/10.1145/362814.362819},
//             publisher = {ACM Press},
//             address = {New York, NY, USA},
//         }
//
// It should be pointed out that the author does not provide a complete analysis
// for either time or space. This is in part, due to the fact that it's a fairly
// input sensitive problem related to the density and construction of the graph,
// not just its size.
//
// I've also taken some liberties with the interpretation of the algorithm -
// I've basically modernized it to use real data structures (no more arrays and
// matrices). Oh... and there's explicit control structures - not just gotos.
//
// The problem is definitely NP-complete, an unbounded implementation of this
// will probably run for quite a while on a large graph. The conclusions
// of this paper also reference a Paton algorithm for undirected graphs as being
// much more efficient (apparently based on spanning trees). Although not
// implemented, it can be found here:
//
//     @article{363232,
//         author = {Keith Paton},
//         title = {An algorithm for finding a fundamental set of cycles of a
//         graph}, journal = {Commun. ACM}, volume = {12}, number = {9}, year =
//         {1969}, issn = {0001-0782}, pages = {514--518}, doi =
//         {http://doi.acm.org/10.1145/363219.363232},
//             publisher = {ACM Press},
//             address = {New York, NY, USA},
//         }

/**
 * The default cycle visitor provides an empty visit function for cycle
 * visitors.
 */
struct cycle_visitor
{
    template < typename Path, typename Graph >
    inline void cycle(const Path& p, const Graph& g)
    {
    }
};

/**
 * The min_max_cycle_visitor simultaneously records the minimum and maximum
 * cycles in a graph.
 */
struct min_max_cycle_visitor
{
    min_max_cycle_visitor(std::size_t& min_, std::size_t& max_)
    : minimum(min_), maximum(max_)
    {
    }

    template < typename Path, typename Graph >
    inline void cycle(const Path& p, const Graph& g)
    {
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
        std::size_t len = p.size();
        minimum = min BOOST_PREVENT_MACRO_SUBSTITUTION(minimum, len);
        maximum = max BOOST_PREVENT_MACRO_SUBSTITUTION(maximum, len);
    }
    std::size_t& minimum;
    std::size_t& maximum;
};

inline min_max_cycle_visitor find_min_max_cycle(
    std::size_t& min_, std::size_t& max_)
{
    return min_max_cycle_visitor(min_, max_);
}

namespace detail
{
    template < typename Graph, typename Path >
    inline bool is_vertex_in_path(const Graph&,
        typename graph_traits< Graph >::vertex_descriptor v, const Path& p)
    {
        return (std::find(p.begin(), p.end(), v) != p.end());
    }

    template < typename Graph, typename ClosedMatrix >
    inline bool is_path_closed(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor u,
        typename graph_traits< Graph >::vertex_descriptor v,
        const ClosedMatrix& closed)
    {
        // the path from u to v is closed if v can be found in the list
        // of closed vertices associated with u.
        typedef typename ClosedMatrix::const_reference Row;
        Row r = closed[get(vertex_index, g, u)];
        if (find(r.begin(), r.end(), v) != r.end())
        {
            return true;
        }
        return false;
    }

    template < typename Graph, typename Path, typename ClosedMatrix >
    inline bool can_extend_path(const Graph& g,
        typename graph_traits< Graph >::edge_descriptor e, const Path& p,
        const ClosedMatrix& m)
    {
        BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< Graph >));
        BOOST_CONCEPT_ASSERT((VertexIndexGraphConcept< Graph >));
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;

        // get the vertices in question
        Vertex u = source(e, g), v = target(e, g);

        // conditions for allowing a traversal along this edge are:
        // 1. the index of v must be greater than that at which the
        //    path is rooted (p.front()).
        // 2. the vertex v cannot already be in the path
        // 3. the vertex v cannot be closed to the vertex u

        bool indices
            = get(vertex_index, g, p.front()) < get(vertex_index, g, v);
        bool path = !is_vertex_in_path(g, v, p);
        bool closed = !is_path_closed(g, u, v, m);
        return indices && path && closed;
    }

    template < typename Graph, typename Path >
    inline bool can_wrap_path(const Graph& g, const Path& p)
    {
        BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< Graph >));
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
        typedef typename graph_traits< Graph >::out_edge_iterator OutIterator;

        // iterate over the out-edges of the back, looking for the
        // front of the path. also, we can't travel along the same
        // edge that we did on the way here, but we don't quite have the
        // stringent requirements that we do in can_extend_path().
        Vertex u = p.back(), v = p.front();
        OutIterator i, end;
        for (boost::tie(i, end) = out_edges(u, g); i != end; ++i)
        {
            if ((target(*i, g) == v))
            {
                return true;
            }
        }
        return false;
    }

    template < typename Graph, typename Path, typename ClosedMatrix >
    inline typename graph_traits< Graph >::vertex_descriptor extend_path(
        const Graph& g, Path& p, ClosedMatrix& closed)
    {
        BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< Graph >));
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
        typedef typename graph_traits< Graph >::out_edge_iterator OutIterator;

        // get the current vertex
        Vertex u = p.back();
        Vertex ret = graph_traits< Graph >::null_vertex();

        // AdjacencyIterator i, end;
        OutIterator i, end;
        for (boost::tie(i, end) = out_edges(u, g); i != end; ++i)
        {
            Vertex v = target(*i, g);

            // if we can actually extend along this edge,
            // then that's what we want to do
            if (can_extend_path(g, *i, p, closed))
            {
                p.push_back(v); // add the vertex to the path
                ret = v;
                break;
            }
        }
        return ret;
    }

    template < typename Graph, typename Path, typename ClosedMatrix >
    inline bool exhaust_paths(const Graph& g, Path& p, ClosedMatrix& closed)
    {
        BOOST_CONCEPT_ASSERT((GraphConcept< Graph >));
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;

        // if there's more than one vertex in the path, this closes
        // of some possible routes and returns true. otherwise, if there's
        // only one vertex left, the vertex has been used up
        if (p.size() > 1)
        {
            // get the last and second to last vertices, popping the last
            // vertex off the path
            Vertex last, prev;
            last = p.back();
            p.pop_back();
            prev = p.back();

            // reset the closure for the last vertex of the path and
            // indicate that the last vertex in p is now closed to
            // the next-to-last vertex in p
            closed[get(vertex_index, g, last)].clear();
            closed[get(vertex_index, g, prev)].push_back(last);
            return true;
        }
        else
        {
            return false;
        }
    }

    template < typename Graph, typename Visitor >
    inline void all_cycles_from_vertex(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor v, Visitor vis,
        std::size_t minlen, std::size_t maxlen)
    {
        BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
        typedef std::vector< Vertex > Path;
        BOOST_CONCEPT_ASSERT((CycleVisitorConcept< Visitor, Path, Graph >));
        typedef std::vector< Vertex > VertexList;
        typedef std::vector< VertexList > ClosedMatrix;

        Path p;
        ClosedMatrix closed(num_vertices(g), VertexList());
        Vertex null = graph_traits< Graph >::null_vertex();

        // each path investigation starts at the ith vertex
        p.push_back(v);

        while (1)
        {
            // extend the path until we've reached the end or the
            // maxlen-sized cycle
            Vertex j = null;
            while (((j = detail::extend_path(g, p, closed)) != null)
                && (p.size() < maxlen))
                ; // empty loop

            // if we're done extending the path and there's an edge
            // connecting the back to the front, then we should have
            // a cycle.
            if (detail::can_wrap_path(g, p) && p.size() >= minlen)
            {
                vis.cycle(p, g);
            }

            if (!detail::exhaust_paths(g, p, closed))
            {
                break;
            }
        }
    }

    // Select the minimum allowable length of a cycle based on the directedness
    // of the graph - 2 for directed, 3 for undirected.
    template < typename D > struct min_cycles
    {
        enum
        {
            value = 2
        };
    };
    template <> struct min_cycles< undirected_tag >
    {
        enum
        {
            value = 3
        };
    };
} /* namespace detail */

template < typename Graph, typename Visitor >
inline void tiernan_all_cycles(
    const Graph& g, Visitor vis, std::size_t minlen, std::size_t maxlen)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_iterator VertexIterator;

    VertexIterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
    {
        detail::all_cycles_from_vertex(g, *i, vis, minlen, maxlen);
    }
}

template < typename Graph, typename Visitor >
inline void tiernan_all_cycles(const Graph& g, Visitor vis, std::size_t maxlen)
{
    typedef typename graph_traits< Graph >::directed_category Dir;
    tiernan_all_cycles(g, vis, detail::min_cycles< Dir >::value, maxlen);
}

template < typename Graph, typename Visitor >
inline void tiernan_all_cycles(const Graph& g, Visitor vis)
{
    typedef typename graph_traits< Graph >::directed_category Dir;
    tiernan_all_cycles(g, vis, detail::min_cycles< Dir >::value,
        (std::numeric_limits< std::size_t >::max)());
}

template < typename Graph >
inline std::pair< std::size_t, std::size_t > tiernan_girth_and_circumference(
    const Graph& g)
{
    std::size_t min_ = (std::numeric_limits< std::size_t >::max)(), max_ = 0;
    tiernan_all_cycles(g, find_min_max_cycle(min_, max_));

    // if this is the case, the graph is acyclic...
    if (max_ == 0)
        max_ = min_;

    return std::make_pair(min_, max_);
}

template < typename Graph > inline std::size_t tiernan_girth(const Graph& g)
{
    return tiernan_girth_and_circumference(g).first;
}

template < typename Graph >
inline std::size_t tiernan_circumference(const Graph& g)
{
    return tiernan_girth_and_circumference(g).second;
}

} /* namespace boost */

#endif

/* tiernan_all_cycles.hpp
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
*/