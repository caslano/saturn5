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
BJyq63hOg8/Da+BKOAOugjPhO/A6uA7eAD+Es+HH8Bb4ObwVHoK3wx+h2B15GHNgOpwHq8C7YW14D6wP74PN4f3wTDgfdoQLYBf4ELwILoQD4CI4Fj4CJ8AlcAp8FE6Dj8MZ8Al4B3wKzoNPwydhL/gMLIIrYX+4Cg5QO6rfw7XwOfgevAjuh/3gQfgC/BaugBW99E2YBV+FNeFrMB++AXvAVfBi+CYcAd+Cs+Ef4SNwLXwcroPPwPVwOXwProYb4Ub4PtwKN8FdcDP8BG6Fh+AH8Hu4DdqMJx/CRLgDJutxBtwFM+HHsDb8BJ4EP4Xnwr2wrabrDFfDQvg27AP3w2HwM3gJ/ALeBQ/A++FBuAh+CR+Dh+Hr8AhcA7+Cm+DXcCc8CvfCb+Bn8C/wMPwZ/gwtm+tQPzWZ0AebQD88DSbA3jAJXgxTYAlMhTNhGrwbVoQPwnS4EP4p1N/hd3AFzEC+GgbhdlgZ7oZVYIL6rUmF2TAX1oAt4fHwfFgTDoQnwImwNrwC1oE3wbrwHlgPPgvrw7dgA7gtyq9NE+hRPzUNYHPYVI9bwRZwEvTBafBsOBeeA++GeXABbA2XwrbweZgPV8J28DV4KlwNc+E7sCNcB8+DO2EnuAd2hvtgF/glDPW/P6sfmwT1Y1MR9oJVYW9YE/aBDWBf2BheqOuV/uUJD7aEpKPzTiDMISwmvPrJL/sNWb2Tvyjh1k/K7Qv/n+0LZ5fbGJbbGP6X2hhG7AuPfvL/ZVv4z9X/jx7/W+j/s61U+d0vkY8SrxVeEKaoeNy4iF66Z5bLNgCZyzYAmcs2AJnbNkDlbt8AInf7BkAWaxugsgRdx69N9z7douUBXZdP5aaMxOi1BlWWLLLu+WGpI09x6+dFnmX0807abNXFY1mQ3z2q7ONUrqUYeXWVh7waFESdM0fleYWFtLIjr6HytvmFeW06cD6VH6/ygs4dO+djeBCdp2bsmoVGXkvzcL0F0ddVV9u8bX47k7aephVpVBknirxN907t8rt2iiqjfrRNgsoax/pvMPKT3XYUIj/FbXch8iZu+wqRn2rkseXnhsvpyi3pEt0HmopcrECMrKVZq9LJf3rsGpQm7Rnh+981WnamyNp179rZyX9WuK/1aH1efpvovnm26YNio2LKOEf7YZuO3YyslWO3YWR5ep+wfDFlto61kTHy82LXvzTy9QHp20WYxHQviOrHG1TerWunjm2i+ut7EXmP7t26FuSb/rdR5eH+LYYnVg2Nez8mjoexW+z93KTx9PWOZDP5Nsfm69C1oDCm3C2x8fmd8zrSBZ1nYmtsPK3plP2BxtH4Xbvn04E7FnZsk9fJxG8Lx6sFEbYx+W3OL4gqe7vG0/PDkVFl7ygdV5TXqVNU/IcxbWuym/idGp/fuxsJOhZqQnPuXZG6denQsTXReV2cuN2l4jrndTNxH2lc79OanF5UUNi9I70xcs6PzTkL83nE21L5mLbco/E9CvK5gZ0K8wqc+n4Sez1qVuXEfxqO17YoKAh1+ej4vRpf2L1HQSGn1q5o4vdpfEGPjoX5rYtOzW1Z1LVLJ+ea97vinXp/Viru9Fyn3M8j9c7rXtgxL3Sv8njAnfgvNL5LV25gYTi6ICr+gInXS5Puy7iq8Qdj+19ej8IORZ3ye+Z3ikrzpaahh3TtRdN17U2HKPUuOBR5Rjvl0S6O/LDIGSU6MH6IPBF52fZcncSeS/zhsBqdJVtHQiXCOYT7yGc9Ij818CVRNGhgjB+SscbHAsVouipGL1hFjk82NlK22kipPZemzzI69Sw5bhKl4+UDY6yzzlRNia9ubIXOkmOP8TnQhUq0z/hl/y0hXUATo0fgGlTWElI=
*/