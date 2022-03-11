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