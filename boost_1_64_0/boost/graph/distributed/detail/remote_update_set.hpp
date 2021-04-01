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
Sji64YraPpTkezNO6hWARx+nKhCony8kUxXcxNp2m7eu0UHdOkz/8HFLQh0y4SjeMKazzrMmkvqCJzwozACf+m4UX6TCp+HB60prBwIqh7vPOFQK75ZwMqIVTUD9MtKFcwzWbAtHs+PkHXVPBxVPQgeWikq8XIm6Pfi3TQIuZYJ47ovHjg996DZaNSY5kcVvQHaesuBxDG6UOs8KdIC+KLQELd6NDslkNcZfZdx2H+SBI+pdDP/FgyuCsuqq+ZwRSOesjMA0ostq9pFF0taOU3lTV05yZC/bTRNGrbtOj2/eVjLr6b5pdnyO31C5dzAeyXeI444tR1gh7jnb6wx+UpO1VbXFQMDaZydmICHx0+55i+MGfFeqfch92sLJ8dAMdMzWR01BarrAQs7OHnDQIML/X7Ak2sKrCtbzgNRLoJTgV3EK3mztVWSa7mi5h4HwA9Glkx8m94J8RDxJP8drAd9KG2SVt9Px7J2mYAka3e6bpr1EIBOzX6qwPypKsrJrg50XzwsKkCa7Rugrp4fUEcgxhBTX9o0QSfBRIFqoYbLDPxmFRHPGsVg28w==
*/