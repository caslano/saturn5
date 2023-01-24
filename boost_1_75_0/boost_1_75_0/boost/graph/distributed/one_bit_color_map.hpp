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
XhvxPz0fgY7faEpCMS74CRos75LXC3LCkL5dfJWEuLOipfUzZe453XyLh4PsuyNA3DrfxC/JpHZ3vpkJbe/L4oEsYbgVPgfmcE8wZq7FzGvw6lB8jYrczNx0Bckvz0OuVsyVh4u+hB6wecLWoBo4rT0D0K2dacCi6Qoef0WcbYhzBylGW+cdmeju6Tw1H932zmPEbe0cQ+LPdI6gbhBxj3f+PC+g2LuBZO55X7HTkHgvEj/cj5k7Og/PE4h+SN1/BCK3AMokgtwHvtGIvPkkIG+kyBsp0jrq1l2N/MU5H/Jx8O1eeQqQMylyJkW6k7qzrkZ+aRD5GUTuRuTxFHk8RRpF3ZCrkYsGke9CZBkin7wsZD45VyBylLoH5grxjTT8DnXfnBtA9BD2/yDRYCS68DT2PyW6hiKtpK6dEi2n4SLqLrya6Ls9PqI7wLe7A4n+kRL941yha/9A3cmU6AQaDqPusLlXVd86SPRuJFp+Boie+lnIfCqDyhF1D2YI8Xtp+F3q/i3jKqLyQaIhSLQXia4lRBs61xKk7Z2riLuz0xGAvH4lWu0tntYfffj7f0Rp+BzwEyh+AsU3UXzVNfA3DuI/jPjdiB+M+PW78dbsIEStfxW9F9PRi3eZdXanBxDCXVpATxokZEJCC78AQnsuIcoeRHmHYG9H7xvEuxO9WwMJ1QqEBn7wEeoF3+5DSKjmktB8NemC+t5D3cJ0
*/