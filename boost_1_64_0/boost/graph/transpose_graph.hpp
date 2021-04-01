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
9UcRN5S62x36i/Gf0KAr+bHm4Hg+akDX8atZwHau3dQJ3lyPLVIiTvqTeipd2IV4u5lV9NaDvn/NX2xWAMT347tmcBNrco9Cu8+znbbGSJcOBbChDnEnrlzj0jRi6inYMmof1qXhrXB54AfK0HBXki1ekyMIh7yPcWe1qllOyzW3ylYEIATUGIYlbs/aK7V5rtd7qWBRnKXLZ0hFmAmJldJFbakrqyD2HES1CkI+6cwAHeyANo1t6PTgVfj29XFZu4ySnToU47G3d8QQZ5ISYst9qf3bWDmEiQY1RLEnNhKRHWa9xKqEV28gil/x1DxD9f0kFgzw5wFQ5jBcpT5TWcaRt9aV1OXVf1VjXQqhyrkENljZ36Pw6oOvk/pNHpdQdZMhuQ/PMCblWccpyeWaRRCoQr0/lrZ7oG4VZlyssw9ddqe5pVmFtnrkF0y0ibsthTXHMa5yPHlzAYDoftqSfsHo0WPLGhwLN08Qe5GVmHUfMtG8BiMOTDDeHKKN+dfk3nxPMQGSxh17XrHSCTBLeTreG08z7QGDuh+Ah1Fq0FYL2T5S7EdSxPQnbQ==
*/