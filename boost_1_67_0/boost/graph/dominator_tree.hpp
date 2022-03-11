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