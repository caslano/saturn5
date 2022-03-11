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