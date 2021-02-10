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
bIqzthMVtQ/uMUefmiBBhmuGuh1YhB0oyRh1f3wvieBSch2/i85MC9R8x9t9JVJelMGwNs2iZZhAQxsuHnjMLP5lnZQatMStY9yExq0/eVzhedUO2UAOO2SxcC5C/nnEhIozXE8hWHF4m2a0RRGybsmFr+eNXQPfeKZrZiaLlUgfVbVdcnVhcaqQRtXZcFm4Ld5ONY3+JDZzW5Nz2cBgrPM6mu3cIEXjWZziFZdFLY7JxK/DvzXUvWUKvYLWX8dxG2G4uvgtx/mLmL2JUDSWDj+bexZpFplKsCjfKiNgOTdFy7V75L1D5/h4gSYWFbEiTI0h0yxVtsKg4mZHvoSYMz10DuH23sPP+O1Xu8htpIE/umWkMoWAKwd+1QkuXr74NVlGPQW3Hr+23Vinuhp2/9uKeWuYEdesbyh3JnGFK02iCfvkkXMzXkyIUEhG7Xlwcx5qVz/qTf3PCrMexCE5o6Sr5RLdVHD7Gk29WH+gXx0py8vOtCh2vkzT3UJeCvi0J9rLnFEr+OfuPnXxTfPg40S4F1hl6nsglHA664P9dYzrjvS/zyj/+hH+Rpim7pq8SkMfuIALK6ROmynFCgEroXfMumJgfZ0PnxmqZxgcNIQ+ZX7mfIEd+JmhDOZH6HbMoSR4JxWWNaNJcNhw
*/