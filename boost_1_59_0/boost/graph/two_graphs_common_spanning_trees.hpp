//          Copyright (C) 2012, Michele Caini.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//          Two Graphs Common Spanning Trees Algorithm
//      Based on academic article of Mint, Read and Tarjan
//     Efficient Algorithm for Common Spanning Tree Problem
// Electron. Lett., 28 April 1983, Volume 19, Issue 9, p.346-347

#ifndef BOOST_GRAPH_TWO_GRAPHS_COMMON_SPANNING_TREES_HPP
#define BOOST_GRAPH_TWO_GRAPHS_COMMON_SPANNING_TREES_HPP

#include <boost/config.hpp>

#include <boost/bimap.hpp>
#include <boost/type_traits.hpp>
#include <boost/concept/requires.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/undirected_dfs.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <vector>
#include <stack>
#include <map>

namespace boost
{

namespace detail
{

    template < typename TreeMap, typename PredMap, typename DistMap,
        typename LowMap, typename Buffer >
    struct bridges_visitor : public default_dfs_visitor
    {
        bridges_visitor(TreeMap tree, PredMap pred, DistMap dist, LowMap low,
            Buffer& buffer)
        : mTree(tree), mPred(pred), mDist(dist), mLow(low), mBuffer(buffer)
        {
            mNum = -1;
        }

        template < typename Vertex, typename Graph >
        void initialize_vertex(const Vertex& u, const Graph& g)
        {
            put(mPred, u, u);
            put(mDist, u, -1);
        }

        template < typename Vertex, typename Graph >
        void discover_vertex(const Vertex& u, const Graph& g)
        {
            put(mDist, u, ++mNum);
            put(mLow, u, get(mDist, u));
        }

        template < typename Edge, typename Graph >
        void tree_edge(const Edge& e, const Graph& g)
        {
            put(mPred, target(e, g), source(e, g));
            put(mTree, target(e, g), e);
        }

        template < typename Edge, typename Graph >
        void back_edge(const Edge& e, const Graph& g)
        {
            put(mLow, source(e, g),
                (std::min)(get(mLow, source(e, g)), get(mDist, target(e, g))));
        }

        template < typename Vertex, typename Graph >
        void finish_vertex(const Vertex& u, const Graph& g)
        {
            Vertex parent = get(mPred, u);
            if (get(mLow, u) > get(mDist, parent))
                mBuffer.push(get(mTree, u));
            put(mLow, parent, (std::min)(get(mLow, parent), get(mLow, u)));
        }

        TreeMap mTree;
        PredMap mPred;
        DistMap mDist;
        LowMap mLow;
        Buffer& mBuffer;
        int mNum;
    };

    template < typename Buffer >
    struct cycle_finder : public base_visitor< cycle_finder< Buffer > >
    {
        typedef on_back_edge event_filter;
        cycle_finder() : mBuffer(0) {}
        cycle_finder(Buffer* buffer) : mBuffer(buffer) {}
        template < typename Edge, typename Graph >
        void operator()(const Edge& e, const Graph& g)
        {
            if (mBuffer)
                mBuffer->push(e);
        }
        Buffer* mBuffer;
    };

    template < typename DeletedMap > struct deleted_edge_status
    {
        deleted_edge_status() {}
        deleted_edge_status(DeletedMap map) : mMap(map) {}
        template < typename Edge > bool operator()(const Edge& e) const
        {
            return (!get(mMap, e));
        }
        DeletedMap mMap;
    };

    template < typename InLMap > struct inL_edge_status
    {
        inL_edge_status() {}
        inL_edge_status(InLMap map) : mMap(map) {}
        template < typename Edge > bool operator()(const Edge& e) const
        {
            return get(mMap, e);
        }
        InLMap mMap;
    };

