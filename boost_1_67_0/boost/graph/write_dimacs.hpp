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