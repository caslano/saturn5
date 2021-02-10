// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_PARALLEL_DIJKSTRA_DETAIL_HPP
#define BOOST_GRAPH_PARALLEL_DIJKSTRA_DETAIL_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/property_map/property_map.hpp>

namespace boost { namespace graph { namespace distributed { namespace detail {

/**********************************************************************
 * Dijkstra queue message data                                        *
 **********************************************************************/
template<typename DistanceMap, typename PredecessorMap>
class dijkstra_msg_value
{
  typedef typename property_traits<DistanceMap>::value_type distance_type;
  typedef typename property_traits<PredecessorMap>::value_type
    predecessor_type;

public:
  typedef std::pair<distance_type, predecessor_type> type;

  static type create(distance_type dist, predecessor_type pred)
  { return std::make_pair(dist, pred); }
};

template<typename DistanceMap>
class dijkstra_msg_value<DistanceMap, dummy_property_map>
{
  typedef typename property_traits<DistanceMap>::key_type vertex_descriptor;
public:
  typedef typename property_traits<DistanceMap>::value_type type;

  static type create(type dist, vertex_descriptor) { return dist; }
};
/**********************************************************************/

} } } } // end namespace boost::graph::distributed::detail

#endif // BOOST_GRAPH_PARALLEL_DIJKSTRA_DETAIL_HPP

/* dijkstra_shortest_paths.hpp
YdG5IEOXUc4lBSZATJhRCH/agNEzAoLLs71CejHsfV0BO/B9XJtBQOw2b2BxhA3fB99Yu7Sw0S/vJyrpI2vIjRgRbQd/rKqDiyOqXgEI9E+rCtL2wFuCGJvJBtaWjuLoOiTYM0suoyoiYTg5lvAUBTJ+3f0Jfvym0SJxXKf278hfUFdC2f1JPjImcWlHAMVlKWgs3ySUtdipggzl4KeFFbJBnDROThRT49IAwmfq6G2wM0+ZwUkLmVAdgdvmyY0PKjJOtls0aUFp0PKmtG1WkLi6WnjwCZaQYo/FjzUgTQkdJqZRHeSAQo8ajmIR+WxFQy0qiJY+1GAM3BAn9B1qdMuFQgU66QahFrdoTZINIh1lS9tyHusJhhzddQaX3WF7jJvBce+iezq4GnOxz5oO0DSOPLTof1ogTBCkaTz3UT+ctSSZoFCQPU1za+aeQg76qoddYRXNHJxWIBheWLx25GDv4LViXBB796iM2yhkZU1MHNJb0JpVz23moV0XcU8lGICv508tEj8zBx6TojUadN50x87L9ml1g9i5ivZknx/WnqyKvVX8KNulAWpw2y1RqNhSVFglK+hjyArQt9eVztn75/zr8eHBwYFmQ2AMwtZif+K4KfBxKNgQoVm8wORsr9pfxGgMjVB+C+5v
*/