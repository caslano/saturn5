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
9NPT0Wpv0EupeuN1tC/ph1vC6R+WkqaysFvbGtBji45XMCV0Pw3eyKaIVtWK68J8dr4gNxPOfgjyH1xBcIYEfHkgHdcgCyvGdfs50OUaHyzwf6wPlyBphxZNb9VZW2X196YLHIvwLXx61TENU8veme7l+yHJJ5jsEmmUaZmtirz1pD5P/ORyX+crZa4FHqhYkNmyMV7kgcQobnnb9BC3YQUoavCSlI49liZ9h1Q9NsNY05wt/hfy0sZQxQGbHkhH4jhbM3JfKzV4xQdAVXwhTcF6JnVlShbH4Tn1PAx8oEYHJTPH+fidTi9/cfNo7nwzlQGmRCw8unmba8Uv+haizOP5RM1UkX32jG65bHAbMru+QXTsJ52zcqJ6CXsFbOQc9Hx+nvkqvI2shSuWTTFhoiuEKguHxajV1jZbaQ5qugvAc+oROpo3ekdRY1IzRCqmSo1km1B6+pK3GPMn0r+hdczDQjNbvFJ894V/cSRr2raNMTo0g9XmDsJbu9tQkjqGQBJix6sKshyBO2w0PGfjaDZHA8pzoglg98QQ1aHmQ7OAaBm4RxPIQ3MmtA==
*/