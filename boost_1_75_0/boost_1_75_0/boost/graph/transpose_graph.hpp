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
PFwthBNmCo1+jKyI+uU6dy7xSdpcKmzm+RfxTW3Rt0PLlaAVeTPVETC2dpMSqG1Qx4k1A/dAiLauEmrzWVkVrRxpwYRqjBjsYvKICaoz2AbUeWLUgfmgXacD9I8VWG4/oOrHVsetysPgfD9Q3W8WEMfaXgJi1wh9h0xVx5ERFu+w19M0SbClX9iyxXrbpmyBaO6epx1lXcl0kaAmGjOGKJIo8hkaA7Pavg56NZIEogMCaVIXJi82i3HYLSfBn0C/TxqJ4VSlyF7hOAsi32cVSgvkqolZUoHKDbPW1RVGbvxhllLCD7O5WZkdvzb2KHlYgCz1seR7jP4v7b4arb5HzcaLs0br8sanSusfEB3K5AjKbU+F88uJTxmax8oJ4pNDNTAeS5PkU3SAtQYJf3lK7CXHUvJEBm3VFqPZxUqKrrzTxgVXhEruWJOVqVSaqpGf4k0vyaKxyPMc7A/oIyyzTbaJXBSK8OAGUk3pX6OITuhqUzoXRdsLXTJICWiLec/xecWpzxt2S0fwqyp5nPT/YjXSwJ3j9P9OxvJRQ5vJe+GTf4FZ0S2/tBz/35LEm9VOr2qt5w/Il+ySyoHgZ1X0rvaHrwZAhBmXAa4F/q3y6wiHRnPCD7/Evhk5LyDWxgwQNHD8Ieo4aFsQWUo6vv/6sECokxOoo4jqnPoAlDUvWTk51zzB9s9kPBXdKj08b1jmu8tiNUk8nDy4itu0
*/