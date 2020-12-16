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
AIFt5loaJgHzK5Xby9Daq+waZeJkXbrf3K/8qY6sBiYek4Cx3DyeANU6vTWwqc8/zA38fRVmmzZqDc8JrNlqHW2v0YqOsNZZtddrtH50a1kHS/a1LWtvyT63ZVmWbKcta2fJ3rRlmZZsk5ZlnW7J1tuyLpZslS3rbMlutWWdLNn1tkw/x1W2TD/HAlumn2O2LdPPMcWW6ecYb8v0c5yjZe30c5xly/RzZNky/RzVbZm+51oRWtbBOrtyTZRfxu5JonOG0plazvack8tlPdazhuOsQXUW5WbsK+KVjJdUCrIdWk+//0Q+Wu91Z9XH9lqr2u5wa2LCrXkKt7Yp3NqpcGu2Tn5t1smukQq9hizcmq3wa7PGydqg/Kf/MPblv+Q8N3l+4aQVOd7G4dZChVubFW6NVLi1TeHWMJ382qnQa4BOfg1T6LVl4dZg/efWPIVe23Tya7zwytjsVm149S3RkD9m8vdG5IYaF68Pe8MGcAA8DQ6Fl8Fh8HqYCx+B58OtcDzcBgvgLlgI98BieABOgAdhCfwFlkLfTUyC0XAyjINlsCacClPhNFgfToeNYSVsBmfADHghbANnwSw4G3aEc2BXeAk8E86FPeE8/j8HzodD4AI4HC6C4+BlMB8uhqXwClgGr4Iz4dVwDlwKF8Jr4BXwWrgUXgevhdfD5XA5vAneCG+DN8N74Aq4Bt4K/wjHwufhOLgN3gnfg3fBnXAU/AqOhr/AVZCq1rgHpsLVsBm8H54J18De8AHYBz4Mh8BHYTF8Cs6Ff4IL4Z/h1XAjXAGfhM/DP8AX4WPwG7gJ/gCfgxHkmRehF74Ea8HNsB58BbaFr8I+8E14HtwCJ8C34CVwG7wcvguvge/Bu+EO+DjcCV+Du+AWuBt+BPfAQ3AfPAL3QzMCfRgPP4GN4KewFfwMDoDfwwnwG3gp/BbOh4fgrfBzeDs8DP8If4F/hr/CN6Hv4/cDaMIPYQT8FHpgTcp8JGwEo2ATGA0zYAxsB2NhPxgHc2B1OBbWgAUwHl4AE+ClMBEuh0nwIZgMH4U1Ybyav7FoAPdbwThiJeOImA6YfphxmHLMIswKzEr0jjWHY51Pf7Rx0nM3Ts3bCDlvI3DOxr88X+N1zDHmaZzwHI0wczP+K+dknMx8jN9yLsb/+zwMNf/iv2buRcC8i5Oac2HNt9haeWq+w6nfqd+p36nfqd+p36nf/8fv9x7/l8F/w/iXx/8PBY//Iwse/z8UPP4vMpcaT1dD5Frutsb65YItjwieLyByj/LHKYu0/HDIokSWM6InqpafMXr8XnS1vJqWV/U3XuSDh6CtZQkiG549erjtPlFkg4b0HjFwRK7D32SR9+qf0y97mCHyaOSh5wX8nGzos9CPxvKP6gdvrLiCK4d/NNW8AJkUEDgnQI931/gFPTmtt64ae7LcLtBnWiaJTkrYuQC2vnM83j4jYcZPXGcUuK05QY9jrv7ZJ8tx7C9YyWaSPLcay+0hbqJchbhxu1xq71LLXZEe2z5P9B4MGutPVGfadZbrWz1bzAjZ2/OQGu/PUvt0XizXbzBbEXIfYnconAwvJAdchrmBvO826xjp3EeiuDHV86xlhO8WxxyBUrWZsL2v3Vor3rjXw9jrirtDHttN+cxJecVlhdNtNwPk+aKV3QrLo8dPp4j9Vk+o8fYMFd9dfvXp3Ok6gxxYwF3OxizBvIH5BPMdJrFKOuwzc1hBlqjG68+QMF735LszjHBj9lcgGSh6f/Y49lrWc00eNuUMLMpyTUboY43mat7ErYbsF88dJDF+H8cug92Mcv6+wojj2iq1l2Co/FFYUlw4Sc/hGC9h3+8JN7Y/C7YXnXfCjtuPh7b/5TM=
*/