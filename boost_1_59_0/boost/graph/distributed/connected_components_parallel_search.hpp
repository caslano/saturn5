// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Brian Barrett
//           Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_PARALLEL_CC_PS_HPP
#define BOOST_GRAPH_PARALLEL_CC_PS_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/assert.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/parallel/algorithm.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/graph/distributed/concepts.hpp>
#include <boost/graph/parallel/properties.hpp>
#include <boost/graph/parallel/process_group.hpp>
#include <boost/optional.hpp>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#include <map>
#include <boost/graph/parallel/container_traits.hpp>
#include <boost/graph/iteration_macros.hpp>


// Connected components algorithm based on a parallel search.
//
// Every N nodes starts a parallel search from the first vertex in
// their local vertex list during the first superstep (the other nodes
// remain idle during the first superstep to reduce the number of
// conflicts in numbering the components).  At each superstep, all new
// component mappings from remote nodes are handled.  If there is no
// work from remote updates, a new vertex is removed from the local
// list and added to the work queue.
//
// Components are allocated from the component_value_allocator object,
// which ensures that a given component number is unique in the
// system, currently by using the rank and number of processes to
// stride allocations.
//
// When two components are discovered to actually be the same
// component, a mapping is created in the collisions object.  The
// lower component number is prefered in the resolution, so component
// numbering resolution is consistent.  After the search has exhausted
// all vertices in the graph, the mapping is shared with all
// processes, and they independently resolve the comonent mapping (so
// O((N * NP) + (V * NP)) work, in O(N + V) time, where N is the
// number of mappings and V is the number of local vertices).  This
// phase can likely be significantly sped up if a clever algorithm for
// the reduction can be found.
namespace boost { namespace graph { namespace distributed {
  namespace cc_ps_detail {
    // Local object for allocating component numbers.  There are two
    // places this happens in the code, and I was getting sick of them
    // getting out of sync.  Components are not tightly packed in
    // numbering, but are numbered to ensure each rank has its own
    // independent sets of numberings.
    template<typename component_value_type>
    class component_value_allocator {
    public:
      component_value_allocator(int num, int size) :
        last(0), num(num), size(size)
      {
      }

      component_value_type allocate(void)
      {
        component_value_type ret = num + (last * size);
        last++;
        return ret;
      }

    private:
      component_value_type last;
      int num;
      int size;
    };


    // Map of the "collisions" between component names in the global
    // component mapping.  TO make cleanup easier, component numbers
    // are added, pointing to themselves, when a new component is
    // found.  In order to make the results deterministic, the lower
    // component number is always taken.  The resolver will drill
    // through the map until it finds a component entry that points to
    // itself as the next value, allowing some cleanup to happen at
    // update() time.  Attempts are also made to update the mapping
    // when new entries are created.
    //
    // Note that there's an assumption that the entire mapping is
    // shared during the end of the algorithm, but before component
    // name resolution.
    template<typename component_value_type>
    class collision_map {
    public:
      collision_map() : num_unique(0)
      {
      }

      // add new component mapping first time component is used.  Own
      // function only so that we can sanity check there isn't already
      // a mapping for that component number (which would be bad)
      void add(const component_value_type &a) 
      {
        BOOST_ASSERT(collisions.count(a) == 0);
        collisions[a] = a;
      }

      // add a mapping between component values saying they're the
      // same component
      void add(const component_value_type &a, const component_value_type &b)
      {
        component_value_type high, low, tmp;
        if (a > b) {
          high = a;
          low = b;
        } else {
          high = b;
          low = a;
        }

        if (collisions.count(high) != 0 && collisions[high] != low) {
          tmp = collisions[high];
          if (tmp > low) {
            collisions[tmp] = low;
            collisions[high] = low;
          } else {
            collisions[low] = tmp;
            collisions[high] = tmp;
          }
        } else {
          collisions[high] = low;
        }

      }

      // get the "real" component number for the given component.
      // Used to resolve mapping at end of run.
      component_value_type update(component_value_type a)
      {
        BOOST_ASSERT(num_unique > 0);
        BOOST_ASSERT(collisions.count(a) != 0);
        return collisions[a];
      }

