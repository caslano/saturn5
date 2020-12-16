//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_GRAPH_TRANSPOSE_HPP
#define BOOST_GRAPH_TRANSPOSE_HPP

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/reverse_graph.hpp>
#include <boost/graph/copy.hpp>

namespace boost
{

template < class VertexListGraph, class MutableGraph >
void transpose_graph(const VertexListGraph& G, MutableGraph& G_T)
{
    reverse_graph< VertexListGraph > R(G);
    copy_graph(R, G_T);
}

template < class VertexListGraph, class MutableGraph, class P, class T,
    class R >
void transpose_graph(const VertexListGraph& G, MutableGraph& G_T,
    const bgl_named_params< P, T, R >& params)
{
    reverse_graph< VertexListGraph > Rev(G);
    copy_graph(Rev, G_T, params);
}

} // namespace boost

#endif // BOOST_GRAPH_TRANSPOSE_HPP

/* transpose_graph.hpp
qfZOW5jfqzx4vdrb+qFeS2wrEci4yVPjLrZNTBvpHOh8ooKeJtL147dV59bD1yXbPTWfRduj6qOJ5q11JdQyUMOJsO/7ksw2dc3uIVIfzUsuI/P3dbuk3HjtUUr2IWTfbPZfydYGbyr7GOtZ9k+ke6YWzf8uhFHfp1l3vzXak3qANmbv0y6l2l/JPEle62LLwH68493a8tdRtYEUjXqboK2zrLpm1X7SuQ/ieJeQcb/jneon3NxXDJV0mEqzHx2tp/3uu84Pcvbv2K2WVTdzmKG2fUWKub5PlG5/aCs1R/Fx2Mr3NJ+pGy7lQxzbNA9z/3KWui603Y92DSjqOdUtgPQ//s/lYl8G9vW9c5az56eYxlBMwDas77NkXvLk9xBpGfr5s/lTP1tbVJxtWt8nq37CzbYt10l6kEMv307KyyBU/Rrlq5htK26U9EDK255LUcMfRffd0r2To3jblXpV75NuoQ5/7Y7ZzsyZMXpegNkm5efO8TnusP35Sxkjr5HklS36PLU5nL1SJrBEP14Ohm3sD5k3fgaQYG9f+DspV9ohabO/MtKmuy8ztoHKW6R/B+1ZxYeGALXibeV1VOUKRjGsIJZhH9qWdvPxdfVwcw32cKd9P39XL9r5iyId6l3Nu553J49QVxdSVT1CXF28I73rUdylUjjD1SfxvHxvqr77sVn8eGq2Byr1l8kSra7yjHkIc4Rpp2U9H+N8rsncjn6V7hulL+O5iKMyHBe1T7K36y3PZathNpflHmA+h2D9lu6SdN+q9ddaWd/h6+/cp17eljYbO5RoP/A/HC9ku4g3txPWY5WXiu0kT62rnK97yvRzfK/k3HZuaNSdq6bNrahpvo6Vby9rP8XN9W7bxGarMr9rlsB2K/l3Tn/k+ebTk2d1+upmQtqg6oWaNtBdz9/22eYv/gztNOlA6zHHDkbvm6lpD4Xo+ZdnRLxVf3/mncnXl25/dmnltXxn7NDzs45nPP/btZqH//Fqu7B655t/qGkTpPz7r4x+rd6MbcPPlf9rzW+1qkRzrHLV8zecH1DlzfhVpZ/zPuIIvvnudk2rJuPNnfFE1uLGZ9LWrv++2+qlE2M1jcGTf61tr7BxtWbO2F2h5UyvwruXNC0mVM/v2DMx5HzsjXpeWWGFzzS59SF5ZQnHmfW/ttn0+tKlA38+/vighd9/x3pVRs9P1c60TXHLOLjrowmftRyWXFfTysj0PBaRfPOpwSl1XZ9M8c69mPwPjjUy3qnvvvX5D4eioiYf6puT9vLyy5r2TmU93/VDv6Rho+u/M3/1pifuRh5J5HtwqYexIS/+Nrn3/IHP1XlikW+01/fsE6V82arL67/J07MvNolwSY3eynSGRej5vo3ffbRppkfiqX3bLy5f/f4aTbvupucv3jh/74mPR9+a5L8tsK7n7z007ZrM74lJ/zj892+v3JgwvXL5zTMGscG0CtPzQ/bmzrhTNXbXCzldNz6/Y/0RtluZ3wM+ATvjoqP3tXKv+/Do8A4M4wUpHxW1rN+PJ/6s0OfUpLA+i8IKOI5IPYyuXDvivfJzNv4x4f1px1683of9v8xXr/dX9Dz799ouv6x6Y17p1dUXsg3JcIbumLTU94vgd7s+e2FI+q3YtzVtkyz3Sl8keqcP7TbljNfzWdVqxyzWtDuSv2zu8D7vuV35dteSGn/PnzNtCUcfWQ+DfZK6HOt9OaNO9bkv5k5Y9RvnCFIPE/3nfvTR6JD+x98ZsbWw9iDu5h2poOdvfqz7jTstmv7j9YvnDiU6Ej9lGyul57f8vVbNfjdzX1jTaWCFy6WmP8P1s4ue/+Xs84fbJqe9PfmfE4dtilzpznTK8r07bHnq/rA=
*/