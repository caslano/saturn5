// Copyright (C) 2006-2010 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Jeremiah Willcock
//           Andrew Lumsdaine

// Distributed version of the one-bit color map
#ifndef BOOST_DISTRIBUTED_ONE_BIT_COLOR_MAP_HPP
#define BOOST_DISTRIBUTED_ONE_BIT_COLOR_MAP_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/one_bit_color_map.hpp>
#include <boost/property_map/parallel/distributed_property_map.hpp>
#include <boost/property_map/parallel/local_property_map.hpp>

namespace boost {

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
class one_bit_color_map<local_property_map<ProcessGroup,GlobalMap,StorageMap> >
  : public parallel::distributed_property_map<ProcessGroup, GlobalMap,
                                              one_bit_color_map<StorageMap> >
{
  typedef one_bit_color_map<StorageMap> local_map;

  typedef parallel::distributed_property_map<ProcessGroup, GlobalMap, 
                                             local_map >
    inherited;

  typedef local_property_map<ProcessGroup, GlobalMap, StorageMap>
    index_map_type;

public:
  one_bit_color_map(std::size_t inital_size, 
                    const index_map_type& index = index_map_type())
    : inherited(index.process_group(),  index.global(),
                local_map(inital_size, index.base())) { }

  inherited&       base()       { return *this; }
  const inherited& base() const { return *this; }
};

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline one_bit_color_type
get(one_bit_color_map<local_property_map<ProcessGroup,GlobalMap,StorageMap> >
      const& pm,
    typename property_traits<GlobalMap>::key_type key)
{
  return get(pm.base(), key);
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline void
put(one_bit_color_map<local_property_map<ProcessGroup,GlobalMap,StorageMap> >
      const& pm, 
    typename property_traits<GlobalMap>::key_type key,
    one_bit_color_type value)
{
  put(pm.base(), key, value);
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
class one_bit_color_map<parallel::distributed_property_map<
                          ProcessGroup, GlobalMap, StorageMap> > 
  : public parallel::distributed_property_map<
             ProcessGroup, GlobalMap, one_bit_color_map<StorageMap> >
{
  typedef one_bit_color_map<StorageMap> local_map;

  typedef parallel::distributed_property_map<ProcessGroup,GlobalMap,local_map>
    inherited;

  typedef parallel::distributed_property_map<ProcessGroup, GlobalMap,  
                                             StorageMap>
    index_map_type;

public:
  one_bit_color_map(std::size_t inital_size, 
                    const index_map_type& index = index_map_type())
    : inherited(index.process_group(),  index.global(),
                local_map(inital_size, index.base())) { }

  inherited&       base()       { return *this; }
  const inherited& base() const { return *this; }
};

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline one_bit_color_type
get(one_bit_color_map<
      parallel::distributed_property_map<
        ProcessGroup, GlobalMap, one_bit_color_map<StorageMap> > > const& pm,
    typename property_traits<GlobalMap>::key_type key)
{
  return get(pm.base(), key);
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline void
put(one_bit_color_map<
      parallel::distributed_property_map<
        ProcessGroup, GlobalMap, one_bit_color_map<StorageMap> > > const& pm, 
    typename property_traits<GlobalMap>::key_type key,
    one_bit_color_type value)
{
  put(pm.base(), key, value);
}

} // end namespace boost

#endif // BOOST_DISTRIBUTED_ONE_BIT_COLOR_MAP_HPP

/* one_bit_color_map.hpp
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
*/