// Copyright 2008-2010 Gordon Woodhull
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_MPL_GRAPH_DEPTH_FIRST_SEARCH_HPP_INCLUDED
#define BOOST_MSM_MPL_GRAPH_DEPTH_FIRST_SEARCH_HPP_INCLUDED

#include <boost/msm/mpl_graph/mpl_graph.hpp>

#include <boost/mpl/has_key.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/has_key.hpp>

#include "search_colors.hpp"

namespace boost {
namespace msm {
namespace mpl_graph {

// dfs takes a visitor which has all the bgl-like metafunctions encapsulated in an 
// "operations" member class, and also a state.  the operations are expected to return a new state
// in addition, the visitor operations are expected to update the colors of vertices
// and need to support a new metafunction get_color<Vertex, State>

struct dfs_default_visitor_operations {
    template<typename Vertex, typename Graph, typename State>
    struct initialize_vertex {
        typedef State type;       
    };
    
    template<typename Vertex, typename Graph, typename State>
    struct discover_vertex {
        typedef State type;       
    };
    
    template<typename Vertex, typename Graph, typename State>
    struct finish_vertex {
        typedef State type;       
    };
        
    template<typename Edge, typename Graph, typename State>
    struct tree_edge {
        typedef State type;
    };
    
    template<typename Edge, typename Graph, typename State>
    struct back_edge {
        typedef State type;
    };
    
    template<typename Edge, typename Graph, typename State>
    struct forward_or_cross_edge {
        typedef State type;
    };  
};

// requires IncidenceGraph
// returns pair<VisitorState, ColorState>
template<typename Graph, typename VisitorOps, typename VisitorState,
         typename Vertex, 
         typename ColorState = create_search_color_map::type >
struct depth_first_search {
    // enter vertex
    typedef typename VisitorOps::template 
        discover_vertex<Vertex, Graph, VisitorState>::type 
            discovered_state;
    typedef typename search_color_map_ops::template 
        set_color<Vertex, search_colors::Gray, ColorState>::type 
            discovered_colors;
            
    // loop over out edges
    typedef typename 
        mpl::fold<typename mpl_graph::out_edges<Vertex, Graph>::type, 
                  mpl::pair<discovered_state, discovered_colors>,
                  mpl::if_<boost::is_same<search_color_map_ops::get_color<mpl_graph::target<mpl::_2, Graph>, mpl::second<mpl::_1> >, 
                                          search_colors::White>,
                           // unseen target: recurse
                           depth_first_search<Graph, 
                                              VisitorOps, typename VisitorOps::template tree_edge<mpl::_2, Graph, mpl::first<mpl::_1> >, 
                                              mpl_graph::target<mpl::_2, Graph>, 
                                              mpl::second<mpl::_1> >,
                           // seen: back or forward edge
                           mpl::pair<mpl::if_<boost::is_same<typename search_color_map_ops::template 
                                                 get_color<mpl_graph::target<mpl::_2, Graph>, mpl::second<mpl::_1 > >, 
                                                 search_colors::Gray>,
                                              typename VisitorOps::template back_edge<mpl::_2, Graph, mpl::first<mpl::_1> >,
                                              typename VisitorOps::template forward_or_cross_edge<mpl::_2, Graph, mpl::first<mpl::_1> > >,  // Black
                                     mpl::second<mpl::_1> > > 
                 >::type after_outedges;
                 
    // leave vertex, and done!
    typedef mpl::pair<typename VisitorOps::template finish_vertex<Vertex, Graph, typename mpl::first<after_outedges>::type >::type,
                      typename search_color_map_ops::template set_color<Vertex, search_colors::Black, typename mpl::second<after_outedges>::type>::type> type;
};

// requires IncidenceGraph, VertexListGraph
template<typename Graph, typename VisitorOps, typename VisitorState,
         typename FirstVertex = typename mpl::front<typename mpl_graph::vertices<Graph>::type>::type,
         typename ColorState = create_search_color_map::type>
struct depth_first_search_all : // visit first then rest
    mpl::fold<typename mpl_graph::vertices<Graph>::type,
              typename depth_first_search<Graph, 
                                          VisitorOps, VisitorState, 
                                          FirstVertex, 
                                          ColorState>::type, 
              mpl::if_<boost::is_same<search_color_map_ops::get_color<mpl::_2, mpl::second<mpl::_1> >,
                                      search_colors::White>, // visit any yet unvisited
                       depth_first_search<Graph,
                                 VisitorOps, mpl::first<mpl::_1>,
                                 mpl::_2,
                                 mpl::second<mpl::_1> >,
                       mpl::_1> >   
{};

} // namespace mpl_graph
} // namespace msm
} // namespace boost


#endif // BOOST_MSM_MPL_GRAPH_DEPTH_FIRST_SEARCH_HPP_INCLUDED

/* depth_first_search.hpp
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
*/