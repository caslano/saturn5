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
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
*/