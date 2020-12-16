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
v+V/XKexkqnjCAoh3zL5OU+u9H/TrEc+LPdxzz5kYnTeyYhmJx1wjH/FAbIfDyzZWfIU7Oe6fK6UCdgf4B0NPr7FEjZ5AFeDL/LW3ehiOf+1Qmk04Ze78cuFW4N/CfuUPJS/jM7Ko2LlG+7JtM9d5aPp55QyryvAH0Xv2qoPuXdHmDSsN1xs+9Ydn5s/PjHEFQlE5GkhqSB+K98EvjhsLOmt6sXBNdKVo1UavjCZelWOUz+qneWW3FM+Pdtt75x1mo1X+1uAP937AN/O3tmJ/pBx8VS/Pzo82C0JSjaP9TWL60IMA8+lnfiekpNFisbVfD7lvcZGqyW+GOR/G/kt0jfaP2iH5zr+bBGuMr5hO/VpDl8jKlk9CF6aQeYk/bm52ssk0LI2hFRDL7OeiEAwlX8nL/c68gE9unILrJniePIqi38DvUg1008n51XBHEJBnXUhLQHugxuLkorqUWIYfDn2TuAlF+WK4unJWhMYT9OM+BFPglXxuRUVfoNE7T+kH9O2UgajvQ1FdwVUt6RwfDMyST+KX6L24zS281BWGFjGCdQ6IatwtH2oADK/cUtqKruFm5yNiXbGFG0BMqr/EpC0/TkGl8OxHewdSwQJJRQa0gKiH9Uiw04CP75EH0H6GfEW8oI/OO9+I/PuN86eycINVxbgXfduBYc/ZFRdL7FXada9gbN6FB4hwaXRGvk52nTj8ZPNradf/uArX/3a13d29/bbz7/z4uC7Lw9fHR2ffO+0c/b6zfd/8MMf9c77shpcXg1/8XZ0LSbFv5TNzOLm3e37X9E+lteVI/NY6oVk9HEEOsNq6ngMCTh81wL8UvlzPvd+yWgKWTTgA57xz9E+HCY6wZg4k/x0t9YRhWv/ysWq763F9bjg+bu6KL4RuXEAA0/Sq6mH3arrTe16lPDUD1pqYmzAAQdez3am+tqC89zt+n3zAXiabva7XEaFWQ1va2C9MXbMb7Cynst6rZ5+oWtrofjG30lpO7tPf+t2miq+fIG4pS1oaEj2fdqnqrO3Ma84l6WF+9CFfyXW8SPHTccTOLviuSDsU+jPSmSwVy9xfq16klEmcFdSH3j7zef+VRihHqsn8QZNUWcPHcIJgFCUdiRcqummmy4tibVx1nmxs7nW0C31OQdeeP5zstuu6Ri4l2bvxPB8oIEswtuz0UTC5g7HKd9f1QTZmQ9G9kCB6ChET96fTYrJxTyTEBP6PfdN8fd2YhLZauKVby30U+po+Kc6zO8nbZge57f6sd7mfQbPz1rko7Yg4IGanZUiTkdmljSeoI9i/0hx9zXkk98G5XnVQbPmtzLSxJ0apLWGg5OVtgJn5yQG2IjzS7XhmJcjdA7ecSMYVfURtLR9BU4qllKs+n/C06vRGXyjoUw6PofWmKx3LmiZCjqf39wKn18xQwPaf0S+/5k2fzfRDpP2kBWEM249uIJh3Ylicp5KgerenVLcQE+g2ZndYmCziIngp8Xpnu6Uy4mhSDKponPEJfPJEDHwYv8gTuzDUMJbW3OWmOWVSR3WUZOh+wQv0JDMEzRFkGT1J0RML4Vuj+Un4ozDAt5fnrCEplvP0OPwKzmRk4+IkyE96j6+RFpxj9Govh0UvZREvaas8nQp4gaCbQ9Z7jZaNCg64w+u03ipISqWHZRVx/Ovd60j0FTKOsLz9T5Hj5Nat3nG4NfDbzXDdYWuvc5nwhfGflTE+miOttISEQbEiU9RHSBfNS9zDYbt9Tc4FNvOnF/J896l0d/tXWY79tQZ0qNw52o2WagMIQmCpyTS8/SIXke9blHFXjDF6osH/G0Pr6lgUUr0m2GCt+E0u+11SscWjjtIXio8fS7JaTzkhm/KYLM=
*/