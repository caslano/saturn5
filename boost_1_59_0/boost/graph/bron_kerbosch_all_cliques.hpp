// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_CLIQUE_HPP
#define BOOST_GRAPH_CLIQUE_HPP

#include <vector>
#include <deque>
#include <boost/config.hpp>

#include <boost/concept/assert.hpp>

#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/lookup_edge.hpp>

#include <boost/concept/detail/concept_def.hpp>
namespace boost
{
namespace concepts
{
    BOOST_concept(CliqueVisitor, (Visitor)(Clique)(Graph))
    {
        BOOST_CONCEPT_USAGE(CliqueVisitor) { vis.clique(k, g); }

    private:
        Visitor vis;
        Graph g;
        Clique k;
    };
} /* namespace concepts */
using concepts::CliqueVisitorConcept;
} /* namespace boost */
#include <boost/concept/detail/concept_undef.hpp>

namespace boost
{
// The algorithm implemented in this paper is based on the so-called
// Algorithm 457, published as:
//
//     @article{362367,
//         author = {Coen Bron and Joep Kerbosch},
//         title = {Algorithm 457: finding all cliques of an undirected graph},
//         journal = {Communications of the ACM},
//         volume = {16},
//         number = {9},
//         year = {1973},
//         issn = {0001-0782},
//         pages = {575--577},
//         doi = {http://doi.acm.org/10.1145/362342.362367},
//             publisher = {ACM Press},
//             address = {New York, NY, USA},
//         }
//
// Sort of. This implementation is adapted from the 1st version of the
// algorithm and does not implement the candidate selection optimization
// described as published - it could, it just doesn't yet.
//
// The algorithm is given as proportional to (3.14)^(n/3) power. This is
// not the same as O(...), but based on time measures and approximation.
//
// Unfortunately, this implementation may be less efficient on non-
// AdjacencyMatrix modeled graphs due to the non-constant implementation
// of the edge(u,v,g) functions.
//
// TODO: It might be worthwhile to provide functionality for passing
// a connectivity matrix to improve the efficiency of those lookups
// when needed. This could simply be passed as a BooleanMatrix
// s.t. edge(u,v,B) returns true or false. This could easily be
// abstracted for adjacency matricies.
//
// The following paper is interesting for a number of reasons. First,
// it lists a number of other such algorithms and second, it describes
// a new algorithm (that does not appear to require the edge(u,v,g)
// function and appears fairly efficient. It is probably worth investigating.
//
//      @article{DBLP:journals/tcs/TomitaTT06,
//          author = {Etsuji Tomita and Akira Tanaka and Haruhisa Takahashi},
//          title = {The worst-case time complexity for generating all maximal
//          cliques and computational experiments}, journal = {Theor. Comput.
//          Sci.}, volume = {363}, number = {1}, year = {2006}, pages = {28-42}
//          ee = {https://doi.org/10.1016/j.tcs.2006.06.015}
//      }

/**
 * The default clique_visitor supplies an empty visitation function.
 */
struct clique_visitor
{
    template < typename VertexSet, typename Graph >
    void clique(const VertexSet&, Graph&)
    {
    }
};

/**
 * The max_clique_visitor records the size of the maximum clique (but not the
 * clique itself).
 */
struct max_clique_visitor
{
    max_clique_visitor(std::size_t& max) : maximum(max) {}

    template < typename Clique, typename Graph >
    inline void clique(const Clique& p, const Graph& g)
    {
        BOOST_USING_STD_MAX();
        maximum = max BOOST_PREVENT_MACRO_SUBSTITUTION(maximum, p.size());
    }
    std::size_t& maximum;
};

inline max_clique_visitor find_max_clique(std::size_t& max)
{
    return max_clique_visitor(max);
}

namespace detail
{
    template < typename Graph >
    inline bool is_connected_to_clique(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor u,
        typename graph_traits< Graph >::vertex_descriptor v,
        typename graph_traits< Graph >::undirected_category)
    {
        return lookup_edge(u, v, g).second;
    }

    template < typename Graph >
    inline bool is_connected_to_clique(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor u,
        typename graph_traits< Graph >::vertex_descriptor v,
        typename graph_traits< Graph >::directed_category)
    {
        // Note that this could alternate between using an || to determine
        // full connectivity. I believe that this should produce strongly
        // connected components. Note that using && instead of || will
        // change the results to a fully connected subgraph (i.e., symmetric
        // edges between all vertices s.t., if a->b, then b->a.
        return lookup_edge(u, v, g).second && lookup_edge(v, u, g).second;
    }

    template < typename Graph, typename Container >
    inline void filter_unconnected_vertices(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor v,
        const Container& in, Container& out)
    {
        BOOST_CONCEPT_ASSERT((GraphConcept< Graph >));

        typename graph_traits< Graph >::directed_category cat;
        typename Container::const_iterator i, end = in.end();
        for (i = in.begin(); i != end; ++i)
        {
            if (is_connected_to_clique(g, v, *i, cat))
            {
                out.push_back(*i);
            }
        }
    }

