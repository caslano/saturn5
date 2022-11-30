// Copyright (C) 2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Jeremiah Willcock
//           Andrew Lumsdaine

// Distributed version of the two-bit color map
#ifndef BOOST_DISTRIBUTED_TWO_BIT_COLOR_MAP_HPP
#define BOOST_DISTRIBUTED_TWO_BIT_COLOR_MAP_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/two_bit_color_map.hpp>
#include <boost/property_map/parallel/distributed_property_map.hpp>
#include <boost/property_map/parallel/local_property_map.hpp>

namespace boost {

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
class two_bit_color_map<local_property_map<ProcessGroup,GlobalMap,StorageMap> >
  : public parallel::distributed_property_map<ProcessGroup, GlobalMap,
                                              two_bit_color_map<StorageMap> >
{
  typedef two_bit_color_map<StorageMap> local_map;

  typedef parallel::distributed_property_map<ProcessGroup, GlobalMap, 
                                             local_map >
    inherited;

  typedef local_property_map<ProcessGroup, GlobalMap, StorageMap>
    index_map_type;

public:
  two_bit_color_map(std::size_t inital_size, 
                    const index_map_type& index = index_map_type())
    : inherited(index.process_group(),  index.global(),
                local_map(inital_size, index.base())) { }

  inherited&       base()       { return *this; }
  const inherited& base() const { return *this; }
};

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline two_bit_color_type
get(two_bit_color_map<local_property_map<ProcessGroup,GlobalMap,StorageMap> >
      const& pm,
    typename property_traits<GlobalMap>::key_type key)
{
  return get(pm.base(), key);
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline void
put(two_bit_color_map<local_property_map<ProcessGroup,GlobalMap,StorageMap> >
      const& pm, 
    typename property_traits<GlobalMap>::key_type key,
    two_bit_color_type value)
{
  put(pm.base(), key, value);
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
class two_bit_color_map<parallel::distributed_property_map<
                          ProcessGroup, GlobalMap, StorageMap> > 
  : public parallel::distributed_property_map<
             ProcessGroup, GlobalMap, two_bit_color_map<StorageMap> >
{
  typedef two_bit_color_map<StorageMap> local_map;

  typedef parallel::distributed_property_map<ProcessGroup,GlobalMap,local_map>
    inherited;

  typedef parallel::distributed_property_map<ProcessGroup, GlobalMap,  
                                             StorageMap>
    index_map_type;

public:
  two_bit_color_map(std::size_t inital_size, 
                    const index_map_type& index = index_map_type())
    : inherited(index.process_group(),  index.global(),
                local_map(inital_size, index.base())) { }

  inherited&       base()       { return *this; }
  const inherited& base() const { return *this; }
};

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline two_bit_color_type
get(two_bit_color_map<
      parallel::distributed_property_map<
        ProcessGroup, GlobalMap, two_bit_color_map<StorageMap> > > const& pm,
    typename property_traits<GlobalMap>::key_type key)
{
  return get(pm.base(), key);
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline void
put(two_bit_color_map<
      parallel::distributed_property_map<
        ProcessGroup, GlobalMap, two_bit_color_map<StorageMap> > > const& pm, 
    typename property_traits<GlobalMap>::key_type key,
    two_bit_color_type value)
{
  put(pm.base(), key, value);
}

} // end namespace boost

#endif // BOOST_DISTRIBUTED_TWO_BIT_COLOR_MAP_HPP

/* two_bit_color_map.hpp
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
*/