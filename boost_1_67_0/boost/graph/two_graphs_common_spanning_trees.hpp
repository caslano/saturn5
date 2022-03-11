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