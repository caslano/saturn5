// Copyright 2004, 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Nick Edmonds
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DISTRIBUTED_RMAT_GENERATOR_HPP
#define BOOST_GRAPH_DISTRIBUTED_RMAT_GENERATOR_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/assert.hpp>
#include <boost/graph/parallel/algorithm.hpp>
#include <boost/graph/parallel/process_group.hpp>
#include <math.h>

namespace boost {

  // Memory-scalable (amount of memory required will scale down
  // linearly as the number of processes increases) generator, which
  // requires an MPI process group.  Run-time is slightly worse than
  // the unique rmat generator.  Edge list generated is sorted and
  // unique.
  template<typename ProcessGroup, typename Distribution, 
           typename RandomGenerator, typename Graph>
  class scalable_rmat_iterator
  {
      typedef typename graph_traits<Graph>::directed_category directed_category;
      typedef typename graph_traits<Graph>::vertices_size_type vertices_size_type;
      typedef typename graph_traits<Graph>::edges_size_type edges_size_type;

  public:
      typedef std::input_iterator_tag iterator_category;
      typedef std::pair<vertices_size_type, vertices_size_type> value_type;
      typedef const value_type& reference;
      typedef const value_type* pointer;
      typedef void difference_type;

      // No argument constructor, set to terminating condition
      scalable_rmat_iterator()
        : gen(), done(true)
      { }

      // Initialize for edge generation
      scalable_rmat_iterator(ProcessGroup pg, Distribution distrib,
                             RandomGenerator& gen, vertices_size_type n, 
                             edges_size_type m, double a, double b, double c, 
                             double d, bool permute_vertices = true)
          : gen(), done(false)
      {
          BOOST_ASSERT(a + b + c + d == 1);
          int id = process_id(pg);

          this->gen.reset(new uniform_01<RandomGenerator>(gen));

          std::vector<vertices_size_type> vertexPermutation;
          if (permute_vertices) 
              generate_permutation_vector(gen, vertexPermutation, n);

          int SCALE = int(floor(log(double(n))/log(2.)));
          boost::uniform_01<RandomGenerator> prob(gen);
      
          std::map<value_type, bool> edge_map;

          edges_size_type generated = 0, local_edges = 0;
          do {
              edges_size_type tossed = 0;
              do {
                  vertices_size_type u, v;
                  boost::tie(u, v) = generate_edge(this->gen, n, SCALE, a, b, c, d);

                  if (permute_vertices) {
                      u = vertexPermutation[u];
                      v = vertexPermutation[v];
                  }

                  // Lowest vertex number always comes first (this
                  // means we don't have to worry about i->j and j->i
                  // being in the edge list)
                  if (u > v && is_same<directed_category, undirected_tag>::value)
                      std::swap(u, v);

                  if (distrib(u) == id || distrib(v) == id) {
                      if (edge_map.find(std::make_pair(u, v)) == edge_map.end()) {
                          edge_map[std::make_pair(u, v)] = true;
                          local_edges++;
                      } else {
                          tossed++;

                          // special case - if both u and v are on same
                          // proc, ++ twice, since we divide by two (to
                          // cover the two process case)
                          if (distrib(u) == id && distrib(v) == id)
                              tossed++;
                      }
                  }
                  generated++;

              } while (generated < m);
              tossed = all_reduce(pg, tossed, boost::parallel::sum<vertices_size_type>());
              generated -= (tossed / 2);
          } while (generated < m);
          // NGE - Asking for more than n^2 edges will result in an infinite loop here
          //       Asking for a value too close to n^2 edges may as well

          values.reserve(local_edges);
          typename std::map<value_type, bool>::reverse_iterator em_end = edge_map.rend();
          for (typename std::map<value_type, bool>::reverse_iterator em_i = edge_map.rbegin();
               em_i != em_end ;
               ++em_i) {
              values.push_back(em_i->first);
          }

          current = values.back();
          values.pop_back();
      }

      reference operator*() const { return current; }
      pointer operator->() const { return &current; }
    
      scalable_rmat_iterator& operator++()
      {
          if (!values.empty()) {
              current = values.back();
              values.pop_back();
          } else 
              done = true;

          return *this;
      }

      scalable_rmat_iterator operator++(int)
      {
          scalable_rmat_iterator temp(*this);
          ++(*this);
          return temp;
      }

      bool operator==(const scalable_rmat_iterator& other) const
      {
          return values.empty() && other.values.empty() && done && other.done;
      }

      bool operator!=(const scalable_rmat_iterator& other) const
      { return !(*this == other); }

  private:

      // Parameters
      shared_ptr<uniform_01<RandomGenerator> > gen;

      // Internal data structures
      std::vector<value_type> values;
      value_type              current;
      bool                    done;
  };

} // end namespace boost

#endif // BOOST_GRAPH_DISTRIBUTED_RMAT_GENERATOR_HPP

/* rmat_graph_generator.hpp
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
*/