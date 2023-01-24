// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_MATRIX_PROPERTY_MAP_HPP
#define BOOST_GRAPH_MATRIX_PROPERTY_MAP_HPP

#include <boost/graph/property_maps/container_property_map.hpp>

namespace boost
{
// This property map is built specifically for property maps over
// matrices. Like the basic property map over a container, this builds
// the property abstraction over a matrix (usually a vector of vectors)
// and returns property maps over the nested containers.
template < typename Graph, typename Key, typename Matrix >
struct matrix_property_map
: boost::put_get_helper<
      container_property_map< Graph, Key, typename Matrix::value_type >,
      matrix_property_map< Graph, Key, Matrix > >
{
    // abstract the indexing keys
    typedef typename detail::choose_indexer< Graph, Key >::indexer_type
        indexer_type;

    // aliases for the nested container and its corresponding map
    typedef typename Matrix::value_type container_type;
    typedef container_property_map< Graph, Key, container_type > map_type;

    typedef Key key_type;

    // This property map doesn't really provide access to nested containers,
    // but returns property maps over them. Since property maps are all
    // copy-constructible (or should be anyways), we never return references.
    // As such, this property is only readable, but not writable. Curiously,
    // the inner property map is actually an lvalue pmap.
    typedef map_type value_type;
    typedef map_type reference;
    typedef readable_property_map_tag category;

    matrix_property_map() : m_matrix(0), m_graph(0) {}

    matrix_property_map(Matrix& m, const Graph& g)
    : m_matrix(&m), m_graph(const_cast< Graph* >(&g))
    {
    }

    matrix_property_map(const matrix_property_map& x)
    : m_matrix(x.m_matrix), m_graph(x.m_graph)
    {
    }

    inline reference operator[](key_type k) const
    {
        typedef typename indexer_type::value_type Index;
        Index x = indexer_type::index(k, *m_graph);
        return map_type((*m_matrix)[x], *m_graph);
    }

private:
    mutable Matrix* m_matrix;
    mutable Graph* m_graph;
};
}

#endif

/* matrix_property_map.hpp
WlPE7tDxt/CD7+mfzTLKenPTZs5qa86P/X34zf9csdWQxK/lGBAmmUql8IF8nJlBcTfYbFZ4u8oy9oaB/3fM4fnLAWcgR1nhyZ3509rXZVumWbAEq73wxh0jo42WlM7TxMtgrb4uo1Koe4JCk8lcA50IDR4Npg9LWuR3uM6q4oMxBO8UTtWEORF2M/dVgUGQKCOGpkEhSZ1Vpew+qOaCuJhT3BTB58bLvGIJ/L1aW0gyv4MT+3ncjxrCxGVYjKMGbfUq5vHM7eZYYJjVVg94kUVpsz7T0srgfvTjvMLtxngwomLnObUsypGCa56gzMPwpEnBnZ6XcSVvLlA0tdZDt4nHZz9zJ93xu3ZE42JeGtvQfMKDoRMg3bH4j7ZkWZse/saWpAhWgQsmuEIllHJhu0Z4x9ZYhXJZmwoz2zwTKvRJ5Kwp/+3Q+FY+Ys0J4K8uaxA8SxnhQNjkuEF9Fisclv5Isr7QXS/U0dhdVMBMuUYejZNhGAyJzkhrq/z626NyzlY1VJ7lHNaS+WX/sizhewF/rEXmGzIxq69M2nGJk+z8dm1DUWb2AzVCKipupFVFZA1kDX+YS8AGBy7qt53sdZcb+QHLdULtXpGAvmBA2CyVnoa+J1/n6Pd1R0UA0NX5zIy5PL5zRcy/TzH/DaPdUv8TNvNE/gkJa2W3pa2NhIOYS2QrfZp6ZracstAgIVN4a4H9g+gabeNXLjyB
*/