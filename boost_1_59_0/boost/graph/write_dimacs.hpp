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
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
*/