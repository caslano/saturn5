// Copyright (C) 2007 Douglas Gregor 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file contains code for the distributed adjacency list's
// initializations. It should not be included directly by users.

#ifndef BOOST_GRAPH_DISTRIBUTED_ADJLIST_INITIALIZE_HPP
#define BOOST_GRAPH_DISTRIBUTED_ADJLIST_INITIALIZE_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

namespace boost { 

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
template<typename EdgeIterator>
void
PBGL_DISTRIB_ADJLIST_TYPE::
initialize(EdgeIterator first, EdgeIterator last,
           vertices_size_type, const base_distribution_type& distribution, 
           vecS)
{
  process_id_type id = process_id(process_group_);
  while (first != last) {
    if ((process_id_type)distribution(first->first) == id) {
      vertex_descriptor source(id, distribution.local(first->first));
      vertex_descriptor target(distribution(first->second),
                               distribution.local(first->second));
      add_edge(source, target, *this);
    }
    ++first;
  }

  synchronize(process_group_);
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
template<typename EdgeIterator, typename EdgePropertyIterator>
void
PBGL_DISTRIB_ADJLIST_TYPE::
initialize(EdgeIterator first, EdgeIterator last,
           EdgePropertyIterator ep_iter,
           vertices_size_type, const base_distribution_type& distribution, 
           vecS)
{
  process_id_type id = process_id(process_group_);
  while (first != last) {
    if (static_cast<process_id_type>(distribution(first->first)) == id) {
      vertex_descriptor source(id, distribution.local(first->first));
      vertex_descriptor target(distribution(first->second),
                               distribution.local(first->second));
      add_edge(source, target, *ep_iter, *this);
    }
    ++first;
    ++ep_iter;
  }

  synchronize(process_group_);
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
template<typename EdgeIterator, typename EdgePropertyIterator,
         typename VertexListS>
void
PBGL_DISTRIB_ADJLIST_TYPE::
initialize(EdgeIterator first, EdgeIterator last,
           EdgePropertyIterator ep_iter,
           vertices_size_type n, const base_distribution_type& distribution,
           VertexListS)
{
  using boost::parallel::inplace_all_to_all;

  typedef vertices_size_type vertex_number_t;
  typedef typename std::iterator_traits<EdgePropertyIterator>::value_type
    edge_property_init_t;

  typedef std::pair<vertex_descriptor, vertex_number_t>
    st_pair;
  typedef std::pair<st_pair, edge_property_init_t> delayed_edge_t;

  process_group_type pg = process_group();
  process_id_type id = process_id(pg);

  // Vertex indices
  std::vector<local_vertex_descriptor> index_to_vertex;
  index_to_vertex.reserve(num_vertices(*this));
  BGL_FORALL_VERTICES_T(v, base(), inherited)
    index_to_vertex.push_back(v);

  // The list of edges we can't add immediately.
  std::vector<delayed_edge_t> delayed_edges;

  std::vector<std::vector<vertex_number_t> > descriptor_requests;
  descriptor_requests.resize(num_processes(pg));

  // Add all of the edges we can, up to the point where we run
  // into a descriptor we don't know.
  while (first != last) {
    if (distribution(first->first) == id) {
      if (distribution(first->second) != id) break;
      vertex_descriptor source
        (id, index_to_vertex[distribution.local(first->first)]);
      vertex_descriptor target
        (distribution(first->second),
         index_to_vertex[distribution.local(first->second)]);
      add_edge(source, target, *ep_iter, *this);
    }
    ++first;
    ++ep_iter;
  }

  // Queue all of the remaining edges and determine the set of
  // descriptors we need to know about.
  while (first != last) {
    if (distribution(first->first) == id) {
      vertex_descriptor source
        (id, index_to_vertex[distribution.local(first->first)]);
      process_id_type dest = distribution(first->second);
      if (dest != id) {
        descriptor_requests[dest]
          .push_back(distribution.local(first->second));
        // Compact request list if we need to
        if (descriptor_requests[dest].size() >
              distribution.block_size(dest, n)) {
          std::sort(descriptor_requests[dest].begin(),
                    descriptor_requests[dest].end());
          descriptor_requests[dest].erase(
            std::unique(descriptor_requests[dest].begin(),
                        descriptor_requests[dest].end()),
            descriptor_requests[dest].end());
        }
      }

      // Save the edge for later
      delayed_edges.push_back
        (delayed_edge_t(st_pair(source, first->second), *ep_iter));
    }
    ++first;
    ++ep_iter;
  }

  // Compact descriptor requests
  for (process_id_type dest = 0; dest < num_processes(pg); ++dest) {
    std::sort(descriptor_requests[dest].begin(),
              descriptor_requests[dest].end());
    descriptor_requests[dest].erase(
      std::unique(descriptor_requests[dest].begin(),
                  descriptor_requests[dest].end()),
      descriptor_requests[dest].end());
  }

  // Send out all of the descriptor requests
  std::vector<std::vector<vertex_number_t> > in_descriptor_requests;
  in_descriptor_requests.resize(num_processes(pg));
  inplace_all_to_all(pg, descriptor_requests, in_descriptor_requests);

  // Reply to all of the descriptor requests
  std::vector<std::vector<local_vertex_descriptor> >
    descriptor_responses;
  descriptor_responses.resize(num_processes(pg));
  for (process_id_type dest = 0; dest < num_processes(pg); ++dest) {
    for (std::size_t i = 0; i < in_descriptor_requests[dest].size(); ++i) {
      local_vertex_descriptor v =
        index_to_vertex[in_descriptor_requests[dest][i]];
      descriptor_responses[dest].push_back(v);
    }
    in_descriptor_requests[dest].clear();
  }
  in_descriptor_requests.clear();
  inplace_all_to_all(pg, descriptor_responses);

  // Add the queued edges
  for(typename std::vector<delayed_edge_t>::iterator i
        = delayed_edges.begin(); i != delayed_edges.end(); ++i) {
    process_id_type dest = distribution(i->first.second);
    local_vertex_descriptor tgt_local;
    if (dest == id) {
      tgt_local = index_to_vertex[distribution.local(i->first.second)];
    } else {
      std::vector<vertex_number_t>& requests = descriptor_requests[dest];
      typename std::vector<vertex_number_t>::iterator pos =
        std::lower_bound(requests.begin(), requests.end(),
                         distribution.local(i->first.second));
      tgt_local = descriptor_responses[dest][pos - requests.begin()];
    }
    add_edge(i->first.first, vertex_descriptor(dest, tgt_local),
             i->second, *this);
  }
  synchronize(process_group_);
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
template<typename EdgeIterator, typename VertexListS>
void
PBGL_DISTRIB_ADJLIST_TYPE::
initialize(EdgeIterator first, EdgeIterator last,
           vertices_size_type n, const base_distribution_type& distribution,
           VertexListS)
{
  using boost::parallel::inplace_all_to_all;

  typedef vertices_size_type vertex_number_t;

  typedef std::pair<vertex_descriptor, vertex_number_t> delayed_edge_t;

  process_group_type pg = process_group();
  process_id_type id = process_id(pg);

  // Vertex indices
  std::vector<local_vertex_descriptor> index_to_vertex;
  index_to_vertex.reserve(num_vertices(*this));
  BGL_FORALL_VERTICES_T(v, base(), inherited)
    index_to_vertex.push_back(v);

  // The list of edges we can't add immediately.
  std::vector<delayed_edge_t> delayed_edges;

  std::vector<std::vector<vertex_number_t> > descriptor_requests;
  descriptor_requests.resize(num_processes(pg));

  // Add all of the edges we can, up to the point where we run
  // into a descriptor we don't know.
  while (first != last) {
    if (distribution(first->first) == id) {
      if (distribution(first->second) != id) break;
      vertex_descriptor source
        (id, index_to_vertex[distribution.local(first->first)]);
      vertex_descriptor target
        (distribution(first->second),
         index_to_vertex[distribution.local(first->second)]);
      add_edge(source, target, *this);
    }
    ++first;
  }

  // Queue all of the remaining edges and determine the set of
  // descriptors we need to know about.
  while (first != last) {
    if (distribution(first->first) == id) {
      vertex_descriptor source
        (id, index_to_vertex[distribution.local(first->first)]);
      process_id_type dest = distribution(first->second);
      if (dest != id) {
        descriptor_requests[dest]
          .push_back(distribution.local(first->second));
        // Compact request list if we need to
        if (descriptor_requests[dest].size() >
              distribution.block_size(dest, n)) {
          std::sort(descriptor_requests[dest].begin(),
                    descriptor_requests[dest].end());
          descriptor_requests[dest].erase(
            std::unique(descriptor_requests[dest].begin(),
                        descriptor_requests[dest].end()),
            descriptor_requests[dest].end());
        }
      }

      // Save the edge for later
      delayed_edges.push_back(delayed_edge_t(source, first->second));
    }
    ++first;
  }

  // Compact descriptor requests
  for (process_id_type dest = 0; dest < num_processes(pg); ++dest) {
    std::sort(descriptor_requests[dest].begin(),
              descriptor_requests[dest].end());
    descriptor_requests[dest].erase(
      std::unique(descriptor_requests[dest].begin(),
                  descriptor_requests[dest].end()),
      descriptor_requests[dest].end());
  }

  // Send out all of the descriptor requests
  std::vector<std::vector<vertex_number_t> > in_descriptor_requests;
  in_descriptor_requests.resize(num_processes(pg));
  inplace_all_to_all(pg, descriptor_requests, in_descriptor_requests);

  // Reply to all of the descriptor requests
  std::vector<std::vector<local_vertex_descriptor> >
    descriptor_responses;
  descriptor_responses.resize(num_processes(pg));
  for (process_id_type dest = 0; dest < num_processes(pg); ++dest) {
    for (std::size_t i = 0; i < in_descriptor_requests[dest].size(); ++i) {
      local_vertex_descriptor v =
        index_to_vertex[in_descriptor_requests[dest][i]];
      descriptor_responses[dest].push_back(v);
    }
    in_descriptor_requests[dest].clear();
  }
  in_descriptor_requests.clear();
  inplace_all_to_all(pg, descriptor_responses);

  // Add the queued edges
  for(typename std::vector<delayed_edge_t>::iterator i
        = delayed_edges.begin(); i != delayed_edges.end(); ++i) {
    process_id_type dest = distribution(i->second);
    local_vertex_descriptor tgt_local;
    if (dest == id) {
      tgt_local = index_to_vertex[distribution.local(i->second)];
    } else {
      std::vector<vertex_number_t>& requests = descriptor_requests[dest];
      typename std::vector<vertex_number_t>::iterator pos =
        std::lower_bound(requests.begin(), requests.end(),
                         distribution.local(i->second));
      tgt_local = descriptor_responses[dest][pos - requests.begin()];
    }
    add_edge(i->first, vertex_descriptor(dest, tgt_local), *this);
  }
  synchronize(process_group_);
}

}   // end namespace boost

#endif // BOOST_GRAPH_DISTRIBUTED_ADJLIST_INITIALIZE_HPP

/* initialize.hpp
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
*/