// Copyright (c) Jeremy Siek 2001, Marc Wintermantel 2002
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_BANDWIDTH_HPP
#define BOOST_GRAPH_BANDWIDTH_HPP

#include <algorithm> // for std::min and std::max
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/detail/numeric_traits.hpp>

namespace boost
{

template < typename Graph, typename VertexIndexMap >
typename graph_traits< Graph >::vertices_size_type ith_bandwidth(
    typename graph_traits< Graph >::vertex_descriptor i, const Graph& g,
    VertexIndexMap index)
{
    BOOST_USING_STD_MAX();
    using std::abs;
    typedef
        typename graph_traits< Graph >::vertices_size_type vertices_size_type;
    vertices_size_type b = 0;
    typename graph_traits< Graph >::out_edge_iterator e, end;
    for (boost::tie(e, end) = out_edges(i, g); e != end; ++e)
    {
        int f_i = get(index, i);
        int f_j = get(index, target(*e, g));
        b = max BOOST_PREVENT_MACRO_SUBSTITUTION(
            b, vertices_size_type(abs(f_i - f_j)));
    }
    return b;
}

template < typename Graph >
typename graph_traits< Graph >::vertices_size_type ith_bandwidth(
    typename graph_traits< Graph >::vertex_descriptor i, const Graph& g)
{
    return ith_bandwidth(i, g, get(vertex_index, g));
}

template < typename Graph, typename VertexIndexMap >
typename graph_traits< Graph >::vertices_size_type bandwidth(
    const Graph& g, VertexIndexMap index)
{
    BOOST_USING_STD_MAX();
    using std::abs;
    typedef
        typename graph_traits< Graph >::vertices_size_type vertices_size_type;
    vertices_size_type b = 0;
    typename graph_traits< Graph >::edge_iterator i, end;
    for (boost::tie(i, end) = edges(g); i != end; ++i)
    {
        int f_i = get(index, source(*i, g));
        int f_j = get(index, target(*i, g));
        b = max BOOST_PREVENT_MACRO_SUBSTITUTION(
            b, vertices_size_type(abs(f_i - f_j)));
    }
    return b;
}

template < typename Graph >
typename graph_traits< Graph >::vertices_size_type bandwidth(const Graph& g)
{
    return bandwidth(g, get(vertex_index, g));
}

template < typename Graph, typename VertexIndexMap >
typename graph_traits< Graph >::vertices_size_type edgesum(
    const Graph& g, VertexIndexMap index_map)
{
    typedef typename graph_traits< Graph >::vertices_size_type size_type;
    typedef
        typename detail::numeric_traits< size_type >::difference_type diff_t;
    size_type sum = 0;
    typename graph_traits< Graph >::edge_iterator i, end;
    for (boost::tie(i, end) = edges(g); i != end; ++i)
    {
        diff_t f_u = get(index_map, source(*i, g));
        diff_t f_v = get(index_map, target(*i, g));
        using namespace std; // to call abs() unqualified
        sum += abs(f_u - f_v);
    }
    return sum;
}

} // namespace boost

#endif // BOOST_GRAPH_BANDWIDTH_HPP

/* bandwidth.hpp
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
*/