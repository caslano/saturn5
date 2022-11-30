//=======================================================================
// Copyright (C) 2005-2009 Jongsoo Park <jongsoo.park -at- gmail.com>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_DOMINATOR_HPP
#define BOOST_GRAPH_DOMINATOR_HPP

#include <boost/config.hpp>
#include <deque>
#include <set>
#include <boost/graph/depth_first_search.hpp>
#include <boost/concept/assert.hpp>

// Dominator tree computation

namespace boost
{
namespace detail
{
    /**
     * An extended time_stamper which also records vertices for each dfs number
     */
    template < class TimeMap, class VertexVector, class TimeT, class Tag >
    class time_stamper_with_vertex_vector
    : public base_visitor<
          time_stamper_with_vertex_vector< TimeMap, VertexVector, TimeT, Tag > >
    {
    public:
        typedef Tag event_filter;
        time_stamper_with_vertex_vector(
            TimeMap timeMap, VertexVector& v, TimeT& t)
        : timeStamper_(timeMap, t), v_(v)
        {
        }

        template < class Graph >
        void operator()(const typename property_traits< TimeMap >::key_type& v,
            const Graph& g)
        {
            timeStamper_(v, g);
            v_[timeStamper_.m_time] = v;
        }

    private:
        time_stamper< TimeMap, TimeT, Tag > timeStamper_;
        VertexVector& v_;
    };

    /**
     * A convenient way to create a time_stamper_with_vertex_vector
     */
    template < class TimeMap, class VertexVector, class TimeT, class Tag >
    time_stamper_with_vertex_vector< TimeMap, VertexVector, TimeT, Tag >
    stamp_times_with_vertex_vector(
        TimeMap timeMap, VertexVector& v, TimeT& t, Tag)
    {
        return time_stamper_with_vertex_vector< TimeMap, VertexVector, TimeT,
            Tag >(timeMap, v, t);
    }

    template < class Graph, class IndexMap, class TimeMap, class PredMap,
        class DomTreePredMap >
    class dominator_visitor
    {
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
        typedef
            typename graph_traits< Graph >::vertices_size_type VerticesSizeType;

    public:
        /**
         * @param g [in] the target graph of the dominator tree
         * @param entry [in] the entry node of g
         * @param indexMap [in] the vertex index map for g
         * @param domTreePredMap [out] the immediate dominator map
         *                             (parent map in dominator tree)
         */
        dominator_visitor(const Graph& g, const Vertex& entry,
            const IndexMap& indexMap, DomTreePredMap domTreePredMap)
        : semi_(num_vertices(g))
        , ancestor_(num_vertices(g), graph_traits< Graph >::null_vertex())
        , samedom_(ancestor_)
        , best_(semi_)
        , semiMap_(make_iterator_property_map(semi_.begin(), indexMap))
        , ancestorMap_(make_iterator_property_map(ancestor_.begin(), indexMap))
        , bestMap_(make_iterator_property_map(best_.begin(), indexMap))
        , buckets_(num_vertices(g))
        , bucketMap_(make_iterator_property_map(buckets_.begin(), indexMap))
        , entry_(entry)
        , domTreePredMap_(domTreePredMap)
        , numOfVertices_(num_vertices(g))
        , samedomMap(make_iterator_property_map(samedom_.begin(), indexMap))
        {
        }

