// Copyright 2008-2010 Gordon Woodhull
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_MPL_GRAPH_ADJACENCY_LIST_GRAPH_HPP_INCLUDED
#define BOOST_MSM_MPL_GRAPH_ADJACENCY_LIST_GRAPH_HPP_INCLUDED

// graph implementation based on an adjacency list
// sequence< pair< source_vertex, sequence< pair<edge, target_vertex> > > >

// adjacency_list_graph labels such a sequence as manipulable by the metafunctions
// in the corresponding implementation header detail/adjacency_list_graph.ipp
// to produce the metadata structures needed by mpl_graph.hpp 

// the public interface
#include <boost/msm/mpl_graph/mpl_graph.hpp>

// the implementation
#include <boost/msm/mpl_graph/detail/adjacency_list_graph.ipp>

namespace boost {
namespace msm {
namespace mpl_graph {
   
template<typename AdjacencyList>
struct adjacency_list_graph {
    typedef detail::adjacency_list_tag representation;
    typedef AdjacencyList data;
};

}
}
}

#endif // BOOST_MSM_MPL_GRAPH_ADJACENCY_LIST_GRAPH_HPP_INCLUDED

/* adjacency_list_graph.hpp
VXW7fAINsxOtjPUfibYFghJrJUT8ErUTKzJNXgFH13ymRyy9W9oajlyOTVOfKiSGQn6bfwkJQsoghSOgqYqPjojPhlP+KBxs2RiopJEKTMDtojvlTfVt0n7pf0grgXBQRfRJqmr6J/xQkd3mxUpdeX4WNlML6/nTvDjsfYfAG1lUQbZdfeX38HVROSTMmtJs+lcIiw5mXZEf8IQ8pQ2v2C107p+QuC3Q5VjuMoiuXdU1MfLkqYZcV/sAGcnXoJAUqbP8vmnknwcsxGNP2mUcwn/zbHgXOOqV/KMTXsW+N+Odxz4FNE9YftzdsK97bqN40uQGlZiHFL+kJI6vmzUdvG1VL3ZZlZByZ/JjTAU+FVK208FLbSh2HoXQpcrwpQLBtFSpvuWfxN+uYtP2WhixCp3+M35m1SjEXou/E5ZleEh7+wzhuNYFn9vfOnJrRgNmdiAwlRBwkRAi3t9FP3tCU8LsG2+4qFIF9/L6ZHOfAKs1wWy/rgnpz+R2H1J4etabUsNMn+FDb8OBNLm3TWW8HxpsFBqCtkmOEpmrjmZpXwRS1LwgGcnPZj7Y0dnVDu6Y+cOXIWeNZntzarEmqne6j+Fu2u69yWZk4sVmCEq5YjMypXzBv4uqCDDcxcdkW4Q+v52GntJAm+wFRncGRZzU4dKKq/i+1Icz1W86t3JfRm8xkPkm1jcMBzzrF6pVNDcsY0TVXYiSMLs+bu8q
*/