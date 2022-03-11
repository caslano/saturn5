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
JOKqkUmDhjN896gVfpmHxMTKR+AhLDZjOFUNhOMGx0GfIl78YIKQcNMXm2OJd65zha/5LvHkMDJ3JVAM7QDOAynxZFQ2Bx3vfOwKhYVEZtbNXL6g73hUJboFneRkxRr5u7qLPtakcq6xr9jNHZ0Ugaxr4O7kFrRHh/8q4cFvR5g2pLlcGS8tPUFygR7DMk09UVNGTVJNPQEI/oti1HMr8+Rq63Occs7QaLIt0TSjUfN5G2fq/xIBpP8S3Huq/xKRPENQonMvB8+heE24JD8/0BUGH5pYVv6UMCR/i9qEx4olKZqEVzBbsD53ZnnohMqozKWpQ1yJZA5QKXiAY8Es5rOIKk8gaJDQS6af+x6/QUL6gDwUFDi4Sp3844xsWLcgJD9d4nC5bg52dlAiZtYqGQE0XtnJ85pHYHoFRQpoGF7QroNR/TSyU4Ast1ZsusWtBMfNUiY+ozlpx/SKsxSoG1r1ctbquEzqoeDLFyNIGpM8g/BEcEQ2wp8zi6/DfAtHHajvJ8Ov/wz+I389NiKMFRgq42r+jpURNCzLa/aBxeFP9qLb8Bm4ye/kfS7SBCWT4z31Sg37nTZDm57qezLfS8wDOyriOt9L9C77Io6zh2PTLRf2d0/2NtHFH/ECmxJR+Obco9xXSQ9ILAgHP9XMP1CmoFjjNoioPDAtNHrk5xguk6RKpujvTTCvNr4Pna69B23Dj/Bo51n4rVGsofvpQ8po6QsB+ojz6blpp0INnAQUFmBt1JthUZltWhBm1mMGsVkvw2MQz9mR8x5QylQ2TgBLReIa92tmRf+WCpdLlkXzfFYITHt9B+a9ycf9S0T3jUReZZPBNswbkbd/tFoYjWILVOuvGymoFjV5HXbJGDXDDB49fxKPGzW61nW2MBp2ETYb3/IVrscuX1ngahk1Ew8Oy6pGnfFqdoz8tpFZ7QYdNqmiPGluU1EFL7MG25l9/5kek3n5B8qSoTakhoPLHr72BWjx2Yxu/cTYetSil8symngJx+nOoWMzhNc34XBcRtvcZCpnlTy4lZVKeDaPqSjFRnNXhtzdkGZmNfD6WRGD29Rk8vYRYbVN2z0+m1szyCjipYB4MRnxB/2Xns35aDdYDJqRrLUuzXLjM07z9MWkhLrTHv56O+AU0JrtbNPSh3dxK7HuNAMmJOe6QKJ9NnCTZ5PVsEGW4KTj9Ehw4t1JcnpKXkNJblO25HAY5L5dW0LDsjVb20QzcNrs2l3tGtpy6EzOxfcYbZpjkf10f+T6eSEyWqDv2TSf1wXFydwVhNkB7cnJI73IHG8p2sTk7wN9m65AfMZVnoYJZ3w6xoAkEQ0J5MxnYUQfxA5yDQcQLHsyrVHbqJNrsBYKku1jd7IUdehoNfOdHEULFO6R7X+Q2yhwNYv87obwYjKq1mF4M4GVfZmJxnK9XIuv+GOawTBSC8FliR0LSU4DfItpiho5I6cKvvwVpyQrK94AZ0IfpEpe3XI+iJcDNhON8pjpZko/2TuxJblquRLSBeeZEz/uYvJEoq/A/LQR0jBgZpgxw226EoOQFbIy73mk00HBhofKe1ehY8eGi8p8l6OD3wyPynfXoaPXjNfoTma0E4f7iaG6K63zZt78w1m/tMLHrxnW2aE0aetbsyVbNNS0dyXeKBT5HtuzQWnNB0HzkPZvI1OPNSSjqKO9w8UG8Es/s4Fjg7bJM8svaBzoMwbqcd/vVtnBLeaT1ZhvCtV94NXVGkmXIw0e+ZcNphty+l6kUpyl3BxSanbIG+RY+GLsIjKmU3v2GtVWG9CDgNh8AgWl1e2F+kKrhlBpE5RjwzW9D3JTbJwk6dzPwYa4RInzCDO9/XdURd+bCzOOVCO+HBVakpl4ZPWOkIMXRfDzFvm3e9ugD2nXZ8Hsnfw16EszgBuByeYFyqMf4FqgwSyvRc5YBiNh8xjQT6QI9Khu+V1VdgwoiBK/ultrFSF5erlIFFnfrNv4mrrSLOZh3mzQ693u3bs1VaPGaEDiH2qwEu5S/878HJi3Rm/AR9N/rCPytlLoK2i9Yi1kSRmFvr9asbZmTlnVgjliGwkwqaYcxIsChUtDxyuNaU56so/qQ2u48C6UicT+1wDfCBMJg40gILJMOZq1mbqt1R6tKyQODGA/YmlcuZlv8Ip8ORy7W52yJy17OJWmz43N6Lj89/xahpSDViYjuWJGXyjNwHi2E65JvUb+ViHT2v5E8u0KpCrwmH/+v6AmsHCUKa9xgdv5u8X5ipYtygcc8GBojfYGZfg2tEr1eM6kvZJ2RLcL1Dh0rIZ2UhI5pSEvmQb1aiVVc4YwjVaqj5Q5xw23xtSu7O8h77RWf40BfkBwsbJCndLo79Gmi2NUJmhH2ir1AJMsY8FDwO9yk3latjhW7YIcpxeRtlhWPVClongZgJi/k2hd4b2MsEhOmTpmphUkSp7xp9oMQgBGIrVQkH++4wbS+o95Rboe2AYOiQ+KHQTXj/8L4I1kY4kbo7HQNnJAFFYEZ+4KTY3RaSgd6cpfKfDttMORq6izToyqg7XgPr+MslZdCFh6RBdN5fdflsanLlzjqzA3Jq+gIWfYiyPXivJz7xoUGL0sILfFBgbVYarESZmVpNTLlJmYm4IfJFXG9aA3+6FKqA7rIGwNhJooNzj+JAN/VaxrtOEVvhZbmh2+clmbQJeBKqHh2BmVOSkdkdRG5P9tQA+PlFuaHr/crY+RkQZVcAksDSpdVW2xWnJ0Ev7bUU+ZzXz4PQGRa9V7FviCIoIWdDukztEB0agUndKAlp90Z/bnwriqsW1GDtmFTUWie3toWVD6lWiH7hFd/H9BoVLxk2jH9lHl/8cGNrcyJlukNzlQfraNlyqlNK53vjGBXUx5WPdwaTK1MLrmjG+VJxoL8LG2z2zu8Roy4MNJLb0U2nEs129zrqYbe0CEXjU9fX5ucPa5so9HCFqtP0BCTLH24DzFwjeg5lecef7hBU/iI/BA4YX+f4FUZ0MX20nl4tLZxotRQOXCaPb5YHiT8ZGVgnDtO65Rj3/i0KqDagJYFwGja/ahgNXgKszyT2WiYdl6dILTqBpyDehLR0MNWeAUU+NTIQaCHKCGGVTp+S0LECDQwdE6Y8EBZ2qJMJFt+IV1wPsAv8EVtFmWawBtFv+2aOkqDNUmV2NKbgxKGi4a4R3zPFNlJgmeKo5XD/5LYnUSBK6UZhqqmEZ9zjzY+IS88tbTqwzYzcyvlWTkETqI/9fQ0Xs1M7tdlpkPZ60COl/XqOp/J4+ytvkvGdweB50vbVUMa50reag5bU0Na91rDl4hj7nRjSfQiPZNLvRRd1EYNa2iy6strLYeKmO9I41qgLrao/QxVty+c3zdzBL0YcJtJolec5zNKmRtGDVGEAJviTYVVhd2+ShjgElWNu0O7Vuw83Nr1BPdW0aFIKYxnguExzhpRySvIFwkS0uja/ekHFhLi306S9fSx8/Hwl1aV4H/KmkDtGyQ91QvKH5ZU+A+Usu/bBvO+S/6vU4QO2AW3Q1SdnFduUZNC2hd0ragHXUwJzZN4kz3rLTrMTtGVM3Y3NkGPscHnxyOZT5+XwM4qZtgXTtnmjUqfHh3lgC5CGlop8/xOc3I+EO7dBC4+A1jwNh1XgNq1USnZebHB0lSb6mC8X9YVqklwXaUm0Iza7zqm8EiiVBmFlLN0zccOHkhdUhDuiKx9Kva6rax6bekGyQ4VqeF6kekVm3oVh+F4ofUzZDmHaIq+UHYMjphLqpFqLMyMejHRl2z5diDtKmoLXhHy1aLxd+2heZOYCjcb0QG1C7CEFqh8btbJ2/QcDoVqrZi69aeY4rZX0M/Wn/Vik24l7FfyMlvMvkoWBcofsKOaS3Dkkwpe02w0ZK4PMY+UCwu19YscLGVymt1yMperxW5c4icMbkpYJh4cPno241ZXt9H+BBWVS1gLFf+qCM10+Aru7bGLOdfRGLDajRa+1mWd4E0G2BCnPNpECMFmKaNcipUds2vJouQjR6HdPZZIyJXPWxBu5pOLeFyqKyvaU0FZlY7ICuTE5Z2eEclxVp6YFnUeFa+M11mLAfPK9nQDbAW8J2iV5WtgzGeRmG/Vn78TOouL6irTFxxHB3jf4BSlNRbsah+BU/srl1QL9mE6mrK5yQnRkOKhPUkqLxhK3lnpTVKGfr/kXhQlOa6zqzQEgoweMhY2EmQ2vXelFRB9aPR50VMoSB/wVC6JvIbD7KRpUqPzXOri2yFamZFf3NSVV2G5bCrt7OzHGPxpAopNqlF96xJ7Wug0eYnWuo0OtUxbivvuSoLGqtyEclQElqCJI4K0clGJPo0W+X2oXvyMKFLri/Kkv4sfsWjp2zlr0Njvj9VwxOaVcfVkfTkTt91lEdc994tlXIuNpUfuJqYv6D+sCttbYYYISl92T8q+4D5yH0oJS/Z0gw0qiuMEWQ1ZkzTKtvxX1lITNOqiHjdNEOXmXC9VaC+6ZtOP7tMf1YKy+sxmuCkyEIu/2u0mSasTBSyf0p0XeYQfIBopLGhWhAy0Y5IyXEdaCurvGWIti7REfNR4RSrH1/Q/fOk1AWGK+lVzS5u4oKaG1b8YY9XbakQopJXesyk7XKHGR0OyeKEVRfJJRsbpr4kPTvTuEyXpCIXu6/JJIvknFEIywsm5m8WPsGi8uskTSx8Aj6lT4Im7d6WrkGZT9YAshTJNaMKtnY4Uhb/GMifAp6ZiHcNVF86+L28eW+chqpy6NHqJCXnIqHUph1MzO1TMyGp4kG7fHpfQ9dWqaBWf1Vy7TamNLRkUBANRwdJVWXVuhiKxa4Nq3K14lDd+iSVRltZmGU/PPl8BdRhvWFTbYAXWtmqTMl3xZLReaqIpt/zekNYiRbFk68QwKhti+UuB3776ET/cxs/fsqpGnd+J6pSqS3gp63HelZ/9tdmniiunG7bliFK+WGXzcJlRBnKrfGyIeWcUQVu1h/eb2W/Unv2Odp+xVLlmadaA0tIm74Slp8Sy6FWTVngqSDEeNKtq2Ac4nJK/cxTamhJKGt01faTP+V7O0788au8Swte3vmVGWo7r+qDe7gRPnNzG68SadAm91NHt3LXN40oz6Kzmx8TFU+MK0+V5SP1+Ezn2j2VlXn845P2apAY76i1shl12hq1PxYp76KoZ1g9RNf1iad1Uudl0u4Sl0Zl8uDARcwyW7EcBWYKdJlytha1++CqMzIEbJez16RqPNs5HOnq8tFWP66OxnnAbMazz5azvW6xq5icAFnsai/o54JHmi38te+4jQ2Tl7Z9m+VI/xC1B2FaYjcLkNYfHadrUJ6+G6dony9nRL38YAUAl2mzqz7CxdaK2x622qAJLGx9kK5oxTO1dpLeIBOPlp8OnHkNJO6OiTmc4ln8eBOdoCScRr0cdAksUj3pa3nEM0u2o84RE2vXFTb5452XYveG/Ys1brraLNZ/rzejs+KTTEVeD5QEgtp8WrnjWe666FsgSaa8rycuoSUa/r05kAvM07z7bqLVrA9hCTsh8c9ffJiDPt+TOJ/vCY6k69ds3sJLNGnXLwZ/ZmgJu+/wf7MF5qXfArIxxDMt+OLPvyVuy2IOuoA2kcPvQQWAOhHUxgjqxIc+HR7JVA1+/xS0hNN5mL3Ffx2DT4MG9WjEvuS/HeRt+UC95Evm+q+XSPu15mnMPtSV/x30leMFB2r7mv6A+G/TsXO3/n/ncEL/7zD8bGbQYV/Qxx+QenF4pbwuOH0hfgnHNOGZJOdJG+J053DRO486ZryRXD8STRfidvH8i9uujDiuqNvW444b9cxudC0EZf5Odu/luk9UF12htJbm12osXaG0qeYbaDRdAbS55L2XbZ4ktP+YKy0bPY1t8svrLOM8/aGDDFb1ccnrz/AZAGqKeEgfEvXsMtd8UeHGudNBLcosOtP9UpTVNtljDKL+PqVhcsyYtAFLqaTW5jm5R8VPWvi559xtpKO9NG7EhoHo2TUup5xT/YgXod2H1Dm9UtXu/v/I+MeoW2KmWwDdj23btm3btm17P7Zt27Zt27btu9/3O+ee7447xsrsVCpdVZmpTic/ek3t6+o7gCx6eUwdH/garptJbQBZJm+rKT/LLWzmTPp8lutMGjOUfCzvtdObfUZO6WWMevwMOIUUdcgejEzUv3xIaDPGWPSMcuR2QiT0hLX/ffwIfYpLaM/zG9MaHN+ypx7OvBLBhWonBCH5zZ2VakvFnFbwnpF9Vh/4XhL3XOnaMeIwK10aanMoOca1yAJLGaA066GMxiqedwi2mtGNdb6BGGM7DRMDTRU3CD7JelQf//7zPN5+ET9cvKg+6HjjWXUgyqCe6KTreWTPx+936v2oPl2MX4XCQTnbnAUV2UwwOuaEowa8kWh0nD4bXFYXc9zmiWpPx4/m9MUD1T6OXbyeKec0wMPm4JHXWsDqxNLw4YnqZMqdInWDl6PVBo9rZzO5dZ9TvCUtP7olksPVRghARcq26wSnNgduFVEGSasIRsXm1mpG0sofGtBuP9suaYt/5Hbo+uiQrN1CGqLVb1Czz56jusC+gzBbiI0xynWoMRzv0MU5i6SdH+Mau/3IPX4d+iXpmOuec1DBPKGcZXHf/wi9Kow2WXgsN+u0JT03eVL2DkKrhpZqPWwpdkJoVhWa3P4hexmpjWAeit45dHxxeMxb5bv2geiG9iSlTHNqzi9Q+Tn3QYlmzT+hODodbwRZe6lNOyS9UtZlax/LXKHorGt04ZLpxFh0lOId2khP3Owc+viVmgYX4+C10ua5vS8IPc66tW/JX7rKjGakG+3AUVtzj6gC2tFLunaJ69bKIPsuEbV9mhBlb32VJV/reZOGMP5N4DYonumlVxuKbSRtcWvXPrqFZNSVAmsV6smz34N+qArf7Jq0qlTTCLFS16zUrWt/T8p+vNb82KXrAJL3bqXm3r2/c/CFXHgbnf0W8wkZ0Xtq8pvD9YcicsX26aNvOX1vi0kr1cPnwFm6fmJV1d1nvyMtQfNjZpi/yvCaovZWm+PsbYOzFm+DiatC43PtsrTKy4rP4ztBpT7l/qfUP6oLpUt1dJXTnQqrrJhtuNFS8kcv03yHP1pq+jjYc9E7DPPWjYIPRa8mhElSF88uZpVhlIHCzR/PKsaox4NhJ/rNM0zCZP7YS31P/beLYcfzCxfKZmps86+dYbiR0uNBF8y7bwo7afJiGF++Qoahx47ezgi3WXF08xPr8WG1fRU53brWtF4dIYv5DF4jYXVflp17kSUJTnn5Tgo3h2JjV7W7YxGq++bDapX9ZMUE1UvLocqKOpowx51tnlZBxh1C3qkHV3f2m3vcUoP22zumBNGzD4/2O89KEa/OOy5rEej2GyaWotn0G2lLUcrWu7uWIh2udzNNOYSc7myMtZdTTgPR5s6XXku3R6BN7YPtuv7mrGerbd01W5ePh1KXrKz6a99mbCsARm1j0Zc7WVyhaI7jTTmur3cZjkhPwAxcilGTHH5uTPFZz0wfWVhtXaG+aJG/HJZvG896SMuXssa098ZDpDHIB/AjinrE9CWht+AbH3ad5Orzy/nYqD/lCswLxOEpx963fKttkRyab31V+L+wmTUWvQfeseW/O4RzwX15zrY7QHi33xQ15Ja33yXjCPV2m8Bq7YdGI1x+LHNzvhDFsKGeN6+Qxk9ZhiHN6xdL2fwwlhj9GuWY7U6DUq1S/YbM8HMvg4waH2c/oPeFsh06dZl3ZohCbvejjKAe0N6gj9XYE324onaPol4HT7yRLNF7YZrkCrtnkrgdeaP4jqXHjVYH3z/xLa482X9liCyuPhpm/+VS4M22t5Al8O6QSGfKKC/Rm26D7kfU0agFcTfDyowjci5Ewgl37IlboKSOII3Yoxt/IqiIRsw+hlo08y169HFmQNGtV+zxYF1S7dDxyAPVvzM/6eHbNua+m8zIvQv+eXSFwxdY3BPssrvuaHTCbn5GXyuYxK2gzFGofxFbheG7M/U0lkriezZ84k5+xpSakLSnFWWMH0TCTkbGwCZr4VFrScl9jnrGa1HJI43Agpfi4rvu9F2Oq+7vuhknH9pRp6//LHSPdqFYl/IqhLcLU1dpZxWffkafVrsRjPrvoBnpLWxGL+77TMLrfMVzyJLeF7rbtS7Dw3ekXILJPlem3qFsf9cTeK7wD/XZZ5n8ZPuXGPXOOsuIJa7dqUD/1qP8pIc39NhCc6scop7/cKs9js0z2y/60tpy36ndzlpiAMYjAi/U2y538zvHO+2RkYBipvpQaYCkjuY77QGVQCJo87PO1KuV7PhtNs1xaWARa33SrE0NjQbVbrG3PRTkzj74q85IaTO+jSFGLlBHz46qH4YfZuRve0+5L+QvxlJTn6ofyO0SYmkUOfpZ5sgr8DT53tPC27m6t69AM2O2HIAOOfpJ5sytZTmNFKvk6S3/VSX65J4C1QIp49tJtXim+ribtcjGkKSvMlWXz8KP1vhmS5+N4cYgWKLaQ6OWxesu5S41L4wi7kbduhtKLpjngbl49cG/GVSrVrt3yVPCIl5vGTmu2pav1h7uDLS1C0NGWcGcMcNyDb/Evgku3nIfYsuMTVWhoZzBmnQ4dNnF7gmHexJl432aPv7WOlSk80pDbs3Au4xu/jHIpLByp8KrQipYeVDhTeL+5YytBZVwI/f4MsFr/z3PHOV7zNcPeuu04/2dCdVGWHnk7Dmaas2ZfRg0kdgsu2zNiYXoo9xMq9kZik02OW5N78X4+9hI1VTUcveMHzsA7An1y/j3SH6CCrBZMk/Kw4hahH+f5Vi1p7RKOZbRF0PccpXrLYDfG8eKrsYJzI8nTvt34r007sHZSazX8QeKvOvO/5VWF0G4xRzNDjVIiqdtbtkObReXuWJu044NDyRDE/2qNZQucXnRDs8PiLmTfqM2oHRTv5rcu4K3jyzgASr0A+dIasPwmgr72C2Mzio0OZu1vzbBzSJ2edmhYxfBF/jMcN+7l5JXVrVi18EX4sx1H7RX6QttLnSAx3fZWx2MOhDg9Hvm0aPh5lNnr9e5zwYQxeepcwrsO8RE+SlWj0YP7IEO8evSvRG+S1tYwej3sou2hiR4lmi1vPWIaRdPJGTJhpczSDvb9tHJmON9d99JiNzdbXT7gdYPnNmcn2rSy5tH3NPtFEAu2HLW7Cfl2XtR/vq9KvlYqEeKfCdzgeWGgQ+S+PqVzBs=
*/