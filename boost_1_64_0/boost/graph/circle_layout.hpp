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
a1i+rHLIOPeo/xEf1kfxfCmqqFC9cD7nZ5+0STIMvwPtPM43SzUQEzE9hv9d64JkO1+4NOXeTmTu5GXeTmIBsNXmenoBW08VZNDkWGQ3N2lxTSgLFhgB+d0ovUFcngVzns6GWgnyyPg7XSJryBFbn23YgUgHfOGEWzDu//NKaup6VuMPrHRO4XJBqisiBhJKQK8lulmhH3OmwMkvF3Qt81N0MNGY8SQVQf7970Qa0eFfHBKIyZDPJSSCvTjKbOlcqVG6tMTzQZcXFubkb7uMkmwyMW2dpFLqdWBeog0LWDMTLXK1pXE0Jk2yTTstnlmCKS4qpSAQt4OwkynvedUyeeeMCGi/LpG56VnRUoZd4hm0S2o9xT/8hiqkeEXlNFBlyzUG46IpQ8V09eR9yfBzFX7JkKwiB/h20UItCv1+Ble7GyuJeonXjSwZBo0l32d/MFq9BVlGoFtWTcFso3jHjv9eS7N2SKg9Nf1DIIE0FO6CV9lnpdBCyYbXNE07xJzvr7gnvqRdGrAXjlG7369W3rqMe+69UjGUJG6pZ24xySev1nkW0B4EuqwkyQ==
*/