    template < typename Graph, typename Func, typename Seq, typename Map >
    void rec_two_graphs_common_spanning_trees(const Graph& iG,
        bimap< bimaps::set_of< int >,
            bimaps::set_of< typename graph_traits< Graph >::edge_descriptor > >
            iG_bimap,
        Map aiG_inL, Map diG, const Graph& vG,
        bimap< bimaps::set_of< int >,
            bimaps::set_of< typename graph_traits< Graph >::edge_descriptor > >
            vG_bimap,
        Map avG_inL, Map dvG, Func func, Seq inL)
    {
        typedef graph_traits< Graph > GraphTraits;

        typedef typename GraphTraits::vertex_descriptor vertex_descriptor;
        typedef typename GraphTraits::edge_descriptor edge_descriptor;

        typedef typename Seq::size_type seq_size_type;

        int edges = num_vertices(iG) - 1;
        //
        //  [ Michele Caini ]
        //
        //  Using the condition (edges != 0) leads to the accidental submission
        //  of
        //    sub-graphs ((V-1+1)-fake-tree, named here fat-tree).
        //  Remove this condition is a workaround for the problem of fat-trees.
        //  Please do not add that condition, even if it improves performance.
        //
        //  Here is proposed the previous guard (that was wrong):
        //     for(seq_size_type i = 0; (i < inL.size()) && (edges != 0); ++i)
        //
        {
            for (seq_size_type i = 0; i < inL.size(); ++i)
                if (inL[i])
                    --edges;

            if (edges < 0)
                return;
        }

        bool is_tree = (edges == 0);
        if (is_tree)
        {
            func(inL);
        }
        else
        {
            std::map< vertex_descriptor, default_color_type > vertex_color;
            std::map< edge_descriptor, default_color_type > edge_color;

            std::stack< edge_descriptor > iG_buf, vG_buf;
            bool found = false;

            seq_size_type m;
            for (seq_size_type j = 0; j < inL.size() && !found; ++j)
            {
                if (!inL[j] && !get(diG, iG_bimap.left.at(j))
                    && !get(dvG, vG_bimap.left.at(j)))
                {
                    put(aiG_inL, iG_bimap.left.at(j), true);
                    put(avG_inL, vG_bimap.left.at(j), true);

                    undirected_dfs(
                        make_filtered_graph(iG,
                            detail::inL_edge_status< associative_property_map<
                                std::map< edge_descriptor, bool > > >(aiG_inL)),
                        make_dfs_visitor(detail::cycle_finder<
                            std::stack< edge_descriptor > >(&iG_buf)),
                        associative_property_map<
                            std::map< vertex_descriptor, default_color_type > >(
                            vertex_color),
                        associative_property_map<
                            std::map< edge_descriptor, default_color_type > >(
                            edge_color));
                    undirected_dfs(
                        make_filtered_graph(vG,
                            detail::inL_edge_status< associative_property_map<
                                std::map< edge_descriptor, bool > > >(avG_inL)),
                        make_dfs_visitor(detail::cycle_finder<
                            std::stack< edge_descriptor > >(&vG_buf)),
                        associative_property_map<
                            std::map< vertex_descriptor, default_color_type > >(
                            vertex_color),
                        associative_property_map<
                            std::map< edge_descriptor, default_color_type > >(
                            edge_color));

                    if (iG_buf.empty() && vG_buf.empty())
                    {
                        inL[j] = true;
                        found = true;
                        m = j;
                    }
                    else
                    {
                        while (!iG_buf.empty())
                            iG_buf.pop();
                        while (!vG_buf.empty())
                            vG_buf.pop();
                        put(aiG_inL, iG_bimap.left.at(j), false);
                        put(avG_inL, vG_bimap.left.at(j), false);
                    }
                }
            }

            if (found)
            {

                std::stack< edge_descriptor > iG_buf_copy, vG_buf_copy;
                for (seq_size_type j = 0; j < inL.size(); ++j)
                {
                    if (!inL[j] && !get(diG, iG_bimap.left.at(j))
                        && !get(dvG, vG_bimap.left.at(j)))
                    {

                        put(aiG_inL, iG_bimap.left.at(j), true);
                        put(avG_inL, vG_bimap.left.at(j), true);

                        undirected_dfs(
                            make_filtered_graph(iG,
                                detail::inL_edge_status<
                                    associative_property_map<
                                        std::map< edge_descriptor, bool > > >(
                                    aiG_inL)),
                            make_dfs_visitor(detail::cycle_finder<
                                std::stack< edge_descriptor > >(&iG_buf)),
                            associative_property_map< std::map<
                                vertex_descriptor, default_color_type > >(
                                vertex_color),
                            associative_property_map< std::map< edge_descriptor,
                                default_color_type > >(edge_color));
                        undirected_dfs(
                            make_filtered_graph(vG,
                                detail::inL_edge_status<
                                    associative_property_map<
                                        std::map< edge_descriptor, bool > > >(
                                    avG_inL)),
                            make_dfs_visitor(detail::cycle_finder<
                                std::stack< edge_descriptor > >(&vG_buf)),
                            associative_property_map< std::map<
                                vertex_descriptor, default_color_type > >(
                                vertex_color),
                            associative_property_map< std::map< edge_descriptor,
                                default_color_type > >(edge_color));

                        if (!iG_buf.empty() || !vG_buf.empty())
                        {
                            while (!iG_buf.empty())
                                iG_buf.pop();
                            while (!vG_buf.empty())
                                vG_buf.pop();
                            put(diG, iG_bimap.left.at(j), true);
                            put(dvG, vG_bimap.left.at(j), true);
                            iG_buf_copy.push(iG_bimap.left.at(j));
                            vG_buf_copy.push(vG_bimap.left.at(j));
                        }

                        put(aiG_inL, iG_bimap.left.at(j), false);
                        put(avG_inL, vG_bimap.left.at(j), false);
                    }
                }

                // REC
                detail::rec_two_graphs_common_spanning_trees< Graph, Func, Seq,
                    Map >(iG, iG_bimap, aiG_inL, diG, vG, vG_bimap, aiG_inL,
                    dvG, func, inL);

                while (!iG_buf_copy.empty())
                {
                    put(diG, iG_buf_copy.top(), false);
                    put(dvG,
                        vG_bimap.left.at(iG_bimap.right.at(iG_buf_copy.top())),
                        false);
                    iG_buf_copy.pop();
                }
                while (!vG_buf_copy.empty())
                {
                    put(dvG, vG_buf_copy.top(), false);
                    put(diG,
                        iG_bimap.left.at(vG_bimap.right.at(vG_buf_copy.top())),
                        false);
                    vG_buf_copy.pop();
                }

                inL[m] = false;
                put(aiG_inL, iG_bimap.left.at(m), false);
                put(avG_inL, vG_bimap.left.at(m), false);

                put(diG, iG_bimap.left.at(m), true);
                put(dvG, vG_bimap.left.at(m), true);

                std::map< vertex_descriptor, edge_descriptor > tree_map;
                std::map< vertex_descriptor, vertex_descriptor > pred_map;
                std::map< vertex_descriptor, int > dist_map, low_map;

                detail::bridges_visitor<
                    associative_property_map<
                        std::map< vertex_descriptor, edge_descriptor > >,
                    associative_property_map<
                        std::map< vertex_descriptor, vertex_descriptor > >,
                    associative_property_map<
                        std::map< vertex_descriptor, int > >,
                    associative_property_map<
                        std::map< vertex_descriptor, int > >,
                    std::stack< edge_descriptor > >
                iG_vis(associative_property_map<
                           std::map< vertex_descriptor, edge_descriptor > >(
                           tree_map),
                    associative_property_map<
                        std::map< vertex_descriptor, vertex_descriptor > >(
                        pred_map),
                    associative_property_map<
                        std::map< vertex_descriptor, int > >(dist_map),
                    associative_property_map<
                        std::map< vertex_descriptor, int > >(low_map),
                    iG_buf),
                    vG_vis(associative_property_map<
                               std::map< vertex_descriptor, edge_descriptor > >(
                               tree_map),
                        associative_property_map<
                            std::map< vertex_descriptor, vertex_descriptor > >(
                            pred_map),
                        associative_property_map<
                            std::map< vertex_descriptor, int > >(dist_map),
                        associative_property_map<
                            std::map< vertex_descriptor, int > >(low_map),
                        vG_buf);

                undirected_dfs(
                    make_filtered_graph(iG,
                        detail::deleted_edge_status< associative_property_map<
                            std::map< edge_descriptor, bool > > >(diG)),
                    iG_vis,
                    associative_property_map<
                        std::map< vertex_descriptor, default_color_type > >(
                        vertex_color),
                    associative_property_map<
                        std::map< edge_descriptor, default_color_type > >(
                        edge_color));
                undirected_dfs(
                    make_filtered_graph(vG,
                        detail::deleted_edge_status< associative_property_map<
                            std::map< edge_descriptor, bool > > >(dvG)),
                    vG_vis,
                    associative_property_map<
                        std::map< vertex_descriptor, default_color_type > >(
                        vertex_color),
                    associative_property_map<
                        std::map< edge_descriptor, default_color_type > >(
                        edge_color));

                found = false;
                std::stack< edge_descriptor > iG_buf_tmp, vG_buf_tmp;
                while (!iG_buf.empty() && !found)
                {
                    if (!inL[iG_bimap.right.at(iG_buf.top())])
                    {
                        put(aiG_inL, iG_buf.top(), true);
                        put(avG_inL,
                            vG_bimap.left.at(iG_bimap.right.at(iG_buf.top())),
                            true);

                        undirected_dfs(
                            make_filtered_graph(iG,
                                detail::inL_edge_status<
                                    associative_property_map<
                                        std::map< edge_descriptor, bool > > >(
                                    aiG_inL)),
                            make_dfs_visitor(detail::cycle_finder<
                                std::stack< edge_descriptor > >(&iG_buf_tmp)),
                            associative_property_map< std::map<
                                vertex_descriptor, default_color_type > >(
                                vertex_color),
                            associative_property_map< std::map< edge_descriptor,
                                default_color_type > >(edge_color));
                        undirected_dfs(
                            make_filtered_graph(vG,
                                detail::inL_edge_status<
                                    associative_property_map<
                                        std::map< edge_descriptor, bool > > >(
                                    avG_inL)),
                            make_dfs_visitor(detail::cycle_finder<
                                std::stack< edge_descriptor > >(&vG_buf_tmp)),
                            associative_property_map< std::map<
                                vertex_descriptor, default_color_type > >(
                                vertex_color),
                            associative_property_map< std::map< edge_descriptor,
                                default_color_type > >(edge_color));

                        if (!iG_buf_tmp.empty() || !vG_buf_tmp.empty())
                        {
                            found = true;
                        }
                        else
                        {
                            while (!iG_buf_tmp.empty())
                                iG_buf_tmp.pop();
                            while (!vG_buf_tmp.empty())
                                vG_buf_tmp.pop();
                            iG_buf_copy.push(iG_buf.top());
                        }

                        put(aiG_inL, iG_buf.top(), false);
                        put(avG_inL,
                            vG_bimap.left.at(iG_bimap.right.at(iG_buf.top())),
                            false);
                    }
                    iG_buf.pop();
                }
                while (!vG_buf.empty() && !found)
                {
                    if (!inL[vG_bimap.right.at(vG_buf.top())])
                    {
                        put(avG_inL, vG_buf.top(), true);
                        put(aiG_inL,
                            iG_bimap.left.at(vG_bimap.right.at(vG_buf.top())),
                            true);

                        undirected_dfs(
                            make_filtered_graph(iG,
                                detail::inL_edge_status<
                                    associative_property_map<
                                        std::map< edge_descriptor, bool > > >(
                                    aiG_inL)),
                            make_dfs_visitor(detail::cycle_finder<
                                std::stack< edge_descriptor > >(&iG_buf_tmp)),
                            associative_property_map< std::map<
                                vertex_descriptor, default_color_type > >(
                                vertex_color),
                            associative_property_map< std::map< edge_descriptor,
                                default_color_type > >(edge_color));
                        undirected_dfs(
                            make_filtered_graph(vG,
                                detail::inL_edge_status<
                                    associative_property_map<
                                        std::map< edge_descriptor, bool > > >(
                                    avG_inL)),
                            make_dfs_visitor(detail::cycle_finder<
                                std::stack< edge_descriptor > >(&vG_buf_tmp)),
                            associative_property_map< std::map<
                                vertex_descriptor, default_color_type > >(
                                vertex_color),
                            associative_property_map< std::map< edge_descriptor,
                                default_color_type > >(edge_color));

                        if (!iG_buf_tmp.empty() || !vG_buf_tmp.empty())
                        {
                            found = true;
                        }
                        else
                        {
                            while (!iG_buf_tmp.empty())
                                iG_buf_tmp.pop();
                            while (!vG_buf_tmp.empty())
                                vG_buf_tmp.pop();
                            vG_buf_copy.push(vG_buf.top());
                        }

                        put(avG_inL, vG_buf.top(), false);
                        put(aiG_inL,
                            iG_bimap.left.at(vG_bimap.right.at(vG_buf.top())),
                            false);
                    }
                    vG_buf.pop();
                }

                if (!found)
                {

                    while (!iG_buf_copy.empty())
                    {
                        inL[iG_bimap.right.at(iG_buf_copy.top())] = true;
                        put(aiG_inL, iG_buf_copy.top(), true);
                        put(avG_inL,
                            vG_bimap.left.at(
                                iG_bimap.right.at(iG_buf_copy.top())),
                            true);
                        iG_buf.push(iG_buf_copy.top());
                        iG_buf_copy.pop();
                    }
                    while (!vG_buf_copy.empty())
                    {
                        inL[vG_bimap.right.at(vG_buf_copy.top())] = true;
                        put(avG_inL, vG_buf_copy.top(), true);
                        put(aiG_inL,
                            iG_bimap.left.at(
                                vG_bimap.right.at(vG_buf_copy.top())),
                            true);
                        vG_buf.push(vG_buf_copy.top());
                        vG_buf_copy.pop();
                    }

                    // REC
                    detail::rec_two_graphs_common_spanning_trees< Graph, Func,
                        Seq, Map >(iG, iG_bimap, aiG_inL, diG, vG, vG_bimap,
                        aiG_inL, dvG, func, inL);

                    while (!iG_buf.empty())
                    {
                        inL[iG_bimap.right.at(iG_buf.top())] = false;
                        put(aiG_inL, iG_buf.top(), false);
                        put(avG_inL,
                            vG_bimap.left.at(iG_bimap.right.at(iG_buf.top())),
                            false);
                        iG_buf.pop();
                    }
                    while (!vG_buf.empty())
                    {
                        inL[vG_bimap.right.at(vG_buf.top())] = false;
                        put(avG_inL, vG_buf.top(), false);
                        put(aiG_inL,
                            iG_bimap.left.at(vG_bimap.right.at(vG_buf.top())),
                            false);
                        vG_buf.pop();
                    }
                }

                put(diG, iG_bimap.left.at(m), false);
                put(dvG, vG_bimap.left.at(m), false);
            }
        }
    }

} // namespace detail

template < typename Coll, typename Seq > struct tree_collector
{

public:
    BOOST_CONCEPT_ASSERT((BackInsertionSequence< Coll >));
    BOOST_CONCEPT_ASSERT((RandomAccessContainer< Seq >));
    BOOST_CONCEPT_ASSERT((CopyConstructible< Seq >));

    typedef typename Coll::value_type coll_value_type;
    typedef typename Seq::value_type seq_value_type;

    BOOST_STATIC_ASSERT((is_same< coll_value_type, Seq >::value));
    BOOST_STATIC_ASSERT((is_same< seq_value_type, bool >::value));

    tree_collector(Coll& seqs) : mSeqs(seqs) {}

    inline void operator()(Seq seq) { mSeqs.push_back(seq); }

private:
    Coll& mSeqs;
};

template < typename Graph, typename Order, typename Func, typename Seq >
BOOST_CONCEPT_REQUIRES(
    ((RandomAccessContainer< Order >))((IncidenceGraphConcept< Graph >))(
        (UnaryFunction< Func, void, Seq >))(
        (Mutable_RandomAccessContainer< Seq >))(
        (VertexAndEdgeListGraphConcept< Graph >)),
    (void))
two_graphs_common_spanning_trees(const Graph& iG, Order iG_map, const Graph& vG,
    Order vG_map, Func func, Seq inL)
{
    typedef graph_traits< Graph > GraphTraits;

    typedef typename GraphTraits::directed_category directed_category;
    typedef typename GraphTraits::vertex_descriptor vertex_descriptor;
    typedef typename GraphTraits::edge_descriptor edge_descriptor;

    typedef typename GraphTraits::edges_size_type edges_size_type;
    typedef typename GraphTraits::edge_iterator edge_iterator;

    typedef typename Seq::value_type seq_value_type;
    typedef typename Seq::size_type seq_size_type;

    typedef typename Order::value_type order_value_type;
    typedef typename Order::size_type order_size_type;

    BOOST_STATIC_ASSERT((is_same< order_value_type, edge_descriptor >::value));
    BOOST_CONCEPT_ASSERT((Convertible< order_size_type, edges_size_type >));

    BOOST_CONCEPT_ASSERT((Convertible< seq_size_type, edges_size_type >));
    BOOST_STATIC_ASSERT((is_same< seq_value_type, bool >::value));

    BOOST_STATIC_ASSERT((is_same< directed_category, undirected_tag >::value));

    if (num_vertices(iG) != num_vertices(vG))
        return;

    if (inL.size() != num_edges(iG) || inL.size() != num_edges(vG))
        return;

    if (iG_map.size() != num_edges(iG) || vG_map.size() != num_edges(vG))
        return;

    typedef bimaps::bimap< bimaps::set_of< int >,
        bimaps::set_of< order_value_type > >
        bimap_type;
    typedef typename bimap_type::value_type bimap_value;

    bimap_type iG_bimap, vG_bimap;
    for (order_size_type i = 0; i < iG_map.size(); ++i)
        iG_bimap.insert(bimap_value(i, iG_map[i]));
    for (order_size_type i = 0; i < vG_map.size(); ++i)
        vG_bimap.insert(bimap_value(i, vG_map[i]));

    edge_iterator current, last;
    boost::tuples::tie(current, last) = edges(iG);
    for (; current != last; ++current)
        if (iG_bimap.right.find(*current) == iG_bimap.right.end())
            return;
    boost::tuples::tie(current, last) = edges(vG);
    for (; current != last; ++current)
        if (vG_bimap.right.find(*current) == vG_bimap.right.end())
            return;

    std::stack< edge_descriptor > iG_buf, vG_buf;

    std::map< vertex_descriptor, edge_descriptor > tree_map;
    std::map< vertex_descriptor, vertex_descriptor > pred_map;
    std::map< vertex_descriptor, int > dist_map, low_map;

    detail::bridges_visitor< associative_property_map< std::map<
                                 vertex_descriptor, edge_descriptor > >,
        associative_property_map<
            std::map< vertex_descriptor, vertex_descriptor > >,
        associative_property_map< std::map< vertex_descriptor, int > >,
        associative_property_map< std::map< vertex_descriptor, int > >,
        std::stack< edge_descriptor > >
    iG_vis(associative_property_map<
               std::map< vertex_descriptor, edge_descriptor > >(tree_map),
        associative_property_map<
            std::map< vertex_descriptor, vertex_descriptor > >(pred_map),
        associative_property_map< std::map< vertex_descriptor, int > >(
            dist_map),
        associative_property_map< std::map< vertex_descriptor, int > >(low_map),
        iG_buf),
        vG_vis(associative_property_map<
                   std::map< vertex_descriptor, edge_descriptor > >(tree_map),
            associative_property_map<
                std::map< vertex_descriptor, vertex_descriptor > >(pred_map),
            associative_property_map< std::map< vertex_descriptor, int > >(
                dist_map),
            associative_property_map< std::map< vertex_descriptor, int > >(
                low_map),
            vG_buf);

    std::map< vertex_descriptor, default_color_type > vertex_color;
    std::map< edge_descriptor, default_color_type > edge_color;

    undirected_dfs(iG, iG_vis,
        associative_property_map<
            std::map< vertex_descriptor, default_color_type > >(vertex_color),
        associative_property_map<
            std::map< edge_descriptor, default_color_type > >(edge_color));
    undirected_dfs(vG, vG_vis,
        associative_property_map<
            std::map< vertex_descriptor, default_color_type > >(vertex_color),
        associative_property_map<
            std::map< edge_descriptor, default_color_type > >(edge_color));

    while (!iG_buf.empty())
    {
        inL[iG_bimap.right.at(iG_buf.top())] = true;
        iG_buf.pop();
    }
    while (!vG_buf.empty())
    {
        inL[vG_bimap.right.at(vG_buf.top())] = true;
        vG_buf.pop();
    }

    std::map< edge_descriptor, bool > iG_inL, vG_inL;
    associative_property_map< std::map< edge_descriptor, bool > > aiG_inL(
        iG_inL),
        avG_inL(vG_inL);

    for (seq_size_type i = 0; i < inL.size(); ++i)
    {
        if (inL[i])
        {
            put(aiG_inL, iG_bimap.left.at(i), true);
            put(avG_inL, vG_bimap.left.at(i), true);
        }
        else
        {
            put(aiG_inL, iG_bimap.left.at(i), false);
            put(avG_inL, vG_bimap.left.at(i), false);
        }
    }

    undirected_dfs(
        make_filtered_graph(iG,
            detail::inL_edge_status<
                associative_property_map< std::map< edge_descriptor, bool > > >(
                aiG_inL)),
        make_dfs_visitor(
            detail::cycle_finder< std::stack< edge_descriptor > >(&iG_buf)),
        associative_property_map<
            std::map< vertex_descriptor, default_color_type > >(vertex_color),
        associative_property_map<
            std::map< edge_descriptor, default_color_type > >(edge_color));
    undirected_dfs(
        make_filtered_graph(vG,
            detail::inL_edge_status<
                associative_property_map< std::map< edge_descriptor, bool > > >(
                avG_inL)),
        make_dfs_visitor(
            detail::cycle_finder< std::stack< edge_descriptor > >(&vG_buf)),
        associative_property_map<
            std::map< vertex_descriptor, default_color_type > >(vertex_color),
        associative_property_map<
            std::map< edge_descriptor, default_color_type > >(edge_color));

    if (iG_buf.empty() && vG_buf.empty())
    {

        std::map< edge_descriptor, bool > iG_deleted, vG_deleted;
        associative_property_map< std::map< edge_descriptor, bool > > diG(
            iG_deleted);
        associative_property_map< std::map< edge_descriptor, bool > > dvG(
            vG_deleted);

        boost::tuples::tie(current, last) = edges(iG);
        for (; current != last; ++current)
            put(diG, *current, false);
        boost::tuples::tie(current, last) = edges(vG);
        for (; current != last; ++current)
            put(dvG, *current, false);

        for (seq_size_type j = 0; j < inL.size(); ++j)
        {
            if (!inL[j])
            {
                put(aiG_inL, iG_bimap.left.at(j), true);
                put(avG_inL, vG_bimap.left.at(j), true);

                undirected_dfs(
                    make_filtered_graph(iG,
                        detail::inL_edge_status< associative_property_map<
                            std::map< edge_descriptor, bool > > >(aiG_inL)),
                    make_dfs_visitor(
                        detail::cycle_finder< std::stack< edge_descriptor > >(
                            &iG_buf)),
                    associative_property_map<
                        std::map< vertex_descriptor, default_color_type > >(
                        vertex_color),
                    associative_property_map<
                        std::map< edge_descriptor, default_color_type > >(
                        edge_color));
                undirected_dfs(
                    make_filtered_graph(vG,
                        detail::inL_edge_status< associative_property_map<
                            std::map< edge_descriptor, bool > > >(avG_inL)),
                    make_dfs_visitor(
                        detail::cycle_finder< std::stack< edge_descriptor > >(
                            &vG_buf)),
                    associative_property_map<
                        std::map< vertex_descriptor, default_color_type > >(
                        vertex_color),
                    associative_property_map<
                        std::map< edge_descriptor, default_color_type > >(
                        edge_color));

                if (!iG_buf.empty() || !vG_buf.empty())
                {
                    while (!iG_buf.empty())
                        iG_buf.pop();
                    while (!vG_buf.empty())
                        vG_buf.pop();
                    put(diG, iG_bimap.left.at(j), true);
                    put(dvG, vG_bimap.left.at(j), true);
                }

                put(aiG_inL, iG_bimap.left.at(j), false);
                put(avG_inL, vG_bimap.left.at(j), false);
            }
        }

        int cc = 0;

        std::map< vertex_descriptor, int > com_map;
        cc += connected_components(
            make_filtered_graph(iG,
                detail::deleted_edge_status< associative_property_map<
                    std::map< edge_descriptor, bool > > >(diG)),
            associative_property_map< std::map< vertex_descriptor, int > >(
                com_map));
        cc += connected_components(
            make_filtered_graph(vG,
                detail::deleted_edge_status< associative_property_map<
                    std::map< edge_descriptor, bool > > >(dvG)),
            associative_property_map< std::map< vertex_descriptor, int > >(
                com_map));

        if (cc != 2)
            return;

        // REC
        detail::rec_two_graphs_common_spanning_trees< Graph, Func, Seq,
            associative_property_map< std::map< edge_descriptor, bool > > >(
            iG, iG_bimap, aiG_inL, diG, vG, vG_bimap, aiG_inL, dvG, func, inL);
    }
}

template < typename Graph, typename Func, typename Seq >
BOOST_CONCEPT_REQUIRES(
    ((IncidenceGraphConcept< Graph >))((EdgeListGraphConcept< Graph >)), (void))
two_graphs_common_spanning_trees(
    const Graph& iG, const Graph& vG, Func func, Seq inL)
{
    typedef graph_traits< Graph > GraphTraits;

    typedef typename GraphTraits::edge_descriptor edge_descriptor;
    typedef typename GraphTraits::edge_iterator edge_iterator;

    std::vector< edge_descriptor > iGO, vGO;
    edge_iterator curr, last;

    boost::tuples::tie(curr, last) = edges(iG);
    for (; curr != last; ++curr)
        iGO.push_back(*curr);

    boost::tuples::tie(curr, last) = edges(vG);
    for (; curr != last; ++curr)
        vGO.push_back(*curr);

    two_graphs_common_spanning_trees(iG, iGO, vG, vGO, func, inL);
}

} // namespace boost

#endif // BOOST_GRAPH_TWO_GRAPHS_COMMON_SPANNING_TREES_HPP

/* two_graphs_common_spanning_trees.hpp
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
*/