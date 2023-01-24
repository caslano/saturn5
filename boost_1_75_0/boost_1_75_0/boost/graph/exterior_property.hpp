// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_EXTERIOR_PROPERTY_HPP
#define BOOST_GRAPH_EXTERIOR_PROPERTY_HPP

#include <vector>
#include <boost/graph/property_maps/container_property_map.hpp>
#include <boost/graph/property_maps/matrix_property_map.hpp>

namespace boost
{
namespace detail
{
    // The vector matrix provides a little abstraction over vector
    // types that makes matrices easier to work with.
    template < typename Value > struct vector_matrix
    {
        typedef std::vector< Value > container_type;
        typedef std::vector< container_type > matrix_type;

        typedef container_type value_type;
        typedef container_type& reference;
        typedef const container_type const_reference;
        typedef container_type* pointer;
        typedef typename matrix_type::size_type size_type;

        // Instantiate the matrix over n elements (creates an n by n matrix).
        // The graph has to be passed in order to ensure the index maps
        // are constructed correctly when returning indexible elements.
        inline vector_matrix(size_type n) : m_matrix(n, container_type(n)) {}

        inline reference operator[](size_type n) { return m_matrix[n]; }

        inline const_reference operator[](size_type n) const
        {
            return m_matrix[n];
        }

        matrix_type m_matrix;
    };
} /* namespace detail */

/**
 * The exterior_property metafunction defines an appropriate set of types for
 * creating an exterior property. An exterior property is comprised of a both
 * a container and a property map that acts as its abstraction. An extension
 * of this metafunction will select an appropriate "matrix" property that
 * records values for pairs of vertices.
 *
 * @todo This does not currently support the ability to define exterior
 * properties for graph types that do not model the IndexGraph concepts. A
 * solution should not be especially difficult, but will require an extension
 * of type traits to affect the type selection.
 */
template < typename Graph, typename Key, typename Value >
struct exterior_property
{
    typedef Key key_type;
    typedef Value value_type;

    typedef std::vector< Value > container_type;
    typedef container_property_map< Graph, Key, container_type > map_type;

    typedef detail::vector_matrix< Value > matrix_type;
    typedef matrix_property_map< Graph, Key, matrix_type > matrix_map_type;

private:
    exterior_property() {}
    exterior_property(const exterior_property&) {}
};

/**
 * Define a the container and property map types requried to create an exterior
 * vertex property for the given value type. The Graph parameter is required to
 * model the VertexIndexGraph concept.
 */
template < typename Graph, typename Value > struct exterior_vertex_property
{
    typedef exterior_property< Graph,
        typename graph_traits< Graph >::vertex_descriptor, Value >
        property_type;
    typedef typename property_type::key_type key_type;
    typedef typename property_type::value_type value_type;
    typedef typename property_type::container_type container_type;
    typedef typename property_type::map_type map_type;
    typedef typename property_type::matrix_type matrix_type;
    typedef typename property_type::matrix_map_type matrix_map_type;
};

/**
 * Define a the container and property map types requried to create an exterior
 * edge property for the given value type. The Graph parameter is required to
 * model the EdgeIndexGraph concept.
 */
template < typename Graph, typename Value > struct exterior_edge_property
{
    typedef exterior_property< Graph,
        typename graph_traits< Graph >::edge_descriptor, Value >
        property_type;
    typedef typename property_type::key_type key_type;
    typedef typename property_type::value_type value_type;
    typedef typename property_type::container_type container_type;
    typedef typename property_type::map_type map_type;
    typedef typename property_type::matrix_type matrix_type;
    typedef typename property_type::matrix_map_type matrix_map_type;
};

} /* namespace boost */

#endif

/* exterior_property.hpp
TnEBmwG9SSQC0mlCTIZicItEuV04N/KKC+XfcejyFc6oCue2M8P8s+oFXFgBi2FLoe+0f7tOrnjY3po44TkP2SgjJt5vYsD9sWJtXXJnZ9E0sx/+XZHG6ZnyXfwgU/nnKaBj2Cid72njkI82jZkj4rwC5SgZmDBck2Ey5C7KHt4gMlOmEfk7xOvRRSjNaFyHsjxQDStyurSRW3/kc0T8DD+/h+QZgSkRCY82YtkwezZAZ3n9E+Vd98z01ypLnZ4NpFNIeOvK5fq8zJ3t8fhEPZU6h2PCX5ha9dVD+woHZiuKqxkWmBcYuqo+Hw1u+l1f7B+mqiSTvjTgnob/IUQEp/vEhCjohTb2XH3atEbV89C/PNbWRc3CEnXhORifYCgtqd0bAVRcOAm2KfVu+j4G2cqN+qVTS9NgE6zpckXwMGKNgyWZXh6e1jNG3oGvOdUJ23jRU2/GR6CAlpCwlaHkEBnqarDeuThpESB6UGtiiIfnj4hTnjP3sAfLHVOXl4yxMM/YZfv+NsKe3WMDqL5hokXow2otmNX64spAR6bRxRlN3SEvhxQwtQ3E+WkkNOSy2jWhdVlZua6TY/5wWJX1YOoiYbC66b/ZMYNhWmxA57BnKnw+nt4qNGYpknSXJCfh7ByZ8wpnAFfkzBnCIJ/AskU7cytw/3KxzNjj0+1YxmPQxn9irm9RFDL5slvwsqw4DBnPFxOyB4LJtthq
*/