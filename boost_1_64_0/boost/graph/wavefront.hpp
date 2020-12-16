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
vXAedBP2AuiBFTABVsIkOBVmwCvg6fBKeBa8Cko9b433wrUh6vmLXPgD58C+8BJ4EbwUynsHroDz4Splv1/pS7+oNSYp46B2X2o3KHs6IUqH7WAmzIJnwPYwG3aEY2AnOBV2hpWwC1wOz4C3wW7wDngmXAfPhuthd/gO7Al3w17wAMyGX8I+8CvYF34D+8Ff4QDoi7dB8Ew4GJ4Hc2A5HAqnw+HwMjgC3g5HwkfhKPgYHAtfgOfC1+F58E2YB9+D4+FeWAgPwyJ4FBZD3/fmBFgflsAj8jxqnA0uVunlgR1Ueq0n3hvDp+F4+Bc4ET4LS+EmuA8HFxMBG4r9Z93sgF9jak9w6TNouvD3cEw55ljn0Szh+poJJ37OTIgzZn7382X+G86W+a3OlXmBuOZsmd/9XJmTPVOm6lkywefILMH05nr4M2Ss82OOfXZM+DNjfv/zYk6dFWOoc2L+/efDHONsmJM6Fyb4TBh0Jrh+k3NhnGfCHMJP70TOAsPkYMoxSzBrMe9gDmGiSyjLmO6YIswizBrMVswhTHwpZ8dgcjCzMLdjNmL2YYwLXEZrzEBMJWY5Zj3mdcyhC45/tsyp36nfqd+p36nfqd+p36nfqd9/3+93Pf9vekU+m5/7TgD8l87/853z9109w9dr4jtUL3vYMMOWGSIa0sewZabI+mUP5Bs9Rclcfr3BffsPzjYcum6R9x/slEWIbMiI4Q6ZV2S5/fsOtv2ME9nI7GH9+4xxuq8u8mHZIw1bt4YKv9ewMTnDHfJ4kffOFrnDjyR1X5wrqHWTRZbTIzdX7lfLa4pcnUAo8miRI+0/ZDBHGg7p3ytbnbsXW9PQa1iaxhryS4+k71RxBVfGu2ReuD/18qbIBjtVzjsqJAw1z7pzhE+3gDhrQr9ZLbWuQPvh3weTv84QvbOZH1RX/FoRr/yaac8RV24cZxgRMr/mas54G/HjI4ZhW8hKkNH01F5kXmhMQjLDHanmlrOqKFr2K9ZniT3twc6h3PZ5DzxaHut+HPstrZewZ3jsff3Lp0+daOizHT6R6309jrXuxVCvp9op14d6WOuj8uVU/7PLfAy9169jnStriio4vVHt0ZcMv5P7HGXmGB76NF2G0lX3W1rGnHBrfjtp5V8Tm6bW+bQS+0HZ8eMWg+80zBZMilxnF/Io/542mfg6GHmV+/CvAJRn2YHkbbnfMR5bJ7+irF15/vSKYr3f8LOiM7lKfMxU8dEbviTXJxAf1jqOWXru/x5Jx1QjTezclTz3NtdAnvte406zHwPuua6JRqLzDAbfsnvlfzlcJf5f5bF1yvMrKkrLyFGiMx7Jg6KzwJNSJR6t8xjs82VekLjLJVbqGPUxXTBpal3bc+o5XNxzfUwXTC5Gh0seVbcm4ZbAW8XN9fa9SRyLksTBCOLgXtG5NOj+rXUJo517lHKtSLk9H7cb1T0FnvV1mlpr11zi9zO312jKszQw8hgxmWfezbynrxh7jzOmu6M5n1Ltfa/LS7TshZiJP7slPYa4XjQjA/ZYtNdSNRGdLOKsjdFYhfulL1xKUhSdaaXkw4fxM9K823yU+7X2iR4r7p52VTMekj0hJ6WodOFfa1+PO+T5FkreyZXr9vrmJHF/tqy7t/YUuEb07/THpU7nKb4TRkRnK5LFonOvnadlT1lOmVPpNhBuEJ1Khz88sn9rAskPEUiuFJ3XXXeYXuMNM9r4GlPCEyfK9SrPF1DfSNrqtfKPq7Ac64aLi4t8a0NnSli1kWwWnaWuYiakXIfZgElxparr4cuNnW8KK3lAXSfPkXwer8+lKBd7EyMW2ausgWmHzt0JlC3n2YUOM83x972Y+xznI92JGYX5HPM=
*/