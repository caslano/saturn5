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