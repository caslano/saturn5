// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

#ifndef BOOST_GRAPH_VERTEX_AND_EDGE_RANGE_HPP
#define BOOST_GRAPH_VERTEX_AND_EDGE_RANGE_HPP

#include <boost/graph/graph_traits.hpp>
#include <iterator>

namespace boost
{

namespace graph
{
    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    class vertex_and_edge_range
    {
        typedef graph_traits< Graph > traits_type;

    public:
        typedef typename traits_type::directed_category directed_category;
        typedef
            typename traits_type::edge_parallel_category edge_parallel_category;
        struct traversal_category : public virtual vertex_list_graph_tag,
                                    public virtual edge_list_graph_tag
        {
        };

        typedef std::size_t vertices_size_type;
        typedef VertexIterator vertex_iterator;
        typedef typename std::iterator_traits< VertexIterator >::value_type
            vertex_descriptor;

        typedef EdgeIterator edge_iterator;
        typedef typename std::iterator_traits< EdgeIterator >::value_type
            edge_descriptor;

        typedef std::size_t edges_size_type;

        typedef void adjacency_iterator;
        typedef void out_edge_iterator;
        typedef void in_edge_iterator;
        typedef void degree_size_type;

        static vertex_descriptor null_vertex()
        {
            return traits_type::null_vertex();
        }

        vertex_and_edge_range(const Graph& g, VertexIterator first_v,
            VertexIterator last_v, vertices_size_type n, EdgeIterator first_e,
            EdgeIterator last_e, edges_size_type m)
        : g(&g)
        , first_vertex(first_v)
        , last_vertex(last_v)
        , m_num_vertices(n)
        , first_edge(first_e)
        , last_edge(last_e)
        , m_num_edges(m)
        {
        }

        vertex_and_edge_range(const Graph& g, VertexIterator first_v,
            VertexIterator last_v, EdgeIterator first_e, EdgeIterator last_e)
        : g(&g)
        , first_vertex(first_v)
        , last_vertex(last_v)
        , first_edge(first_e)
        , last_edge(last_e)
        {
            m_num_vertices = std::distance(first_v, last_v);
            m_num_edges = std::distance(first_e, last_e);
        }

        const Graph* g;
        vertex_iterator first_vertex;
        vertex_iterator last_vertex;
        vertices_size_type m_num_vertices;
        edge_iterator first_edge;
        edge_iterator last_edge;
        edges_size_type m_num_edges;
    };

    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    inline std::pair< VertexIterator, VertexIterator > vertices(
        const vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >& g)
    {
        return std::make_pair(g.first_vertex, g.last_vertex);
    }

    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    inline typename vertex_and_edge_range< Graph, VertexIterator,
        EdgeIterator >::vertices_size_type
    num_vertices(
        const vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >& g)
    {
        return g.m_num_vertices;
    }

    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    inline std::pair< EdgeIterator, EdgeIterator > edges(
        const vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >& g)
    {
        return std::make_pair(g.first_edge, g.last_edge);
    }

    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    inline typename vertex_and_edge_range< Graph, VertexIterator,
        EdgeIterator >::edges_size_type
    num_edges(
        const vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >& g)
    {
        return g.m_num_edges;
    }

    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    inline typename vertex_and_edge_range< Graph, VertexIterator,
        EdgeIterator >::vertex_descriptor
    source(typename vertex_and_edge_range< Graph, VertexIterator,
               EdgeIterator >::edge_descriptor e,
        const vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >& g)
    {
        return source(e, *g.g);
    }

    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    inline typename vertex_and_edge_range< Graph, VertexIterator,
        EdgeIterator >::vertex_descriptor
    target(typename vertex_and_edge_range< Graph, VertexIterator,
               EdgeIterator >::edge_descriptor e,
        const vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >& g)
    {
        return target(e, *g.g);
    }

    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    inline vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >
    make_vertex_and_edge_range(const Graph& g, VertexIterator first_v,
        VertexIterator last_v, EdgeIterator first_e, EdgeIterator last_e)
    {
        typedef vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >
            result_type;
        return result_type(g, first_v, last_v, first_e, last_e);
    }

} // end namespace graph

using graph::make_vertex_and_edge_range;
using graph::vertex_and_edge_range;

} // end namespace boost
#endif // BOOST_GRAPH_VERTEX_AND_EDGE_RANGE_HPP

