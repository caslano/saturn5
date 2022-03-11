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