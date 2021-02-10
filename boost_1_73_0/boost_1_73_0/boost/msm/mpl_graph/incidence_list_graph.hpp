// Copyright 2008-2010 Gordon Woodhull
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_MPL_GRAPH_INCIDENCE_LIST_GRAPH_HPP_INCLUDED
#define BOOST_MSM_MPL_GRAPH_INCIDENCE_LIST_GRAPH_HPP_INCLUDED

// graph implementation based on a an mpl sequence of sequences <Edge,Source,Target> 

// incidence_list_graph labels such a sequence as manipulable by the metafunctions
// in the corresponding implementation header detail/incidence_list_graph.ipp
// to produce the metadata structures needed by mpl_graph.hpp 

// the public interface
#include <boost/msm/mpl_graph/mpl_graph.hpp>

// the implementation
#include <boost/msm/mpl_graph/detail/incidence_list_graph.ipp>

namespace boost {
namespace msm {
namespace mpl_graph {
   
template<typename EdgeSequence>
struct incidence_list_graph {
    typedef detail::incidence_list_tag representation;
    typedef EdgeSequence data;
};

}
}
}

#endif // BOOST_MSM_MPL_GRAPH_INCIDENCE_LIST_GRAPH_HPP_INCLUDED

/* incidence_list_graph.hpp
qgS1OwiQ5aFWEDCburzuSvEYhVsbpFskkWYn20R/6VL+GCakQ70J2GT4NJhMLlE/LRfnJN7rFaFh+DgffQgW5BWC5wblCuVLwHI0Crzb8efetN+fCP27mNilOmw+DWdXo8UoBA+hFSUIzSliZEFASQkqk0JhE5IY2kq232HtA6zd6XRAE2rtYq/X7PxskYhjb+BapFgZCPjq0GihoHAStolb1WaAXed5ZhwB/ArBZZamNPtqbH3fP7uZLcLxvH9WYOaz+9D/cfEdPK8wyTMydzDQm/2bjoRB/Wv/Z/+2/3tuyQe/ZqLtwZPSrQc0SbyDwkgQMWkDt0Io3iGshCWjUUPTrjLXZHxT1pZzzVwmMxWw0c1kBqShUb7MD91fted9leL5QpKC+pINdrcch41yQO8k3K+Z/eMP+AdQSwMECgAAAAgALWdKUm3BN+WoAQAAtAIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q5NjhVVAUAAbZIJGBVUu1q2zAU/S/IO9y5lCZQz2yF4maqIbgpDbiJVzuF/iqafF2L2rKRlIS8z95kLzb5o077y/K555z7SQ1qw5nGgFAh89p+3vF4qFWmA5I8pjF5frp/Iau7NaHeKUK9nkzOyBkkqPaoXC0yJFRh
*/