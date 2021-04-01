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
A6WUth702GpyDwW2v0gzaJnLC9jyWHqBiWBQYcOLjcnLFW7mF+nCTXInQHoyTnBOaTx7dWsM9w7egsrgGOImF5uVKIlv1AxZBMdyqIp8DOVp+g/3IMJEonADWSh8HArhnSZ3QYmJv3m93eH9+zvHKjWQtkvP4fT+ERxqqKZPyowthOVn/lUYBSr5AYSC8zm4jbofmpmKJWsWK9hx4k3W/0FZOvUp60Nd0AvKtS7H/eBTRkiQXNXSJgK9RuYSYvVPa6vpPbcKH15IcP2+pr3EsFNENjD8OQWpdn9okCJwoZilg/6keqIyno9Am8cdS6O1CzEPGqQOk6WrCUDFjM02im+XDENDmUXUorsuYLoyCqKRDlS1DpKYHPzyRErXqGE2aMEaabdOH9U34tUQACcbvrUY4vo5cjh+sE+28sX0hoiQJmYkt5qWdfHE4UMUjma93Pd3Cbf8l55QdeBe3FP+XDaz2YRDlHE+s1CfXNksqC4dKjcOm3A3ZRoh9QveEKgiN/OWuC7rSFZ7+TpX+oVLY98O8zJG/5jKLbQGQjhpC7C7sSEnF4LTLW4bBQ==
*/