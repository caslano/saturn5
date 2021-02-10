// Copyright (C) 2004-2008 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Nick Edmonds
//           Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_DISTRIBUTED_FILTERED_GRAPH_HPP
#define BOOST_DISTRIBUTED_FILTERED_GRAPH_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/parallel/process_group.hpp>
#include <boost/graph/filtered_graph.hpp>

namespace boost {
  namespace graph {
          namespace parallel {
      /// Retrieve the process group from a filtered graph
      template<typename Graph, typename EdgePredicate, typename VertexPredicate>
      struct process_group_type<filtered_graph<Graph, EdgePredicate, VertexPredicate> >
        : process_group_type<Graph> { };

      template<typename Graph, typename EdgePredicate, typename VertexPredicate>
      struct process_group_type<const filtered_graph<Graph, EdgePredicate, VertexPredicate> >
        : process_group_type<Graph> { };
    }

  }

  /// Retrieve the process group from a filtered graph
  template<typename Graph, typename EdgePredicate, typename VertexPredicate>
  inline typename graph::parallel::process_group_type<Graph>::type
  process_group(filtered_graph<Graph, EdgePredicate, VertexPredicate> const& g) {
    return process_group(g.m_g);
  }

  /// Forward vertex() to vertex() of the base graph 
  template <typename Graph, typename EdgePredicate, typename VertexPredicate>
  typename graph_traits<Graph>::vertex_descriptor
  vertex(typename graph_traits<Graph>::vertices_size_type i, 
         filtered_graph<Graph, EdgePredicate, VertexPredicate> const& g)
  { return vertex(i, g.m_g); }

}

#endif // BOOST_DISTRIBUTED_FILTERED_GRAPH_HPP

/* filtered_graph.hpp
tJrOaffyZWfgDC87p0MLdsn7gso5PPqlGnZrBezWKth/rYZ9uAL24SrYfyuFfTnoj/qn/QuJoAU3965UBf9UgbPd93AJ3MMKuOX4nrcvhh0LGj1Zuk0wViEPgysbFD5YAYm1NChj7QU+KLsEV57xENezUMnmOt2GB2M3dXEhGQsMYE7sR7DG/dR+dJsGif3Ei8IQNm54iIt7EgmlKZ+y1J/xaJHm1jIPRA/zWRp7bsLthx9/bj5xk7CVGxG11Dz2w3Qi1ZT1ZsZnUXyPbw52aesK3CRluhFtjXITvObHNmbQd8yvFzcEF/uf+bBH4i6YCH0hWTXsD2HNt880dz82W9bLt4PuqJO9PBQaa3ihtBCbBO6NDfP0anCBepZkE7XMm0MlOdUtnNft4SuFRa3Ffv21rFV9CYgjJVPVLdYa5KhqEKHTSAMsbbFyFNFs6TCkIY6WtlhvmNbSYYgxPy1tsd4wlZy5aKvd5OetLVgbC1hLsN861y5sg+HYwfXL/rXFGKxRZwrmDgi1+OcEHsLSYH7k4Q6ovgaR5waTsfoawyJJOX7/fLKlcXjeho26d0arF0bbeyaHE9Krt1TPn4N1IqRX4kaqwhEvCC8AAavOm7ox2w3dGT8xNRhAOxVN8RXBsXsAuDSCkU/MHlEM
*/