/* vertex_and_edge_range.hpp
3HVWecbyp07VcZWCqRXF9riK0mmlx9pG4+8YzNiTeM8ElRX97Co8NbYWz7NtkHnaFUUFAe8fOehSfX/FYWphZtbH3jggLirVkFr4ukm5aajf5aZjruMAfb2WzhPj1LOmn+Szhp7LZ5f9bjKzEP8xSYoN0e1uPxOOpDqZXlxsBN+vSteRop9tv0/FnqLsfGWI3TlWSIaZbsfHHKXvKxddeIjDmAhfOeKJrTh4TJULKx9s5vrLmG0nUWc648HZj9w0y6+8SMXDREwauiuD4qF8enG57xTFwPFSux32B3EzkrISac81UM8Xbm7ri3I9WvcZvqH8OJ1/7bmxJz5/3DlO6kzvko52G6oFPISZg25mE/2cMiYsc/UrwuZfpd9Rn3FSLPb39Dca5XjCRb16lOerfrIB2k2W/vYuEPv2QDfygrLq8jzRmST2HO1HW32ulrepvOMdfhSWqGBVW8py01r3o48T+54ANxKsDvdV0enpbGcpf0xnH5TzPad1MwN0uZWw7zhn34HTTTl2/X7j/pz9DhNF7zV9PdoXb46yOEeuV+3HHyOyxkpmiuxFkY0L+T2QAkvl+jO6T21eAu/WmvIupf0o7yNLJvZFCZgTeEf55iWTblXmJXcPUUf3099lOi+JPKeqXLdzRmu5zgMiH++Ui7rVZxf8TiwP+060zy/byMbwEk88QDyMgnN9dWZTqwypSYdyeBnQC3LCzoNWbtPsNozYv3D2heu6Ileu1bK/TcSepPOY4Vg/xKiV7ne5QPTcum0zRey9cIedv9aJ/Q6jne8LwmhK2Fa/brn0+eZoPz62+4XtsHS+2SQ6U5Td8jfBCOhD0vXlh3J9EKG6Vfs76F6kLTeZuqt3Z2v8udzrSo5tLX0fLhl+Tg/X9/GC+NUPvxKVzDS+EVkL0i/KOQbNt2uocaoTe/d2D+gXljPw7G9csefoft7yKvXykq78o+avJsPn1TzWnGaBeWoGp7SFn8c6RfTXqXmslvv6wfNY9bVaug6fKPb1jnmsZVOtGY7S9tZuUnUf4gVif9Qx/7NM3aHd3zdXdNx6fGRJc599su53mC/Xx+rxkaNyPUVdp83QAju2UH0ae0Q3VZ+FtUzsFxmDkVUdT7Pv50nRidD3c1TCX67v5ym5fraRqO5nn1w/zeQaz4mODmeJ0YzyI88u4xz60XVZXSduvfrds1Hs9wWXBaWfKv4+R3673BhGnkxSeZJ3vzNvOvve1FgGclsHOq8jO4l8nBNiDuzogDmw9vwJO484vxu83fye7sMkYd7FDPW1lVsE5OfyqfyrzlCuMMLm6x7i7im7/Sz2RiHrx04tnPWj0uWuQ821niLXFhqO/Gvfi8ofQ0RnnXNczqHTU8r9INF5wgiuRxzxfxLt1MD47xIQ/931O82+F+e3Su8z1bkGKv4Xq/g30h3x75wYb4SOe+JauUnR7Y8Usc8JOU5bh2u6jtFu61QZO6U06nhrJNenWevwZCw6D9NCjDVufXL9IseKu8Qq371yL1XirTWHvUj8qfkkZ0FfvK0MjDfO2PR1NIaPN8tNfR1vT4u9uRkqzz6e7siz2m2iY4xEAtPx9opcrytzTPbWke+JQme907+lzL3U6TJE7I1C1om1YL5c7xlYL2n35XK9ox6TeVXsNVQdZef3o8kyZgDtdGuEQlNMPjppUNVL1tgCtP9++QTajyeTzs4+See82LVsCiTEJCnO9/Xhy3PNU4uhg85BVXOAlR6uRhk51loGZxtfGn7qRFVxQxjazSSjm2Ms0z6zukT7my5uLsBeO8M/x3yocVrAXGt7rmdN0VlsXKLWgwzV/jRT4ej5obrtd4a4Geb8vsFN1e+b8GdT27rBcxY=
*/