      // collapse the collisions tree, so that update is a one lookup
      // operation.  Count unique components at the same time.
      void uniqify(void)
      {
        typename std::map<component_value_type, component_value_type>::iterator i, end;

        end = collisions.end();
        for (i = collisions.begin() ; i != end ; ++i) {
          if (i->first == i->second) {
            num_unique++;
          } else {
            i->second = collisions[i->second];
          }
        }
      }

      // get the number of component entries that have an associated
      // component number of themselves, which are the real components
      // used in the final mapping.  This is the number of unique
      // components in the graph.
      int unique(void)
      {
        BOOST_ASSERT(num_unique > 0);
        return num_unique;
      }

      // "serialize" into a vector for communication.
      std::vector<component_value_type> serialize(void)
      {
        std::vector<component_value_type> ret;
        typename std::map<component_value_type, component_value_type>::iterator i, end;

        end = collisions.end();
        for (i = collisions.begin() ; i != end ; ++i) {
          ret.push_back(i->first);
          ret.push_back(i->second);
        }

        return ret;
      }

    private:
      std::map<component_value_type, component_value_type> collisions;
      int num_unique;
    };


    // resolver to handle remote updates.  The resolver will add
    // entries into the collisions map if required, and if it is the
    // first time the vertex has been touched, it will add the vertex
    // to the remote queue.  Note that local updates are handled
    // differently, in the main loop (below).

      // BWB - FIX ME - don't need graph anymore - can pull from key value of Component Map.
    template<typename ComponentMap, typename work_queue>
    struct update_reducer {
      BOOST_STATIC_CONSTANT(bool, non_default_resolver = false);

      typedef typename property_traits<ComponentMap>::value_type component_value_type;
      typedef typename property_traits<ComponentMap>::key_type vertex_descriptor;

      update_reducer(work_queue *q,
                     cc_ps_detail::collision_map<component_value_type> *collisions, 
                     processor_id_type pg_id) :
        q(q), collisions(collisions), pg_id(pg_id)
      {
      }

      // ghost cell initialization routine.  This should never be
      // called in this imlementation.
      template<typename K>
      component_value_type operator()(const K&) const
      { 
        return component_value_type(0); 
      }

      // resolver for remote updates.  I'm not entirely sure why, but
      // I decided to not change the value of the vertex if it's
      // already non-infinite.  It doesn't matter in the end, as we'll
      // touch every vertex in the cleanup phase anyway.  If the
      // component is currently infinite, set to the new component
      // number and add the vertex to the work queue.  If it's not
      // infinite, we've touched it already so don't add it to the
      // work queue.  Do add a collision entry so that we know the two
      // components are the same.
      component_value_type operator()(const vertex_descriptor &v,
                                      const component_value_type& current,
                                      const component_value_type& update) const
      {
        const component_value_type max = (std::numeric_limits<component_value_type>::max)();
        component_value_type ret = current;

        if (max == current) {
          q->push(v);
          ret = update;
        } else if (current != update) {
          collisions->add(current, update);
        }

        return ret;
      }                                    

      // So for whatever reason, the property map can in theory call
      // the resolver with a local descriptor in addition to the
      // standard global descriptor.  As far as I can tell, this code
      // path is never taken in this implementation, but I need to
      // have this code here to make it compile.  We just make a
      // global descriptor and call the "real" operator().
      template<typename K>
      component_value_type operator()(const K& v, 
                                      const component_value_type& current, 
                                      const component_value_type& update) const
      {
          return (*this)(vertex_descriptor(pg_id, v), current, update);
      }

    private:
      work_queue *q;
      collision_map<component_value_type> *collisions;
      boost::processor_id_type pg_id;
    };

  } // namespace cc_ps_detail


