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
utEeAjKFk4Jx2lW2YRU9gqEEEOuYIoVjtf4NuOtUt+wsi0kLl/I9wMFPw7IQ1Ke/NA+WA2yReByU9Ze37cNyUAKIGWFawMrUgpO7xZfkV048djiKshcn4e65Na3JjQuBDLc9VufTpEBuMe6r7eRJw97+1nal/+DhyzLn0nssS8pxicf1E5xtLH8dseuuoo+JKgXu10wKFiyw7ILomXAmju73vKV7SRwJxdI2ldcl585+xw56g89eE4PW5iC+u8Y=
*/