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
ntbeLTdmiSe58lfO3ngcw7Su0JdbFO/8IJq5Y50ZM+JgRTDUHvTf+Z23n9KkiAPzH3QQnwXU7iOMClTTW7GQrU8caveT0ujmjFUpG4N9JtZh5H8Y1o4dZW7Bzqn6rN0HQfNS45ygsg5qoAGLi/vW70MKq0f8PDMQ62e588GRzciZn7kXwTvtPajfarUgSGfHBcYVHlOHESLh5PrW1maCX4m3LVRzFLGMEmfDWs5Qf+uK/GkornS1VBj+/AfUj32KD14cVv+1At6TXLnrExqOz53iqQth3T3CTx6HoK/dDtXhXbtk5khpZHIqXtwJqvG/TAyhp4Te7/ggXoq47yMAzUa2Dx58mjxFfih/4n/o6XvDKjMS8DR0J86ns0VhbWk3JHSsuUvR5jgALYBwb6CaF+BBm09WDZQGBOlXL5Ewu6D+CGNE3j8RZ//vwMGLNZRajJ6sjV8o9V36Fi+Sqem0gvx8AkpeSDWZ6HD/G5Ktmai6iAfuJOFsUaKRYPeODTiJoRpSSypK8WqY6GuJOVj3Izd00fchJ8xhUqMbR3tECqRkiRLPVA0gLmnNpA==
*/