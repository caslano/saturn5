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
Vl0QWW1OE26+oNoTr2qhokJUCA2Hp4X0FH0iHOUCOXQgC+vAGRZuSW1bSJgwqYxe5dhwc4uU8YfXO3N0YthLJylpnVb3m5aHA95ylXppNlOy3lgWhv4jmGTfq7rlHys3RydTJkbEKfoRDGxdWmpqYV6TvrHhU/pO8E+k2Zas2mhZpR9fGVtxQTXztDUxSovcb84C82VmP1mZu8nkbzw5BrIM2U7DnRh2BeJoA4f2NA+9F3yMYIJJnZkHzsrumHfqIRz9VaxBKvdQPX+RcG0XHp+cpvPsomGBpkSO3UU0XIdKivKh4tDW0xyNi1+vXfL5d7AkUoNntKTu8f3QuwWSBrFg/qeVfLplRvAggK5YGSPrgFGK60D2JSyVuV8iwwLSWa9AKScgVutOyDolnFnxREbXQCHKTwEU8/hAvCfKat1bC/QiDsRVA2Yd9Ll0k2fXXbkPnnP5JtkEabXIZ10ZwwYgp/Aue2rrvdHJ/Zihp1P5om+lxppPgf5THtK5Z760IlS3LLXrAJr4a8J9Fzdzr1IlyXJkHDioUu+ebQZh/wCknJoYTlWC7nX9zA==
*/