        void operator()(const Vertex& n, const TimeMap& dfnumMap,
            const PredMap& parentMap, const Graph& g)
        {
            if (n == entry_)
                return;

            const Vertex p(get(parentMap, n));
            Vertex s(p);

            // 1. Calculate the semidominator of n,
            // based on the semidominator thm.
            // * Semidominator thm. : To find the semidominator of a node n,
            //   consider all predecessors v of n in the CFG (Control Flow
            //   Graph).
            //  - If v is a proper ancestor of n in the spanning tree
            //    (so dfnum(v) < dfnum(n)), then v is a candidate for semi(n)
            //  - If v is a non-ancestor of n (so dfnum(v) > dfnum(n))
            //    then for each u that is an ancestor of v (or u = v),
            //    Let semi(u) be a candidate for semi(n)
            //   of all these candidates, the one with lowest dfnum is
            //   the semidominator of n.

            // For each predecessor of n
            typename graph_traits< Graph >::in_edge_iterator inItr, inEnd;
            for (boost::tie(inItr, inEnd) = in_edges(n, g); inItr != inEnd;
                 ++inItr)
            {
                const Vertex v = source(*inItr, g);
                // To deal with unreachable nodes
                if (get(dfnumMap, v) < 0 || get(dfnumMap, v) >= numOfVertices_)
                    continue;

                Vertex s2;
                if (get(dfnumMap, v) <= get(dfnumMap, n))
                    s2 = v;
                else
                    s2 = get(semiMap_, ancestor_with_lowest_semi_(v, dfnumMap));

                if (get(dfnumMap, s2) < get(dfnumMap, s))
                    s = s2;
            }
            put(semiMap_, n, s);

            // 2. Calculation of n's dominator is deferred until
            // the path from s to n has been linked into the forest
            get(bucketMap_, s).push_back(n);
            get(ancestorMap_, n) = p;
            get(bestMap_, n) = n;

            // 3. Now that the path from p to v has been linked into
            // the spanning forest, these lines calculate the dominator of v,
            // based on the dominator thm., or else defer the calculation
            // until y's dominator is known
            // * Dominator thm. : On the spanning-tree path below semi(n) and
            //   above or including n, let y be the node
            //   with the smallest-numbered semidominator. Then,
            //
            //  idom(n) = semi(n) if semi(y)=semi(n) or
            //            idom(y) if semi(y) != semi(n)
            typename std::deque< Vertex >::iterator buckItr;
            for (buckItr = get(bucketMap_, p).begin();
                 buckItr != get(bucketMap_, p).end(); ++buckItr)
            {
                const Vertex v(*buckItr);
                const Vertex y(ancestor_with_lowest_semi_(v, dfnumMap));
                if (get(semiMap_, y) == get(semiMap_, v))
                    put(domTreePredMap_, v, p);
                else
                    put(samedomMap, v, y);
            }

            get(bucketMap_, p).clear();
        }

    protected:
        /**
         * Evaluate function in Tarjan's path compression
         */
        const Vertex ancestor_with_lowest_semi_(
            const Vertex& v, const TimeMap& dfnumMap)
        {
            const Vertex a(get(ancestorMap_, v));

            if (get(ancestorMap_, a) != graph_traits< Graph >::null_vertex())
            {
                const Vertex b(ancestor_with_lowest_semi_(a, dfnumMap));

                put(ancestorMap_, v, get(ancestorMap_, a));

                if (get(dfnumMap, get(semiMap_, b))
                    < get(dfnumMap, get(semiMap_, get(bestMap_, v))))
                    put(bestMap_, v, b);
            }

            return get(bestMap_, v);
        }

        std::vector< Vertex > semi_, ancestor_, samedom_, best_;
        PredMap semiMap_, ancestorMap_, bestMap_;
        std::vector< std::deque< Vertex > > buckets_;

        iterator_property_map<
            typename std::vector< std::deque< Vertex > >::iterator, IndexMap >
            bucketMap_;

        const Vertex& entry_;
        DomTreePredMap domTreePredMap_;
        const VerticesSizeType numOfVertices_;

