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