    template < typename Graph,
        typename Clique, // compsub type
        typename Container, // candidates/not type
        typename Visitor >
    void extend_clique(const Graph& g, Clique& clique, Container& cands,
        Container& nots, Visitor vis, std::size_t min)
    {
        BOOST_CONCEPT_ASSERT((GraphConcept< Graph >));
        BOOST_CONCEPT_ASSERT((CliqueVisitorConcept< Visitor, Clique, Graph >));
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;

        // Is there vertex in nots that is connected to all vertices
        // in the candidate set? If so, no clique can ever be found.
        // This could be broken out into a separate function.
        {
            typename Container::iterator ni, nend = nots.end();
            typename Container::iterator ci, cend = cands.end();
            for (ni = nots.begin(); ni != nend; ++ni)
            {
                for (ci = cands.begin(); ci != cend; ++ci)
                {
                    // if we don't find an edge, then we're okay.
                    if (!lookup_edge(*ni, *ci, g).second)
                        break;
                }
                // if we iterated all the way to the end, then *ni
                // is connected to all *ci
                if (ci == cend)
                    break;
            }
            // if we broke early, we found *ni connected to all *ci
            if (ni != nend)
                return;
        }

        // TODO: the original algorithm 457 describes an alternative
        // (albeit really complicated) mechanism for selecting candidates.
        // The given optimizaiton seeks to bring about the above
        // condition sooner (i.e., there is a vertex in the not set
        // that is connected to all candidates). unfortunately, the
        // method they give for doing this is fairly unclear.

        // basically, for every vertex in not, we should know how many
        // vertices it is disconnected from in the candidate set. if
        // we fix some vertex in the not set, then we want to keep
        // choosing vertices that are not connected to that fixed vertex.
        // apparently, by selecting fix point with the minimum number
        // of disconnections (i.e., the maximum number of connections
        // within the candidate set), then the previous condition wil
        // be reached sooner.

        // there's some other stuff about using the number of disconnects
        // as a counter, but i'm jot really sure i followed it.

        // TODO: If we min-sized cliques to visit, then theoretically, we
        // should be able to stop recursing if the clique falls below that
        // size - maybe?

        // otherwise, iterate over candidates and and test
        // for maxmimal cliquiness.
        typename Container::iterator i, j;
        for (i = cands.begin(); i != cands.end();)
        {
            Vertex candidate = *i;

            // add the candidate to the clique (keeping the iterator!)
            // typename Clique::iterator ci = clique.insert(clique.end(),
            // candidate);
            clique.push_back(candidate);

            // remove it from the candidate set
            i = cands.erase(i);

            // build new candidate and not sets by removing all vertices
            // that are not connected to the current candidate vertex.
            // these actually invert the operation, adding them to the new
            // sets if the vertices are connected. its semantically the same.
            Container new_cands, new_nots;
            filter_unconnected_vertices(g, candidate, cands, new_cands);
            filter_unconnected_vertices(g, candidate, nots, new_nots);

            if (new_cands.empty() && new_nots.empty())
            {
                // our current clique is maximal since there's nothing
                // that's connected that we haven't already visited. If
                // the clique is below our radar, then we won't visit it.
                if (clique.size() >= min)
                {
                    vis.clique(clique, g);
                }
            }
            else
            {
                // recurse to explore the new candidates
                extend_clique(g, clique, new_cands, new_nots, vis, min);
            }

            // we're done with this vertex, so we need to move it
            // to the nots, and remove the candidate from the clique.
            nots.push_back(candidate);
            clique.pop_back();
        }
    }
} /* namespace detail */

template < typename Graph, typename Visitor >
inline void bron_kerbosch_all_cliques(
    const Graph& g, Visitor vis, std::size_t min)
{
    BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< Graph >));
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
    BOOST_CONCEPT_ASSERT(
        (AdjacencyMatrixConcept< Graph >)); // Structural requirement only
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename graph_traits< Graph >::vertex_iterator VertexIterator;
    typedef std::vector< Vertex > VertexSet;
    typedef std::deque< Vertex > Clique;
    BOOST_CONCEPT_ASSERT((CliqueVisitorConcept< Visitor, Clique, Graph >));

    // NOTE: We're using a deque to implement the clique, because it provides
    // constant inserts and removals at the end and also a constant size.

    VertexIterator i, end;
    boost::tie(i, end) = vertices(g);
    VertexSet cands(i, end); // start with all vertices as candidates
    VertexSet nots; // start with no vertices visited

    Clique clique; // the first clique is an empty vertex set
    detail::extend_clique(g, clique, cands, nots, vis, min);
}

// NOTE: By default the minimum number of vertices per clique is set at 2
// because singleton cliques aren't really very interesting.
template < typename Graph, typename Visitor >
inline void bron_kerbosch_all_cliques(const Graph& g, Visitor vis)
{
    bron_kerbosch_all_cliques(g, vis, 2);
}

template < typename Graph >
inline std::size_t bron_kerbosch_clique_number(const Graph& g)
{
    std::size_t ret = 0;
    bron_kerbosch_all_cliques(g, find_max_clique(ret));
    return ret;
}

} /* namespace boost */

#endif

/* bron_kerbosch_all_cliques.hpp
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
*/