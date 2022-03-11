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