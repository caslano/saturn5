// Copyright 2008-2010 Gordon Woodhull
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// mpl_graph - defines a metadata implementation of the BGL immutable graph concepts

// (c) 2008 Gordon Woodhull 
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSEmpl::_1_0.txt or copy at
// http://www.boost.org/LICENSEmpl::_1_0.txt)

#ifndef BOOST_MSM_MPL_GRAPH_MPL_GRAPH_HPP_INCLUDED
#define BOOST_MSM_MPL_GRAPH_MPL_GRAPH_HPP_INCLUDED

#include <boost/msm/mpl_graph/detail/graph_implementation_interface.ipp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/back_inserter.hpp>

namespace boost {
namespace msm {
namespace mpl_graph {

// Boost Graph concepts, MPL style

// The metafunctions of the public interface rely 
// metafunctions in the graph implementation to transform the input 
// into the maps which are required to deliver results.  Since the
// maps are produced lazily and are memoized, all of the graph
// concepts can be supported with no cost until they are actually
// used.

// Each of these dispatch to the correct producer metafunctions based
// on the representation inner type tag



// IncidenceGraph
template<typename Edge, typename Graph>
struct source : 
    mpl::first<typename mpl::at<typename detail::produce_edge_st_map<typename Graph::representation, typename Graph::data>::type,Edge>::type> 
{};
template<typename Edge, typename Graph>
struct target : 
    mpl::second<typename mpl::at<typename detail::produce_edge_st_map<typename Graph::representation, typename Graph::data>::type,Edge>::type> 
{};
template<typename Vertex, typename Graph>
struct out_edges :
    mpl::fold<typename detail::produce_out_map<typename Graph::representation, Vertex, typename Graph::data>::type,
         mpl::vector<>,
         mpl::push_back<mpl::_1, mpl::first<mpl::_2> > >
{};
template<typename Vertex, typename Graph>
struct out_degree : 
    mpl::size<typename out_edges<Vertex, Graph>::type>
{};

// BidirectionalGraph
template<typename Vertex, typename Graph>
struct in_edges :
    mpl::fold<typename detail::produce_in_map<typename Graph::representation, Vertex, typename Graph::data>::type,
         mpl::vector<>,
         mpl::push_back<mpl::_1, mpl::first<mpl::_2> > >
{};
template<typename Vertex, typename Graph>
struct in_degree :
    mpl::size<typename in_edges<Vertex, Graph>::type>
{};
template<typename Vertex, typename Graph>
struct degree :
    mpl::plus<typename out_degree<Vertex, Graph>::type,typename in_degree<Vertex, Graph>::type>
{};

// AdjacencyGraph 
template<typename Vertex, typename Graph>
struct adjacent_vertices :
    mpl::transform<typename detail::produce_out_map<typename Graph::representation, Vertex, typename Graph::data>::type,
              mpl::second<mpl::_1>,
              mpl::back_inserter<mpl::vector<> > >
{};

// VertexListGraph
template<typename Graph>
struct vertices :
    detail::produce_vertex_set<typename Graph::representation, typename Graph::data>
{};
template<typename Graph>
struct num_vertices :
    mpl::size<typename vertices<Graph>::type>
{};

// EdgeListGraph
template<typename Graph>
struct edges :
    detail::produce_edge_set<typename Graph::representation, typename Graph::data>
{};
template<typename Graph>
struct num_edges :
    mpl::size<typename edges<Graph>::type>
{};
// source and target are defined in IncidenceGraph

} // mpl_graph
} // msm
} // boost

#endif // BOOST_MSM_MPL_GRAPH_MPL_GRAPH_HPP_INCLUDED

/* mpl_graph.hpp
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
*/