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
CB+Gf4UH4bvwI/gBtAJc7zANfgyz4CewOjwCG8NPYSv4GewFP4eD4BdwFPwGjoN/g7PhcTgHfgcXw+/hjfAE3AB/gDvhj/AZ+AvcB0/Bt6ByUm7QgioFL4yDLpgI42Bl6IUNYCJsCX1wIEyCE2EZWASPBssPfgWvggHkS2EKvAWmwtthGtwK0+HDMAM+CSvA52BF+DKsBPfDTPgXWA6+C3Pg97AqVKn0/zAV1oRt4RmwN6wN+8M6cCSsDwthQzgdngkvg43hUrgb3gJfgJthsH2+DBvhf03rHYZN4GewKfwRngVdafTzMAe2hHVga9getoNdYFvYTft7w/ZwBOwAR2v/ZPgYLIQdYTHsCufDc+AS2B3eAHvCW2AveB88Fz4L+8OX4QD4iU7HDzpelU7/CV3wfNgD5sI+cATsD0fCoXAUnAVHwyvgGHgfnAzfhIXwPRgsJzcfSYvwJ8IpsCUshu3gTNgdzoL94Ww4DF4MZ8NL4Dx4GVwM58Dl8HK4Fi6AG+FCuBUugo/Bq+EOuAT+FV4LP4DXw8/hUvgdXAZPwRtheln6L5gFV8B6MJj+HvDWYDnA22ARvB1Oh2vhTO2/BN4B52r/Iu2/Fq6Ht2n/Wu2/B94JH4B3w/fhBvgZ3Ai/g5vgj9rPd1WpJze8F3rhVlgd3g/rwwdhY/gwbAUfgX10uAK4HV4Id8AF8DZ4NdwJl2j/9dq/QvvX6fBb4VPwcfg0/Ay+DI/BV+CPcB+sUI5xLawOX4Od4JtwCDwAR8Jguc6E7wTLDR6EN8C/wpXwXbgKfgDXww/hNngY7oQfwSfhp/AI/AyehJ/DuCzGN9AHj8Iq8BisD5tz3uba3wZ+DQfDv8HR+niB9hfD4/Bq+C28Sx9/AH4fPD88AXfDH+Er8Cf4N3gS8tlM9L0w6E+Dp2BLqJAPhPFwOEyAY6AXzoSJcAlMgstgK3g39MMtMAU+BlPhU/o8r0AHfBs64SHogl/ClvA7HU9CBfpXmAwzYB1YFnaAFWBX2Bz2h+VgLmwFZ8GK8DJYCc6FleE6rb8FZsMdsAp8FubAz2FV+D2sBn0VeS8AM2ENWA/Wgj1hbTgA1oEjYV14EawHL4P14Y2wMbwVNoGrYVN4D2wI34KtYM9K9F/6/c91Ss/hgY/p90rJ8l029HcSvXLQctNuoQPWhj7YEjphX+iCQ6AbjtD+Udo/SetdBBPhQh1+GYyD98B4+DD0QJ0uPT+Fe8tp0jWfdJWFi2BTeDVsCxfDDtrfWfv7wmvgELgEjtP+idpfBK+Fl8Hr4FIdbo2O/wm4TJfXbqXnRcCfdboy4HadrmfQqwKfh7XhblgPvqDT+SJsA1/S6XpZp+sVeDHcCy+Hr8KFcD9cAl+Ht8ID8A74JrxT++/T8T0BD8Kn4HvwVXgI/gW+D9+HH8AP4Yc6PzPNd3HKVufHByfp/BxBryL8HFaHX+h8HYUN4FewGTwGW8MTsAf8AfaCP8Jh8G8wFx6HxVr+Dcw233Hlu7CcP1h+aVDeu6Lnh6thOlwDM7W/vPY3hGthS3g77ArvgHlwHcyH6+El8E5dz3fper4b3gY36HLdBJ+Dm3W53afLawv8Cm6F8aTtfpgFH4DZ8EHYFD4E28OHYU/4CBwCt8Fc+CicDB+Hs+B2uBg+AZfDnXANXAMfgk/qcpqjwt/ZOKbrKQlSlvI3Er0UmK+vizEwCxbAbDgWNoHjYBst7wYnwBFwIpyu/XPhJHgdnAxXav3X3Ur2Gmo31fmr+wodx91ER/4gbh/uGM5vuVQtXDvcUNxM3DLcJtxu3GFcsJOugGuCOwc3DncVbg1uG24f7ghOOdHDNccNwE3CzcOtwm3BvYQ7gnO5kJM=
*/