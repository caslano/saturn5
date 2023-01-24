// Copyright 2004 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_CIRCLE_LAYOUT_HPP
#define BOOST_GRAPH_CIRCLE_LAYOUT_HPP
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/math/constants/constants.hpp>
#include <utility>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/topology.hpp>
#include <boost/static_assert.hpp>

namespace boost
{
/**
 * \brief Layout the graph with the vertices at the points of a regular
 * n-polygon.
 *
 * The distance from the center of the polygon to each point is
 * determined by the @p radius parameter. The @p position parameter
 * must be an Lvalue Property Map whose value type is a class type
 * containing @c x and @c y members that will be set to the @c x and
 * @c y coordinates.
 */
template < typename VertexListGraph, typename PositionMap, typename Radius >
void circle_graph_layout(
    const VertexListGraph& g, PositionMap position, Radius radius)
{
    BOOST_STATIC_ASSERT(
        property_traits< PositionMap >::value_type::dimensions >= 2);
    const double pi = boost::math::constants::pi< double >();

#ifndef BOOST_NO_STDC_NAMESPACE
    using std::cos;
    using std::sin;
#endif // BOOST_NO_STDC_NAMESPACE

    typedef typename graph_traits< VertexListGraph >::vertices_size_type
        vertices_size_type;

    vertices_size_type n = num_vertices(g);

    vertices_size_type i = 0;
    double two_pi_over_n = 2. * pi / n;
    BGL_FORALL_VERTICES_T(v, g, VertexListGraph)
    {
        position[v][0] = radius * cos(i * two_pi_over_n);
        position[v][1] = radius * sin(i * two_pi_over_n);
        ++i;
    }
}
} // end namespace boost

#endif // BOOST_GRAPH_CIRCLE_LAYOUT_HPP

/* circle_layout.hpp
dRDDHziroBP0qgCzGUCvo/pV7EdzaUNapoRK14hX6qwqXtBPSGIkOSX+S9AFOq9P6ZjjRUAfytDLUGsG5wkgijArDHIDK8lmDI+m1qjViiBFUF3znjd56nexFyaNzF/j5BsZSEnKO87JFX9gqZc/5/VTvH6K10/x+ik/l58SENBI/ipBgEFntaoxBVlUGjXHBZmEuVGvtih1GpVaQQh5Jc6laovBrCfcujDtKNVCBRo2EeE85ciDOD2KAnAuonkoINCdMvVKgh2cVOHDcbQebCqW09EmEpVVPf9/Kx7Pm7zJm7zp3zHNHBXyMRIQZpZwu9MGdYOp/b9kcb7oufe4bz6Fsb0+hlE92sKI7u/Dd13awNDO/2JxCAd9/o4jPiXFpdQP/3pIfWUTVuaUcQdk70mGk2lbIDMlEY7vSIBj2+Lg8NZYOJQUAwcS10LGptWwP2ElGONWwN4Ny2DP+iWwe91CSF29gMVX2L58dr11yDCsheJH9+H2lQuQaz4JV08dg8snD8OFzAw4d3QfnDm0B8z7U8Ek6nciNQmO79oMR7fHo24bnLolrALjxmWwY8XcesUwPZC0DqzFhWApeAhFD+6xWCAPb9+Aezeuwt2rF+H2pTNw89wpuIa6Xck+BpdOHILzR/czvXL2p4Apfbtgs52bmW1SVs1nbZFuWB8QO3+6cc64frYfhqlt+qE9jbpB3QKqyj+4JQZKrRaw
*/