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
K0UqW0YJSnh7Dl4+D1gAzL+OXgsNCzN0Xyp05ci7n1JyflxDEqEa2spnHAutugsy1vH3FSqp4mPsK3/95wrlWJ0yYX/SpspnsaUhYuYqwEVOsx5AfZPzF2Nei4RHSf/hts5teb1l45UonYdeq1DTafW/ADVLhCXztJOWIOZYBtwA1ACM1oIqMCbuqRLzLR1WoFUVcnUYA++xBCgXkOX7wa9A+lOI5wt/KUU/pWKePJblzsR4VlGRafvS7cBSwWOYYxltQ1wFeV8gh9kGNCO/APz5gsfMLaKc56oxDodYm2prfW5FXASJlZZOeV7uMw4aFPp0mFxP1WL+xcT7LrHaVoibHX6v4xA6ucEa61z1VyTIBfKn0N3XoG6LdqdQ/yykgx626NuCJumMoFez6JTdVVQbjhkFcJwBBcqf4tYWK+5QvEgpTpEiwUpxCQ5Bg41SvLi7F3d3KBocgrs7IUggkMnZ2R62s5093u/te/yd+3ArsZ5YQqRqfqQR1Q/vdvN/cRCDxDe4lxlYJWeQWRUZJG2aVjvaBTT9ubAQvqykbmWQj+uTdZw3SDiVHeb5ujMVw53YXfcFTSuhcAsgUeQzq0dQN0F5q/5ATqFn4Xngwu2MVPl6Z80I+uIGtd3HDCL4ciAYFfW7dhR593Ow0dfxQ47T9Arc/kGjLfjLE1chWF7g8MhjMTNE6s9kDrk9Opv2MZ9sImKwi4/VsWJE
*/