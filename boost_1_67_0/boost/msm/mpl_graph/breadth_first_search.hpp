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