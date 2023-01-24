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
BvflSqWkv/v6HfoZEtE4tIDHZb/jD1fwDn7M4gUZeFd+gyg/24DLa7U6SKHUuOon8FsNZHvk501u5WvIVIk8awXJNOwvW+nPrl/JvkQNq8g3JQr24ZWC/EDerXwN8mcz+VXsbEgU5TPRidIftR2JM4nXr2NfG+R/BhPrbsKvI0Hq1urgoKDAxi7Jl/2j8hBVeHjf8PCQ8L4h7HcMTJqQXq1CWgcFs3J1X1VfFZ7hKG4d0jq4dXBwUHCwL+NXh2D9way+qv897XuxepJb1Ig+1i9Bcpne37G9forXT/H6KfX1U6yWRuyP/ajtb8FRXvAd0HVAz6ERm/VxKGczc7aeyl0nNqtzUtXQRCAvp4lLR7MWq8KQbYhvZFcpTeRhOMqt+Fkt1MEmIp2B5kCp/kZ2fTbOMonOn8GFoT/Y+TO4kBw/g4szB/22zX4Grz5Oa3jOh1dyPko8NrRwPpS3NBSOdjseTViezflki+c4P3vf1/rfl7q3fzev6a/9bL9u8iI0eUFha/KC0tbkxerk94T0ysu+0Py3/1ntd9XomZPZb9sZp89Bhvks7M85A8ZTp2FvthnSs3Jg9wkTpGVmQcqxk7DrSCZsP3wMth04ClszDsEW40FI3JsBiXv2QUKaEeJT0mHjzt0Quz0V1m/bBTFbd8K6LTtgrWE7rDFsg87//Fs1+Z7+9v6ktC7J/b7ensrftlIHY//JVSP63pPy
*/