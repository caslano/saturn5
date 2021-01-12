//  Copyright (c) 2006, Stephan Diederich
//
//  This code may be used under either of the following two licences:
//
//    Permission is hereby granted, free of charge, to any person
//    obtaining a copy of this software and associated documentation
//    files (the "Software"), to deal in the Software without
//    restriction, including without limitation the rights to use,
//    copy, modify, merge, publish, distribute, sublicense, and/or
//    sell copies of the Software, and to permit persons to whom the
//    Software is furnished to do so, subject to the following
//    conditions:
//
//    The above copyright notice and this permission notice shall be
//    included in all copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//    OTHER DEALINGS IN THE SOFTWARE. OF SUCH DAMAGE.
//
//  Or:
//
//    Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//    http://www.boost.org/LICENSE_1_0.txt)

/*
  Writes maximal flow problem in extended DIMACS format to an OutputIterator
  Vertex indices are read from an IndexMap and shiftet by 1.
  so their new range is [1..num_vertices(g)]
*/

/* ----------------------------------------------------------------- */

#include <vector>
#include <string>
#include <ostream>

namespace boost
{

template < class Graph, class CapacityMap, class IndexMap >
void write_dimacs_max_flow(const Graph& g, CapacityMap capacity, IndexMap idx,
    typename graph_traits< Graph >::vertex_descriptor src,
    typename graph_traits< Graph >::vertex_descriptor sink, std::ostream& out)
{
    typedef typename graph_traits< Graph >::edge_iterator edge_iterator;

    out << "c DIMACS max-flow file generated from boost::write_dimacs_max_flow"
        << std::endl;
    out << "p max " << num_vertices(g) << " " << num_edges(g)
        << std::endl; // print problem description "max" and number of verts and
                      // edges
    out << "n " << get(idx, src) + 1 << " s" << std::endl;
    ; // say which one is source
    out << "n " << get(idx, sink) + 1 << " t"
        << std::endl; // say which one is sink

    // output the edges
    edge_iterator ei, e_end;
    for (boost::tie(ei, e_end) = edges(g); ei != e_end; ++ei)
    {
        out << "a " << idx[source(*ei, g)] + 1 << " " << idx[target(*ei, g)] + 1
            << " " << get(capacity, *ei) << std::endl;
    }
}

} // namespace boost

/* write_dimacs.hpp
CBu2dzExbiZTi22CK/J7U08s1tga6ClUX5DSGwPN+SWaKguZPE/xnz9hdxR/8oqw0TPJ2aecA8MxWi2T4ZEUjgkYa0BvqRkF2vTsFIvqdO7owoWs3SG1rI9Qy2oX5UkNl/VW0t6d4JuwRBmMwCDqITYLptN+jjRm3JdkZrwcL4c8DZudtDjSZpe6yE0cIjb3Vi+K+vtYIwHukH6iH+GJ0lbfj7BZ7u+VIqyX6YsRbpf7e0VP
*/