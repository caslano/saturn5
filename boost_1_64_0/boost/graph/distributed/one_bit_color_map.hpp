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
dl13CGPGf816RcuV1fCXiqmKewLmPI73w+qwhhnb5RyYmthrYWpj6mDq6rjn+epP/Zox1HrI62Ma6LhoI4x3nHPXGYxzFv5omXHOZ763Qsc0jcwe01xhZPaYZoaR2WOaXY3MHr+sb2T2+GUVI7PHL8sYmT1+6bZlJi0/fGeFjF9+actM+k7aMrOOzju2zKT5VSOzxzQfsmUmzfcYmT2mucLI2oj9eZPe1mKnTAaNefLtETLm+Vkx+5Gfss5szLO0jpmqXPzlmXUyTJ0s8sVBcrM3J8976Bio7omua+LwjOs6EP3/aem4aMk6EOdiHYidUV75oygDeg7vcz8edeTE0euG5ZSsA/F7WQeCIPQ/aZtC2zNtOJjN8dPaLdTTYm4v7AVrwn6wPhwEW8DhcC28CN4OR8AnYCZ8A2bDt+BE+B6cBD+AU2Ak58qB0XA6TIS5sCycAcvDfFgZFsJqcCasCWfDOvAS2ABeBhvDy2ELeAVsB6+EneA8HXedD/vBq+BwuBCOhovgdPgHWACXwKU6DnsdXAbvhSvhw/A6+AS8Hr4F18L34Tr4MbwBfgZvhF/BDfAUvAiehukw2umb8x8LE2BZmAgrwyRYE5aFDWE52BUmw5GwApwFNxLP5XATnAvHwDVwLLwRbob3wi3wMbgNvgK3ww/gDvgJvAuegnfDaO79PbA8vA/Wg/fDZvCPsAfcA/vAh+Aw+ChcAB+Ht8In4Ga4F+6E++CD8Cn4EHwGHoL74TH4J/g2fA5+Cf8MLTd1IvTAF2EKPARrwJdhfXgEtoCvwE7wKOwOX4UD4etwODwGM+GbcDI8Di+Hb8OF8G9wJTwB18D34E3wfXg7/AA+DD+Ej8KP4AF4Eh6Gn8E34Vfwc/g1/AZ+A0/DUzDBw/cRrAxPw/Phd7AF/BG2gjyIzO0FsDd0wqEwAs6FLrgMxsI1MA5ugKXhZlgBltV97/bey551mC8xcbvPbN5v4HhXzd0lY12/t7GuknGuknGu/8dxrrTdJeNcJb+S37/YOw/4KKo0gM9syaYRkgVCiASRJkUUAwJ2AoSiNEmoiqGFXiJNVFRARPFQsaDYQRHBiugpKoqFU9SjiRQBAUUBFQQUPT1Pvf9+++2b3Uz2lDuvZ/g9/jPfK/PmzZs3k/2+973yrXwr38q3/6bN98+c/z94/ADjAOA3mP//rkunj8yl00fm0ukji6PTR+6e/69yM//fyFzz/5G55/8jc+b/63Gio983500SWfv8Lufn94k+R3L0fH+VpcTaFyBPRF62Xj2tkmV8YHfQT7NZhIqEawgzybf0NJkfyB0qGjQQWbLRq5eo/jySppMTp+tVVTJxrcPH7H0vx4miD2qpeqQZch+keOMn/HVJN0nnX0bKCco5SsJ6SdGRE2WtkrgGtJPHqkI4QbRArcV38RqJG4UEHSAhmzIy0f34iNsTlLURhEt+hT/k0G/pTcxv4SVy3NIcjzG+pbkejvV6NE8JAZn8Jt5cbRnapoQL3+/nb0flPGJ2f21pmzuOE4iOt36hpr/ErOdyxjeh4/P1GC2p/LbY1G3PoLqzcyV9hto3mPI0Hp2oxFcsbe9gdH7HHQ3FT4zSN9OfdZ58nsR19X/rifYDMGbiaM2/HjaQNEP9rrXtdP2lehLf3++yKVBdcVuJ71TalsH0pUKJ32vWH2wr7dFc+tK7pWwY+kjaXcStt37Jx4C5loHDJ4yPsmFIlTKu837hyVEZ3gS+DcnuRHKlXYZfAeOj/Vpp657ej+xGduT+tZT6tjY2FKdI+QP8Zc37f+q7UFwO/SxF5xNHzt3Hk4rl9kd2/zLXLguqPUQnKbut/2tPd7tMHb/aj3SQdB38P3vOs+M=
*/