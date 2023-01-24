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
PUZx+KmeWRzuuGIUhzpXqAspjnyZSfoFSQv/EvQLksrzZb6yat7Fxzz5Dk/O48lcnnyBJ5/lyZE8+TBPPsCTPXgywVoJX2b8o5ovMy9Qf0/YN8b+nn/CtP6eBR9Tf4+6fo66fM7U1nf5nK3NunyWKaQYR6QYx7p8imcwThyicmIHJf5rbFEGOEfk67p8HvhTY0SRLXapBCOer1Ox7u2sE0D3Rvo7Qw9yZ2h5HT9GbFwFZygjlOtgHwF1cFpdroNP172VDhoZ0VmX62DbuiojLmTOkDW0fEbUxRI/1jarQNPLRhWwXWaMGMdgabRaY8RBctJ0Jer78pLGiMm3YMSBtSt2UTvWDoDKBX9n6Bh3hurV9mPEZZVwhk6FcDTyb2IrXq7N0The+1auqZERV9fmaCytrTJiS+YMTQypgBFTI82M+M5FIyNKFxkjxrFmXwicJ60izdMTYxwSI/wTsWMsEGPYSiNtxlF9Opl9onsUnyiu5A+1p6e+0tPz3DTuEwUxn2iW6hPN8veJ5hh9orsjmE9UZIyG1P6f6aZwqLWi/w3VuUQjNur7f8qM+l+pYOh8rYrd7p21Akjax/4e0Xxd/08tP/0fXgWPKCNIp///oKRMs+n031a1+UNOm07/bar+H2EekTWoUsHQjxF++n/BpP8XdMFQutzoG03/RTnpJVX//6i8/kdUPLrZMSIAKm39PaIm3COqF+Gn/79X
*/