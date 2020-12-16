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
xC0g98KVFlYUO+eRPmSYw5CeTMc8WLikZKE9D5YO7JjNO9Mw4ukIOz3DsxRXq6E2WPOuDVuzz5U1e8gapg/pBm2nG/YMqwP5NA7m2VHJsxMiG9pkR+k/C9092y07+me75+enCn3SI0v2Sp4fkvb4U5i/gCdM/lqKEREmXlmi+utG8u4yJuD/h2z9VcJorXN873B+T7AB8wKci4shS84VWbJ9cJS5exSoV96ZgXhbOdIeWSLJnzTuvGnj8kdPvjDP2qd9c/39Q+IvU929e4Pojth4Fgr5VoD4j3KMZwQz0oIJkMW6h9k4zXclAW/27MsBadv1d39rwZBoANnS18CS86V5Pt8a+a/et9r6nfhL59h3J76jG8J/L/It8akYP8p3NHDspGn26KLNhtYvnxbpscpn3qKwzDc0l/UEb5nYbkX1ykPy23+/muQ3/EfSSTpN6SLXHuA7Jc1BCSAF5ptop1u9acaW0sJypFn3eWmahTd42rkgpsu+T8xV3m8PizKOEw8XSN3e6UxHNUaYheWO2u1bt8Vf69h1W90HcM5+61CU6TDISPAFGxs4hdeNq7XB9EZBzOk4+q4itEk7jgMMI83hXlhoOPrcXXQfrPP2x0nH/dvazO5zogF0lTbTVtqM0donD9lqfNuM+EvnvOu7yJ9ahP978KWkpnRCBiUl4L+EIOqEfn+F+k2n39A/1a5Ubx4p93jIfoimQARt9I1+F/fVYown+qtzL4R+i/B2t/eNkv7M9N//YPnpYt9fRvpTM6RxcGSJce+8qrKwveY5nXzHTK55atyd7LVK+rN104fpniA0dii0idB7nfORetfnFPJ+ZUb0mj0oj+0jZH9C7U+v6AO7I8MxzzZC9iVcgSOlLbAHoU3kTESgt2uDQlxQ+6k54F3nvw9B5xCPMu7bIDvaetNKufox4t44Qvf4bAlmJtXbk50hfPeB794IX6j2Q+fegpB816saTn4kmFjhkC94Lu70Zp80VfeUoCzDzna4hulOcc3hfwI/x2D+BHMcZo5+v70Wm3uaOfzEtjqH7z0rq3Mqs2KMsbJhX6C83jqENVx7/E5dZlVrt66zTmhkFunbPO4HPfTHQncW+oTQs4Ue3sbtPqaNurv21i0fZfDvd3BsD3wZmIA05LV1t8N8TEdzwt7VHjHGsWWL+Jmja2SPkN4jNGY720XoffQfhzhgw0ZD+a3+B2mbW0v6HaEt/zvoPyD+kQC656n/Prq+tZr0h0Jb/veD1vt6K6tr3PtgM0JsI5iIs8dA2xjOs0Jb4TzvCIfzarrmYOviS3BJPu4coN2o9PXAnQxrrfmk0di5drjUuXfwQfKsMn8UHcvCzoozVdtxkmGfreT99vRTJ7TFv4d7rlpIJa8mz3wjRDuTdr+i3TQz1bjT+T2VVY570M9H+0oDfirzWCdgHoL5DOZzmD/DnIT5C8xhh9kA81fPXqG807S/Ne3cZ9XD2qZY12i3HIj6AzvWH9rVwi4gdmCU/kfvGUU5y5y42rHM2J7Xa3t2lJfrbknmh6v/ajbG4N8g6Zf7weQg/twcd7up9u+/hLcf3YMhq++R9Th17+W/P1d52pO+FHQhaNVfdO++LTfzHPxT6N/LHxFbrnlu4TFljdyW219a+1saMP6xZai9FwHfDDt+82n3aabqHn7YuWQt0+vSf3MnGPz7ZRzmloA/A3ZEXLXesokIter65ZMtfeN3yH+X2Qv/fxemhb1PQcLqKONH7BLqQN0I7WgcVhR6xioz8iI94vct7NltBi3gknplFaI8s/lGQl+73Pimt4zIN8XBN8YIki9D61NYqqAty/7YnmdrTGf51jrKt1bqa3uVr9UqYz6n38nqt68=
*/