    public:
        PredMap samedomMap;
    };

} // namespace detail

/**
 * @brief Build dominator tree using Lengauer-Tarjan algorithm.
 *                It takes O((V+E)log(V+E)) time.
 *
 * @pre dfnumMap, parentMap and verticesByDFNum have dfs results corresponding
 *      indexMap.
 *      If dfs has already run before,
 *      this function would be good for saving computations.
 * @pre Unreachable nodes must be masked as
 *      graph_traits<Graph>::null_vertex in parentMap.
 * @pre Unreachable nodes must be masked as
 *      (std::numeric_limits<VerticesSizeType>::max)() in dfnumMap.
 *
 * @param domTreePredMap [out] : immediate dominator map (parent map
 * in dom. tree)
 *
 * @note reference Appel. p. 452~453. algorithm 19.9, 19.10.
 *
 * @todo : Optimization in Finding Dominators in Practice, Loukas Georgiadis
 */
template < class Graph, class IndexMap, class TimeMap, class PredMap,
    class VertexVector, class DomTreePredMap >
void lengauer_tarjan_dominator_tree_without_dfs(const Graph& g,
    const typename graph_traits< Graph >::vertex_descriptor& entry,
    const IndexMap& indexMap, TimeMap dfnumMap, PredMap parentMap,
    VertexVector& verticesByDFNum, DomTreePredMap domTreePredMap)
{
    // Typedefs and concept check
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename graph_traits< Graph >::vertices_size_type VerticesSizeType;

    BOOST_CONCEPT_ASSERT((BidirectionalGraphConcept< Graph >));

    const VerticesSizeType numOfVertices = num_vertices(g);
    if (numOfVertices == 0)
        return;

    // 1. Visit each vertex in reverse post order and calculate sdom.
    detail::dominator_visitor< Graph, IndexMap, TimeMap, PredMap,
        DomTreePredMap >
        visitor(g, entry, indexMap, domTreePredMap);

    VerticesSizeType i;
    for (i = 0; i < numOfVertices; ++i)
    {
        const Vertex u(verticesByDFNum[numOfVertices - 1 - i]);
        if (u != graph_traits< Graph >::null_vertex())
            visitor(u, dfnumMap, parentMap, g);
    }

    // 2. Now all the deferred dominator calculations,
    // based on the second clause of the dominator thm., are performed
    for (i = 0; i < numOfVertices; ++i)
    {
        const Vertex n(verticesByDFNum[i]);

        if (n == entry || n == graph_traits< Graph >::null_vertex())
            continue;

        Vertex u = get(visitor.samedomMap, n);
        if (u != graph_traits< Graph >::null_vertex())
        {
            put(domTreePredMap, n, get(domTreePredMap, u));
        }
    }
}

/**
 * Unlike lengauer_tarjan_dominator_tree_without_dfs,
 * dfs is run in this function and
 * the result is written to dfnumMap, parentMap, vertices.
 *
 * If the result of dfs required after this algorithm,
 * this function can eliminate the need of rerunning dfs.
 */
template < class Graph, class IndexMap, class TimeMap, class PredMap,
    class VertexVector, class DomTreePredMap >
void lengauer_tarjan_dominator_tree(const Graph& g,
    const typename graph_traits< Graph >::vertex_descriptor& entry,
    const IndexMap& indexMap, TimeMap dfnumMap, PredMap parentMap,
    VertexVector& verticesByDFNum, DomTreePredMap domTreePredMap)
{
    // Typedefs and concept check
    typedef typename graph_traits< Graph >::vertices_size_type VerticesSizeType;

    BOOST_CONCEPT_ASSERT((BidirectionalGraphConcept< Graph >));

    // 1. Depth first visit
    const VerticesSizeType numOfVertices = num_vertices(g);
    if (numOfVertices == 0)
        return;

    VerticesSizeType time = (std::numeric_limits< VerticesSizeType >::max)();
    std::vector< default_color_type > colors(
        numOfVertices, color_traits< default_color_type >::white());
    depth_first_visit(g, entry,
        make_dfs_visitor(
            make_pair(record_predecessors(parentMap, on_tree_edge()),
                detail::stamp_times_with_vertex_vector(
                    dfnumMap, verticesByDFNum, time, on_discover_vertex()))),
        make_iterator_property_map(colors.begin(), indexMap));

    // 2. Run main algorithm.
    lengauer_tarjan_dominator_tree_without_dfs(g, entry, indexMap, dfnumMap,
        parentMap, verticesByDFNum, domTreePredMap);
}

/**
 * Use vertex_index as IndexMap and make dfnumMap, parentMap, verticesByDFNum
 * internally.
 * If we don't need the result of dfs (dfnumMap, parentMap, verticesByDFNum),
 * this function would be more convenient one.
 */
template < class Graph, class DomTreePredMap >
void lengauer_tarjan_dominator_tree(const Graph& g,
    const typename graph_traits< Graph >::vertex_descriptor& entry,
    DomTreePredMap domTreePredMap)
{
    // typedefs
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename graph_traits< Graph >::vertices_size_type VerticesSizeType;
    typedef typename property_map< Graph, vertex_index_t >::const_type IndexMap;
    typedef iterator_property_map<
        typename std::vector< VerticesSizeType >::iterator, IndexMap >
        TimeMap;
    typedef iterator_property_map< typename std::vector< Vertex >::iterator,
        IndexMap >
        PredMap;

    // Make property maps
    const VerticesSizeType numOfVertices = num_vertices(g);
    if (numOfVertices == 0)
        return;

    const IndexMap indexMap = get(vertex_index, g);

    std::vector< VerticesSizeType > dfnum(numOfVertices, 0);
    TimeMap dfnumMap(make_iterator_property_map(dfnum.begin(), indexMap));

    std::vector< Vertex > parent(
        numOfVertices, graph_traits< Graph >::null_vertex());
    PredMap parentMap(make_iterator_property_map(parent.begin(), indexMap));

    std::vector< Vertex > verticesByDFNum(parent);

    // Run main algorithm
    lengauer_tarjan_dominator_tree(g, entry, indexMap, dfnumMap, parentMap,
        verticesByDFNum, domTreePredMap);
}

/**
 * Muchnick. p. 182, 184
 *
 * using iterative bit vector analysis
 */
template < class Graph, class IndexMap, class DomTreePredMap >
void iterative_bit_vector_dominator_tree(const Graph& g,
    const typename graph_traits< Graph >::vertex_descriptor& entry,
    const IndexMap& indexMap, DomTreePredMap domTreePredMap)
{
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename graph_traits< Graph >::vertex_iterator vertexItr;
    typedef typename graph_traits< Graph >::vertices_size_type VerticesSizeType;
    typedef iterator_property_map<
        typename std::vector< std::set< Vertex > >::iterator, IndexMap >
        vertexSetMap;

    BOOST_CONCEPT_ASSERT((BidirectionalGraphConcept< Graph >));

    // 1. Finding dominator
    // 1.1. Initialize
    const VerticesSizeType numOfVertices = num_vertices(g);
    if (numOfVertices == 0)
        return;

    vertexItr vi, viend;
    boost::tie(vi, viend) = vertices(g);
    const std::set< Vertex > N(vi, viend);

    bool change = true;

    std::vector< std::set< Vertex > > dom(numOfVertices, N);
    vertexSetMap domMap(make_iterator_property_map(dom.begin(), indexMap));
    get(domMap, entry).clear();
    get(domMap, entry).insert(entry);

    while (change)
    {
        change = false;
        for (boost::tie(vi, viend) = vertices(g); vi != viend; ++vi)
        {
            if (*vi == entry)
                continue;

            std::set< Vertex > T(N);

            typename graph_traits< Graph >::in_edge_iterator inItr, inEnd;
            for (boost::tie(inItr, inEnd) = in_edges(*vi, g); inItr != inEnd;
                 ++inItr)
            {
                const Vertex p = source(*inItr, g);

                std::set< Vertex > tempSet;
                std::set_intersection(T.begin(), T.end(),
                    get(domMap, p).begin(), get(domMap, p).end(),
                    std::inserter(tempSet, tempSet.begin()));
                T.swap(tempSet);
            }

            T.insert(*vi);
            if (T != get(domMap, *vi))
            {
                change = true;
                get(domMap, *vi).swap(T);
            }
        } // end of for (boost::tie(vi, viend) = vertices(g)
    } // end of while(change)

    // 2. Build dominator tree
    for (boost::tie(vi, viend) = vertices(g); vi != viend; ++vi)
        get(domMap, *vi).erase(*vi);

    Graph domTree(numOfVertices);

    for (boost::tie(vi, viend) = vertices(g); vi != viend; ++vi)
    {
        if (*vi == entry)
            continue;

        // We have to iterate through copied dominator set
        const std::set< Vertex > tempSet(get(domMap, *vi));
        typename std::set< Vertex >::const_iterator s;
        for (s = tempSet.begin(); s != tempSet.end(); ++s)
        {
            typename std::set< Vertex >::iterator t;
            for (t = get(domMap, *vi).begin(); t != get(domMap, *vi).end();)
            {
                typename std::set< Vertex >::iterator old_t = t;
                ++t; // Done early because t may become invalid
                if (*old_t == *s)
                    continue;
                if (get(domMap, *s).find(*old_t) != get(domMap, *s).end())
                    get(domMap, *vi).erase(old_t);
            }
        }
    }

    for (boost::tie(vi, viend) = vertices(g); vi != viend; ++vi)
    {
        if (*vi != entry && get(domMap, *vi).size() == 1)
        {
            Vertex temp = *get(domMap, *vi).begin();
            put(domTreePredMap, *vi, temp);
        }
    }
}

template < class Graph, class DomTreePredMap >
void iterative_bit_vector_dominator_tree(const Graph& g,
    const typename graph_traits< Graph >::vertex_descriptor& entry,
    DomTreePredMap domTreePredMap)
{
    typename property_map< Graph, vertex_index_t >::const_type indexMap
        = get(vertex_index, g);

    iterative_bit_vector_dominator_tree(g, entry, indexMap, domTreePredMap);
}
} // namespace boost

#endif // BOOST_GRAPH_DOMINATOR_HPP

/* dominator_tree.hpp
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
*/