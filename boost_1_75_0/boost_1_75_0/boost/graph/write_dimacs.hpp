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
zbPCo6XyKgR58YChGXX3fNfLEW+Kre9x1B8hihnHRfca2hvemY+ydo6FL/22bfLinp2bbELplV6frgxfssmXG7gMDyePHYZBEBXLp+aVGMKy7xehdj/ze6zSDYDLEGZXaoVPdeZdtodELjd1prd2NqcT97gWuViM6TAUQobD7HM9PZ00nQPX1R3L+4NMJ5MOj3RaA7wZs8OuwY5ikxezoIdqX9zQus9Bb7vHbOmpmCGX6pDL7bZz15mv313MG78sTXiznnVwZQW/3G1oV9SZdSScQqKW9rpTDiLZqDm70ArnqMeIVhpkLd/YRL6yddk+0S1UyFW0Uzz3H9YgQrETOSHOq431FiKr9bpsQs130WyCEgioLk858d9lArzWq+PJm6AeTraHI/EMNW06lFlRja5mhkCquhPcWRE/unkfgdVpMPZeRFn4DpHgW8c3hY2GBixpmAyzeuWNOFdsOyHo0DfOYnh5JPym6RLYuCmRUrXv2LtuKVVi+YitOrdwAO6wHwqxNNQqxo3MfJYyTXx0fIBt2eiUDMOkwmuDzk4S7MYc3Outib7J5MI+ZlB2E/fCp7z0JmG56dQ2r+Lni+3GEbRWZsMCXXDo4w44hnBKL3yqPrBRVvNqpZ4Nr1lZL0zobL3Rp6+hlGLelDTW88/rLwyzkaZZusr2TTHX3cFhaE77m3ODtOS2z9ub0Dho2aRhMHOxkvZJatymkp6T
*/