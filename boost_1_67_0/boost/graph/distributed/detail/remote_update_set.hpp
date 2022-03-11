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