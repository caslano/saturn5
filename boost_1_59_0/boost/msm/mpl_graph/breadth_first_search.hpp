// Copyright 2008-2010 Gordon Woodhull
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_MPL_GRAPH_BREADTH_FIRST_SEARCH_HPP_INCLUDED
#define BOOST_MSM_MPL_GRAPH_BREADTH_FIRST_SEARCH_HPP_INCLUDED

#include <boost/msm/mpl_graph/mpl_graph.hpp>

#include <boost/mpl/has_key.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/remove.hpp>

#include "search_colors.hpp"

namespace boost {
namespace msm {
namespace mpl_graph {

// bfs takes a visitor which has all the bgl-like metafunctions encapsulated in an 
// "operations" member class, and also a state.  the operations are expected to return a new state
struct bfs_default_visitor_operations {
    template<typename Vertex, typename Graph, typename State>
    struct initialize_vertex {
        typedef State type;       
    };
    
    template<typename Vertex, typename Graph, typename State>
    struct discover_vertex {
        typedef State type;       
    };
    
    template<typename Vertex, typename Graph, typename State>
    struct examine_vertex {
        typedef State type;       
    };
    
    template<typename Vertex, typename Graph, typename State>
    struct examine_edge {
        typedef State type;       
    };
        
    template<typename Edge, typename Graph, typename State>
    struct tree_edge {
        typedef State type;
    };
    
    template<typename Edge, typename Graph, typename State>
    struct non_tree_edge {
        typedef State type;
    };
    
    template<typename Edge, typename Graph, typename State>
    struct gray_target {
        typedef State type;
    };  
    
    template<typename Edge, typename Graph, typename State>
    struct black_target {
        typedef State type;
    };  
    
    template<typename Vertex, typename Graph, typename State>
    struct finish_vertex {
        typedef State type;       
    };
};

namespace detail {

template<typename Graph, typename VisitorOps, typename VCQState, typename Edge>
struct bfs_run_queue_examine_edge {
    typedef typename VisitorOps::template examine_edge<Edge, Graph, typename mpl::at_c<VCQState, 0>::type>::type visitor_state;
    typedef typename mpl::at_c<VCQState, 1>::type color_state;
    typedef typename mpl::at_c<VCQState, 2>::type vertex_queue;

    typedef typename mpl::if_<typename boost::is_same<typename search_color_map_ops::template get_color<typename mpl_graph::target<Edge, Graph>::type, color_state>::type, search_colors::White>::type,
         // unseen target: tree edge, discover target, paint it gray, and enqueue
         mpl::vector<typename VisitorOps::template discover_vertex<typename mpl_graph::target<Edge, Graph>::type, Graph,
                                                                            typename VisitorOps::template tree_edge<Edge, Graph, visitor_state>::type>::type,
                     typename search_color_map_ops::template set_color<typename mpl_graph::target<Edge, Graph>::type, search_colors::Gray, color_state>::type,
                     typename mpl::push_back<vertex_queue, typename mpl_graph::target<Edge, Graph>::type >::type >,
         // seen
         mpl::vector<typename mpl::if_<typename boost::is_same<typename search_color_map_ops::template get_color<mpl_graph::target<Edge, Graph>, color_state>, 
                                             search_colors::Gray>::type,
                              typename VisitorOps::template gray_target<Edge, Graph, visitor_state>::type,
                              typename VisitorOps::template black_target<Edge, Graph, visitor_state>::type>::type,
                     color_state,
                     vertex_queue> 
         >::type type; 
};

// runs bfs on a queue, passing the new queue forward on recursion
// returns pair<visitor_state, color_state>
template<typename Graph, typename VertexQueue, typename VisitorOps, typename VisitorState, typename ColorMap>
struct bfs_run_queue {
    // enter vertex
    typedef typename mpl::front<VertexQueue>::type Vertex;
    typedef typename mpl::pop_front<VertexQueue>::type Tail;
    typedef typename VisitorOps::template examine_vertex<Vertex, Graph, VisitorState>::type examined_state;
    
    // loop over out edges
    typedef typename mpl::template 
        fold<typename mpl_graph::out_edges<Vertex, Graph>::type, 
             mpl::vector<examined_state, ColorMap, Tail>,
             bfs_run_queue_examine_edge<Graph, VisitorOps, mpl::_1, mpl::_2>
            >::type did_edges;
            
    typedef typename VisitorOps::template 
        finish_vertex<Vertex, Graph, typename mpl::at_c<did_edges, 0>::type>::type 
            finished_vertex; 
    // does map insert always overwrite?  i seem to remember this not working on msvc once
    typedef typename search_color_map_ops::template 
        set_color<Vertex, search_colors::Black, typename mpl::at_c<did_edges, 1>::type>::type 
            colored_vertex;
    typedef typename mpl::at_c<did_edges, 2>::type queued_targets;

    typedef typename 
        mpl::if_<typename mpl::empty<queued_targets>::type,
                 mpl::pair<finished_vertex, colored_vertex>,
                 bfs_run_queue<Graph, queued_targets,
                               VisitorOps, finished_vertex,
                               colored_vertex> >::type::type type;
};

} // namespace detail

template<typename Graph, typename VisitorOps, typename VisitorState, 
         typename Vertex, 
         typename ColorMap = create_search_color_map::type >
struct breadth_first_search {
    typedef typename VisitorOps::template 
        discover_vertex<Vertex, Graph, VisitorState>::type 
            discovered_state;
    typedef typename search_color_map_ops::template 
        set_color<Vertex, search_colors::Gray, ColorMap>::type 
            discovered_colors;
    typedef typename detail::
        bfs_run_queue<Graph, mpl::vector<Vertex>, 
                      VisitorOps, discovered_state, 
                      discovered_colors>::type type;
};

template<typename Graph, typename VisitorOps, typename VisitorState,
         typename FirstVertex = typename mpl::front<typename mpl_graph::vertices<Graph>::type>::type,
         typename ColorMap = create_search_color_map::type>
struct breadth_first_search_all : // visit "first" first, then visit any still white
    mpl::fold<typename mpl_graph::vertices<Graph>::type,
              typename breadth_first_search<Graph, VisitorOps, VisitorState, FirstVertex, ColorMap>::type,
              mpl::if_<boost::is_same<search_color_map_ops::template get_color<mpl::_2, mpl::second<mpl::_1> >,
                                      search_colors::White>,
                       breadth_first_search<Graph, VisitorOps, mpl::first<mpl::_1>,
                                            mpl::_2, mpl::second<mpl::_1> >,
                       mpl::_1> >   
{};

} // namespace mpl_graph
} // namespace msm
} // namespace boost


#endif // BOOST_MSM_MPL_GRAPH_BREADTH_FIRST_SEARCH_HPP_INCLUDED

/* breadth_first_search.hpp
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
*/