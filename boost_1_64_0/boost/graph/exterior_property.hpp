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
+cn7KfeEaxhp9g+D1QN2u5D5AuUeOQG+CLwtdA9GBXz4Hox2+J3IiV69BQ8gJ8EPgouidrlIHTL3eFjlIhu+HBmBrwK3iQyOL9rBVyH38+7dAvcip3r7E8CMO0w7NQyf+qLdTkUEB+vr9FB9zUE/gzPqReAu9DPh6+DZD2fGfR3w8faxDV9hj6O7X3xv+xszXo69vzEXPl755PydGUfU4b5NZDA828HXIpNI/y5wLzLZa1fAI8jxuFev7F19GrU/9JX/zP5N2oVR5yajYOYjTTzUq3Y6jffS+1U7PxP/Q+3F+z3vmh6nPZwYbg9Ptdu3ilftcpxGvxaFb0ea8Qg46czQeAS+dRXtDuHphu9DTiI8/eCB0D1rQ6/a/eOUOPtrI6F8S/qzfd4gIjhYD6eF6mFSaaj+m3vN7HFKFv5UIGfAV4EzCNdML33gVejenJ3w2Flmf1s3PP2ROUfdD19Eeu5vzg/Y9+gdYO7Rs89pHxg6p/3sn227aRismu17cCLDGpt1q1leOsBnhPbbVsHftcq2v9rg+8mfQ7x0gK9bbe97awvd03cY7UUP7geRh3vh11hkub3vLfU1+j/kkfBFgoPjlqOsc7nxx6Hbec7cb/jaf65+1zrp+lbs858l8NZ5t72wH7zxQ0rsc2emvra9ZdezCaae2fUyLdQPdvBculfvwb3IifADb9nlOhLnPN3UOOdRp8GP4E/S5+35jIy37fycHucc6ZQ450gnxzlHOsmcI31/+6zVXo4H93ZftTd+2cfYA3Z7PSM07iD/Tbr2v22PH6d5+QA/fY89TswAz0amwGeDc5HmXCO4AWnKF3hb1C4X2/fY7eOk0HhTPWD3v53ee9GPD41nH91jl8fBPfb4dHLs8akpFyO4Z3xKORX5j3jjwfd332HXP2x9L3gcE9YD4ATwMDgRnPpP8oMJ7ExwEhPc2eBkcC54PLgEnM4Num3gieBO8CRwH3gyeAgcER91eN6hnIGzwJGIi3M9PbgCPA33bR5G3wGe4q1rgdPipGc3erNPB5wA7gebdSpwEngYnGt8TNY4DxQBLwFngWfGq+9a778wFzwOXAROAJeAE8EV4Hf+yXoIWMUpVG2iD6q2g9O89ANP99ILPAPcF4rPIPhg8Ag4CxwZ5+JjwFngY8FF4NngKvAcL7zgueAO8DyvfoCzwT3g+V54wQvAA+DjwENgcydjgouXAjPAy8DZ4BJwLvij4BJwNbgO3AhuBzd56Q2OeuEHnwMeBDebDSgublGx/zK03v/LApt9RWCzDwhs1gXBSV76g9O98gKe6IUfPMkLP3gyuB88xUtvcASskuzyFkmyy1tWkl3ecsH7xol/hdb7f3Vgs+8QbPb5gM2+jiQ7/j1gc384eLxXnsApXvzAqeAR8ARwarJd3zKS7fSdnWynb3aynb5FyXb6ViTb6VsHPszLP/C4d6g/4Gle/U6207sX3Hoc+Zdsp/9QcjD/RI5/9/zIQm/21YLNPrLxtn914Ewv/OBcRfjB7V5+gdU48sfDCeQPON767XRkR8R19/LpKe77prq4d3GClq/AF4X4V+HLQ/wI/Jnw3Scn/Fvjv6HQ+bU67S/n1Cif0QDfjhyP++3gW5G/TufeIfCbyBTcq2m0q8gEwpMDLkKa84tgxmfmnvwqeM77mPudtsP3IKd49wWBFe7zvHUI4YPj1w8zfs3ah/Jxo33vZYXwwfW0k+kz2uG74AsITyf8CHxhnPW0xaH1tB6e+w3p2Q8eQj4Gr6bTLyIfTyd/we3IJfjfAe5HHgk/CE66wr7nNnWGy2cgMzUvEpyDnEUccsHtyKO894JvRmbB94D7kTPgB8Ctj4fuAZ5JeJD7e+E=
*/