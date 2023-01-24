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
8AJm0Y1vcmrxjbAi3gnpMolLYHFq2i17+yZlEYzXXNJ5hTOcRd9q3KY7/fl5/wL/hCBr8tJWyP6WrbzO7NQYHRLgoukmNHg9NBY467LV2ia+78mYkPoOd6UfZyxTsq73RyDhJp8Joq1iZ/1PcHrtBgJpR8IB/7tat0vSJNcrXMtHOPylH7bhp97o9Zr4OSb6nP+RIwwU5Vm9iDG4GBFuvZx801LNx2wjcmOMyNs5+JenhBhkqM/PHtOJnnX6n2D3vs9Vr+qNJAF+QbEqKikrTgYdLkNHbefUqj61kPQGjqqP2yZaZim93VamMQ1W3mDkH1x+QePlKeADcMqGfnpmrVVMIuNLkZ3feIQjW+AhW5CjUO2HoZbq0h+yYwYdnF3yVUp1X5cMzH4QEH/9UtSbAAZjH0LoMbURE54SoJEJKO1iFdYcBqFuhJ2UT2fa6su9s7Fx7BpRbFBm4a2CKegwNAYEyq72E1rZH7NNfErIm8Ja4R/9S6OYm5QrT/9wQAea8V6i7BHt8SZWR0S6YeOXwzMUR2pmc0OYHSpwQTzgRUKs3eouIIpi7ZCBYaIlSXvPE9GPV6+B88Nf0J8YcG3qNzQ/8fYffPKZOUHCXU16WNu4JiX/Hviw50lE59kZeLJWE/RQa8KU8bcdNoeU58PRhqc3fYL5xcR/LrCl2NoUJdmuiZ3ZDRuWazYDBCDF/nIzyl3iTaXQOb/zFSdN
*/