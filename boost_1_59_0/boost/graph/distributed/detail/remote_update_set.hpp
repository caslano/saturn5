// Copyright (C) 2005-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DETAIL_REMOTE_UPDATE_SET_HPP
#define BOOST_GRAPH_DETAIL_REMOTE_UPDATE_SET_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/parallel/process_group.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <vector>
#include <boost/assert.hpp>
#include <boost/optional.hpp>
#include <queue>

namespace boost { namespace graph { namespace detail {

template<typename ProcessGroup>
void do_synchronize(ProcessGroup& pg)
{ 
  using boost::parallel::synchronize;
  synchronize(pg);
}

struct remote_set_queued {};
struct remote_set_immediate {};

template<typename ProcessGroup>
class remote_set_semantics
{
  BOOST_STATIC_CONSTANT
    (bool, 
     queued = (is_convertible<
                 typename ProcessGroup::communication_category,
                 boost::parallel::bsp_process_group_tag>::value));

 public:
  typedef typename mpl::if_c<queued, 
                             remote_set_queued, 
                             remote_set_immediate>::type type;
};


template<typename Derived, typename ProcessGroup, typename Value,
         typename OwnerMap,
         typename Semantics = typename remote_set_semantics<ProcessGroup>::type>
class remote_update_set;

/**********************************************************************
 * Remote updating set that queues messages until synchronization     *
 **********************************************************************/
template<typename Derived, typename ProcessGroup, typename Value,
         typename OwnerMap>
class remote_update_set<Derived, ProcessGroup, Value, OwnerMap,
                        remote_set_queued>
{
  typedef typename property_traits<OwnerMap>::key_type Key;
  typedef std::vector<std::pair<Key, Value> > Updates;
  typedef typename Updates::size_type   updates_size_type;
  typedef typename Updates::value_type  updates_pair_type;

public:

private:
  typedef typename ProcessGroup::process_id_type process_id_type;

  enum message_kind {
    /** Message containing the number of updates that will be sent in
     *  a msg_updates message that will immediately follow. This
     *  message will contain a single value of type
     *  updates_size_type. 
     */
    msg_num_updates,

    /** Contains (key, value) pairs with all of the updates from a
     *  particular source. The number of updates is variable, but will
     *  be provided in a msg_num_updates message that immediately
     *  preceeds this message.
     *
     */
    msg_updates
  };

  struct handle_messages
  {
    explicit 
    handle_messages(remote_update_set* self, const ProcessGroup& pg)
      : self(self), update_sizes(num_processes(pg), 0) { }

    void operator()(process_id_type source, int tag) 
    { 
      switch(tag) {
      case msg_num_updates:
        {
          // Receive the # of updates
          updates_size_type num_updates;
          receive(self->process_group, source, tag, num_updates);

          update_sizes[source] = num_updates;
        }
        break;

      case msg_updates:
        {
          updates_size_type num_updates = update_sizes[source];
          BOOST_ASSERT(num_updates);

          // Receive the actual updates
          std::vector<updates_pair_type> updates(num_updates);
          receive(self->process_group, source, msg_updates, &updates[0],
                  num_updates);
          
          // Send updates to derived "receive_update" member
          Derived* derived = static_cast<Derived*>(self);
          for (updates_size_type u = 0; u < num_updates; ++u)
            derived->receive_update(source, updates[u].first, updates[u].second);

          update_sizes[source] = 0;
        }
        break;
      };
    }

  private:
    remote_update_set* self;
    std::vector<updates_size_type> update_sizes;
  };
  friend struct handle_messages;

 protected:
  remote_update_set(const ProcessGroup& pg, const OwnerMap& owner)
    : process_group(pg, handle_messages(this, pg)),
      updates(num_processes(pg)), owner(owner) { 
    }


  void update(const Key& key, const Value& value)
  { 
    if (get(owner, key) == process_id(process_group)) {
      Derived* derived = static_cast<Derived*>(this);
      derived->receive_update(get(owner, key), key, value);
    }
    else {
      updates[get(owner, key)].push_back(std::make_pair(key, value));
    }
  }

  void collect() { }

  void synchronize()
  {
    // Emit all updates and then remove them
    process_id_type num_processes = updates.size();
    for (process_id_type p = 0; p < num_processes; ++p) {
      if (!updates[p].empty()) {
        send(process_group, p, msg_num_updates, updates[p].size());
        send(process_group, p, msg_updates, 
             &updates[p].front(), updates[p].size());
        updates[p].clear();
      }
    }
    
    do_synchronize(process_group);
  }

  ProcessGroup process_group;

 private:
  std::vector<Updates> updates;
  OwnerMap owner;
};

/**********************************************************************
 * Remote updating set that sends messages immediately                *
 **********************************************************************/
template<typename Derived, typename ProcessGroup, typename Value,
         typename OwnerMap>
class remote_update_set<Derived, ProcessGroup, Value, OwnerMap,
                        remote_set_immediate>
{
  typedef typename property_traits<OwnerMap>::key_type Key;
  typedef std::pair<Key, Value> update_pair_type;
  typedef typename std::vector<update_pair_type>::size_type updates_size_type;

public:
  typedef typename ProcessGroup::process_id_type process_id_type;

private:
  enum message_kind {
    /** Contains a (key, value) pair that will be updated. */
    msg_update
  };

  struct handle_messages
  {
    explicit handle_messages(remote_update_set* self, const ProcessGroup& pg) 
      : self(self)
    { update_sizes.resize(num_processes(pg), 0); }

    void operator()(process_id_type source, int tag) 
    { 
      // Receive the # of updates
      BOOST_ASSERT(tag == msg_update);
      update_pair_type update;
      receive(self->process_group, source, tag, update);
      
      // Send update to derived "receive_update" member
      Derived* derived = static_cast<Derived*>(self);
      derived->receive_update(source, update.first, update.second);
    }

  private:
    std::vector<updates_size_type> update_sizes;
    remote_update_set* self;
  };
  friend struct handle_messages;

 protected:
  remote_update_set(const ProcessGroup& pg, const OwnerMap& owner)
    : process_group(pg, handle_messages(this, pg)), owner(owner) { }

  void update(const Key& key, const Value& value)
  { 
    if (get(owner, key) == process_id(process_group)) {
      Derived* derived = static_cast<Derived*>(this);
      derived->receive_update(get(owner, key), key, value);
    }
    else
      send(process_group, get(owner, key), msg_update, 
           update_pair_type(key, value));
  }

  void collect() 
  { 
    typedef std::pair<process_id_type, int> probe_type;
    handle_messages handler(this, process_group);
    while (optional<probe_type> stp = probe(process_group))
      if (stp->second == msg_update) handler(stp->first, stp->second);
  }

  void synchronize()
  {
    do_synchronize(process_group);
  }

  ProcessGroup process_group;
  OwnerMap owner;
};

} } } // end namespace boost::graph::detail

#endif // BOOST_GRAPH_DETAIL_REMOTE_UPDATE_SET_HPP

/* remote_update_set.hpp
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
*/