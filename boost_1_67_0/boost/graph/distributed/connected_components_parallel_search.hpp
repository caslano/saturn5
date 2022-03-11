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