  template<typename Graph, typename ComponentMap>
  typename property_traits<ComponentMap>::value_type
  connected_components_ps(const Graph& g, ComponentMap c)
  {
    using boost::graph::parallel::process_group;

    typedef typename property_traits<ComponentMap>::value_type component_value_type;
    typedef typename graph_traits<Graph>::vertex_iterator vertex_iterator;
    typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;
    typedef typename boost::graph::parallel::process_group_type<Graph>
      ::type process_group_type;
    typedef typename process_group_type::process_id_type process_id_type;
    typedef std::queue<vertex_descriptor> work_queue;

    static const component_value_type max_component = 
      (std::numeric_limits<component_value_type>::max)();
    typename property_map<Graph, vertex_owner_t>::const_type
      owner = get(vertex_owner, g);

    // standard who am i? stuff
    process_group_type pg = process_group(g);
    process_id_type id = process_id(pg);

    // Initialize every vertex to have infinite component number
    BGL_FORALL_VERTICES_T(v, g, Graph) put(c, v, max_component);

    vertex_iterator current, end;
    boost::tie(current, end) = vertices(g);

    cc_ps_detail::component_value_allocator<component_value_type> cva(process_id(pg), num_processes(pg));
    cc_ps_detail::collision_map<component_value_type> collisions;
    work_queue q;  // this is intentionally a local data structure
    c.set_reduce(cc_ps_detail::update_reducer<ComponentMap, work_queue>(&q, &collisions, id));

    // add starting work
    while (true) {
        bool useful_found = false;
        component_value_type val = cva.allocate();
        put(c, *current, val);
        collisions.add(val);
        q.push(*current);
        if (0 != out_degree(*current, g)) useful_found = true;
        ++current;
        if (useful_found) break;
    }

    // Run the loop until everyone in the system is done
    bool global_done = false;
    while (!global_done) {

      // drain queue of work for this superstep
      while (!q.empty()) {
        vertex_descriptor v = q.front();
        q.pop();
        // iterate through outedges of the vertex currently being
        // examined, setting their component to our component.  There
        // is no way to end up in the queue without having a component
        // number already.

        BGL_FORALL_ADJ_T(v, peer, g, Graph) {
          component_value_type my_component = get(c, v);

          // update other vertex with our component information.
          // Resolver will handle remote collisions as well as whether
          // to put the vertex on the work queue or not.  We have to
          // handle local collisions and work queue management
          if (id == get(owner, peer)) {
            if (max_component == get(c, peer)) {
              put(c, peer, my_component);
              q.push(peer);
            } else if (my_component != get(c, peer)) {
              collisions.add(my_component, get(c, peer));
            }
          } else {
            put(c, peer, my_component);
          }
        }
      }

      // synchronize / start a new superstep.
      synchronize(pg);
      global_done = all_reduce(pg, (q.empty() && (current == end)), boost::parallel::minimum<bool>());

      // If the queue is currently empty, add something to do to start
      // the current superstep (supersteps start at the sync, not at
      // the top of the while loop as one might expect).  Down at the
      // bottom of the while loop so that not everyone starts the
      // algorithm with something to do, to try to reduce component
      // name conflicts
      if (q.empty()) {
        bool useful_found = false;
        for ( ; current != end && !useful_found ; ++current) {
          if (max_component == get(c, *current)) {
            component_value_type val = cva.allocate();
            put(c, *current, val);
            collisions.add(val);
            q.push(*current);
            if (0 != out_degree(*current, g)) useful_found = true;
          }
        }
      }
    }

    // share component mappings
    std::vector<component_value_type> global;
    std::vector<component_value_type> mine = collisions.serialize();
    all_gather(pg, mine.begin(), mine.end(), global);
    for (size_t i = 0 ; i < global.size() ; i += 2) {
      collisions.add(global[i], global[i + 1]);
    }
    collisions.uniqify();

    // update the component mappings
    BGL_FORALL_VERTICES_T(v, g, Graph) {
      put(c, v, collisions.update(get(c, v)));
    }

    return collisions.unique();
  }

} // end namespace distributed

} // end namespace graph

} // end namespace boost

#endif // BOOST_GRAPH_PARALLEL_CC_HPP

/* connected_components_parallel_search.hpp
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
*/