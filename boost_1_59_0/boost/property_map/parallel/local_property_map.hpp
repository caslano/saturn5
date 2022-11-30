// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

// The placement of this #include probably looks very odd relative to
// the #ifndef/#define pair below. However, this placement is
// extremely important to allow the various property map headers to be
// included in any order.
#include <boost/property_map/property_map.hpp>

#ifndef BOOST_PARALLEL_LOCAL_PROPERTY_MAP_HPP
#define BOOST_PARALLEL_LOCAL_PROPERTY_MAP_HPP

#include <boost/assert.hpp>

namespace boost {
  /** Property map that accesses an underlying, local property map
   * using a subset of the global keys.
   */
  template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
  class local_property_map
  {
    typedef typename property_traits<GlobalMap>::value_type owner_local_pair;

  public:
    typedef ProcessGroup                                   process_group_type;
    typedef typename property_traits<StorageMap>::value_type value_type;
    typedef typename property_traits<GlobalMap>::key_type key_type;
    typedef typename property_traits<StorageMap>::reference  reference;
    typedef typename property_traits<StorageMap>::category   category;

    local_property_map() { }

    local_property_map(const ProcessGroup& process_group,
                       const GlobalMap& global, const StorageMap& storage)
      : process_group_(process_group), global_(global), storage(storage) { }

    reference operator[](const key_type& key)
    {
      owner_local_pair p = get(global_, key);
      BOOST_ASSERT(p.first == process_id(process_group_));
      return storage[p.second];
    }

    GlobalMap& global() const { return global_; }
    StorageMap& base() const { return storage; }

    ProcessGroup&       process_group()       { return process_group_; }
    const ProcessGroup& process_group() const { return process_group_; }

  private:
    ProcessGroup process_group_;
    mutable GlobalMap global_;
    mutable StorageMap storage;
  };

  template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
  inline
  typename local_property_map<ProcessGroup, GlobalMap, StorageMap>::reference
  get(const local_property_map<ProcessGroup, GlobalMap, StorageMap>& pm,
      typename local_property_map<ProcessGroup, GlobalMap, StorageMap>::key_type
        const & key)

  {
    typename property_traits<GlobalMap>::value_type p = get(pm.global(), key);
    return get(pm.base(), p.second);
  }

  template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
  inline void
  put(const local_property_map<ProcessGroup, GlobalMap, StorageMap>& pm,
      typename local_property_map<ProcessGroup, GlobalMap, StorageMap>
                 ::key_type const & key,
      typename local_property_map<ProcessGroup, GlobalMap, StorageMap>
                 ::value_type const& v)
  {
    typename property_traits<GlobalMap>::value_type p = get(pm.global(), key);
    BOOST_ASSERT(p.first == process_id(pm.process_group()));
    put(pm.base(), p.second, v);
  }
} // end namespace boost
#endif // BOOST_PARALLEL_LOCAL_PROPERTY_MAP_HPP

/* local_property_map.hpp
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
*/