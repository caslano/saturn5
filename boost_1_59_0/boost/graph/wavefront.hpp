//
//=======================================================================
// Copyright 2002 Marc Wintermantel (wintermantel@even-ag.ch)
// ETH Zurich, Center of Structure Technologies
// (https://web.archive.org/web/20050307090307/http://www.structures.ethz.ch/)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

#ifndef BOOST_GRAPH_WAVEFRONT_HPP
#define BOOST_GRAPH_WAVEFRONT_HPP

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/detail/numeric_traits.hpp>
#include <boost/graph/bandwidth.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <vector>
#include <algorithm> // for std::min and std::max

namespace boost
{

template < typename Graph, typename VertexIndexMap >
typename graph_traits< Graph >::vertices_size_type ith_wavefront(
    typename graph_traits< Graph >::vertex_descriptor i, const Graph& g,
    VertexIndexMap index)
{
    typename graph_traits< Graph >::vertex_descriptor v, w;
    typename graph_traits< Graph >::vertices_size_type b = 1;
    typename graph_traits< Graph >::out_edge_iterator edge_it2, edge_it2_end;
    typename graph_traits< Graph >::vertices_size_type index_i = index[i];
    std::vector< bool > rows_active(num_vertices(g), false);

    rows_active[index_i] = true;

    typename graph_traits< Graph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
    {
        v = *ui;
        if (index[v] <= index_i)
        {
            for (boost::tie(edge_it2, edge_it2_end) = out_edges(v, g);
                 edge_it2 != edge_it2_end; ++edge_it2)
            {
                w = target(*edge_it2, g);
                if ((index[w] >= index_i) && (!rows_active[index[w]]))
                {
                    b++;
                    rows_active[index[w]] = true;
                }
            }
        }
    }

    return b;
}

template < typename Graph >
typename graph_traits< Graph >::vertices_size_type ith_wavefront(
    typename graph_traits< Graph >::vertex_descriptor i, const Graph& g)
{
    return ith_wavefront(i, g, get(vertex_index, g));
}

template < typename Graph, typename VertexIndexMap >
typename graph_traits< Graph >::vertices_size_type max_wavefront(
    const Graph& g, VertexIndexMap index)
{
    BOOST_USING_STD_MAX();
    typename graph_traits< Graph >::vertices_size_type b = 0;
    typename graph_traits< Graph >::vertex_iterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
        b = max BOOST_PREVENT_MACRO_SUBSTITUTION(
            b, ith_wavefront(*i, g, index));
    return b;
}

template < typename Graph >
typename graph_traits< Graph >::vertices_size_type max_wavefront(const Graph& g)
{
    return max_wavefront(g, get(vertex_index, g));
}

template < typename Graph, typename VertexIndexMap >
double aver_wavefront(const Graph& g, VertexIndexMap index)
{
    double b = 0;
    typename graph_traits< Graph >::vertex_iterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
        b += ith_wavefront(*i, g, index);

    b /= num_vertices(g);
    return b;
}

template < typename Graph > double aver_wavefront(const Graph& g)
{
    return aver_wavefront(g, get(vertex_index, g));
}

template < typename Graph, typename VertexIndexMap >
double rms_wavefront(const Graph& g, VertexIndexMap index)
{
    double b = 0;
    typename graph_traits< Graph >::vertex_iterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
        b += std::pow(double(ith_wavefront(*i, g, index)), 2.0);

    b /= num_vertices(g);

    return std::sqrt(b);
}

template < typename Graph > double rms_wavefront(const Graph& g)
{
    return rms_wavefront(g, get(vertex_index, g));
}

} // namespace boost

#endif // BOOST_GRAPH_WAVEFRONT_HPP

/* wavefront.hpp
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
*/