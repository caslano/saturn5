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
C5zJ8N1y8ihlpnsYHa4ZDb4bC+z7znIA5ybQ/w85wPdtnHInEPfu02Iula9X6rYu231vc7fSR80ohvcjeL2QFvINiX3nstr3OLkH8DrnO5uYNZtbm3rff0TDpgHcsMewmEVATsLS2f62ZdO/ARQtcKJyDGfwVYHIJ9myfpcIXS+EK9img8P65nAOyRAiFM7RcDPjjr9s+JhKQsQZhM35YHt1Y6tvsMn87jD4UjjaQCzZzKn3Mdeo4nBfdXcxW0fm3Yl75+UGHBn5v1XTfQ6s3+GSz01lLURyKxV+QVu/Ith44S4UUunJ12Am8PtX9PMilOzcIs69u7sGVPlHK2p5/QJpMU8HBZXXsI9b0cpbZHCRx44GgVFesnc7r+KPwXeLl2LBdeJCLhvOywW2v6KfxREHMm5Bz+O/Gbw9c2canWuqspw9ptoWBmnYgeCKx6M+K8BhtS7dvrlLXZdShE8OWxlsVznQJdtLLcYl7qOF70co8THD18oTj+v7DqzXY5iwF6wllkTcCMbkp8KjhxSEHhdne7EG1C0B/C57r4dgby0xxmSjk5G88x4qx6k52CXwySx2GtLDqhScKfjlkD3nWKHaBDbbEUuBwAh7+r9iJ5fV2DkrwJb0gqk087v4mYewu7i3fALnjvgMhZcqdacj0OoSrtI7C7ryLNV4jHJWfKDVbrqd2XYdxpCr3VmHoRhaHFPsBsZue/H6J3Hv3LMzrutllOdvF2pxrPCEgRpaDYYXnuzoCGPfwugOdjPD9MdMKa9uHD6G4kswHAPZVp0PEJgbJWa02u2PaK+N9tK3mbp33yW+C5MoSmP/vcT34US+p4pvwrJCxn+4t/q9y3zYbAyUPD64T9C3pkP1Pvmp+7Dv/FEBVGH/Lukr92X0ne+b1y26Lef378cw//0t8ys1GJESyS1P7CeMMQRJEEp9eXUHrPnue+D+tTjxHClxH6nHUWUpPskDGK7Ooau8O5x7bnXeucAGGOl5rjyPzkEzGXtDnGmIRrI+ol2NBa1893jlFh9bYs/OBY1Hv9iqvi8WpFPKCGTD8qlUloHZGnIrUZneiaMVvbeB70tVGY4/k75X6iwzKvsLBY292PMOmFX5NWKFJhxmqPZCC9MFhY79g4UMUNrlOqXdH2zMewxFZfVfQGlD/jCj7xuekmdf5nUbfcfyMluHrgQDSPpJKkuptzAaw52cWtbbUReF3ltdRTITSZ8LfqJvzcdra5L+OZ2OvFkzSvodZv58VaVz9KGZSi9VQmC/DotWpb1WCIPkcb5D/YdV+v+ithSCyS7UFCeNcdVuP/OIztQrhtX3I0+hvsdmL79fP07fZ0PkQ/rMr94lvrOwHcyDitQZPHtavwci2DTcchV3+x4o7ktirtFUo+98rsmpJnSaxTxTpxnxiHlG04y+8zlWTTHCizlGU6y029p6SDXHjCkm+C6BzudYNcUaVDY+x9QpRjQxx9QpRjQxx7QpRjZkfH5Z04t4+fxSpxfVT8wvml70nc8vml6UF59f1vSivPj80qYX8fK5ZU0tovO5ZU0tSpvPLW1qES+fV9a0Irkzn1d104rSF/OKppVabzGvzGlF7SXmlZhW8ruYV2Jaye9iXolpJcqAcSPmFU0riqO9DdrfSh1ZDFwx2pjNzGV8n+Tse6VSy0b2jPb+37L9UdVzZWRWLzozMrrutFqzRSG66dRaYj6428aIIsrz6x4DQ9qysizrJgZiQKLzd1adfnGgnW2v1dCFWi+lMbmJMNKReEPKZD9ys07vUrNKhQs1vYV7SDzLT5SZzmx3lnTwGrp3/b303da9U/Xo7gkc9Xl5ZqY05oxWG/WSK4eRvuHOOCGnFenda0fcZDw=
*/